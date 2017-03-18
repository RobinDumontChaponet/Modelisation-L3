#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

template<typename S, typename T>
class dfsNum:
	public Algo<S,T>
{
private:
	int k;
	int l;
	int f;

	void explore(Sommet<T>& i);

public:
	dfsNum(const Graphe<S,T>* g)
	:Algo<S,T>(g),k(1),l(0),f(1) {}
	~dfsNum() {}
	void evaluate();
};


template<typename S, typename T>
void dfsNum<S,T>::evaluate() {
	PElement< Sommet<T>> *li = Algo<S,T>::_graphe->lSommets;

	for (; li; li = li->s) {
		li->v->v.n = Algo<S,T>::_graphe->degrePlus(*li->v);
		li->v->v.num = 0;
		li->v->v.ncomp = 0;
	}

	for (li = Algo<S,T>::_graphe->lSommets; li; li = li->s)
		if (li->v->v.ncomp==0) {
			li->v->v.num = k;
			li->v->v.prefix = k;
			l++;
			li->v->v.ncomp = l;
			explore(*li->v);
		}
}


template<typename S, typename T>
void dfsNum<S,T>::explore(Sommet<T>& i) {
	while(i.v.n > 0) {
		Sommet<T>* j = Algo<S,T>::successeurI(Algo<S,T>::_graphe->successeurs(&i),i.v.n);//  _n[i] successeur de i
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