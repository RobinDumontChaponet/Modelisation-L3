#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 Information associée à un sommet représentant un lieu d'une carte routière.
 Un lieu est défini par un nom et par une position géographique
 */

class InfoSommet {
public:
	string nom;
	int n;
	int num;
	int ncomp;
	int prefix;
	int suffixe;

	double borneInf, borneSup;

	InfoSommet(const string & nom, const double & borneInf, const double & borneSup) : nom(nom), borneInf(borneInf), borneSup(borneSup) {}

	InfoSommet() : nom(""), borneInf(0), borneSup(0) {}

	operator string() const;
};

ostream & operator << ( ostream & os, const InfoSommet & infoSommet);
