#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"
#include "../Error.hpp"
#include <limits>

#include "../Sommet.hpp"
#include "../InfoSommet.hpp"

#include "../Parser.hpp"

class PCC:
	public Algo
{
	unsigned int k;
	unsigned int n;
	double *l;
	bool fin;
	void explore(Sommet<InfoSommet>& i);
	Sommet<InfoSommet> source;
	Sommet<InfoSommet> pit;

	PElement<Sommet<InfoSommet>>* M;
	PElement<Sommet<InfoSommet>>* Mp;
public:
	PCC(const Graphe<InfoArete,InfoSommet>* graphe, const string& sourceName, const string& destName) :Algo(graphe),k(0),n(_graphe->nombreSommets()),fin(false) {
		l = new double[n];
		M = NULL;
		Mp = NULL;

		//	vector<Sommet<InfoSommet>> pj;

		M = new PElement<Sommet<InfoSommet>> (chercheSommet<InfoArete, InfoSommet>(_graphe, sourceName), M);
	}

	~PCC();
	Graphe<InfoArete,InfoSommet> evaluate();
	
};

Graphe<InfoArete, InfoSommet> PCC::evaluate() {
	Sommet<InfoSommet> pj[200];

	fill_n(l, n, DBL_MAX);
	l[0] = 0;

//	M = new PElement<Sommet<InfoSommet>> (chercheSommet<InfoArete, InfoSommet>(&_graphe, sourceName), M);

	if (_graphe->successeurs(M->v)==NULL) {
		cout << "Il existe un circuit de valeur negative." << endl;
	} else {

	while (k <= n-1) {
		k++;
		Mp = NULL;

		cout << "Iteration " << k << " :" << endl;

		const PElement<Sommet<InfoSommet>> * mTmp ;
		for (mTmp = M; mTmp != NULL; mTmp = mTmp->s) {

			cout << "\tOn parcourt M, sommet : " << mTmp->v->v.nom << endl;

			const PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>* >> * sTmp;
			for (sTmp = _graphe->successeurs(mTmp->v); sTmp != NULL; sTmp = sTmp->s) {
				pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>*> xj = *sTmp->v;

				cout << "\t\tOn parcourt le successeur : " << xj.first->v.nom << endl;

				double lSucc = l[xj.second->debut->clef] + xj.second->v.cout;

				cout << "\t\tLambda Parent = " << l[xj.second->debut->clef] << endl;
				cout << "\t\tLamba Parent + Poid de l'arete : " << lSucc << endl;

				if(l[xj.first->clef] > lSucc) {
					l[xj.first->clef] = lSucc;

					cout << "\t\tOn ajoute le successeur à la prochaine iteration." << endl;

					Mp = new PElement<Sommet<InfoSommet>> (xj.first, Mp);

					pj [xj.first->clef] = *xj.second->debut;
				}

				cout << endl;
			}

			cout << endl;
		}

		cout << endl;

		M = Mp;
	}
	}

	//Il faut retourner autre chose car la solution est dans M et on doit retourner un graphe
	return _res;
}
