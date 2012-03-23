/* 
* File: disallowcopy.h
 * -------------------
 * This file provides a macro thaat configures a class to disallowing making
 * object copies.
 */
 
#ifndef _disallowcopy_h
#define _disallowcopy_h

 /*
  * Macro: DISALLOW_COPYING
  * Usage: DISALLOW_COPYING(MyClass)
  * --------------------------------
  * This macro is inserted into the private interface of a class to configure the
  * class to have private declarations of assignment (operator=) and copy
  * construction.  By declaring these private, if a client attempts to invoke
  * them, the compiler will raise an error. This effectively disables object
  * copying: a client will not be able to assign one object to another or 
  * pass/return an object by value. This is appropriate when the class does not
  * provide the facilities for making copies (because of efficiency and/or complexity)
  * and wants to be sure the client doesn't accidentally attempt to make a copy
  * and run into problems because of the non-support.
  */
 #define DISALLOW_COPYING(Classname)  \
		const Classname &operator=(const Classname &) { Error("Copying is disallowed for class "#Classname); return *this; } \
		Classname(const Classname &) { Error("Copying is disallowed for class "#Classname); }

#endif
