/*
 * File: hashmapimpl.cpp
 * Last modified on Wed Dec 14 10:16:54 2011 by eroberts
 * -----------------------------------------------------
 * This file contains the private section of the hashmap.cpp interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _hashmap_h

/*
 * Implementation notes: HashMap class
 * -----------------------------------
 * In this map implementation, the entries are stored in a hashtable.
 * The hashtable keeps a vector of "buckets", where each bucket is a
 * linked list of elements that share the same hash code (i.e. hash
 * collisions are resolved by chaining). The buckets are dynamically
 * allocated so that we can change the the number of buckets (rehash)
 * when the load factor becomes too high. The map should provide O(1)
 * performance on the put/remove/get operations.
 */

template <typename KeyType,typename ValueType>
HashMap<KeyType,ValueType>::HashMap() {
   createBuckets(INITIAL_BUCKET_COUNT);
}

template <typename KeyType,typename ValueType>
HashMap<KeyType,ValueType>::~HashMap() {
   deleteBuckets(buckets);
}

template <typename KeyType,typename ValueType>
int HashMap<KeyType,ValueType>::size() const {
   return numEntries;
}

template <typename KeyType,typename ValueType>
bool HashMap<KeyType,ValueType>::isEmpty() const {
   return size() == 0;
}

template <typename KeyType,typename ValueType>
void HashMap<KeyType,ValueType>::put(KeyType key, ValueType value) {
   (*this)[key] = value;
}

template <typename KeyType,typename ValueType>
ValueType HashMap<KeyType,ValueType>::get(KeyType key) const {
   Cell *cp = findCell(hashCode(key) % nBuckets, key);
   if (cp == NULL) {
      error("Attempt to get value for key which is not contained in map.");
   }
   return cp->value;
}

template <typename KeyType,typename ValueType>
bool HashMap<KeyType,ValueType>::containsKey(KeyType key) const {
   return findCell(hashCode(key) % nBuckets, key) != NULL;
}

template <typename KeyType,typename ValueType>
void HashMap<KeyType,ValueType>::remove(KeyType key) {
   int bucket = hashCode(key) % nBuckets;
   Cell *parent;
   Cell *cp = findCell(bucket, key, parent);
   if (cp != NULL) {
      if (parent == NULL) {
         buckets[bucket] = cp->next;
      } else {
         parent->next = cp->next;
      }
      delete cp;
      numEntries--;
   }
}

template <typename KeyType,typename ValueType>
void HashMap<KeyType,ValueType>::clear() {
   deleteBuckets(buckets);
   numEntries = 0;
}

template <typename KeyType,typename ValueType>
ValueType & HashMap<KeyType,ValueType>::operator[](KeyType key) {
   int bucket = hashCode(key) % nBuckets;
   Cell *cp = findCell(bucket, key);
   if (cp == NULL) {
      if (numEntries > MAX_LOAD_PERCENTAGE * nBuckets / 100.0) {
         expandAndRehash();
      }
      cp = new Cell;
      cp->key = key;
      cp->value = ValueType();
      cp->next = buckets[bucket];
      buckets[bucket] = cp;
      numEntries++;
   }
   return cp->value;
}

template <typename KeyType,typename ValueType>
template <typename ClientData>
void HashMap<KeyType,ValueType>::mapAll(void (*fn)(KeyType, ClientData &),
                                        ClientData & data) {
   for (int i = 0 ; i < buckets.size(); i++) {
      for (Cell *cp = buckets[i]; cp != NULL; cp = cp->next) {
         fn(cp->key, data);
      }
   }
}

template <typename KeyType,typename ValueType>
void HashMap<KeyType,ValueType>::mapAll(void (*fn)(KeyType key)) {
   for (int i = 0 ; i < buckets.size(); i++) {
      for (Cell *cp = buckets[i]; cp != NULL; cp = cp->next) {
         fn(cp->key);
      }
   }
}

#endif
