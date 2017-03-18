#pragma once

template<typename S, typename T>
class Algo
{
public:
	const Graphe<S,T>* _graphe;

	Sommet<T>* successeurI(PElement<pair<Sommet<T> *, Arete<S,T>* >> * successeurs, const int i) const;

	Algo(const Graphe<S,T>* g):
	_graphe(g) {}
	~Algo();
	virtual void evaluate() = 0;
};



template<typename S, typename T>
Sommet<T>* Algo<S,T>::successeurI(PElement<pair<Sommet<T> *, Arete<S,T>* >> * successeurs, const int i) const {
	int tmp = i;
	PElement<pair<Sommet<T> *, Arete<S,T>* >> * l = successeurs;
	for (;l;l=l->s) {
		if(--tmp == 0)
			return l->v->first;
	}
	cerr << "i > nombre de successeurs" << endl;
	exit(1);
}