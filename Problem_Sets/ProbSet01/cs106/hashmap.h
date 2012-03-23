/*
 * File: hashmap.h
 * ---------------
 * This interface exports the template class <code>HashMap</code>, which
 * maintains a collection of <i>key</i>-<i>value</i> pairs using a
 * hashtable as the underlying structure.
 */

#ifndef _hashmap_h
#define _hashmap_h

#include <cstdlib>
#include <string>
#include "error.h"
#include "foreach.h"
#include "vector.h"

/*
 * Class: HashMap<KeyType,ValueType>
 * ---------------------------------
 * The <code>HashMap</code> class maintains an association between
 * keys and values.  The types used for keys and values are
 * specified using templates, which makes it possible to use
 * this structure with any data type.
 */

template <typename KeyType, typename ValueType>
class HashMap {

public:

/*
 * Constructor: HashMap
 * Usage: HashMap<KeyType,ValueType> map;
 * --------------------------------------
 * Initializes a new empty map that associates keys and values of
 * the specified types.  The type used for the key must define
 * the == operator, and there must be a free function available
 * with the following signature:
 *
 *     int hashCode(KeyType key);
 *
 * that returns a positive integer determined by the key.  This
 * interface exports hashCode functions for <code>string</code>
 * and the C++ primitive types.
 */

   HashMap();

/*
 * Destructor: ~HashMap
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this map.
 */

   ~HashMap();

/*
 * Method: size
 * Usage: int nEntries = map.size();
 * ---------------------------------
 * Returns the number of entries in this map.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (map.isEmpty()) . . .
 * -------------------------------
 * Returns <code>true</code> if this map contains no entries.
 */

   bool isEmpty() const;

/*
 * Method: put
 * Usage: map.put(key, value);
 * ---------------------------
 * Associates <code>key</code> with <code>value</code> in this map.
 * Any previous value associated with <code>key</code> is replaced
 * by the new value.
 */

   void put(KeyType key, ValueType value);

/*
 * Method: get
 * Usage: ValueType value = map.get(key);
 * --------------------------------------
 * Returns the value associated with <code>key</code> in this map.
 * If <code>key</code> is not found, the <code>get</code> method
 * signals an error.
 */

   ValueType get(KeyType key) const;

/*
 * Method: containsKey
 * Usage: if (map.containsKey(key)) . . .
 * --------------------------------------
 * Returns <code>true</code> if there is an entry for <code>key</code>
 * in this map.
 */

   bool containsKey(KeyType key) const;

/*
 * Method: remove
 * Usage: map.remove(key);
 * -----------------------
 * Removes any entry for <code>key</code> from this map.
 */

   void remove(KeyType key);

/*
 * Method: clear
 * Usage: map.clear();
 * -------------------
 * Removes all entries from this map.
 */

   void clear();

/*
 * Operator: []
 * Usage: map[key]
 * ---------------
 * Selects the value associated with <code>key</code>.  This syntax
 * makes it easy to think of a map as an "associative array"
 * indexed by the key type.  If <code>key</code> is already present
 * in the map, this function returns a reference to its associated
 * value.  If key is not present in the map, a new entry is created
 * whose value is set to the default for the value type.
 */

   ValueType & operator[](KeyType key);

/*
 * Macro: foreach
 * Usage: foreach (KeyType key in map) . . .
 * -----------------------------------------
 * Iterates over the keys in the map. In a <code>HashMap</code>,
 * the keys are processed in an order determined by the internal
 * structure, which will have no obvious relationship to the keys.
 */

   /* The foreach macro is defined in foreach.h */

/*
 * Method: mapAll
 * Usage: map.mapAll(fn);
 *        map.mapAll(fn, data);
 * ----------------------------
 * Iterates through the keys in this map and calls <code>fn(key)</code>
 * for each one.  The keys are processed in an undetermined order.
 * The second form of the call allows the client to pass a data value
 * of any type to the callback function.
 */

   void mapAll(void (*fn)(KeyType key));

   template <typename ClientDataType>
   void mapAll(void (*fn)(KeyType, ClientDataType &), ClientDataType & data);

#include "private/hashmappriv.h"

};

#include "private/hashmapimpl.cpp"

/*
 * Function: hashCode
 * Usage: int hash = hashCode(key);
 * --------------------------------
 * Returns a hash code for the specified key, which is always a
 * nonnegative integer.  This function is overloaded to support
 * all of the primitive types and the C++ <code>string</code> type.
 */

int hashCode(std::string key);
int hashCode(int key);
int hashCode(char key);
int hashCode(long key);
int hashCode(double key);

#endif
