/*
 * File: hashmappriv.h
 * -------------------
 * This file contains the private section of the hashmap.h interface.
 */

/*
 * Implementation notes:
 * ---------------------
 * The HashMap class is represented using a hash table that uses
 * bucket chaining to resolve collisions.
 */

private:

/* Constant definitions */

   static const int INITIAL_BUCKET_COUNT = 101;
   static const int MAX_LOAD_PERCENTAGE = 70;

/* Type definition for cells in the bucket chain */

   struct Cell {
      KeyType key;
      ValueType value;
      Cell *next;
   };

/* Instance variables */

   Vector<Cell *> buckets;
   int nBuckets;
   int numEntries;

/* Private methods */

/*
 * Private method: createBuckets
 * Usage: createBuckets(nBuckets);
 * -------------------------------
 * Sets up the vector of buckets to have nBuckets entries, each NULL.
 * If asked to make empty vector, makes one bucket just to simplify
 * handling elsewhere.
 */

   void createBuckets(int nBuckets) {
      if (nBuckets == 0) nBuckets = 1;
      buckets = Vector<Cell *>(nBuckets, NULL);
      this->nBuckets = nBuckets;
      numEntries = 0;
   }

/*
 * Private method: deleteBuckets
 * Usage: deleteBuckets(buckets);
 * ------------------------------
 * Deletes all the cells in the linked lists contained in vector.
 */

   void deleteBuckets(Vector <Cell *> & buckets) {
      for (int i = 0; i < buckets.size(); i++) {
         Cell *cp = buckets[i];
         while (cp != NULL) {
            Cell *np = cp->next;
            delete cp;
            cp = np;
         }
         buckets[i] = NULL;
      }
   }

/*
 * Private method: expandAndRehash
 * Usage: expandAndRehash();
 * -------------------------
 * This method is used to increase the number of buckets in the map
 * and then rehashes all existing entries and adds them into new buckets.
 * This operation is used when the load factor (i.e. the number of cells
 * per bucket) has increased enough to warrant this O(N) operation to
 * enlarge and redistribute the entries.
 */

   void expandAndRehash() {
      Vector<Cell *>oldBuckets = buckets;
      createBuckets(oldBuckets.size() * 2 + 1);
      for (int i = 0; i < oldBuckets.size(); i++) {
         for (Cell *cp = oldBuckets[i]; cp != NULL; cp = cp->next) {
            put(cp->key, cp->value);
         }
      }
      deleteBuckets(oldBuckets);
   }

/*
 * Private method: findCell
 * Usage: Cell *cp = findCell(bucket, key);
 *        Cell *cp = findCell(bucket, key, parent);
 * ------------------------------------------------
 * Finds a cell in the chain for the specified bucket that matches key.
 * If a match is found, the return value is a pointer to the cell containing
 * the matching key.  If no match is found, the function returns NULL.
 * If the optional third argument is supplied, it is filled in with the
 * cell preceding the matching cell to allow the client to splice out
 * the target cell in the delete call.  If parent is NULL, it indicates
 * that the cell is the first cell in the bucket chain.
 */

   Cell *findCell(int bucket, string key) const {
      Cell *dummy;
      return findCell(bucket, key, dummy);
   }

   Cell *findCell(int bucket, string key, Cell * & parent) const {
      parent = NULL;
      Cell *cp = buckets.get(bucket);
      while (cp != NULL && key != cp->key) {
         parent = cp;
         cp = cp->next;
      }
      return cp;
   }

   void copyInternalData(const HashMap & rhs) {
      createBuckets(rhs.size());
      for (int i = 0; i < rhs.nBuckets; i++) {
         for (Cell *cp = rhs.buckets.get(i); cp != NULL; cp = cp->next) {
            put(cp->key, cp->value);
         }
      }
   }

public:

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return maps by value
 * and assign from one map to another.
 */

   HashMap & operator=(const HashMap & rhs) {
      if (this != &rhs) {
         clear();
         delete[] buckets;
         copyInternalData(rhs);
      }
      return *this;
   }

   HashMap(const HashMap & rhs) {
      copyInternalData(rhs);
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag, KeyType> {

   private:

      const HashMap *mp;           /* Pointer to the map           */
      int bucket;                  /* Index of current bucket      */
      Cell *cp;                    /* Current cell in bucket chain */

   public:

      iterator() {
        /* Empty */
      }

      iterator(const HashMap *mp, bool end) {
         this->mp = mp;
         if (end) {
            bucket = mp->nBuckets;
            cp = NULL;
         } else {
            bucket = 0;
            cp = mp->buckets.get(bucket);
            while (cp == NULL && ++bucket < mp->nBuckets) {
               cp = mp->buckets.get(bucket);
            }
         }
      }

      iterator(const iterator & it) {
         mp = it.mp;
         bucket = it.bucket;
         cp = it.cp;
      }

      iterator & operator++() {
         cp = cp->next;
         while (cp == NULL && ++bucket < mp->nBuckets) {
            cp = mp->buckets.get(bucket);
         }
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return mp == rhs.mp && bucket == rhs.bucket && cp == rhs.cp;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      KeyType operator*() {
         return cp->key;
      }

      friend class HashMap;

   };

   iterator begin() const {
      return iterator(this, false);
   }

   iterator end() const {
      return iterator(this, true);
   }
