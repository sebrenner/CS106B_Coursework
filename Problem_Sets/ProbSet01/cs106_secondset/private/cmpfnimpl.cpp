/*
 * File: cmpfnimpl.cpp
 * -------------------
 * This file contains the implementation of the cmpfn.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _cmpfn_h

template <typename Type>
int operatorCmp(Type v1, Type v2) {
   if (v1 == v2) return 0;
   if (v1 < v2) return -1;
   return 1;
}

#endif
