/*
 * File: set.h
 * -----------
 * This interface file contains the Set class template, a
 * collection for efficiently storing a set of distinct elements.
 *
 * Last updated: Tue Jan  2 14:34:06 PST 2007 by zelenski
 */

#ifndef _set_h_
#define _set_h_
#include "cmpfn.h"
#include "bst.h"
#include "vector.h"


/*
 * Class: Set
 * ----------
 * This interface defines a class template that stores a collection of
 * distinct elements, using a sorted relation on the elements to 
 * provide efficient managaement of the collection.  
 * For maximum generality, the Set is supplied as a class template. 
 * The element type is determined by the client. The client configures 
 * the set to hold values of a specific type, e.g. Set<int> or 
 * Set<studentT>. The one requirement on the element type is that the 
 * client must supply a comparison function that compares two elements 
 * (or be willing to use the default comparison function that uses
 * the built-on operators  < and ==).
 */
template <typename ElemType>
  class Set {
  
   	public: 
   	
		/*
		 * Constructor: Set
		 * Usage: Set<int> set;
		 *        Set<student> students(CompareStudentsById);
		 *        Set<string> *sp = new Set<string>;
		 * -----------------------------------------
		 * The constructor initializes an empty set. The optional 
		 * argument is a function pointer that is applied to
		 * two elements to determine their relative ordering. The 
		 * comparison function should return 0 if the two elements 
		 * are equal, a negative result if first is "less than" second, 
		 * and a positive resut if first is "greater than" second. If 
		 * no argument is supplied, the OperatorCmp template is used as 
		 * a default, which applies the bulit-in < and == to the 
		 * elements to determine ordering.
		 */
	    Set(int (cmpFn)(ElemType, ElemType) = OperatorCmp);
	    
	    
		/*
		 * Destructor: ~Set
		 * Usage: delete sp;
		 * -----------------
		 * The destructor deallocates  storage associated with set.
		 */
	     ~Set();

	  	/*
		 * Member function: size
		 * Usage: count = set.size();
		 * --------------------------
		 * This member function returns the number of elements in this set.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (set.isEmpty())...
		 * ----------------------------
		 * This member function returns true if this set contains no
		 * elements, false otherwise.
		 */
		 bool isEmpty();
		 

		/*
		 * Member function: add
		 * Usage: set.add(value);
		 * ----------------------
		 * This member function adds an element to this set. If the 
		 * value was already contained in the set, the existing entry is 
		 * overwritten by the new copy, and the set's size is unchanged. 
		 * Otherwise, the value is added and set's size increases by one.
		 */
		void add(ElemType elem);	
		
		/*
		 * Member function: remove
		 * Usage: set.remove(value);
		 * -----------------------
		 * This member function removes an element from this set. If the 
		 * element was not contained in the set, the set is unchanged. 
		 * Otherwise, the element is removed and the set's size decreases 
		 * by one.
		 */
		void remove(ElemType elem);
		
		/*
		 * Member function: contains
		 * Usage: if (set.contains(value))...
		 * -----------------------------------
		 * Returns true if the element in this set, false otherwise.
		 */
		bool contains(ElemType elem);


		/*
		 * Member function: find
		 * Usage: eptr = set.find(elem);
		 * -----------------------------
		 * If the element is contained in this set, returns a pointer 
		 * to that elem.  The pointer allows you to update that element 
		 * in place. If element is not contained in this set, NULL is 
		 * returned.
		 */
		ElemType *find(ElemType elem);


		/*
		 * Member function: equals
		 * Usage: if (set.equals(set2)) . . .
		 * -----------------------------------
		 * This predicate function implements the equality relation
		 * on sets.  It returns true if this set and set2 contain 
		 * exactly the same elements, false otherwise.
		 */
	 	 bool equals(Set & otherSet);
	 	 
	 	 
		/*
		 * Member function: isSubsetOf
		 * Usage: if (set.isSubsetOf(set2)) . . .
		 * --------------------------------------
		 * This predicate function implements the subset relation
		 * on sets.  It returns true if all of the elements in this
		 * set are contained in set2.  The set2 does not have to 
		 * be a proper subset (that is, it may be equals).
		 */
	 	bool isSubsetOf(Set & otherSet);

		/*
		 * Member functions: unionWith, intersect, subtract
		 * Usage: set.unionWith(set2);
		 *        set.intersect(set2);
		 *        set.subtract(set2);
		 * ---------------------------
		 * These fmember unctions modify the receiver set as follows:
		 *
		 * set.unionWith(set2);  Adds all elements from set2 to this set.
		 * set.intersect(set2);  Removes any element not in set2 from this set.
		 * set.subtract(set2);   Removes all element in set2 from this set.
	 	*/    
	 	void unionWith(Set & otherSet);
	    void intersect(Set & otherSet);
	    void subtract(Set & otherSet);


		/*
		 * Member function: clear
		 * Usage: set.clear();
		 * -------------------
		 * This member function removes all elements from this set. The 
		 * set is made empty and will have size() = 0 after being cleared.
		 */	
		void clear();


		/* 
		 * SPECIAL NOTE: mapping/iteration support
		 * ---------------------------------------
		 * The set supports both a mapping operation and an iterator which
		 * allow the client access to all elements one by one.  In general,
		 * these  are intended for _viewing_ elements and can behave
		 * unpredictably if you attempt to modify the set's contents during 
		 * mapping/iteration. 
		 */


		/*
		 * Member function: mapAll
		 * Usage: set.mapAll(Print);
		 * -------------------------
		 * This member function iterates through this set's contents
		 * and calls the function fn once for each element.
		 */
		void mapAll(void (fn)(ElemType elem));
		

		/*
		 * Member function: mapAll
		 * Usage: set.mapAll(PrintToFile, outputStream);
		 * --------------------------------------------
		 * This member function iterates through this set's contents
		 * and calls the function fn once for each element, passing
		 * the element and the client's data. That data can be of whatever 
		 * type is needed for the client's callback.
		 */
		template <typename ClientDataType>
			void mapAll(void (fn)(ElemType elem, ClientDataType &data),
							ClientDataType &data);
							

		class Iterator;
		
		/*
		 * Member function: iterator
		 * Usage: itr = set.iterator();
		 * --------------------------
		 * This member function creates an iterator that allows the client
		 * to iterate through the elements in this set. The elements are
		 * accessed in order as determined by the elem comparison function.
		 */
		Iterator iterator();



		/*
		 * Class: Set<ElemType>::Iterator
		 * ---------------------------------
		 * This interface defines a nested class within the Set template that
		 * provides iterator access to the Set contents.  
		 *
		 * The idiomatic code for accessing elements using an iterator is
		 * to create the iterator from the collection and then enter a loop
		 * that calls next() while hasNext() is true, like this:
		 *
		 *	Set<int>::Iterator itr = set.iterator();
		 *  while (itr.hasNext())
		 *      int num = itr.next();
		 */
		class Iterator {
			public:
				Iterator(); 
				bool hasNext();
				ElemType next();
				
			private:
				Iterator(Set *setptr);
				Set *sp;
				Vector<ElemType> elems;
				int curIndex;
				friend class Set;
		};
		friend class Iterator;


		/*
		 * Deep copying support
		 * --------------------
		 * Because all Set data members have correct behavior on operator=
		 * and copy constructor, the default for these as synthesized by
		 * the compiler make a correct copy of the Set. When pass/return
		 * sets by value, or assign one to another, the entire contents of 
		 * the set, including all elements, are copied. Each set
		 * element is copied from the original set to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, sets are typically passed by 
		 * reference, however, when a copy is needed, these operations 
		 * are supported.
		 *
		 * const Set &operator=(const Set &rhs); 
		 * Set(const Set &rhs);
		 */

	private:
		BST<ElemType> bst;
		int (*cmpFn)(ElemType, ElemType);
			
};
	
template <typename ElemType>
  Set<ElemType>::Set(int (cmp)(ElemType, ElemType)) : bst(cmp)
	{
	    cmpFn = cmp;
	}


template <typename ElemType>
  Set<ElemType>::~Set()
	{
	}


template <typename ElemType>
  int Set<ElemType>::size()
	{
	    return bst.size();
	}

template <typename ElemType>
  bool Set<ElemType>::isEmpty()
	{
	    return bst.isEmpty();
	}

template <typename ElemType>
  void Set<ElemType>::add(ElemType element)
	{
	    bst.add(element);
	}


template <typename ElemType>
  void Set<ElemType>::remove(ElemType element)
	{
	    bst.remove(element);
	}


template <typename ElemType>
  bool Set<ElemType>::contains(ElemType element)
	{
	    return (find(element) != NULL);
	}
	
template <typename ElemType>
  ElemType *Set<ElemType>::find(ElemType element)
	{
	    return (bst.find(element));
	}


template <typename ElemType>
  void Set<ElemType>::clear()
	{
	    bst.clear();
	}

/*
 * Implementation notes: Set operations
 * ------------------------------------
 * The code for equals, isSubsetOf, unionWith, intersect, and subtract
 * is similar in structure.  Each one uses an iterator to walk over
 * one (or both) sets, doing add/remove/comparision.
 */

template <typename ElemType>
  bool Set<ElemType>::equals(Set & otherSet)
	{
		if (cmpFn != otherSet.cmpFn) Error("otherSet passed to equals doesn't have same comparison function");
	    Iterator thisItr = iterator(), otherItr = otherSet.iterator();
	    while (thisItr.hasNext() && otherItr.hasNext()) {
    		if (cmpFn(thisItr.next(), otherItr.next()) != 0) 
	    		return false;
	    }
	    return (!thisItr.hasNext() && !otherItr.hasNext());
	}

template <typename ElemType>
  bool Set<ElemType>::isSubsetOf(Set & otherSet)
	{
		if (cmpFn != otherSet.cmpFn) Error("otherSet passed to isSubsetOf doesn't have same comparison function");
		Iterator itr = iterator();
	    while (itr.hasNext()) {
	    	if (!otherSet.contains(itr.next())) 
		    	return false;
    	}
	    return true;
	}

template <typename ElemType>
  void Set<ElemType>::unionWith(Set & otherSet)
	{
		if (cmpFn != otherSet.cmpFn) Error("otherSet passed to unionWith doesn't have same comparison function");
		Iterator itr = otherSet.iterator();
		while (itr.hasNext())
			add(itr.next());
	}

template <typename ElemType>
  void Set<ElemType>::intersect(Set & otherSet)
	{
		if (cmpFn != otherSet.cmpFn) Error("otherSet passed to intersect doesn't have same comparison function");
		Iterator itr = iterator();
		while (itr.hasNext()) {
			ElemType elem = itr.next();
			if (!otherSet.contains(elem))
				remove(elem);
		}
	}

template <typename ElemType>
  void Set<ElemType>::subtract(Set & otherSet)
	{
		if (cmpFn != otherSet.cmpFn) Error("otherSet passed to subtract doesn't have same comparison function");
		Iterator itr = otherSet.iterator();
		while (itr.hasNext())
			remove(itr.next());
	}

	
template <typename ElemType> 
  void Set<ElemType>::mapAll(void (fn)(ElemType))
	{
		bst.mapAll(fn);
	}
		
template <typename ElemType>
 template <typename ClientDataType> 
  void Set<ElemType>::mapAll(void (fn)(ElemType, ClientDataType&), ClientDataType &data)
	{
		bst.mapAll(fn, data);
	}

	
/* 
 * Set::Iterator class implementation
 * ----------------------------------
 * The Iterator for Set tracks a pointer to the original Set and a vector containing
 * of the elems that was assembled at the time of iteration creation.  The
 * iterator tracks an index into that vector that identifies the next key to return.
 * Each use of next() increments that index, hasNext() verifies the index < the vector's 
 * size. This is an example of an "offline" iterator because it copies the set's 
 * data, instead of accessing it in-place. This is a bit inefficient (since it copies)
 * but it makes the iterator simplier to write and sidesteps any problems where the 
 * client is modifying the set during iteration.
 */

template <typename ElemType> 
  Set<ElemType>::Iterator::Iterator()
	{
		sp = NULL;
	}

template <typename ElemType> 
  typename Set<ElemType>::Iterator Set<ElemType>::iterator()
	{ 
		return Iterator(this);
	}

		

template <typename ElemType>
  static void AddToVector(ElemType elem, Vector<ElemType> &vec)
	{
		vec.add(elem);
	}
	
template <typename ElemType> 
  Set<ElemType>::Iterator::Iterator(Set *setptr) : elems(setptr->size())
	{
		sp = setptr;
		sp->mapAll<Vector<ElemType> >(AddToVector, elems);
		curIndex = 0;
	}

template <typename ElemType> 
  bool Set<ElemType>::Iterator::hasNext() 
	{
		if (sp == NULL) Error("hasNext called on uninitialized iterator");
		 return curIndex < elems.size();
	}

template <typename ElemType> 
  ElemType Set<ElemType>::Iterator::next() 
	{
		if (sp == NULL) Error("next called on uninitialized iterator");
		if (!hasNext()) Error("Attempt to get next from iterator where hasNext() is false");
		return elems[curIndex++];
	}
	
#endif // _set_h_

