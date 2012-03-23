#ifndef GENLIB_H_
#define GENLIB_H_

/* 
 * File: genlib.h
 * Version: 1.0CPP
 * Last modified on Wed Sep 18 13:41:31 PDT 2002 by jzelenski
 * ----------------------------------------------------------
 * This header file is indicated to be included in
 * all the programs written for CS106B/X and provides a few
 * common definitions. Note this header has a "using namespace std" 
 * clause. If a file includes this header, it can then use
 * features from the std namespace without qualifying by scope. 
 */

#include <string>
using namespace std;

/*
 * Function: Error
 * Usage: Error(msg)
 * ------------------
 * Error outputs an error string to the cerr stream and
 * then throws a string exception corresponding to the error.
 */

void Error(string str);


/*
 * Function macro: main
 * --------------------
 * The purpose of this macro definition is to rename the student
 * main to Main in order to allow a custom main defined in our
 * libraries to configure the application before passing control
 * back to the student program.
 */
#ifdef __APPLE__
#define main Main
#endif


#endif /*GENLIB_H_*/