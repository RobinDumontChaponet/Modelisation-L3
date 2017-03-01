#include <iostream>
#include <list>
#include <stack>
#include <limits.h>

#include <cctype>
#include <fstream>
#include <sstream>

#include <unordered_set>
#include <string>
#include <float.h>

#include <vector>
#include "Graphe.cpp"

#include "InfoArete.hpp"
#include "InfoSommet.hpp"

#include <time.h>

using namespace std;


// Nom du fichier à parser
string fileName = "data_VRPTW_100_10_5_9.gpr";










// Petit utilitaire pour le parsing
istream& skipspace(istream& in) {
	while (isspace(in.peek())) {
		int c(in.peek());
		in.ignore();
		if (c == '\n') {
			in.setstate(ios_base::failbit);
			break;
		}
	}
	return in;
}

// Petit utilitaire pour trouver un sommet par son nom
Sommet<InfoSommet> * chercheSommet (Graphe<InfoArete, InfoSommet> * g, string name) {
	Sommet<InfoSommet> *s = nullptr;

	const PElement<Sommet<InfoSommet>> * pTmp;
	for (pTmp = g->lSommets; pTmp != NULL; pTmp = pTmp->s)
		if (((pTmp->v)->v).nom == name)
			s = pTmp->v;

	return s;
}


int main() {
	// Calcul du temps d'execution
	clock_t start, end;
	start = clock();

	// Notre graphe
	Graphe<InfoArete, InfoSommet> g;
	string sourceName;
	string pitName;
	string graphName;

	// Le parsing
	unordered_set<string> instructions = {"sectionSommets", "sources", "puits", "sectionArcs", "sectionGraphes"};

	ifstream inFile(fileName);
	if (!inFile) {
		cerr << "File not found." << endl;
		return -1;
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

				//cout << state << endl;
				continue;
			}

			istringstream iss(line);

			for (string value; iss >> skipspace >> value; )
				values.push_back(value);

			// sommet ; bornes inferieur ; borne superieure de la fenêtre
			if (state == "sectionSommets")
				g.creeSommet(InfoSommet(
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
				Sommet<InfoSommet> *s = nullptr, *d = nullptr;

				s = chercheSommet(&g, values[1]);

				d = chercheSommet(&g, values[2]);

				g.creeArete(
					s,
					d,
					InfoArete(values[0],
					(values[3].length())?stod(values[3]):0,
					(values[4].length())?stod(values[4]):0
				));// ici on peut donc faire values[0] ; values[1] ; values[2] ; values[3] ; values[4]
			}

			// nom-graphe ; sommet-source ; sommet-puits
			if(state == "sectionGraphe")
				graphName = values[0];

			values.clear();
		}
	}
	inFile.close();

	cout << "--- Detail de l'execution -------------------"<< endl << endl;

	unsigned int k = 0;
	int n = g.nombreSommets();
	double *l = new double[n];
	PElement<Sommet<InfoSommet>> * M = NULL;
	PElement<Sommet<InfoSommet>> * Mp = NULL;

//	vector<Sommet<InfoSommet>> pj;
	Sommet<InfoSommet> pj[200];

	fill_n(l, n, DBL_MAX);
	l[0] = 0;

	M = new PElement<Sommet<InfoSommet>> (chercheSommet(&g, sourceName), M);

	if (g.successeurs(M->v)==NULL) {
		cout << "Il existe un circuit de valeur negative." << endl;

		return 0;
	}

	while (k <= n-1) {
		k++;
		Mp = NULL;

		cout << "Iteration " << k << " :" << endl;

		const PElement<Sommet<InfoSommet>> * mTmp ;
		for (mTmp = M; mTmp != NULL; mTmp = mTmp->s) {

			cout << "\tOn parcourt M, sommet : " << mTmp->v->v.nom << endl;

			const PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>* >> * sTmp;
			for (sTmp = g.successeurs(mTmp->v); sTmp != NULL; sTmp = sTmp->s) {
				pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>*> xj = *sTmp->v;

				cout << "\t\tOn parcourt le successeur : " << xj.first->v.nom << endl;

				double lSucc = l[xj.second->debut->clef] + xj.second->v.cout;

				cout << "\t\tLambda Parent = " << l[xj.second->debut->clef] << endl;
				cout << "\t\tLamba Parent + Poid de l'arete : " << lSucc << endl;

				if(l[xj.first->clef] > lSucc) {
					l[xj.first->clef] = lSucc;

					cout << "\t\tOn ajoute le successeur à la prochaine iteration." << endl;

					Mp = new PElement<Sommet<InfoSommet>> (xj.first, Mp);

					pj [xj.first->clef] = *xj.second->debut;
				}

				cout << endl;
			}

			cout << endl;
		}

		cout << endl;

		M = Mp;
	}

	cout << "--- Chemin -------------------------------"<< endl << endl;

	cout << pitName;
	Sommet<InfoSommet> *r = &pj[chercheSommet(&g, pitName)->clef];
	while(r->clef!=0) {
		cout << " < " << r->v.nom;
		r = &pj[r->clef];
	}
	cout << " < " << sourceName << endl << endl;

	cout << "--- Temps d'execution  -------------------"<< endl << endl;

	end = clock();
	cout << (double)(end-start)/CLOCKS_PER_SEC << " secondes." << endl << endl;

	system("pause");

	return 0;
}