/*********************************************
 *	      Error class implementation         *
 *********************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include "Error.hpp"

using namespace std;

Error::Error() {
	strcpy(this->message, "Error !");
}

Error::Error(const char * errorMessage) {
	strcpy(this->message, "Error : ");
	size_t l = strlen(errorMessage);
	static int n = WIDTH_MESSAGE - 9;
	if (l <= n) strcat(this->message, errorMessage);
	else {
		strncat(this->message, errorMessage, n);
		this->message[WIDTH_MESSAGE] = '\0';
	}
}

Error::operator string() const {
	return string(this->message);
}

ostream & operator << (ostream & os, const Error & error) {
	os << (string)error;
	return os;
}
