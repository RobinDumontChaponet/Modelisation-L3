#pragma once

#include <stdio.h>
#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Graphe.hpp"

using namespace std;


// Petit utilitaire pour trouver un sommet par son nom
template <class A, class S>
Sommet<S> * chercheSommet (const Graphe<A, S> * g, string name) {
	Sommet<S> *s = NULL;

	const PElement<Sommet<S>> * pTmp;
	for (pTmp = g->lSommets; pTmp != NULL; pTmp = pTmp->s)
		if (((pTmp->v)->v).nom == name)
			s = pTmp->v;

	return s;
}

template <class S>
string printSommetReverse(PElement<Sommet<S> > *element) {
	if(element == NULL) return "";

	ostringstream oss;

	oss << printSommetReverse<S>(element->s);
	oss << element->v->v.nom << "  " << element->v->v.borneInf << "  " << element->v->v.borneSup << endl;

	return oss.str();
}

template <class S, class T>
string printAreteReverse(PElement<Arete<S, T> > *element) {
	if(element == NULL) return "";

	ostringstream oss;

	oss << printAreteReverse<S, T>(element->s);
	oss << element->v->v.nom << "  " << element->v->debut->v.nom << "  " << element->v->fin->v.nom << "  " << element->v->v.cout << "  " << element->v->v.temps << endl;

	return oss.str();
}


template <class A, class S>
class Parser {
private:
	Graphe<A, S> graph;
	string sourceName;
	string pitName;
	string graphName;

	unordered_set<string> sections = {"sectionSommets", "sources", "puits", "sectionArcs", "sectionGraphes"};

	// Petit utilitaire pour le parsing
	static istream& skipSpace(istream& in) {
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

public:
	Parser();

	bool parse(string fileName);

	bool save(string fileName);

	operator string () const;

	const Graphe<A, S> & getGraph() {
		return graph;
	}

	string getSourceName() const {
		return sourceName;
	}

	string getPitName() const {
		return pitName;
	}

	string getGraphName() const {
		return graphName;
	}
};

template <class A, class S>
Parser<A, S>::operator string () const {
	ostringstream oss;

//	oss << "File("<< endl;
//	oss << fileName << endl;
//	oss << ")";
	return oss.str();
}

template <class A, class S>
ostream & operator << (ostream & os, const Parser<A, S> & parser) {
	return os << (string) parser;
}
