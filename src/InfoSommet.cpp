#include "InfoSommet.hpp"

InfoSommet::operator string() const {
	ostringstream oss;
	oss << "nom = " << nom << "; borneInf = " << borneInf << "; borneSup = " << borneSup << endl;

	return oss.str();
}

ostream & operator << ( ostream & os, const InfoSommet & infoSommet) {
	return os << (string)infoSommet;
}
