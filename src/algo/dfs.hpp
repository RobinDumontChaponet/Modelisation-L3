#pragma once
#include "../Graphe.hpp"

template<typename S, typename T>
class dfs
{
private:
	int k;
	int l;
	const Graphe<S,T>* _graphe;

	void explore(Sommet<T>& i);
	Sommet<T> successeurI(PElement<pair<Sommet<T> *, Arete<S,T>* >> * successeurs, const int i) const;

public:
	dfs(const Graphe<S,T>* g)
	:k(1),l(1),_graphe(g) {}
	~dfs() {}
	void evaluate();
};


template<typename S, typename T>
void dfs<S,T>::evaluate() {
	PElement< Sommet<T>> *li = _graphe->lSommets;

	for (; li; li = li->s) {
		li->v->v.n = _graphe->degrePlus(*li->v);
		li->v->v.num = 0;
		li->v->v.ncomp = 0;
	}

	for (li = _graphe->lSommets; li; li = li->s)
		if (li->v->v.ncomp) {
			li->v->v.num = k;
			l++;
			li->v->v.ncomp = l;
			explore(*li->v);
		}
}


template<typename S, typename T>
void dfs<S,T>::explore(Sommet<T>& i) {
	while(i.v.n > 0) {
		Sommet<T> j = successeurI(_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
		i.v.n--;
		if (j.v.num == 0) {
			k++;
			j.v.num = k;
			explore(j);
		}
	}
}


template<typename S, typename T>
Sommet<T> dfs<S,T>::successeurI(PElement<pair<Sommet<T> *, Arete<S,T>* >> * successeurs, const int i) const {
	int tmp = i;
	PElement<pair<Sommet<T> *, Arete<S,T>* >> * l = successeurs;
	for (;l;l=l->s) {
		if( tmp-- == 0)
			return *l->v->first;
	}
}
