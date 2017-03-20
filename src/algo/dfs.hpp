#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

class dfs:
	public Algo
{
private:
	int k;
	int l;
	

	void explore(Sommet<InfoSommet>& i);
	
public:
	dfs(const Graphe<InfoArete,InfoSommet>* g) :Algo(g),k(1),l(0) {}

	~dfs() {}

	Graphe<InfoArete,InfoSommet> evaluate();
};


Graphe<InfoArete,InfoSommet> dfs::evaluate() {
	PElement< Sommet<InfoSommet>> *li = Algo::_graphe->lSommets;
	// Pour chaque sommet
	for (; li; li = li->s) {
		li->v->v.n = Algo::_graphe->degrePlus(*li->v);
		li->v->v.num = 0;
		li->v->v.ncomp = 0;
	}


	for (li = Algo::_graphe->lSommets; li; li = li->s)
		if (li->v->v.ncomp==0) {
			li->v->v.num = k;
			l++;
			li->v->v.ncomp = l;
			// On ajoute le sommet source du graphe au resultat
			_res.creeSommet(li->v->v);
			explore(*li->v);
		}
	return _res;
}


void dfs::explore(Sommet<InfoSommet>& i) {
	while(i.v.n > 0) {
		Sommet<InfoSommet>* j = Algo::successeurI(Algo::_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
		i.v.n--;
		if (j->v.num == 0) {
			_res.creeSommet(j->v);
			_res.creeArete(&i, j, InfoArete("",0,0));
			k++;
			j->v.num = k;
			explore(*j);
		}
	}
}

