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

#include "Parser.cpp"

#include "algo/dfs.hpp"
#include "algo/dfsNum.hpp"
#include "algo/pcc.hpp"

#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
	string fileName;

	if (argc < 3) {
		cerr << "Format: prog <option> <file> avec option: " << endl;
		cerr << "\t-dfs : pour réaliser un DFS" << endl;
		cerr << "\t-num : pour numéroter les sommets" << endl;
		cerr << "\t-circle : detection de circuit" << endl;
		cerr << "\t-topo : tri topologique" << endl;
		cerr << "\t-connex : " << endl;
		cerr << "\t..." << endl;
		exit(1);
	} 

	fileName = argv[argc-1];

	Parser<InfoArete, InfoSommet> parser;

	if(!parser.parse(fileName)) {
		cerr << "La lecture du fichier à échoué." << endl;
		exit(1);
	}	

	const Graphe<InfoArete, InfoSommet> & graph = parser.getGraph();
	string sourceName = parser.getSourceName();
	string pitName = parser.getPitName();
	string graphName = parser.getGraphName();
	Algo<InfoArete, InfoSommet>* algo;

	if (string(argv[1]).compare("-dfs") == 0) {
		cout << "Execution de l'algorithme de recherche en profondeur d'abord (DFS)" << endl;
		algo = new dfs<InfoArete, InfoSommet>(&graph);
	}else if (string(argv[1]).compare("-num") == 0 ) {
		cout << "Execution de l'algorithme de numérotation du graphe" << endl;
		algo = new dfsNum<InfoArete, InfoSommet>(&graph);
	}else if(string(argv[1]).compare("-pcc") == 0) {
		if (argc != 5) {
			cerr << "Format: prog -pcc <source> <destination> <file>" << endl;
		}else
		cout << "Execution de l'algorithme de recherche du plus court chemin" << endl;
		string sourceName(argv[2]);
		string destName(argv[3]);
		algo = new PCC<InfoArete, InfoSommet>(&graph, sourceName, destName);
	}else {
		cerr << "algo " << argv[1] << " n'existe pas " << endl;
		exit(1);
	}

	algo->evaluate();
	//TODO afficher


	// SI on choisit d'enregistrer
	parser.save("../../../../../graphes/saved.gpr");

	// Ici on a l'ancienne recherche du plus court chemin. Ça peut servir.r

//	// Calcul du temps d'execution
//	clock_t start, end;
//	start = clock();
//
//	const Graphe<InfoArete, InfoSommet> & graph = parser.getGraph();
//	string sourceName = parser.getSourceName();
//	string pitName = parser.getPitName();
//	string graphName = parser.getGraphName();
//
//	cout << "--- Detail de l'execution -------------------"<< endl << endl;
//
//	unsigned int k = 0;
//	int n = graph.nombreSommets();
//	double *l = new double[n];
//	PElement<Sommet<InfoSommet>> * M = NULL;
//	PElement<Sommet<InfoSommet>> * Mp = NULL;
//
////	vector<Sommet<InfoSommet>> pj;
//	Sommet<InfoSommet> pj[200];
//
//	fill_n(l, n, DBL_MAX);
//	l[0] = 0;
//
//	M = new PElement<Sommet<InfoSommet>> (chercheSommet<InfoArete, InfoSommet>(&graph, sourceName), M);
//
//	if (graph.successeurs(M->v)==NULL) {
//		cout << "Il existe un circuit de valeur negative." << endl;
//
//		return 0;
//	}
//
//	while (k <= n-1) {
//		k++;
//		Mp = NULL;
//
//		cout << "Iteration " << k << " :" << endl;
//
//		const PElement<Sommet<InfoSommet>> * mTmp ;
//		for (mTmp = M; mTmp != NULL; mTmp = mTmp->s) {
//
//			cout << "\tOn parcourt M, sommet : " << mTmp->v->v.nom << endl;
//
//			const PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>* >> * sTmp;
//			for (sTmp = graph.successeurs(mTmp->v); sTmp != NULL; sTmp = sTmp->s) {
//				pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>*> xj = *sTmp->v;
//
//				cout << "\t\tOn parcourt le successeur : " << xj.first->v.nom << endl;
//
//				double lSucc = l[xj.second->debut->clef] + xj.second->v.cout;
//
//				cout << "\t\tLambda Parent = " << l[xj.second->debut->clef] << endl;
//				cout << "\t\tLamba Parent + Poid de l'arete : " << lSucc << endl;
//
//				if(l[xj.first->clef] > lSucc) {
//					l[xj.first->clef] = lSucc;
//
//					cout << "\t\tOn ajoute le successeur à la prochaine iteration." << endl;
//
//					Mp = new PElement<Sommet<InfoSommet>> (xj.first, Mp);
//
//					pj [xj.first->clef] = *xj.second->debut;
//				}
//
//				cout << endl;
//			}
//
//			cout << endl;
//		}
//
//		cout << endl;
//
//		M = Mp;
//	}
//
//	cout << "--- Chemin -------------------------------"<< endl << endl;
//
//	cout << pitName;
//	Sommet<InfoSommet> *r = &pj[chercheSommet<InfoArete, InfoSommet>(&graph, pitName)->clef];
//	while(r->clef!=0) {
//		cout << " < " << r->v.nom;
//		r = &pj[r->clef];
//	}
//	cout << " < " << sourceName << endl << endl;
//
//	cout << "--- Temps d'execution  -------------------"<< endl << endl;
//
//	end = clock();
//	cout << (double)(end-start)/CLOCKS_PER_SEC << " secondes." << endl << endl;

	system("pause"); // cin.ignore().get();

	return 0;
}
