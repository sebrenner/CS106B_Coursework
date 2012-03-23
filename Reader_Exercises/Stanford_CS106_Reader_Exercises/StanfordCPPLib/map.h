/*
 * File: map.h
 * -----------
 * This interface exports the template class <code>Map</code>, which
 * maintains a collection of <i>key</i>-<i>value</i> pairs.
 */

#ifndef _map_h
#define _map_h

#include <cstdlib>
#include "cmpfn.h"
#include "error.h"
#include "foreach.h"
#include "stack.h"

/*
 * Class: Map<KeyType,ValueType>
 * -----------------------------
 * The <code>Map</code> class maintains an association between
 * keys and values.  The types used for keys and values are
 * specified using templates, which makes it possible to use
 * this structure with any data type.
 */

template <typename KeyType, typename ValueType>
class Map {

public:

/*
 * Constructor: Map
 * Usage: Map<KeyType,ValueType> map;
 *        Map<KeyType,ValueType> map(cmpFn);
 * -----------------------------------------
 * Initializes a new empty map that associates keys and values of
 * the specified types.  The optional argument specifies a comparison
 * function, which is called to compare data values.  This argument
 * is typically omitted, in which case the implementation uses
 * the <code>operatorCmp</code> function from <code>cmpfn.h</code>,
 * which applies the built-in operators <code>&lt;</code> and
 * <code>==</code> to determine the ordering.
 */

   Map(int (*cmpFn)(KeyType, KeyType) = operatorCmp);

/*
 * Destructor: ~Map
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this map.
 */

   ~Map();

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
 * Iterates over the keys in the map. The keys are processed in
 * ascending order, as defined by the comparison function.
 */

   /* The foreach macro is defined in foreach.h */

/*
 * Method: mapAll
 * Usage: map.mapAll(fn);
 *        map.mapAll(fn, data);
 * ----------------------------
 * Iterates through the keys in this map and calls <code>fn(key)</code>
 * for each one.  The keys are processed in ascending order, as defined
 * by the comparison function.  The second form of the call allows the
 * client to pass a data value of any type to the callback function.
 */

   void mapAll(void (*fn)(KeyType key));

   template <typename ClientDataType>
   void mapAll(void (*fn)(KeyType, ClientDataType &), ClientDataType & data);

#include "private/mappriv.h"

};

#include "private/mapimpl.cpp"

#endif
