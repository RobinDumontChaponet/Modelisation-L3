#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

class dfsNum:
	public Algo
{
private:
	int k;
	int l;
	int f;

	void explore(Sommet<InfoSommet>& i);

public:
	dfsNum(const Graphe<InfoArete,InfoSommet>* g)
	:Algo(g),k(1),l(0),f(1) {}
	~dfsNum() {}
	Graphe<InfoArete,InfoSommet> evaluate();
};


Graphe<InfoArete,InfoSommet> dfsNum::evaluate() {
	PElement< Sommet<InfoSommet>> *li = Algo::_graphe->lSommets;

	for (; li; li = li->s) {
		li->v->v.n = Algo::_graphe->degrePlus(*li->v);
		li->v->v.num = 0;
		li->v->v.ncomp = 0;
	}

	for (li = Algo::_graphe->lSommets; li; li = li->s)
		if (li->v->v.ncomp==0) {
			li->v->v.num = k;
			li->v->v.prefix = k;
			l++;
			li->v->v.ncomp = l;
			explore(*li->v);
		}
}


void dfsNum::explore(Sommet<InfoSommet>& i) {
	while(i.v.n > 0) {
		Sommet<InfoSommet>* j = Algo::successeurI(Algo::_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
		i.v.n--;
		if (j->v.num == 0) {
			k++;
			j->v.num = k;
			j->v.prefix = k;
			j->v.ncomp = l;
			explore(*j);
		}
	}
	i.v.suffixe = f;
	f++;
}