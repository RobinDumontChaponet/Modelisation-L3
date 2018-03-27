#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

class dfs: public Algo
{
// comme la liste des sommets est à l'envers, le dfs s'effectue du puit vers la source.
// l'ordre préffixe et suffixe est implanté mais pas affiché

private:
	int k;
	int l;
	int s;

	void explore(Sommet<InfoSommet>& i);

public:
	dfs(const Graphe<InfoArete,InfoSommet>* g) :Algo(g),k(1),l(0),s(0) {}

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


	for (li = Algo::_graphe->lSommets; li; li = li->s) //s = sommet suivant
		if (li->v->v.ncomp==0) { // v = le sommet ->v = info du sommet
			li->v->v.num = k; // k corespond a l'ordre d'ouverture des sommmets, 0 coresspond a non exploré
			li->v->v.prefix = k; //numerotation ordre prefixe
			l++;
			li->v->v.ncomp = l; // identifiant sous grafe dfs
			// On ajoute le sommet source du graphe au resultat
			_res.creeSommet(li->v->v);

			explore(*li->v);
			li->v->v.suffixe = s; //numerotation ordre sufixe
		}
	return _res;
}


void dfs::explore(Sommet<InfoSommet>& i) {
	while(i.v.n > 0) {
		Sommet<InfoSommet>* j = Algo::successeurI(Algo::_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
		i.v.n--; //quand n = 0 cela veux dire que le sommet est fermé

		if (j->v.ncomp == 0) j->v.ncomp = l; //identifiant sous grafe dfs

		if (j->v.num == 0) {
			_res.creeSommet(j->v);
			Arete<InfoArete, InfoSommet>* a =_graphe->getAreteParSommets(&i, j);
			a->v.nom = "arcArb " + a->v.nom;
			_res.creeArete(&i, j, a->v);

			k++;
			j->v.num = k;
			j->v.prefix = k; //numerotation ordre prefixe
			explore(*j);
		}
		else if(j->v.ncomp != i.v.ncomp )
		{
			Arete<InfoArete, InfoSommet>* a = _graphe->getAreteParSommets(&i, j);
			a->v.nom = "arcCroi " + a->v.nom;
			_res.creeArete(&i, j, a->v);
		}
		else if(j->v.num < i.v.num)
		{
			Arete<InfoArete, InfoSommet>* a = _graphe->getAreteParSommets(&i, j);
			a->v.nom = "arcArr " + a->v.nom;
			_res.creeArete(&i, j, a->v);
		}
		else
		{
			Arete<InfoArete, InfoSommet>* a = _graphe->getAreteParSommets(&i, j);
			a->v.nom = "arcAv " + a->v.nom;
			_res.creeArete(&i, j, a->v);
		}
	}
	i.v.suffixe = s; //numerotation ordre sufixe
	s++;
}

