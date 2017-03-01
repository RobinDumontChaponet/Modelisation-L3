#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 Information associée à une arête  (segment rectiligne) joignant 2 lieux d'une carte routière.

 On ne stocke que le côut de l'arête, c-à-d sa longueur
 */

class InfoArete {
public:

	string nom;
	double cout;
	double temps;

	InfoArete(const string & nom, const double & cout, const double & temps) : nom(nom), cout(cout), temps(temps) {}

	operator string() const;
};

ostream & operator << ( ostream & os, const InfoArete & infoArete);