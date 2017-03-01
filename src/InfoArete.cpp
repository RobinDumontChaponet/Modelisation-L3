#include "InfoArete.hpp"

InfoArete::operator string() const {
	ostringstream oss;

	oss << "nom = " << nom << "; coût = " << cout << "; temps= " << temps << endl;

	return oss.str();
}

ostream & operator << ( ostream & os, const InfoArete & infoArete) {
	return os << (string)infoArete;
}
