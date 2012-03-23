/*
 * File: bst.h
 * -----------
 * This interface file contains the BST class template, an 
 * implementation of a general binary search tree.
 *
 * Last updated: Tue Jan  2 14:23:33 PST 2007 by zelenski
 */

#ifndef _bst_h
#define _bst_h

#include "cmpfn.h"
#include "vector.h"

/*
 * Class: BST
 * ----------
 * This interface defines a class template for a binary search tree.
 * For maximum generality, the BST is supplied as a class template. 
 * The element type is set by the client. The client specializes 
 * the tree for specific type, e.g. BST<int> or BST<studentT>.
 * The one requirement on the element type is that the client must
 * supply a comparison fn that compares two elements (or be willing 
 * to use the default comparison function that relies on < and ==).
 */

template <typename ElemType>
  class BST {
    public:

		/*
		 * Constructor: BST
		 * Usage: BST<int> bst;
		 *        BST<song> songs(CompareSong)
		 *        BST<string> *bp = new BST<string>;
		 * -----------------------------------------
		 * The constructor initializes a new empty binary search tree.
		 * The one argument is a comparison function, which is called
		 * to compare data values.  This argument is optional, if not
		 * given, the OperatorCmp function from cmpfn.h is used, which
		 * applies the built-in operator < to its operands. If the
		 * behavior of < on your ElemType is defined and sufficient,
		 * you do not need to supply your own comparison function.
		 */
		BST(int (cmpFn)(ElemType one, ElemType two) = OperatorCmp);


		/*
		 * Destructor: ~BST
		 * Usage: delete bp;
		 * ------------------
		 * The destructor deallocates storage for this tree.
		 */
		~BST();


	  	/*
		 * Member function: size
		 * Usage: count = bst.size();
		 * --------------------------
		 * This member function returns the number of elements in 
		 * this tree.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (bst.isEmpty())...
		 * ----------------------------
		 * This member function returns true if this tree contains no
		 * elements, false otherwise.
		 */
		 bool isEmpty();


		/*
		 * Member function: find
		 * Usage:  if (bst.find(key) != NULL)...
		 * ---------------------------------------
		 * This member function applies the binary search algorithm to 
		 * find a particular key in this tree.  The second argument is 
		 * the key to use for comparison. If a node matching key appears 
		 * in the tree, find returns a pointer to the data in that node; 
		 * otherwise, find returns NULL.
		 */
		ElemType *find(ElemType key);


		/*
		 * Member function: add
		 * Usage: bst.add(val);
		 * --------------------
		 * This member function adds a new node to this tree. The elem 
		 * argument is compared with the data in existing nodes to find 
		 * the proper position. If a node with the same value already 
		 * exists, the contents are overwritten with the new copy and 
		 * false is returned.  If no matching node is found, a new node 
		 * is allocated and added to the tree, true is returned.
		 */
		bool add(ElemType elem);


		/*
		 * Member function: remove
		 * Usage: bst.remove(key);
		 -------------------------
		 * This member function removes a node in this tree that matches 
		 * the specified key. If a node matching key is found, the node 
		 * is removed from the tree and true is returned. If no match 
		 * is found, no changes are made and false is returned.
		 */
		bool remove(ElemType key);


		/*
		 * Member function: clear
		 * Usage: bst.clear();
		 * -------------------
		 * This member function removes all elements from this tree. The 
		 * tree is made empty and will have no nodes after being cleared.
		 */	
		void clear();
		
		/*
		 * Member function: mapAll
		 * Usage: bst.mapAll(Print);
		 * -------------------------
		 * This member function iterates through this tree and calls the 
		 * function fn once for each element. The order is determined by an 
		 * InOrder walk of the tree.
		 */
		void mapAll(void (fn)(ElemType elem));
		

		/*
		 * Member function: mapAll
		 * Usage: bst.mapAll(PrintToFile, outputStream);
		 * ---------------------------------------------
		 * This member function iterates through this tree con
		 * and calls the function fn once for each element, passing
		 * the element and the client's data. That data can be of 
		 * whatever type is needed for the client's callback. The order 
		 * of calls is determined by an InOrder walk of the tree.
		 */
		template <typename ClientDataType>
			void mapAll(void (fn)(ElemType elem, ClientDataType &data),
							ClientDataType &data);

		/*
		 * Deep copying support
		 * --------------------
		 * This copy constructor and operator= are defined to make a
		 * deep copy, making it possible to pass/return trees by value
		 * and assign from one tree to another. The entire contents of 
		 * the tree, including all elements, are copied. Each tree
		 * element is copied from the original tree to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, trees are typically passed 
		 * by reference, however, when a copy is needed, these operations 
		 * are supported.
		 */
		const BST &operator=(const BST &rhs);
		BST(const BST &rhs);
				
	private:

		struct nodeT {
		    ElemType data;
		    nodeT *left, *right;
		    int bf;	// AVL balance factor
		};

		nodeT *root;
		int numNodes;
		int (*cmpFn)(ElemType, ElemType);
		
		static const int RightHeavy = +1;
		static const int Even = 0;
		static const int LeftHeavy = -1;

		nodeT *recFindNode(nodeT * t, ElemType & key);
		bool recAddNode(nodeT * & t, ElemType & key, bool &createdNewNode);
		bool recRemoveNode(nodeT * &, ElemType & key, bool & didRemove);
		bool removeTargetNode(nodeT * & t);
		void updateBF(nodeT * &t, int bfDelta);
		void recDeleteTree(nodeT * t);
		void recMapAll(nodeT * t, void (fn)(ElemType));
		template <typename ClientDataType>
		void recMapAll(nodeT * t, void (fn)(ElemType, ClientDataType &), ClientDataType &);
		void fixRightImbalance(nodeT * &t);
		void fixLeftImbalance(nodeT * &t);
		void rotateRight(nodeT * &t);
		void rotateLeft(nodeT * &t);
		void copyOtherEntries(const BST &other);
};


#include <cstdlib> // NULL

template <typename ElemType>
  BST<ElemType>::BST(int (cmp)(ElemType, ElemType))
	{
	    root = NULL;
	    cmpFn = cmp;
		numNodes = 0;
	}

template <typename ElemType>
  BST<ElemType>::~BST()
	{
	    recDeleteTree(root);
	}

template <typename ElemType>
  void BST<ElemType>::recDeleteTree(nodeT * t)
	{
	    if (t != NULL) {
			recDeleteTree(t->left);
			recDeleteTree(t->right);
			delete t;
	  	}	
	}
	
template <typename ElemType>
  int BST<ElemType>::size()
	{
	    return (numNodes);
	}

template <typename ElemType>
  bool BST<ElemType>::isEmpty()
	{
	    return (root == NULL);
	}


template <typename ElemType>
  void BST<ElemType>::clear()
	{
	    recDeleteTree(root);
		root = NULL;
		numNodes = 0;
	}


/*
 * Implementation notes: find, recFindNode
 * ----------------------------------------------
 * The rind function simply calls recFindNode to do
 * the work.  The recursive function takes the current
 * node along with the original argument. If found, 
 * it overwrites the reference parameter with the copy
 * and returns a pointer to the data.
 */

template <typename ElemType>
  ElemType *BST<ElemType>::find(ElemType key)
	{
	    nodeT * found = recFindNode(root, key);
	    if (found != NULL) {
	    	return (&found->data);
	    }
	    return (NULL);
	}

template <typename ElemType>
  typename BST<ElemType>::nodeT * BST<ElemType>::recFindNode(nodeT * t, 
                                                       ElemType & key)
	{
	    if (t == NULL) return (NULL);
	    int sign = cmpFn(key, t->data);
	    if (sign == 0) return (t);
	    if (sign < 0) {
	        return (recFindNode(t->left, key));
	    } else {
	        return (recFindNode(t->right, key));
	    }
	}

/*
 * Implementation notes: add, recAddNode
 * -------------------------------------------
 * The add member function is implemented as a simple wrapper
 * to recAddNode, which does all the work.  The difference
 * between the prototypes is that recAddNode takes a reference
 * to the root of the current subtree as an extra argument.
 * For reasons of efficiency (we don't know how large ElemType
 * might be), we pass it by reference.
 * The return value from recAddNode is true or false, depending on
 * whether the height of the subtree was increased by one or not.
 * At base case, returns true for new node, false for overwite. As
 * it works its way upwards, if that additional height is added to
 * to existing balanace factor and results in factor that is
 * more than +- 1, then a rotation is done to fix the imbalance.
 */
 
template <typename ElemType>
  bool BST<ElemType>::add(ElemType data)
	{
	    bool createdNewNode = false;
	    recAddNode(root, data, createdNewNode);
	    return (createdNewNode);
	}


// returns true if height at t has increased, false otherwise
template <typename ElemType>
  bool BST<ElemType>::recAddNode(nodeT * & t, ElemType & data, bool &createdNewNode)
	{
	    if (t == NULL) {
	        t = new nodeT;
	        t->data = data;
	        t->bf = Even;
	        t->left = t->right = NULL;
	        createdNewNode = true;
			numNodes++;
	        return (true);
	    }
	    int sign = cmpFn(data, t->data);
	    if (sign == 0) {
			t->data = data;
	    	createdNewNode = false;
	    	return (false);
		}
		int bfDelta = 0;
	    if (sign < 0) {
	        if (recAddNode(t->left, data, createdNewNode))
	        	bfDelta = -1;	// inserted node has caused increase in left subtree height
	    } else {
	        if (recAddNode(t->right, data, createdNewNode))
	        	bfDelta = +1;	// inserted node has caused increase in right subtree height
	    }
	    updateBF(t, bfDelta); // adds height change and rebalances if necessary
	    // height of t increased iff subtree increased and this node ended heavy
	    return (bfDelta != 0 && t->bf != Even);
	}


/*
 * Function: updateBF
 * Usage: updateBF(t, 1);
 * ----------------------
 */
template <typename ElemType>
  void BST<ElemType>::updateBF(nodeT * & t, int bfDelta)
	{
	    t->bf += bfDelta;	// add height change to existing balance factor
	    if (t->bf < LeftHeavy) 
	    	fixLeftImbalance(t);
	    else if (t->bf > RightHeavy) 
	    	fixRightImbalance(t);
	}

/*
 * Function: fixLeftImbalance
 * Usage: fixLeftImbalance(t);
 * ---------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the left.
 * Depending on the balance factor of the left child, the
 * code performs a single or double rotation.
 */

template <typename ElemType>
  void BST<ElemType>::fixLeftImbalance(nodeT * & t)
	{
	    nodeT * child = t->left;

	    if (child->bf == RightHeavy) {
	        int oldBF = child->right->bf;
	        rotateLeft(t->left);
	        rotateRight(t);
	        t->bf = Even;
	        switch (oldBF) {
	          case LeftHeavy: t->left->bf = Even; t->right->bf = RightHeavy; break;
	          case Even: t->left->bf = t->right->bf = Even; break;
	          case RightHeavy: t->left->bf = LeftHeavy; t->right->bf = Even; break;
	        }
	    } else if (child->bf == Even) {
	        rotateRight(t);
	        t->bf = RightHeavy;
	        t->right->bf = LeftHeavy;
	    } else {	
	        rotateRight(t);
	        t->right->bf = t->bf = Even;
	    }
	}

/*
 * Function: rotateLeft
 * Usage: rotateLeft(t);
 * ---------------------
 * This function performs a single left rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */
template <typename ElemType>
  void BST<ElemType>::rotateLeft(nodeT * & t)
	{
	    nodeT * child = t->right;
	    t->right = child->left;
	    child->left = t;
	    t = child;
	}


/*
 * Function: fixRightImbalance
 * Usage: fixRightImbalance(t);
 * ---------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the right.
 * Depending on the balance factor of the right child, the
 * code performs a single or double rotation.
 */
template <typename ElemType>
  void BST<ElemType>::fixRightImbalance(nodeT * & t)
	{
	    nodeT * child = t->right;
	    
	    if (child->bf == LeftHeavy) {
	        int oldBF = child->left->bf;
	        rotateRight(t->right);
	        rotateLeft(t);
	        t->bf = Even;
	        switch (oldBF) {
	          case LeftHeavy: t->left->bf = Even; t->right->bf = RightHeavy; break;
	          case Even: t->left->bf = t->right->bf = Even; break;
	          case RightHeavy: t->left->bf = LeftHeavy; t->right->bf = Even; break;
	        }
	     } else if (child->bf == Even) {
	        rotateLeft(t);
	        t->bf = LeftHeavy;
	        t->left->bf = RightHeavy;
	    } else {	
	        rotateLeft(t);
	        t->left->bf = t->bf = Even;
		}
	}

/*
 * Function: rotateRight
 * Usage: rotateRight(t);
 * ----------------------
 * This function performs a single right rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */
template <typename ElemType>
  void BST<ElemType>::rotateRight(nodeT * & t)
	{
	    nodeT * child = t->left;
	    t->left = child->right;
	    child->right = t;
	    t = child;
	}



 /*
 * Implementation notes: remove, recRemoveNode
 * -------------------------------------------
 * The first step in removing a node is to find it using binary
 * search, which is performed by these two functions.  If the
 * node is found, RemoveTargetNode does the actual deletion.
 */
template <typename ElemType>
  bool BST<ElemType>::remove(ElemType data)
	{
	    bool didRemove = false;
	    recRemoveNode(root, data, didRemove);
	    return (didRemove);
	}




// returns change in size of tree rooted at t
// 0, if same height as before, -1 if height decreases
template <typename ElemType>
  bool BST<ElemType>::recRemoveNode(nodeT * & t, ElemType & data, bool & didRemove)
	{
	    if (t == NULL) 
	    	return (false);
	    int sign = cmpFn(data, t->data);
	    if (sign == 0) {
	    	didRemove = true;
	        return (removeTargetNode(t));
	    } 
	    int bfDelta = 0;
	    if (sign < 0) {
	    	if (recRemoveNode(t->left, data, didRemove))
	    		bfDelta = +1;
	    } else {
	    	if (recRemoveNode(t->right, data, didRemove))
	    		bfDelta = -1;
		}
	    updateBF(t, bfDelta);
	    // height decreased iff subtree decreased and this node ended even
	    return (bfDelta != 0 && t->bf == Even);
	}


    
/*
 * Implementation notes: removeTargetNode
 * --------------------------------------
 * This function removes the node which is passed by
 * reference as t.  The easy case occurs when either of the
 * children is NULL; all you need to do is replace the node with
 * its non-NULL child.  If both children are non-NULL, this code
 * finds the rightmost descendent of the left child; this node
 * may not be a leaf, but will have no right child.  Its left
 * child replaces it in the tree, after which the replacement
 * data is moved to the position occupied by the target node.
 */
template <typename ElemType>
  bool BST<ElemType>::removeTargetNode(nodeT *  & t)
	{
	    nodeT * toDelete = t;

	    if (t->left == NULL) {	// no left child, replace with right
	        t = t->right;
	        delete toDelete;
			numNodes--;
	        return (true);
	    } else if (t->right == NULL) {	// no right child, replace with left
	        t = t->left;
	        delete toDelete;
			numNodes--;
	        return (true);
	    } else {	// node has both children, replace with successor (max of left)
	    	nodeT * successor = t->left;
	    	while (successor->right != NULL)
	    		successor = successor->right;
	    	t->data = successor->data;	// copy over the data from succ node (it will be removed)
	    	bool unused;
	    	if (recRemoveNode(t->left, successor->data, unused)) {
	    		updateBF(t, 1); // decreased one on left
	    		return (t->bf == Even);
			} else
				return (false);
	    }
	}


/*
 * Implementation notes: mapAll, recMapAll
 * ----------------------------------------
 * The mapAll function is implemented as a wrapper to the
 * recursive function recMapAll, which does the actual work
 * of calling the function on all values during an InOrder walk.
 */
template <typename ElemType>
  void BST<ElemType>::mapAll(void (fn)(ElemType))
	{
	    recMapAll(root, fn);
	}

template <typename ElemType>
  void BST<ElemType>::recMapAll(nodeT * t, void (fn)(ElemType))
	{
	    if (t != NULL) {
	        recMapAll(t->left, fn);
	        fn(t->data);
	        recMapAll(t->right, fn);
	    }
	}
	
	
template <typename ElemType>
  template <typename ClientDataType>
	void BST<ElemType>::mapAll(void (fn)(ElemType, ClientDataType &), ClientDataType &data)
	{
	    recMapAll(root, fn, data);
	}


template <typename ElemType>
  template <typename ClientDataType>

	void BST<ElemType>::recMapAll(nodeT * t, void (fn)(ElemType, ClientDataType &), ClientDataType &data)
	{
	    if (t != NULL) {
	        recMapAll(t->left, fn ,data);
	        fn(t->data, data);
	        recMapAll(t->right, fn, data);
	    }
	}

template <typename ElemType> 
  const BST<ElemType> &BST<ElemType>::operator=(const BST &rhs) 
	{
		if (this != &rhs) {
			clear();
    		copyOtherEntries(rhs);
		}
		return *this;
	}		 

template <typename ElemType> 
  BST<ElemType>::BST(const BST &rhs)
	{
    	root = NULL;
    	copyOtherEntries(rhs);
	}	
	
template <typename ElemType> 
  static void AddToTree(ElemType elem, BST<ElemType> &tree)
	{
    	tree.add(elem);
	}	
	
	
/*
 * Private member function: copyOtherEntries
 * Usage: copyOtherEntries(otherMap);
 * ----------------------------------
 * This member functions adds a copy of all entries from the other map to
 * this one.
 */
template <typename ElemType> 
  void BST<ElemType>::copyOtherEntries(const BST &constRhs)
	{
		// We aren't really adhering to const. Even though the member functions
		// invoked on rhs don't modify it, they aren't marked const, and thus
		// trigger compiler problems. We cast away const-ness to avoid this
		// erroneous complaints. Sigh.
		BST &rhs = const_cast<BST &>(constRhs);
		cmpFn = rhs.cmpFn;
		
		// This is a workaround for a bug in Metrowerks C++ compiler.
		// It can't handle the dual-templated map function correctly, so
		// we have to manually map over the cells to copy. 
		rhs.mapAll<BST<ElemType> >(AddToTree, *this);	// add by using mapping function
		numNodes = rhs.numNodes;
	}	
		
#endif
