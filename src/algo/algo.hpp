#pragma once

#include "../InfoArete.hpp"
#include "../InfoSommet.hpp"

class Algo
{
public:
	const Graphe<InfoArete,InfoSommet>* _graphe;
	Graphe<InfoArete,InfoSommet> _res;
	Sommet<InfoSommet>* successeurI(PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet>* >> * successeurs, const int i) const;

	Algo(const Graphe<InfoArete,InfoSommet>* g):
	_graphe(g) {}
	~Algo();
	virtual Graphe<InfoArete,InfoSommet> evaluate() = 0;
};



Sommet<InfoSommet>* Algo::successeurI(PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet>* >> * successeurs, const int i) const {
	int tmp = i;
	PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet>* >> *  l = successeurs;
	for (;l;l=l->s) {
		if(--tmp == 0)
			return l->v->first;
	}
	cerr << "i > nombre de successeurs" << endl;
	exit(1);
}