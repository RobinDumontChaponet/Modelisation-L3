#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

template<typename S, typename T>
class dfs:
	public Algo<S,T>
{
private:
	int k;
	int l;
	

	void explore(Sommet<T>& i);
	
public:
	dfs(const Graphe<S,T>* g)
	:Algo<S,T>(g),k(1),l(0) {}
	~dfs() {}
	void evaluate();
};


template<typename S, typename T>
void dfs<S,T>::evaluate() {
	PElement< Sommet<T>> *li = Algo<S,T>::_graphe->lSommets;

	for (; li; li = li->s) {
		li->v->v.n = Algo<S,T>::_graphe->degrePlus(*li->v);
		li->v->v.num = 0;
		li->v->v.ncomp = 0;
	}

	for (li = Algo<S,T>::_graphe->lSommets; li; li = li->s)
		if (li->v->v.ncomp==0) {
			li->v->v.num = k;
			l++;
			li->v->v.ncomp = l;
			explore(*li->v);
		}
}


template<typename S, typename T>
void dfs<S,T>::explore(Sommet<T>& i) {
	while(i.v.n > 0) {
		Sommet<T>* j = Algo<S,T>::successeurI(Algo<S,T>::_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
		i.v.n--;
		if (j->v.num == 0) {
			k++;
			j->v.num = k;
			explore(*j);
		}
	}
}

