/*
 * File: stackpriv.h
 * -----------------
 * This file contains the private section of the stack.h interface.
 * This portion of the class definition is taken out of the stack.h
 * header so that the client need not have to see all of these
 * details.
 */

/*
 * Implementation notes: Stack data structure
 * ------------------------------------------
 * The easiest way to implement a stack is to store the elements in a
 * Vector.  Doing so means that the problems of dynamic memory allocation
 * and copy assignment are already solved by the implementation of the
 * underlying Vector class.
 */

private:
   Vector<ValueType> elements;
