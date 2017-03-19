#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

template<typename S, typename T>
class PCC:
	public Algo<S,T>
{
	void explore(Sommet<T>& i);
public:
	PCC(const Graphe<S,T>* graphe, const string& sourceName, const string& destName)
	:Algo<S,T>(graphe) {}
	~PCC();
	void evaluate();
	
};

template<typename S, typename T>
void PCC<S,T>::evaluate() {

}