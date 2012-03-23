/*
 * File: map.h
 * -----------
 * This interface file contains the Map class template, a
 * collection for efficiently storing key-value pairs.
 *
 * Last updated: Tue Jan  2 14:14:44 PST 2007 by zelenski
 */

#ifndef _map_h_
#define _map_h_

#include "vector.h"
#include <string>
#include "genlib.h"
#include <cstdlib> // for NULL

/*
 * Class: Map
 * ----------
 * This interface defines a class template that stores a collection
 * of key-value pairs. 
 * For maximum generality, the Map is supplied as a class template. 
 * The keys are always of type string, but the value type is set
 * by the client. The client specializes the map to hold values of a 
 * specific type, e.g. Map<int> or Map<studentT>, as needed.
 */

template <typename ValueType> 
  class Map {
	public:
		
		/*
		 * Constructor: Map
		 * Usage: Map<int> map;
		 *	      Map<int> map(500);
		 *        Map<string> *mp = new Map<string>;
		 * -----------------------------------------
		 * The constructor initializes a new empty map. The optional 
		 * argument is a hint about the expected number of entries
		 * that this map will hold, which allows the map to configure 
		 * itself for efficiency at that size.  If not specified, a 
		 * reasonable default is used and the map will adapt as entries 
		 * are added. The explicit keyword is used to prevent  
		 * accidental construction of a Map from an integer.
		 * Raises an error if sizeHint is negative.
	     */
		explicit Map(int sizeHint = 101);
		
		
		/*
		 * Destructor: ~Map
		 * Usage: delete mp;
		 * -----------------
		 * The destructor deallocates  storage associated with this map.
		 */
		~Map();


		/*
		 * Member function: size
		 * Usage: nEntries = map.size();
		 * -----------------------------
		 * This member function returns the number of entries in this map.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (map.isEmpty())...
		 * ----------------------------
		 * This member function returns true if this map contains no
		 * entries, false otherwise.
		 */
		 bool isEmpty();
		 

		/*
		 * Member function: add
		 * Usage: map.add(key, value);
		 * ---------------------------
		 * This member function associates key with value in this map.
		 * Any previous value associated with key is replaced by this new
		 * entry. If there was already an entry for this key, the map's
		 * size is unchanged; otherwise, it increments by one.
		 */
		void add(string key, ValueType value);	
		
		
		/*
		 * Member function: remove
		 * Usage: map.remove(key);
		 * -----------------------
		 * This member function removes any entry for key from this map.
		 * If there is no entry for the key, the map is unchanged. 
		 * Otherwise, the key and its associated value are removed and 
		 * the map's size decreases by one.
		 */
		void remove(string key);
		
		
		/*
		 * Member function: containsKey
		 * Usage: if (map.containsKey(key))...
		 * -----------------------------------
		 * Returns true if there is an entry for key in this map, 
		 * false otherwise.
		 */
		bool containsKey(string key);


		/*
		 * Member function: getValue
		 * Usage: value = map.getValue(key);
		 * ---------------------------------
		 * If key is found in this map, this member function returns the 
		 * associated value.  If key is not found, raises an error. The
		 * containsKey member function can be used to verify the presence 
		 * of a key in the map before attempting to get its value.
		 */
		ValueType getValue(string key);


		/*
		 * Member function: operator[]
		 * Usage: map[key] = newValue;
		 * ---------------------------
		 * This member function overloads [] to access values from this 
		 * map by key. The argument inside the brackets is the key (a 
		 * string). This allows the client to use notation of an 
		 * "associative-array" to get/set the value associated with a key. 
		 * If the key is already present in the map, this function returns 
		 * a reference to its associated value, and the size of the map is 
		 * unchanged. If key is not present in the map, a new entry for the 
		 * key is added, and the size of the map increases by one. The
		 * value for the newly entered key is set to the default for value 
		 * type, and a reference to that value is returned.  Because this 
		 * function returns the value by reference, it allows in-place 
		 * modification of the value.
		 */			
		ValueType &operator[](string key);
		
		
		/*
		 * Member function: clear
		 * Usage: map.clear();
		 * -------------------
		 * This member function removes all entries from this map. The 
		 * map is made empty and will have size() = 0 after being cleared.
		 */	
		void clear();


		/* 
		 * SPECIAL NOTE: mapping/iteration support
		 * ---------------------------------------
		 * The map supports both a mapping operation and an iterator which
		 * allow the client access to all entries one by one.  In general,
		 * these  are intended for _viewing_ entries and can behave
		 * unpredictably if you attempt to modify the map's contents during 
		 * mapping/iteration. 
		 */

		/*
		 * Member function: mapAll
		 * Usage: map.mapAll(Print);
		 * -------------------------
		 * This member function goes through every entry in this map
		 * and calls the function fn, passing it two arguments:
		 * the key and its associated value.
		 */
		void mapAll(void (fn)(string key, ValueType val));
		

		/*
		 * Member function: mapAll
		 * Usage: map.mapAll(PrintToFile, outputStream);
		 * ---------------------------------------------
		 * This member function goes through every entry in this map
		 * and calls the function fn, passing it three arguments:
		 * the key, its associated value, and the client's data. That data 
		 * can be of whatever type is needed for the client's callback.
		 */
		template <typename ClientDataType>
			void mapAll(void (fn)(string key, ValueType val, ClientDataType &data),
							ClientDataType &data);
							
		
		class Iterator;
		
		/*
		 * Member function: iterator
		 * Usage: itr = map.iterator();
		 * ----------------------------
		 * This member function creates an iterator that allows the client
		 * to iterate through the keys in this map.  Note that the iterator
		 * returns the _keys_ one by one.  If needed, you can retrieve the 
		 * associated value from the map using getValue or operator[].
		 */
		Iterator iterator();



		/*
		 * Class: Map<ValType>::Iterator
		 * ------------------------------
		 * This interface defines a nested class within the Map template that
		 * provides iterator access to the keys contained in the Map.  
		 *
		 * The idiomatic code for accessing elements using an iterator is
		 * to create the iterator from the collection and then enter a loop
		 * that calls next() while hasNext() is true, like this:
		 *
		 *	Map<int>::Iterator itr = map.iterator();
		 *  while (itr.hasNext())
		 *      string key = itr.next();
		 */
		class Iterator {
			public:
				Iterator(); 
				bool hasNext();
				string next();
			
			private:
				Iterator(Map *mp);
				Map *mp;
				Vector<string> keys;
				int curIndex;
				friend class Map;
		};
		friend class Iterator;
		
			
		/*
		 * Deep copying support
		 * --------------------
		 * This copy constructor and operator= are defined to make a
		 * deep copy, making it possible to pass/return maps by value
		 * and assign from one map to another. The entire contents of 
		 * the map, including all entries, are copied. Each map
		 * entry is copied from the original map to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, maps are typically passed by 
		 * reference, however, when a copy is needed, these operations 
		 * are supported.
		 */
		const Map &operator=(const Map &rhs);
		Map(const Map &rhs);
		
		private:	
			struct cell {
				string key;
				ValueType value;
				cell *next;
			};
			
			Vector<cell *> buckets;	
			int numEntries;
	
			void initBuckets(int nBuckets);
			void deleteBuckets(Vector<cell *> &bucketsToDelete);
			int hash(string s);
			cell *findCell(cell *head, string key, cell **prev = NULL);
			void expandAndRehash();
			void copyOtherEntries(const Map &rhs);
	};
	

/* 
 * Because of the way C++ templates are compiled, we must put the class implementation in
 * the header file. This is a bit quirky and seems to contradict the principles of
 * encapsulation and abstraction. As a client of this class, you don't need to know
 * anything about the internals and shouldn't depend on any implementation details. In
 * fact, you probably should just stop reading right here!
 */
 


/*
 * Class: Map
 * -------------
 * In this mapimplementation, the entries are stored in a hashtable.
 * The hashtable keeps a vector of "buckets", where each bucket is a linked list
 * of elements that share the same hash code (i.e. hash collisions are resolved
 * by chaining). The buckets are dynamically allocated so that we can change the
 * the number of buckets (rehash) when the load factor becomes too high. The
 * map should provide O(1) performance on the add/remove/getValue operations.
 */


template <typename ValueType>
  Map<ValueType>::Map(int sizeHint)
	{
	  if (sizeHint < 0) Error("Negative sizeHint given to Map constructor");
		initBuckets(sizeHint);
	}

template <typename ValueType>
  Map<ValueType>::~Map()
	{
		deleteBuckets(buckets);
	}

template <typename ValueType>
  int Map<ValueType>::size()
	{
	    return numEntries;
	}

template <typename ValueType>
  bool Map<ValueType>::isEmpty()
	{
	    return (size() == 0);
	}

template <typename ValueType>
  void Map<ValueType>::add(string key, ValueType value)
	{
		(*this)[key] = value;	// adds entry if not present
	}

template <typename ValueType>
  void Map<ValueType>::remove(string key)
	{
	   	int hashCode = hash(key);
	   	cell *prev, *found = findCell(buckets[hashCode], key, &prev);
		if (found != NULL) {
			if (prev != NULL) 
				prev->next = found->next;	 // splice out of list if in middle
			else 
				buckets[hashCode] = found->next;	// remove head node if first
			numEntries--;
			delete found;
		}
	}

template <typename ValueType>
  void Map<ValueType>::clear()
	{
	   	deleteBuckets(buckets);
		numEntries = 0;
	}


template <typename ValueType>
  bool Map<ValueType>::containsKey(string key)
	{
		int hashCode = hash(key);
		return (findCell(buckets[hashCode], key) != NULL);
	}
	

template <typename ValueType>
  ValueType Map<ValueType>::getValue(string key)
	{
		if (containsKey(key))
			return (*this)[key];
		Error("Attempt to getValue for key which is not contained in map.");
		return ValueType();	// this code is never reached, but here to placate compiler
	}


template <typename ValueType> 
  ValueType & Map<ValueType>::operator[](string key)
	{
		int hashCode = hash(key);
		cell *cp = findCell(buckets[hashCode], key);
		if (cp == NULL) {
		    if (numEntries > buckets.size()*2) expandAndRehash();
		    hashCode = hash(key); // num buckets has changed
			cp = new cell;
			cp->key = key;
			cp->next = buckets[hashCode];
			buckets[hashCode] = cp;
			numEntries++;
		}
		return cp->value;
	}

template <typename ValueType> 
  const Map<ValueType> &Map<ValueType>::operator=(const Map &rhs) 
	{
		if (this != &rhs) {
			deleteBuckets(buckets);
    		copyOtherEntries(rhs);
		}
		return *this;
	}		 

template <typename ValueType> 
  Map<ValueType>::Map(const Map &rhs)
	{
    	copyOtherEntries(rhs);
	}	


template <typename ValueType> 
  template <typename ClientData>
	void Map<ValueType>::mapAll(void (*fn)(string key, ValueType value, ClientData &cd), ClientData &data)
	{	
		for (int i =0 ; i < buckets.size(); i++)
			for (cell *cp = buckets[i]; cp != NULL; cp = cp->next)
				fn(cp->key, cp->value, data);	
	}
	
	
template <typename ValueType> 
  void Map<ValueType>::mapAll(void (*fn)(string key, ValueType value))
	{	
		for (int i =0 ; i < buckets.size(); i++)
			for (cell *cp = buckets[i]; cp != NULL; cp = cp->next)
				fn(cp->key, cp->value);	
	}
	


/* Private member functions */


/*
 * Private member function: deleteBuckets
 * Usage: deleteBuckets(buckets);
 * ------------------------------
 * This function deletes all the cells in the linked lists contained in vector.
 */

template <typename ValueType>
  void Map<ValueType>::deleteBuckets(Vector<cell *> &b)
	{
		for (int i = 0; i < b.size(); i++) {
		    while (b[i] != NULL) {
		        cell *next = b[i]->next;
		        delete b[i];
		        b[i] = next;
		    }
	    }
	}

/*
 * Private member function: findCell
 * Usage: cp = findCell(cp, key, &prev);
 * -------------------------------------
 * This function finds a cell in the chain beginning at cp that
 * matches key.  If a match is found, a pointer to that cell is
 * returned.  If no match is found, the function returns NULL.
 * The optional third argument is a pointer to the previous cell
 * pointer, which the client may need if attempting to splice out
 * the found cell. If not specified, NULL is the default value.
 */
template <typename ValueType>
  typename Map<ValueType>::cell 
         *Map<ValueType>::findCell(cell *cp, string key, cell **prevByRef)
	{
		cell *prev = NULL;
	    while (cp != NULL && key != cp->key) {
	    	prev = cp;
	        cp = cp->next;
	    }
	    if (prevByRef != NULL) *prevByRef = prev;
	    return (cp);
	}


/*
 * Private member function: hash
 * Usage: bucket = hash(key);
 * --------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is an integer in the range [0, buckets.size() - 1].  The hash
 * code is computed using a method called linear congruence.
 */
template <typename ValueType>
  int Map<ValueType>::hash(string s)
	{
		const long Multiplier = -1664117991;
	    unsigned long hashcode = 0;
	    for (string::size_type i = 0; i < s.length(); i++) {
	        hashcode = hashcode * Multiplier + s[i];
	    }
	    return (hashcode % buckets.size());
	}



/*
 * Private member function: expandAndRehash
 * Usage: expandAndRehash();
 * -------------------------
 * This member function is used to increase the number of buckets in the map
 * and then rehashes all existing entries and adds them into new buckets.  This
 * operation is used when the load factor (i.e. the number of cells per bucket)
 * has increased enough to warrant this O(N) operation to enlarge and redistribute
 * the entries.
 */
template <typename ValueType>
  void Map<ValueType>::expandAndRehash()
	{
		Vector<cell *>oldBuckets = buckets;	// make copy of existing buckets
		initBuckets(oldBuckets.size()*2 + 1); 	// make bigger array of empty buckets
	    for (int i = 0; i < oldBuckets.size(); i++)
	        for (cell *cp = oldBuckets[i]; cp != NULL; cp = cp->next)
	            add(cp->key, cp->value);	// add all old cells into new buckets
	    deleteBuckets(oldBuckets);			// delete previous cells
	}

		
/*
 * Private member function: initBuckets
 * Usage: initBuckets(101);
 * -----------------------
 * This member functions sets up the vector of buckets to have nBuckets
 * entries, each NULL. If asked to make empty vector, makes one bucket
 * just to simplify handling elsewhere.
 */
template <typename ValueType> 
  void Map<ValueType>::initBuckets(int nBuckets)
	{
	  if (nBuckets == 0) nBuckets = 1;
		buckets = Vector<cell *>(nBuckets);
    	for (int i = 0; i < nBuckets; i++) 
    		buckets.add(NULL);
        numEntries = 0;
	}	
	
	
template <typename ValueType>
  static void AddToMap(string key, ValueType val, Map<ValueType> &map)
	{
		map.add(key, val);
  	}
	
/*
 * Private member function: copyOtherEntries
 * Usage: copyOtherEntries(otherMap);
 * ----------------------------------
 * This member functions adds a copy of all entries from the other map to
 * this one.
 */
template <typename ValueType> 
	void Map<ValueType>::copyOtherEntries(const Map &constRhs)
	{
		// We aren't really adhering to const. Even though the member functions
		// invoked on rhs don't modify it, they aren't marked const, and thus
		// trigger compiler problems. We cast away const-ness to avoid this
		// erroneous complaints. Sigh.
		Map &rhs = const_cast<Map &>(constRhs);
		initBuckets(rhs.size());
		rhs.mapAll<Map<ValueType> >(AddToMap, *this);	// add by using mapping function
	}	
		

		

	
/* 
 * Map::Iterator class implementation
 * ----------------------------------
 * The Iterator for Map tracks a pointer to the original Map and a vector containing
 * of the map keys that was assembled at the time of iteration creation.  The
 * iterator tracks an index into that vector that identifies the next key to return.
 * Each use of next() increments that index, hasNext() verifies the index < the vector's 
 * size. This is an example of an "offline" iterator because it copies the map's 
 * data, instead of accessing it in-place. This is a bit inefficient (since it copies)
 * but it makes the iterator simplier to write and sidesteps any problems where the 
 * client is modifying the map during iteration.
 */

template <typename ValueType> 
  Map<ValueType>::Iterator::Iterator()
	{
		mp = NULL;
	}

template <typename ValueType> 
  typename Map<ValueType>::Iterator Map<ValueType>::iterator()
	{ 
		return Iterator(this);
	}

		

template <typename ValueType>
  static void AddToVector(string key, ValueType val, Vector<string> &vec)
	{
		vec.add(key);
	}
	
template <typename ValueType> 
  Map<ValueType>::Iterator::Iterator(Map *mapptr) : keys(mapptr->size())
	{
		mp = mapptr;
		mp->mapAll<Vector<string> >(AddToVector, keys);
		curIndex = 0;
	}

template <typename ValueType> 
  bool Map<ValueType>::Iterator::hasNext() 
	{
		if (mp == NULL) Error("hasNext called on uninitialized iterator");
		 return curIndex < keys.size();
	}

template <typename ValueType> 
  string Map<ValueType>::Iterator::next() 
	{
		if (mp == NULL) Error("next called on uninitialized iterator");
		if (!hasNext()) Error("Attempt to get next from iterator where hasNext() is false");
		return keys[curIndex++];
	}
	
#endif // _map_h_
