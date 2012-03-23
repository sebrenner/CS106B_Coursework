/*
 * File: vector.h
 * --------------
 * This interface file contains the Vector class template, an
 * efficient, safer, convenient replacement for the built-in array.
 *
 * Last updated: Tue Jan  2 13:56:15 PST 2007 by zelenski
 */

#ifndef _vector_h_
#define _vector_h_

#include "genlib.h"


/*
 * Class: Vector
 * -------------
 * This interface defines a class template that stores a homogeneous 
 * indexed collection. The basic operations are similar to those 
 * in the built-in array type, with the added features of dynamic 
 * memory management, bounds-checking on indexes, and convenient 
 * insert/remove operations. Like an array, but better!
 * For maximum generality, the Vector is supplied as a class template. 
 * The client specializes the vector to hold values of a specific
 * type, e.g. Vector<int> or Vector<studentT>, as needed
 */

template <typename ElemType> 
  class Vector {
		
	public:
	
		/*
		 * Constructor: Vector
		 * Usage: Vector<int> vec;
		 *	      Vector<student> dormlist(200);
		 *        Vector<string> *vp = new Vector<string>;
		 * -----------------------------------------------
		 * The constructor initializes a new empty vector. The optional 
		 * argument is a hint about the expected number of elements that
		 * this vector will hold, which allows vector to configure itself
		 * for that capacity during initialization.  If not specified, 
		 * it is initialized with default capacity and grows as elements 
		 * are added. Note that capacity does NOT mean size, a newly 
		 * constructed vector always has size() = 0. A large starting 
		 * capacity allows you to add that many elements without requiring 
		 * any internal reallocation. The explicit keyword is required to 
		 * avoid accidental construction of a vector from an int.
	     */
		 explicit Vector(int sizeHint = 0);
		
		/*
		 * Destructor: ~Vector
		 * Usage: delete vp;
		 * -----------------
		 * The destructor deallocates storage associated with this vector.
		 */
		~Vector();
		
		
		/*
		 * Member function: size
		 * Usage: nElems = vec.size();
		 * ---------------------------
		 * This member function returns the number of elements in 
		 * this vector.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (vec.isEmpty())...
		 * -----------------------------
		 * This member function returns true if this vector contains no
		 * elements, false otherwise.
		 */
		 bool isEmpty();
		 
		
		/*
		 * Member function: getAt
		 * Usage: val = vec.getAt(3);
		 * --------------------------
		 * This member function returns the element at the specified index
		 * in this vector. Elements are indexed starting from 0.  A call to
		 * vec.getAt(0) returns the first element, vec.getAt(vec.size()-1) 
		 * returns the last. Raises an error if index is outside the range 
		 * [0, size()-1].
		 */	
	 	ElemType getAt(int index);
	 	
		
	 	/*
		 * Member function: setAt
		 * Usage: vec.setAt(3, value);
		 * ---------------------------
		 * This member function replaces the element at the specified index
		 * in this vector with a new value.  The previous value at that
		 * index is overwritten with the new value. The size of the vector
		 * is unchanged. Raises an error if index is not within the 
		 * range [0, size()-1].
		 */		
		void setAt(int index, ElemType value);
		
		/*
		 * Member function: operator[]
		 * Usage: vec[0] = vec[1];
		 * -----------------------
		 * This member function overloads [] to access elements from
		 * this vector. This allows the client to use array-like notation
		 * to get/set individual vector elements. Returns a reference to 
		 * the element to allow in-place modification of values. Raises
		 * an error if index is not within the range [0, size()-1].
		 */			
		 ElemType &operator[](int index);
		
		
		/*
		 * Member function: add
		 * Usage: vec.add(value);
		 * ----------------------
		 * This member function adds an element to the end of this vector. 
		 * The vector's size increases by one.
		 */
 		void add(ElemType elem);
 		
		
 		/*
		 * Member function: insertAt
		 * Usage: vec.insertAt(0, value);
		 * ------------------------------
		 * This member function inserts the element into this vector at
		 * the specified index, shifting all subsequent elements one
		 * index higher. A call to vec.insertAt(0, val) inserts a new 
		 * element at the beginning, vec.insertAt(vec.size(), val) add 
		 * a new element to the end. The vector's size increases by one.
		 * Raises an error if index is outside the range [0, size()].
		 */	
		void insertAt(int index, ElemType elem);
		
		
		/*
		 * Member function: removeAt
		 * Usage: vec.removeAt(3);
		 * -----------------------
		 * This member function removes the element at the specified
		 * index from this vector, shifting all subsequent elements one
		 * index lower. A call to vec.removeAt(0) removes the first 
		 * element, vec.removeAt(vec.size()-1), removes the last. The 
		 * vector's size decreases by one. Raises an error if index is 
		 * outside the range [0, size()-1].
		 */	
		void removeAt(int index);

		
		/*
		 * Member function: clear
		 * Usage: vec.clear();
		 * -------------------
		 * This member function removes all elements from this vector. The 
		 * vector is made empty and will have size() = 0.
		 */	
		void clear();
		

		/*
		 * Deep copying support
		 * --------------------
		 * This copy constructor and operator= are defined to make a
		 * deep copy, making it possible to pass/return vectors by value
		 * and assign from one vector to another. The entire contents of 
		 * the vector, including all elements, are copied. Each vector
		 * element is copied from the original vector to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, vectors are typically passed 
		 * by reference, however, when a copy is needed, these operations 
		 * are supported.
		 */
		const Vector &operator=(const Vector &rhs); 
		Vector(const Vector &rhs);
		
		
	private:
		ElemType *elements;
		int numAllocated, numUsed;

		void checkRange(int index, const char *msg);
		void enlargeCapacity();
		void copyInternalData(const Vector &other);
	};
	
	



/* 
 * Because of the way C++ templates are compiled, we must put the class implementation in
 * the header file. This is a bit quirky and seems to contradict the principles of
 * encapsulation and abstraction. As a client of this class, you don't need to know
 * anything about the internals and shouldn't depend on any implementation details. In
 * fact, you probably should just stop reading right here!
 */
 
 
 
 
/* 
 * Vector class implementation
 * ---------------------------
 * The Vector is internally managed as a dynamic array of elements.  It tracks capacity
 * (numAllocated) separately from size (numUsed).  All access is bounds-checked for
 * safety. 
 */

#include "strutils.h" // for IntegerToString calls in error messages
#include <cstdlib> // for NULL

template <typename ElemType> 
  Vector<ElemType>::Vector(int capacity)
	{
		elements = new ElemType[capacity];
		numAllocated = capacity;
		numUsed = 0;
	}
	
template <typename ElemType> 
  Vector<ElemType>::~Vector()
	{
		delete[] elements;
	}
	
template <typename ElemType> 
inline   int Vector<ElemType>::size()
	{
		return numUsed; 
	}

template <typename ElemType> 
  bool Vector<ElemType>::isEmpty() 
	{ 
		return (size() == 0); 
	}

template <typename ElemType> 
  ElemType Vector<ElemType>::getAt(int index) 
	{ 
		checkRange(index, "getAt"); 
		return elements[index];
	}
	
template <typename ElemType> 
  void Vector<ElemType>::setAt(int index, ElemType elem) 
	{
		checkRange(index, "setAt");
		elements[index] = elem;
	}
	
/* Private member function: checkRange
 * -----------------------------------
 * Verifies that index is in range for this vector, if not, raises an
 * error.  The verb string is used in the error message to describe the
 * operation that caused the range error, .e.g "setAt" or "removeAt".
 */
template <typename ElemType> 
 inline void Vector<ElemType>::checkRange(int index, const char *verb)  
	{ 
		if (index < 0 || index >= size())
			Error("Attempt to " + string(verb) + " index " + IntegerToString(index) + 
				" in a vector of size " + IntegerToString(size()) + ".");
	}

	
template <typename ElemType> 
 inline ElemType &Vector<ElemType>::operator[](int index) 
	{ 
		checkRange(index, "access"); 
		return elements[index];
	}
	
template <typename ElemType> 
  void Vector<ElemType>::add(ElemType elem)
	{ 
		insertAt(numUsed, elem);	// add is just a special-case of insertAt
	}
					
template <typename ElemType> 
  void Vector<ElemType>::insertAt(int index, ElemType elem) 
	{
		if (numAllocated == numUsed) 
			enlargeCapacity(); 
		if (index != numUsed) checkRange(index, "insertAt"); 
		for (int i = numUsed; i > index; i--)
			elements[i] = elements[i-1];
		elements[index] = elem;
		numUsed++;
	}
	
template <typename ElemType> 
  void Vector<ElemType>::removeAt(int index) 
	{
		checkRange(index, "removeAt"); 
		for (int i = index; i < numUsed-1; i++)
			elements[i] = elements[i+1];
		numUsed--;
	}
	
template <typename ElemType> 
  void Vector<ElemType>::clear() 
	{
		delete[] elements;
		elements = NULL;
		numUsed = numAllocated = 0;
	}


template <typename ElemType> 
  const Vector<ElemType> &Vector<ElemType>::operator=(const Vector &rhs) 
	{
		if (this != &rhs) {
			clear();
			copyInternalData(rhs);			
		}
		return *this;
	}		 

template <typename ElemType> 
  Vector<ElemType>::Vector(const Vector &rhs)
	{
		copyInternalData(rhs);					
	}	
	
	
/* Private member function: enlargeCapacity
 * -----------------------------------------
 * Doubles the current capacity of the vector's internal storage,
 * copying all existing values.
 */
template <typename ElemType> 
  void Vector<ElemType>::enlargeCapacity() 
	{
		numAllocated = (numAllocated == 0 ? 10 : numAllocated*2);
		ElemType *newArray = new ElemType[numAllocated];
		for (int i = 0; i < numUsed; i++)
			newArray[i] = elements[i];
		delete[] elements;
		elements = newArray;
	}
	
	
/* Private member function: copyInternalData
 * -----------------------------------------
 * Common code factored out of the copy constructor and operator= to
 * copy the contents from the other vector.
 */

template <typename ElemType> 
  void Vector<ElemType>::copyInternalData(const Vector &other)
	{
		elements = new ElemType[other.numUsed];
		for (int i = 0; i < other.numUsed; i++)
			elements[i] = other.elements[i];
		numUsed = other.numUsed;
		numAllocated = other.numUsed;	
	}
		
		
	

#endif //_vector_h_
