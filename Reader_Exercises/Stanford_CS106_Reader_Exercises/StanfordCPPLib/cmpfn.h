/*
 * File: cmpfn.h
 * -------------
 * This interface exports a template function for comparing values of
 * an unspecified type.  Most clients will have no need to use this
 * interface explicitly.  Its primary purpose is to provide a default
 * comparison function that allows maps and sets to use the standard
 * operators defined for their base type.
 */

#ifndef _cmpfn_h
#define _cmpfn_h

/*
 * Function: operatorCmp
 * Usage: int sign = operatorCmp(v1, v2);
 * --------------------------------------
 * This template function is a generic function that compares two
 * values using the built-in <code>==</code> and <code>&lt;</code>
 * operators.  It is supplied as a convenience for those situations
 * where a comparison function is required, and the type has a
 * built-in ordering that you would like to use.
 */

template <typename Type>
int operatorCmp(Type v1, Type v2);

#include "private/cmpfnimpl.cpp"

#endif
