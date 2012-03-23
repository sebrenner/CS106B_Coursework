/*
 * File: mappriv.h
 * ---------------
 * This file contains the private section of the map.h interface.
 */

/*
 * Implementation notes:
 * ---------------------
 * The map class is represented using a binary search tree.  The
 * specific implementation used here is the classic AVL algorithm
 * developed by Georgii Adel'son-Vel'skii and Evgenii Landis in 1962.
 */

private:

/* Constant definitions */

   static const int BST_RIGHT_HEAVY = +1;
   static const int BST_IN_BALANCE = 0;
   static const int BST_LEFT_HEAVY = -1;

/* Type definition for nodes in the binary search tree */

   struct BSTNode {
      KeyType key;             /* The key stored in this node         */
      ValueType value;         /* The corresponding value             */
      BSTNode *left;           /* Subtree containing all smaller keys */
      BSTNode *right;          /* Subtree containing all larger keys  */
      int bf;                  /* AVL balance factor                  */
   };

/* Instance variables */

   BSTNode *root;                  /* Pointer to the root of the tree */
   int nodeCount;                  /* Number of entries in the map    */
   int (*cmpFn)(KeyType, KeyType); /* Function used to compare keys   */

/* Private method prototypes */

   ValueType *findNode(BSTNode *t, KeyType & key) const;
   ValueType *addNode(BSTNode * & t, KeyType & key, bool & heightChanged);
   bool removeNode(BSTNode * & t, KeyType & key);
   bool removeTargetNode(BSTNode * & t);
   void updateBF(BSTNode * & t, int bfDelta);
   void fixLeftImbalance(BSTNode * & t);
   void rotateLeft(BSTNode * & t);
   void fixRightImbalance(BSTNode * & t);
   void rotateRight(BSTNode * & t);
   void deleteTree(BSTNode *t);
   void mapAll(BSTNode *t, void (*fn)(KeyType));
   template <typename ClientDataType>
   void mapAll(BSTNode *t, void (*fn)(KeyType), ClientDataType & data);

   void copyInternalData(const Map & other) {
      root = copyTree(other.root);
      nodeCount = other.nodeCount;
      cmpFn = other.cmpFn;
   }

   BSTNode *copyTree(BSTNode * const t) {
      if (t == NULL) return NULL;
      BSTNode *np = new BSTNode();
      np->key = t->key;
      np->value = t->value;
      np->bf = t->bf;
      np->left = copyTree(t->left);
      np->right = copyTree(t->right);
      return np;
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

   Map & operator=(const Map & rhs) {
      if (this != &rhs) {
         clear();
         copyInternalData(rhs);
      }
      return *this;
   }

   Map(const Map & rhs) {
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

      struct NodeMarker {
         BSTNode *np;
         bool processed;
      };

      const Map *mp;               /* Pointer to the map         */
      int index;                   /* Index of current element   */
      Stack<NodeMarker> stack;     /* Stack of unprocessed nodes */

      void findLeftmostChild() {
         BSTNode *np = stack.peek().np;
         if (np == NULL) return;
         while (np->left != NULL) {
            NodeMarker marker = { np->left,  false };
            stack.push(marker);
            np = np->left;
         }
      }

   public:

      iterator() {
        /* Empty */
      }

      iterator(const Map *mp, bool end) {
         this->mp = mp;
         if (end || mp->nodeCount == 0) {
            index = mp->nodeCount;
         } else {
            index = 0;
            NodeMarker marker = { mp->root, false };
            stack.push(marker);
            findLeftmostChild();
         }
      }

      iterator(const iterator & it) {
         mp = it.mp;
         index = it.index;
         stack = it.stack;
      }

      iterator & operator++() {
         NodeMarker marker = stack.pop();
         BSTNode *np = marker.np;
         if (np->right == NULL) {
            while (!stack.isEmpty() && stack.peek().processed) {
               stack.pop();
            }
         } else {
            marker.processed = true;
            stack.push(marker);
            marker.np = np->right;
            marker.processed = false;
            stack.push(marker);
            findLeftmostChild();
         }
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return mp == rhs.mp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      KeyType operator*() {
         return stack.peek().np->key;
      }

      friend class Map;

   };

   iterator begin() const {
      return iterator(this, false);
   }

   iterator end() const {
      return iterator(this, true);
   }
