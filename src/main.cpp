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

#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
	string fileName;

	if (argc < 3) {
		cerr << "Format: prog <option> <file> avec option: " << endl;
			cerr << "\t-dfs : pour réaliser un DFS" << endl;
			cerr << "\t-num : pour numéroter les sommets" << endl;
			cerr << "\t-circle : detection de circuit" << endl;
			cerr << "\t-topo : trie topologique" << endl;
			cerr << "\t-connex : " << endl;
			cerr << "\t..." << endl;
			exit(1);
	} 
	
	fileName = argv[2];

	Parser<InfoArete, InfoSommet> parser(fileName);

	if(!parser.parse()) {
		cerr << "La lecture du fichier à échoué." << endl;
		exit(1);
	}	

	const Graphe<InfoArete, InfoSommet> & graph = parser.getGraph();
	string sourceName = parser.getSourceName();
	string pitName = parser.getPitName();
	string graphName = parser.getGraphName();
	
	Algo<InfoArete, InfoSommet>* algo;
	algo = new dfs<InfoArete, InfoSommet>(&graph);
	/*if(argc == 3) {
		if (str1.compare(argv[1])==0)
		else if(str2.compare(argv[1]) == 0) 
			algo = new dfsNum<InfoArete, InfoSommet>(&graph);
		else {
			cerr << "Algorithme non trouvé " << endl << endl;
			exit(1); 
		}
	}*/

	algo->evaluate();
	//TODO afficher

	system("pause");

	return 0;
}
