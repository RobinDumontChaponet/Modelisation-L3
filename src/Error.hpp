#pragma once
/******************************
 *	      Error class         *
 ******************************/
#ifndef ERROR
#define ERROR

using namespace std;

#include <string>
#include <iostream>

class Error {
public:
	const static int WIDTH_MESSAGE = 100;
	char message[1 + WIDTH_MESSAGE];
	Error();
	Error(const char * errorMessage);


	inline static void testEqual(int m, int n, const char * message);

	/********************************************
	 *			  Checks a <= b					*
	 *			Exception if a > b				*
	 ********************************************/
	inline static void testLessOrEqual(const int a, const int b, const char * message);

	/********************************************
	 *	     Exception if x isn't in [a,b]		*
	 ********************************************/
	inline static void testBelongsTo(int a, int x, int b, const char * message);

	/********************************************
	 *	      Exception if d is empty			*
	 ********************************************/
	inline static void testNotEmpty(const void *d, const char * message);

	operator string() const;
};

ostream & operator << (ostream & os, const Error & error);

/********************************************
 *			  Checks a = b					*
 *			Exception if a != b				*
 ********************************************/
inline void Error::testEqual(int m, int n, const char * message) {
#ifdef DEBUG
	if (m != n) throw Error(message);
#endif
}

/********************************************
 *			  Checks a <= b					*
 *			Exception if a > b				*
 ********************************************/
inline /*static*/ void Error::testLessOrEqual(const int a, const int b, const char * message) {
#ifdef DEBUG
	if (a > b) throw Error(message);
#endif
}

/********************************************
 *	     Exception if x isn't in [a,b]		*
 ********************************************/
inline /*static*/ void Error::testBelongsTo(int a, int x, int b, const char * message) {
	Error::testLessOrEqual(a, x, message);
	Error::testLessOrEqual(x, b, message);
}

/********************************************
 *	      Exception if d is empty			*
 ********************************************/
inline /*static*/ void Error::testNotEmpty(const void *d, const char * message) {
#ifdef DEBUG
	if (!d) throw Error(message);
#endif
}
#endif