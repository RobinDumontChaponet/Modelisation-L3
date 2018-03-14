#include "Parser.hpp"

template <class A, class S>
Parser<A, S>::Parser(bool verbose):_verbose(verbose) {};
template <class A, class S>
bool Parser<A, S>::parse(string fileName) { // Parse fileName.gpr
	ifstream file(fileName);
	if (!file) {
		cerr << "File \"" << fileName << "\" not found." << endl;
		return false;
	}

	string state("");
	string line;
	vector<string> values;
	while (getline(file, line)) {
		if (line.empty()) continue;

		if(!line.compare(0, 1, "#") && _verbose)
			cout << line << endl << endl;
		else {
			if(sections.find(line) != sections.end()) {
				state = line;

				if(_verbose)
					cout << "Lecture de la section \"" << state << '"' << endl;
				continue;
			}

			istringstream iss(line);

			for (string value; iss >> skipSpace >> value; )
				values.push_back(value);

			// sommet ; bornes inferieur ; borne superieure de la fenêtre
			if (state == "sectionSommets")
				graph.creeSommet(
					S(
						values[0],
						(values[1].length())?stod(values[1]):0,
						(values[2].length())?stod(values[2]):0)
					); // ici on peut donc faire values[0] ; values[1] ; values[2]

			// nom-sommet-source
			if(state == "sources") {
				sourceName = values[0];
			}

			// nom-sommet-puit
			if(state == "puits") {
				pitName = values[0];
			}


			// nom-arc ; sommet-initial ; sommet-terminal ; coût ; temps
			if(state == "sectionArcs") {
				Sommet<S> *s = nullptr, *d = nullptr;

				s = chercheSommet<A, S>(&graph, values[1]);

				d = chercheSommet<A, S>(&graph, values[2]);

				graph.creeArete(
					s,
					d,
					A(
						values[0],
						(values[3].length())?stod(values[3]):0,
						(values[4].length())?stod(values[4]):0
					)
				);// ici on peut donc faire values[0] ; values[1] ; values[2] ; values[3] ; values[4]
			}

			// ici on ne respecte pas tout à fait le "format-gpr.pdf" mais on respecte les fichier .gpr fournies…
			// nom-graphe; i ; sommet-source ; sommet-puits
//			if(state == "sectionGraphes") {
//				graphName = values[0];
//				sourceName = values[2];
//				pitName = values[3];
//			}

			values.clear();
		}
	}
	file.close();

	return true;
}

template <class A, class S>
bool Parser<A, S>::save(string fileName) { // Parse fileName.gpr
	ofstream file(fileName);
	if (!file) {
		cerr << "Cannot write file \"" << fileName << "\"." << endl;
		return false;
	}

	string state("");
	string line;
	vector<string> values;

	time_t * rawtime = new time_t;
	struct tm * timeinfo;
	time(rawtime);
	timeinfo = localtime(rawtime);

	file << "# saved on " << asctime(timeinfo) << endl;

	file << "ressources 1" << endl;
	file << endl;

	file << "sectionSommets" << endl;
	// sommet ; bornes inferieur ; borne superieure de la fenêtre
	file << printSommetReverse<S>(graph.lSommets);
	file << endl;

	file << "sources" << endl;
	file << sourceName << endl;
	file << endl;

	file << "puits" << endl;
	file << pitName << endl;
	file << endl;

	file << "sectionArcs" << endl;
	// nom-arc ; sommet-initial ; sommet-terminal ; coût ; temps
	file << printAreteReverse<A, S>(graph.lAretes);
	file << endl;

	// ici on ne respecte pas tout à fait le "format-gpr.pdf" mais on respecte les fichier .gpr fournies…
	file << "sectionGraphe" << endl << endl;
	file << graphName << " i  " << sourceName << "  " << pitName << "  " << endl;

	file.close();
	
	return true;
}
