#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"
#include "../Error.hpp"
#include "../PElement.hpp"
#include <limits>

class PCC:
	public Algo
{
	unsigned int k;
	unsigned int n;
	bool fin;
	void explore(Sommet<InfoSommet>& i);
	Sommet<InfoSommet> dep;
	Sommet<InfoSommet> arriv;

	PElement<Sommet<InfoSommet>>* S;
	PElement<Sommet<InfoSommet>>* Mp;
public:
	PCC(const Graphe<InfoArete,InfoSommet>* graphe, const string& sourceName, const string& destName)
	:Algo(graphe),k(0),n(_graphe->nombreSommets()),fin(false),S(NULL){
		bool tmp1 = false, tmp2 = false;
		PElement< Sommet<InfoSommet>>* l;
		for(l=Algo::_graphe->lSommets; l; l=l->s)
			if (l->v->v.nom.compare(sourceName) == 0) {
				dep = *l->v;
				tmp1 = true;
			}
			else if(l->v->v.nom.compare(destName) == 0) {
				arriv = *l->v;
				tmp2 = true;
			}
		if (!tmp1 || !tmp2) throw Error("PCC: sommet source ou sommet destination non trouvés");
	}
	~PCC();
	Graphe<InfoArete,InfoSommet> evaluate();
	
};

Graphe<InfoArete, InfoSommet> PCC::evaluate() {
	S = new PElement(dep, S);
	PElement<Sommet<InfoSommet>>* l;
	
	//Met tout les sommets à +infiny
	for (l=Algo::_graphe->lSommets; l; l=l->s)
		l->v->v.lambda = std::numeric_limits<int>::max();
	dep.v.lambda = 0;

	while (k<=n-1 && !fin) {
		k++;
		Mp = NULL;
		PElement<Sommet<InfoSommet>> * mTmp ;
		for (mTmp = S; mTmp; mTmp = mTmp->s) {
			PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>* >> * sTmp;
			for (sTmp = Algo::_graphe->successeurs(mTmp->v); sTmp; sTmp = sTmp->s) {
				pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>*> xj = *sTmp->v;

				double lSucc = xj.second->debut->v.lambda + xj.second->v.cout;
				if(xj.first->v.lambda > lSucc) {
					xj.first->v.lambda = lSucc;

					Mp = new PElement<Sommet<InfoSommet>> (xj.first, Mp);
				}
			}
		}
		S = Mp;
	}

	//Il faut retourner autre chose car la solution est dans M et on doit retourner un graphe
	return _res;
}