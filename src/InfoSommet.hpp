#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * n = nombre successeurs;
 * num = ordre ouverture sommets dfs;
 * ncomp = identifiant du sous-graphe (dfs);
 */

class InfoSommet {
public:
	string nom;
	int n;
	int num;
	int ncomp;
	int prefix;
	int suffixe;
	int lambda;

	double borneInf, borneSup;

	InfoSommet(const string & nom, const double & borneInf, const double & borneSup) : nom(nom), borneInf(borneInf), borneSup(borneSup) {}

	InfoSommet() : nom(""), borneInf(0), borneSup(0) {}

	operator string() const;
};

ostream & operator << ( ostream & os, const InfoSommet & infoSommet);
