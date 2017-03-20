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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iomanip>

using namespace std;

template<typename T> void printLeft(T t) {
	cout << left << setw(22) << setfill(' ') << t;
}

/* Flag set by ‘--verbose’. */
static int verbose_flag = 1;

int main(int argc, char *argv[]) {
	string inputFileName, outputFileName;

	static int query;

//	bool dFlag, nFlag, cFlag, tFlag, xFlag = false;

	/* use gnu getOpt for CLI arguments */
	int c;

	while (1) {
		static struct option long_options[] = {
			/* These options set a flag. */
			{"verbose", no_argument,       &verbose_flag, 1},
			{"brief",   no_argument,       &verbose_flag, 0},

			{"help",    no_argument,       0, 'h'},

			{"dfs",   no_argument,       &query, 'd'},
			{"num",     no_argument,       &query, 'n'},
			{"pcc",     no_argument,       &query, 'p'},
			{"circuit",  no_argument,       &query, 'c'},
			{"topo",    no_argument,       &query, 't'},
			{"connex",  no_argument,       &query, 'x'},

			{"input",   required_argument, 0, 'i'},
			{"output",  required_argument, 0, 'o'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "hdnpctxi:o:", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'i':
				inputFileName = optarg;
				break;

			case 'o':
				outputFileName = optarg;
				break;

			case '?': case 'h':
				cout << endl << "Usage: program [OPTIONS]…" << endl << endl;
				printLeft("Option");
				printLeft("GNU long option");
				printLeft("Meaning");
				cout << endl;

				printLeft(" -h, -?");
				printLeft("--help");
				printLeft("Show this message");
				cout << endl;

				printLeft(" -d");
				printLeft("--dfs");
				printLeft("réalise un DFS");
				cout << endl;

				printLeft(" -p");
				printLeft("--pcc");
				printLeft("réalise une recherche du plus court chemin");
				cout << endl;

				printLeft(" -n");
				printLeft("--num");
				printLeft("numérote les sommets");
				cout << endl;

				printLeft(" -c");
				printLeft("--circuit");
				printLeft("réalise une detection de circuit");
				cout << endl;

				printLeft(" -t");
				printLeft("--topo");
				printLeft("réalise un tri topologique");
				cout << endl;

				printLeft(" -x");
				printLeft("--connex");
				printLeft("réalise une detection de connexité");
				cout << endl;

				printLeft(" -i <fileName>");
				printLeft("--input=<fileName>");
				printLeft("charge le fichier .gpr");
				cout << endl;

				printLeft(" -o <fileName>");
				printLeft("--output=<fileName>");
				printLeft("sauvegarde dans le fichier .gpr");
				cout << endl;

				exit( EXIT_FAILURE );

				break;

			default:
				abort ();
		}
	}

	// Calcul du temps d'execution
	clock_t start, end;
	start = clock();

	if(inputFileName.empty()) {
		cerr << "Aucun fichier fourni." << endl;
		cerr << "See -h or --help for information" << endl;

		exit(EXIT_FAILURE);
	}

	Parser<InfoArete, InfoSommet> parser(verbose_flag);

	if(verbose_flag)
		cout << endl << endl << "--- Lecture du fichier.  -------------------" << endl;

	if(!parser.parse(inputFileName)) {
		cerr << "--- La lecture du fichier à échoué." << endl;
		exit(EXIT_FAILURE);
	}
	
	const Graphe<InfoArete, InfoSommet> & graph = parser.getGraph();
	string sourceName = parser.getSourceName();
	string pitName = parser.getPitName();
	string graphName = parser.getGraphName();

	Graphe<InfoArete, InfoSommet> * result = nullptr;

	if(query) {
		Algo* algo;

		switch (query) {
			case 'd':
				cout << "Execution de l'algorithme de recherche en profondeur d'abord (DFS)" << endl;
				algo = new dfs(&graph);
			break;

			case 'n':
				cout << "Execution de l'algorithme de numérotation du graphe" << endl;
				algo = new dfsNum(&graph);
			break;

			case 'p':
				cout << "Execution de l'algorithme de recherche du plus court chemin" << endl;
//				algo = new PCC(&graph, sourceName, pitName);

				//	cout << "--- Chemin -------------------------------"<< endl << endl;
				//
				//	cout << pitName;
				//	Sommet<InfoSommet> *r = &pj[chercheSommet<InfoArete, InfoSommet>(&graph, pitName)->clef];
				//	while(r->clef!=0) {
				//		cout << " < " << r->v.nom;
				//		r = &pj[r->clef];
				//	}
				//	cout << " < " << sourceName << endl << endl;
			break;

			default:
				break;
		}

		result = new Graphe<InfoArete, InfoSommet>(algo->evaluate());

		if(verbose_flag) {
			cout << endl << endl << "--- graphe résultant  -------------------" << endl;
			cout << *result << endl;
		}
	}

	if(!outputFileName.empty()) { // SI on choisit d'enregistrer
		if(result!=NULL)
			parser.setGraph(*result);

		if(verbose_flag)
			cout << "--- Sauvegarde dans le fichier " << '"' << outputFileName << '"' << endl;

		if(!parser.save(outputFileName))
			cout << "Sauvegarde échouée." << endl;
	}


	// Calcul du temps d'execution
	if(verbose_flag) {
		cout << "--- Temps d'execution  -------------------"<< endl;

		end = clock();
		cout << (double)(end-start)/CLOCKS_PER_SEC << " secondes." << endl << endl;
	}

//	system("pause"); // cin.ignore().get();

	return 0;
}
