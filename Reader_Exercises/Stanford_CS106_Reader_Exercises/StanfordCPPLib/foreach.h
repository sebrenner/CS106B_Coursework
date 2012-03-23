/*
 * File: foreach.h
 * ---------------
 * This interface defines the <code>foreach</code> keyword, which is
 * used to simplify iteration.  All iterable classes import this
 * interface, so clients never need to do so explicitly.  This version
 * of the interface also supports C++ strings and arrays.
 */

#ifndef _foreach_h
#define _foreach_h

/*
 * Statement: foreach
 * Usage: foreach (type var in collection) { . . . }
 * -------------------------------------------------
 * The <code>foreach</code> statement steps through the elements in
 * a collection.  It works correctly with the collection classes in
 * both the Standard Template Library and the Stanford C++ libraries,
 * but can also be used with C++ strings and statically initialized
 * arrays.
 *
 * <p>The following code, for example, prints every element in the
 * string vector <code>lines</code>:
 *
 *<pre>
 *    foreach (string str in lines) {
 *       cout << str << endl;
 *    }
 *</pre>
 *
 * Similarly, the following function calculates the sum of the character
 * codes in a string:
 *
 *<pre>
 *    int sumCharacterCodes(string str) {
 *       int sum = 0;
 *       foreach (char ch in str) sum += ch;
 *       return sum;
 *    }
 *</pre>
 *
 * As a simplification when iterating over maps, the <code>foreach</code>
 * macro iterates through the keys rather than the key/value pairs.
 */

   /* The foreach and in macros are defined in the foreachpriv.h file */

#include "private/foreachpriv.h"

#endif
