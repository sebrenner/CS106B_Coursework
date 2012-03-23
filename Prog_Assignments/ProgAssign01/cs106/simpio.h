#ifndef SIMPIO_H_
#define SIMPIO_H_
/*
 * File: simpio.h
 * Version: 1.0CPP
 * Last modified on Wed Sep 18 13:34:29 PDT 2002 by jzelenski
 * ----------------------------------------------------------
 * This interface provides access to a simple package of
 * functions that simplify the reading of console input.
 */

#include "genlib.h"

/*
 * Function: GetInteger
 * Usage: n = GetInteger();
 * ------------------------
 * GetInteger reads a line of text from standard input and scans
 * it as an integer.  The integer value is returned.  If an
 * integer cannot be scanned or if more characters follow the
 * number, the user is given a chance to retry.
 */
 
int GetInteger();


/*
 * Function: GetLong
 * Usage: n = GetLong();
 * ---------------------
 * GetLong reads a line of text from standard input and scans
 * it into a long integer.  The long is returned.  If the 
 * number cannot be scanned or if extra characters follow it,
 * the user is given a chance to retry.
 */
 
long GetLong();

/*
 * Function: GetReal
 * Usage: x = GetReal();
 * ---------------------
 * GetReal reads a line of text from standard input and scans
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 */

double GetReal();


/*
 * Function: GetLine
 * Usage: s = GetLine();
 * ---------------------
 * GetLine reads a line of text from standard input and returns
 * the line as a string.  The newline character that terminates
 * the input is not stored as part of the string that is returned.
 */
 
string GetLine();

#endif /*SIMPIO_H_*/
