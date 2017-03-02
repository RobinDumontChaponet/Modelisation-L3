#include "Parser.hpp"

template <class A, class S>
Parser<A, S>::Parser(string fileName):fileName(fileName){}

template <class A, class S>
bool Parser<A, S>::parse() { // Parse .gpr
	cout << fileName << endl;

	unordered_set<string> instructions = {"sectionSommets", "sources", "puits", "sectionArcs", "sectionGraphes"};

	ifstream inFile(fileName);
	if (!inFile) {
		cerr << "File \"" << fileName << "\" not found." << endl;
		return false;
	}

	string state("");
	string line;
	vector<string> values;
	while (getline(inFile, line)) {
		if (line.empty()) continue;

		if(!line.compare(0, 1, "#"))
			cout << line << endl << endl;
		else {
			if(instructions.find(line) != instructions.end()) {
				state = line;

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
			if(state == "sources")
				sourceName = values[0];

			// nom-sommet-puit
			if(state == "puits")
				pitName = values[0];

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

			// nom-graphe ; sommet-source ; sommet-puits
			if(state == "sectionGraphe")
				graphName = values[0];
			
			values.clear();
		}
	}
	inFile.close();

	return true;
}
