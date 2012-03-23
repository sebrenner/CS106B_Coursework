/*
 * File: mapimpl.cpp
 * -----------------
 * This file contains the private section of the map.cpp interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _map_h

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::Map(int (*cmpFn)(KeyType, KeyType)) {
   root = NULL;
   nodeCount = 0;
   this->cmpFn = cmpFn;
}

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::~Map() {
   deleteTree(root);
}

template <typename KeyType, typename ValueType>
int Map<KeyType,ValueType>::size() const {
   return nodeCount;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::isEmpty() const {
   return nodeCount == 0;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::put(KeyType key, ValueType value) {
   bool dummy;
   *addNode(root, key, dummy) = value;
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType,ValueType>::get(KeyType key) const {
   ValueType *vp = findNode(root, key);
   if (vp == NULL) {
      error("Attempt to get value for key which is not contained in map.");
   }
   return *vp;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::remove(KeyType key) {
   removeNode(root, key);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::clear() {
   deleteTree(root);
   root = NULL;
   nodeCount = 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::containsKey(KeyType key) const {
   return findNode(root, key) != NULL;
}

template <typename KeyType, typename ValueType>
ValueType & Map<KeyType,ValueType>::operator[](KeyType key) {
   bool dummy;
   return *addNode(root, key, dummy);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::mapAll(void (*fn)(KeyType)) {
   mapAll(root, fn);
}

template <typename KeyType, typename ValueType>
template <typename ClientData>
void Map<KeyType,ValueType>::mapAll(void (*fn)(KeyType, ClientData &),
                                    ClientData & data) {
   mapAll(root, fn, data);
}

/*
 * Implementation notes: findNode(t, key)
 * --------------------------------------
 * Searches the tree rooted at t to find the specified key, searching
 * in the left or right subtree, as approriate.  If a matching node
 * is found, findNode returns a pointer to the value cell in that node.
 * If no matching node exists in the tree, findNode returns NULL.
 */

template <typename KeyType, typename ValueType>
ValueType *Map<KeyType,ValueType>::findNode(BSTNode *t,
                                            KeyType & key) const {
   if (t == NULL)  return NULL;
   int sign = cmpFn(key, t->key);
   if (sign == 0) return &t->value;
   if (sign < 0) {
      return findNode(t->left, key);
   } else {
      return findNode(t->right, key);
   }
}

/*
 * Implementation notes: addNode(t, key, heightChanged)
 * ----------------------------------------------------
 * Searches the tree rooted at t to find the specified key, searching
 * in the left or right subtree, as approriate.  If a matching node
 * is found, addNode returns a pointer to the value cell in that node,
 * just like findNode.  If no matching node exists in the tree, addNode
 * creates a new node with a default value.  The heightChanged reference
 * parameter returns a bool indicating whether the height of the tree
 * was changed by this operation.
 */

template <typename KeyType, typename ValueType>
ValueType *Map<KeyType,ValueType>::addNode(BSTNode * & t,
                                           KeyType & key,
                                           bool & heightChanged) {
   heightChanged = false;
   if (t == NULL)  {
      t = new BSTNode();
      t->key = key;
      t->value = ValueType();
      t->bf = BST_IN_BALANCE;
      t->left = t->right = NULL;
      heightChanged = true;
      nodeCount++;
      return &t->value;
   }
   int sign = cmpFn(key, t->key);
   if (sign == 0) return &t->value;
   ValueType *vp = NULL;
   int bfDelta = BST_IN_BALANCE;
   if (sign < 0) {
      vp = addNode(t->left, key, heightChanged);
      if (heightChanged) bfDelta = BST_LEFT_HEAVY;
   } else {
      vp = addNode(t->right, key, heightChanged);
      if (heightChanged) bfDelta = BST_RIGHT_HEAVY;
   }
   updateBF(t, bfDelta);
   heightChanged = (bfDelta != 0 && t->bf != BST_IN_BALANCE);
   return vp;
}

/*
 * Implementation notes: removeNode(t, key)
 * ----------------------------------------
 * Removes the node containing the specified key from the tree rooted
 * at t.  The return value is true if the height of this subtree
 * changes.  The removeTargetNode method does the actual deletion.
 */

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::removeNode(BSTNode * & t, KeyType & key) {
   if (t == NULL) return false;
   int sign = cmpFn(key, t->key);
   if (sign == 0) return removeTargetNode(t);
   int bfDelta = BST_IN_BALANCE;
   if (sign < 0) {
      if (removeNode(t->left, key)) bfDelta = BST_RIGHT_HEAVY;
   } else {
      if (removeNode(t->right, key)) bfDelta = BST_LEFT_HEAVY;
   }
   updateBF(t, bfDelta);
   return bfDelta != 0 && t->bf == BST_IN_BALANCE;
}

/*
 * Implementation notes: removeTargetNode(t)
 * -----------------------------------------
 * Removes the node which is passed by reference as t.  The easy case
 * occurs when either (or both) of the children is NULL; all you need
 * to do is replace the node with its non-NULL child, if any.  If both
 * children are non-NULL, this code finds the rightmost descendent of
 * the left child; this node may not be a leaf, but will have no right
 * child.  Its left child replaces it in the tree, after which the
 * replacement data is moved to the position occupied by the target node.
 */

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::removeTargetNode(BSTNode * & t) {
   BSTNode *toDelete = t;
   if (t->left == NULL) {
      t = t->right;
      delete toDelete;
      nodeCount--;
      return true;
   } else if (t->right == NULL) {
      t = t->left;
      delete toDelete;
      nodeCount--;
      return true;
   } else {
      BSTNode *successor = t->left;
      while (successor->right != NULL) {
         successor = successor->right;
      }
      t->key = successor->key;
      t->value = successor->value;
      if (removeNode(t->left, successor->key)) {
         updateBF(t, BST_RIGHT_HEAVY);
         return (t->bf == BST_IN_BALANCE);
      }
      return false;
   }
}

/*
 * Implementation notes: updateBF(t, bfDelta)
 * ------------------------------------------
 * Updates the balance factor in the node and rebalances the tree
 * if necessary.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::updateBF(BSTNode * & t, int bfDelta) {
   t->bf += bfDelta;
   if (t->bf < BST_LEFT_HEAVY) {
      fixLeftImbalance(t);
   } else if (t->bf > BST_RIGHT_HEAVY) {
      fixRightImbalance(t);
   }
}

/*
 * Implementation notes: fixLeftImbalance(t)
 * -----------------------------------------
 * This function is called when a node has been found that is out
 * of balance with the longer subtree on the left.  Depending on
 * the balance factor of the left child, the code performs a
 * single or double rotation.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::fixLeftImbalance(BSTNode * & t) {
   BSTNode *child = t->left;
   if (child->bf == BST_RIGHT_HEAVY) {
      int oldBF = child->right->bf;
      rotateLeft(t->left);
      rotateRight(t);
      t->bf = BST_IN_BALANCE;
      switch (oldBF) {
       case BST_LEFT_HEAVY:
         t->left->bf = BST_IN_BALANCE;
         t->right->bf = BST_RIGHT_HEAVY;
         break;
       case BST_IN_BALANCE:
         t->left->bf = t->right->bf = BST_IN_BALANCE;
         break;
       case BST_RIGHT_HEAVY:
         t->left->bf = BST_LEFT_HEAVY;
         t->right->bf = BST_IN_BALANCE;
         break;
      }
   } else if (child->bf == BST_IN_BALANCE) {
      rotateRight(t);
      t->bf = BST_RIGHT_HEAVY;
      t->right->bf = BST_LEFT_HEAVY;
   } else {
      rotateRight(t);
      t->right->bf = t->bf = BST_IN_BALANCE;
   }
}

/*
 * Implementation notes: rotateLeft(t)
 * -----------------------------------
 * This function performs a single left rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::rotateLeft(BSTNode * & t) {
   BSTNode *child = t->right;
   t->right = child->left;
   child->left = t;
   t = child;
}

/*
 * Implementation notes: fixRightImbalance(t)
 * ------------------------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the right.
 * Depending on the balance factor of the right child, the
 * code performs a single or double rotation.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::fixRightImbalance(BSTNode * & t) {
   BSTNode *child = t->right;
   if (child->bf == BST_LEFT_HEAVY) {
      int oldBF = child->left->bf;
      rotateRight(t->right);
      rotateLeft(t);
      t->bf = BST_IN_BALANCE;
      switch (oldBF) {
       case BST_LEFT_HEAVY:
         t->left->bf = BST_IN_BALANCE;
         t->right->bf = BST_RIGHT_HEAVY;
         break;
       case BST_IN_BALANCE:
         t->left->bf = t->right->bf = BST_IN_BALANCE;
         break;
       case BST_RIGHT_HEAVY:
         t->left->bf = BST_LEFT_HEAVY;
         t->right->bf = BST_IN_BALANCE;
         break;
      }
   } else if (child->bf == BST_IN_BALANCE) {
      rotateLeft(t);
      t->bf = BST_LEFT_HEAVY;
      t->left->bf = BST_RIGHT_HEAVY;
   } else {
      rotateLeft(t);
      t->left->bf = t->bf = BST_IN_BALANCE;
   }
}

/*
 * Implementation notes: rotateRight(t)
 * ------------------------------------
 * This function performs a single right rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::rotateRight(BSTNode * & t) {
   BSTNode *child = t->left;
   t->left = child->right;
   child->right = t;
   t = child;
}

/*
 * Implementation notes: deleteTree(t)
 * -----------------------------------
 * Deletes all the nodes in the tree.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::deleteTree(BSTNode *t) {
   if (t != NULL) {
      deleteTree(t->left);
      deleteTree(t->right);
      delete t;
   }
}

/*
 * Implementation notes: mapAll(t, fn)
 * -----------------------------------
 * Calls fn(key) on every key in the tree.
 */

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::mapAll(BSTNode *t, void (*fn)(KeyType)) {
   if (t != NULL) {
      mapAll(t->left, fn);
      fn(t->key);
      mapAll(t->right, fn);
   }
}

/*
 * Implementation notes: mapAll(t, fn, data)
 * -----------------------------------------
 * Calls fn(key, data) on every key in the tree.
 */

template <typename KeyType, typename ValueType>
template <typename ClientDataType>
void Map<KeyType,ValueType>::mapAll(BSTNode *t, void (*fn)(KeyType),
                                    ClientDataType & data) {
   if (t != NULL) {
      mapAll(t->left, fn, data);
      fn(t->key, data);
      mapAll(t->right, fn, data);
   }
}

#endif
