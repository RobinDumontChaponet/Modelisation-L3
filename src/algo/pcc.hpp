#pragma once
#include "algo.hpp"
#include "../Graphe.hpp"

class pcc: public Algo
{
private:
	unsigned int k;
	unsigned int n;
	double *l;
	bool fin;
	void explore(Sommet<InfoSommet>& i);
	Sommet<InfoSommet>* source;
	Sommet<InfoSommet>* pit;

	PElement<Sommet<InfoSommet>>* M;
	PElement<Sommet<InfoSommet>>* Mp;

	const unsigned int type;

	string printSommet(PElement<Sommet<InfoSommet>> *element) {
		if(element == NULL) return "";

		ostringstream oss;

		oss << " > " << element->v->v.nom;
		oss << printSommet(element->s);

		return oss.str();
	}
	
public:
	static const unsigned int typeCout = 0;
	static const unsigned int typeTemps = 1;

	pcc(const Graphe<InfoArete,InfoSommet>* graphe, Sommet<InfoSommet>* s, Sommet<InfoSommet>* d, const unsigned int type = pcc::typeCout) :Algo(graphe),k(0),n(_graphe->nombreSommets()),fin(false), type(type) {
		l = new double[n];
		M = NULL;
		Mp = NULL;

		source = s;
		pit = d;

		//	vector<Sommet<InfoSommet>> pj;
		//	M = new PElement<Sommet<InfoSommet>> (chercheSommet<InfoArete, InfoSommet>(_graphe, sourceName), M);
	};

	~pcc() {};

	Graphe<InfoArete, InfoSommet> evaluate();

	void setPit(Sommet<InfoSommet> * p) {
		pit = p;
	};
	void setSource(Sommet<InfoSommet> * s) {
		source = s;
	};
};

Graphe<InfoArete, InfoSommet> pcc::evaluate() {
	Sommet<InfoSommet> pj[200];

	fill_n(l, n, DBL_MAX);
	l[0] = 0;

	M = new PElement<Sommet<InfoSommet>> (source, M);

	if (Algo::_graphe->successeurs(M->v)==NULL) {
		cout << "Il existe un circuit de valeur negative." << endl << endl;

		abort();
	}

	PElement<Arete<InfoArete, InfoSommet>> *li = Algo::_graphe->lAretes;
	// Pour chaque sommet
	for (; li; li = li->s) {
		if(type == pcc::typeCout) {
			if(li->v->v.cout < 0) {
				cout << "Il existe un arc de valeur negative." << endl;

				abort();
			}
		} else {
			if(li->v->v.temps < 0) {
				cout << "Il existe un arc de valeur negative." << endl;

				abort();
			}
		}
	}

	while (k <= n-1) {
		k++;
		Mp = NULL;

		const PElement<Sommet<InfoSommet>> * mTmp ;
		for (mTmp = M; mTmp != NULL; mTmp = mTmp->s) {

			const PElement<pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>* >> * sTmp;
			for (sTmp = _graphe->successeurs(mTmp->v); sTmp != NULL; sTmp = sTmp->s) {
				pair<Sommet<InfoSommet> *, Arete<InfoArete, InfoSommet>*> xj = *sTmp->v;

				double lSucc;
				if(type == pcc::typeCout) {
					lSucc = l[xj.second->debut->clef] + xj.second->v.cout;
				} else {
					lSucc = l[xj.second->debut->clef] + xj.second->v.temps;
				}

				if(l[xj.first->clef] > lSucc) {
					l[xj.first->clef] = lSucc;

					Mp = new PElement<Sommet<InfoSommet>> (xj.first, Mp);

					pj [xj.first->clef] = *xj.second->debut;
				}
			}
		}

		M = Mp;
	}

	unsigned int i = 1;
	std::stringstream arcName;
	arcName << "arc" << i;
	_res.creeSommet(pit->v);
	_res.creeArete(pit, &pj[pit->clef], InfoArete(arcName.str(), 0, 0));

	Sommet<InfoSommet> *r = &pj[pit->clef];
	while(r->clef!=0) {
		_res.creeSommet(
			r->v
		);

		arcName.clear();
		arcName.str(std::string());
		arcName << "arc" << ++i;
		_res.creeArete(r, &pj[r->clef], InfoArete(arcName.str(), 0, 0));

		r = &pj[r->clef];
	}
	_res.creeSommet(source->v);

	cout << endl << "--- Chemin -------------------------------"<< endl;
	cout << printSommet(_res.lSommets) << endl;

	return _res;
}
