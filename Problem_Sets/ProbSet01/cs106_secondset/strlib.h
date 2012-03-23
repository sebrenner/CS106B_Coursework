/*
 * File: strlib.h
 * --------------
 * This interface exports several useful string functions that are
 * not included in the C++ string library.
 */

#ifndef _strlib_h
#define _strlib_h

#include <string>

/*
 * Function: integerToString
 * Usage: string s = integerToString(n);
 * -------------------------------------
 * Converts an integer into the corresponding string of digits.
 * For example, calling <code>integerToString(123)</code> returns
 * the string <code>"123"</code>.
 */

std::string integerToString(int n);

/*
 * Function: stringToInteger
 * Usage: int n = stringToInteger(str);
 * ------------------------------------
 * Converts a string of digits into an integer.  If the string is not a
 * legal integer or contains extraneous characters other than whitespace,
 * <code>stringToInteger</code> calls <code>error</code> with an
 * appropriate message.
 */

int stringToInteger(std::string str);

/*
 * Function: realToString
 * Usage: string s = realToString(d);
 * ----------------------------------
 * Converts a floating-point number into the corresponding string form.
 * For example, calling <code>realToString(23.45)</code> returns
 * the string <code>"23.45"</code>.
 */

std::string realToString(double d);

/*
 * Function: stringToReal
 * Usage: double d = stringToReal(str);
 * ------------------------------------
 * Converts a string representing a real number into its corresponding
 * value.  If the string is not a legal floating-point number or contains
 * extraneous characters other than whitespace, <code>stringToReal</code>
 * calls <code>error</code> with an appropriate message.
 */

double stringToReal(std::string str);

/*
 * Function: toUpperCase
 * Usage: string s = toUpperCase(str);
 * -----------------------------------
 * Returns a new string in which all lowercase characters have been converted
 * into their uppercase equivalents.
 */

std::string toUpperCase(std::string str);

/*
 * Function: toLowerCase
 * Usage: string s = toLowerCase(str);
 * -----------------------------------
 * Returns a new string in which all uppercase characters have been converted
 * into their lowercase equivalents.
 */

std::string toLowerCase(std::string str);

/*
 * Function: equalsIgnoreCase
 * Usage: if (equalsIgnoreCase(s1, s2)) . . .
 * ------------------------------------------
 * Returns <code>true</code> if <code>s1</code> and <code>s2</code> are
 * equal discounting differences in case.
 */

bool equalsIgnoreCase(std::string s1, std::string s2);

/*
 * Function: startsWith
 * Usage: if (startsWith(str, prefix)) . . .
 * -----------------------------------------
 * Returns <code>true</code> if the string <code>str</code> starts with
 * the specified prefix, which may be either a string or a character.
 */

bool startsWith(std::string str, std::string prefix);
bool startsWith(std::string str, char prefix);

/*
 * Function: endsWith
 * Usage: if (endsWith(str, suffix)) . . .
 * ---------------------------------------
 * Returns <code>true</code> if the string <code>str</code> ends with
 * the specified suffix, which may be either a string or a character.
 */

bool endsWith(std::string str, std::string suffix);
bool endsWith(std::string str, char suffix);

/*
 * Function: trim
 * Usage: string trimmed = trim(str);
 * ----------------------------------
 * Returns a new string after removing any whitespace characters
 * from the beginning and end of the argument.
 */

std::string trim(std::string str);

#endif
