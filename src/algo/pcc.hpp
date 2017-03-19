#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

class PCC:
	public Algo
{
	void explore(Sommet<InfoSommet>& i);
public:
	PCC(const Graphe<InfoArete,InfoSommet>* graphe, const string& sourceName, const string& destName)
	:Algo(graphe) {}
	~PCC();
	Graphe<InfoArete,InfoSommet> evaluate();
	
};

Graphe<InfoArete, InfoSommet> PCC::evaluate() {
	return _res;
}