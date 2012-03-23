/*
 * File: set.h
 * -----------
 * This interface exports the <code>Set</code> class, a
 * collection for efficiently storing a set of distinct elements.
 */

#ifndef _set_h
#define _set_h

#include "cmpfn.h"
#include "error.h"
#include "foreach.h"
#include "map.h"
#include "vector.h"

/*
 * Class: Set<ValueType>
 * ---------------------
 * This template class stores a collection of distinct elements.
 */

template <typename ValueType>
class Set {

public:

/*
 * Constructor: Set
 * Usage: Set<ValueType> set;
 *        Set<ValueType> set(cmpFn);
 * ---------------------------------
 * Initializes a set of the specified element type, which is either
 * empty or initialized to match the elements of the C++ array
 * passed as the <code>initializers</code> parameter.  The optional
 * <code>cmpFn</code> argument specifies a comparison function, which
 * is called to compare data values.  This argument is typically omitted,
 * in which case the implementation uses the <code>operatorCmp</code>
 * function from <code>cmpfn.h</code>, which applies the built-in
 * operators <code>&lt;</code> and <code>==</code> to determine
 * the ordering.
 */

   explicit Set(int (*cmpFn)(ValueType, ValueType) = operatorCmp);

/*
 * Destructor: ~Set
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with set.
 */

   ~Set();

/*
 * Method: size
 * Usage: count = set.size();
 * --------------------------
 * Returns the number of elements in this set.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (set.isEmpty()) . . .
 * -------------------------------
 * Returns <code>true</code> if this set contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: add
 * Usage: set.add(value);
 * ----------------------
 * Adds an element to this set, if it was not already there.  For
 * compatibility with the STL <code>set</code> class, this method
 * is also exported as <code>insert</code>.
 */

   void add(const ValueType & value);
   void insert(const ValueType & value);

/*
 * Method: remove
 * Usage: set.remove(value);
 * -------------------------
 * Removes an element from this set.  If the value was not
 * contained in the set, no error is generated and the set
 * remains unchanged.
 */

   void remove(const ValueType & value);

/*
 * Method: contains
 * Usage: if (set.contains(value)) . . .
 * -------------------------------------
 * Returns <code>true</code> if the specified value is in this set.
 */

   bool contains(const ValueType & value) const;

/*
 * Method: isSubsetOf
 * Usage: if (set.isSubsetOf(set2)) . . .
 * --------------------------------------
 * Implements the subset relation on sets.  It returns
 * <code>true</code> if every element of this set is
 * contained in <code>set2</code>.
 */

   bool isSubsetOf(const Set & set2) const;

/*
 * Method: clear
 * Usage: set.clear();
 * -------------------
 * Removes all elements from this set.
 */

   void clear();

/*
 * Operator: ==
 * Usage: set1 == set2
 * -------------------
 * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
 * contain the same elements.
 */

   bool operator==(const Set & set2) const;

/*
 * Operator: !=
 * Usage: set1 != set2
 * -------------------
 * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
 * are different.
 */

   bool operator!=(const Set & set2) const;

/*
 * Operator: +
 * Usage: set1 + set2
 *        set1 + element
 * ---------------------
 * Returns the union of sets <code>set1</code> and <code>set2</code>, which
 * is the set of elements that appear in at least one of the two sets.  The
 * right hand set can be replaced by an element of the value type, in which
 * case the operator returns a new set formed by adding that element.
 */

   Set operator+(const Set & set2) const;
   Set operator+(const ValueType & element) const;

/*
 * Operator: *
 * Usage: set1 * set2
 * ------------------
 * Returns the intersection of sets <code>set1</code> and <code>set2</code>,
 * which is the set of all elements that appear in both.
 */

   Set operator*(const Set & set2) const;

/*
 * Operator: -
 * Usage: set1 - set2
 *        set1 - element
 * ---------------------
 * Returns the difference of sets <code>set1</code> and <code>set2</code>,
 * which is all of the elements that appear in <code>set1</code> but
 * not <code>set2</code>.  The right hand set can be replaced by an
 * element of the value type, in which case the operator returns a new
 * set formed by removing that element.
 */

   Set operator-(const Set & set2) const;
   Set operator-(const ValueType & element) const;

/*
 * Operator: +=
 * Usage: set1 += set2;
 *        set1 += value;
 * ---------------------
 * Adds all of the elements from <code>set2</code> (or the single
 * specified value) to <code>set1</code>.  As a convenience, the
 * <code>Set</code> package also overloads the comma operator so
 * that it is possible to initialize a set like this:
 *
 *<pre>
 *    Set<int> digits;
 *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
 *</pre>
 */

   Set & operator+=(const Set & set2);
   Set & operator+=(const ValueType & value);

/*
 * Operator: *=
 * Usage: set1 *= set2;
 * --------------------
 * Removes any elements from <code>set1</code> that are not present in
 * <code>set2</code>.
 */

   Set & operator*=(const Set & set2);

/*
 * Operator: -=
 * Usage: set1 -= set2;
 *        set1 -= value;
 * ---------------------
 * Removes the elements from <code>set2</code> (or the single
 * specified value) from <code>set1</code>.  As a convenience, the
 * <code>Set</code> package also overloads the comma operator so
 * that it is possible to remove multiple elements from a set
 * like this:
 *
 *<pre>
 *    digits -= 0, 2, 4, 6, 8;
 *</pre>
 *
 * which removes the values 0, 2, 4, 6, and 8 from the set
 * <code>digits</code>.
 */

   Set & operator-=(const Set & set2);
   Set & operator-=(const ValueType & value);

/*
 * Macro: foreach
 * Usage: foreach (ValueType value in set) . . .
 * ---------------------------------------------
 * Iterates over the elements of the set. The values are returned
 * in ascending order, as defined by the comparison function.
 */

   /* The foreach macro is defined in foreach.h */

/*
 * Method: first
 * Usage: ValueType value = set.first();
 * -------------------------------------
 * Returns the first value in the set in the order established by the
 * <code>foreach</code> macro.  If the set is empty, <code>first</code>
 * generates an error.
 */

   ValueType first() const;

/*
 * Method: mapAll
 * Usage: set.mapAll(fn);
 *        set.mapAll(fn, data);
 * ----------------------------
 * Iterates through the elements of the set and calls <code>fn(value)</code>
 * for each one.  The values are processed in ascending order, as defined
 * by the comparison function.  The second form of the call allows the
 * client to pass a data value of any type to the callback function.
 */

   void mapAll(void (*fn)(ValueType value));

   template <typename ClientDataType>
   void mapAll(void (*fn)(ValueType, ClientDataType &), ClientDataType & data);

#include "private/setpriv.h"

};

#include "private/setimpl.cpp"

#endif
