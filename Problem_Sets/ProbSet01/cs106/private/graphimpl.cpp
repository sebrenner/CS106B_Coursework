/*
 * File: graphimpl.cpp
 * -------------------
 * This file provides the private implementation for the Graph class.
 * As with all template classes, the C++ compiler must have access to
 * this code when it processes the interface.  Putting this code in a
 * separate file means that the client is not confused by these details.
 */

#ifdef _graph_h

/*
 * Implementation notes: nodeCompare, arcCompare
 * ---------------------------------------------
 * These functions are the comparison functions used for nodes and arcs,
 * respectively.  Their purpose is to ensure that the sets containing
 * nodes and arcs process their elements in a predictable order.  Nodes
 * are processed in alphabetical order by node name; arcs are compared
 * in much the same way, looking first at the start node and then
 * continuing on to look at the finish node if the start nodes match.
 * These comparison functions, however, return 0 only if the arguments
 * are identical, in the sense that they are at the same address.  If
 * two distinct arcs, for example, connect the same pair of nodes (which
 * is perfectly legal in the graph abstraction and can be used to
 * represent multiple modes of travel between two nodes), those arcs
 * are not the same.  The comparison function must therefore return
 * a nonzero value to ensure that both arcs can coexist in the arc set.
 */

template <typename NodeType>
int nodeCompare(NodeType *n1, NodeType *n2) {
   if (n1 == n2) return 0;
   if (n1->name == n2->name) return (n1 < n2) ? -1 : +1;
   return (n1->name < n2->name) ? -1 : +1;
}

template <typename NodeType,typename ArcType>
int arcCompare(ArcType *a1, ArcType *a2) {
   if (a1 == a2) return 0;
   NodeType *n1 = a1->start;
   NodeType *n2 = a2->start;
   int cmp = nodeCompare(n1, n2);
   if (cmp != 0) return cmp;
   n1 = a1->finish;
   n2 = a2->finish;
   cmp = nodeCompare(n1, n2);
   if (cmp != 0) return cmp;
   return (a1 < a2) ? -1 : +1;
}

/*
 * Implementation notes: Graph constructor
 * ---------------------------------------
 * Even though the body of the Graph constructor is empty, important
 * work is done by the initializers, which ensure that the nodes and
 * arcs set are given the correct comparison functions.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::Graph() : nodes(nodeCompare<NodeType>),
                                   arcs(arcCompare<NodeType,ArcType>) {
   /* Empty */
}

/*
 * Implementation notes: Graph destructor
 * --------------------------------------
 * The destructor must free all heap storage used by this graph to
 * represent the nodes and arcs.  The clear metho must also reclaim
 * this memory, which means that the destructor can simply call
 * clear to do the work.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::~Graph() {
   clear();
}

/*
 * Implementation notes: size, isEmpty
 * -----------------------------------
 * These methods are defined in terms of the node set, so the implementation
 * simply forwards the request there.  Note that it is impossible for a
 * graph to have arcs if it has no nodes.
 */

template <typename NodeType,typename ArcType>
int Graph<NodeType,ArcType>::size() {
   return nodes.size();
}

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isEmpty() {
   return nodes.isEmpty();
}

/*
 * Implementation notes: clear
 * ---------------------------
 * The implementation of clear first frees the nodes and arcs in
 * their respective sets and then uses the Set class clear method
 * to ensure that these sets are empty.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::clear() {
   foreach (NodeType *node in nodes) {
      delete node;
   }
   foreach (ArcType *arc in arcs) {
      delete arc;
   }
   arcs.clear();
   nodes.clear();
   nodeMap.clear();
}

/*
 * Implementation notes: addNode
 * -----------------------------
 * The addNode method appears in two forms: one that creates a node
 * from its name and one that assumes that the client has created
 * the new node.  In each case, the implementation must add the node
 * the set of nodes for the graph and add the name-to-node association
 * to the node map.
 */

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::addNode(string name) {
   NodeType *node = new NodeType();
   node->arcs = Set<ArcType *>(arcCompare<NodeType,ArcType>);
   node->name = name;
   return addNode(node);
}

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::addNode(NodeType *node) {
   if (nodeMap.containsKey(node->name)) {
      error("addNode: node " + node->name + " already exists");
   }
   nodes.add(node);
   nodeMap[node->name] = node;
   return node;
}

/*
 * Implementation notes: removeNode
 * --------------------------------
 * The removeNode method must remove the specified node but must
 * also remove any arcs in the graph containing the node.  To avoid
 * changing the node set during iteration, this implementation creates
 * a vector of arcs that require deletion.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeNode(string name) {
   removeNode(getNode(name));
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeNode(NodeType *node) {
   Vector<ArcType *> toRemove;
   foreach (ArcType *arc in arcs) {
      if (arc->start == node || arc->finish == node) {
         toRemove.add(arc);
      }
   }
   foreach (ArcType *arc in toRemove) {
      removeArc(arc);
   }
   nodes.remove(node);
}

/*
 * Implementation notes: getNode, nodeExists
 * -----------------------------------------
 * These methods provide access to the node map in the graph.
 */

template <typename NodeType,typename ArcType>
NodeType *Graph<NodeType,ArcType>::getNode(string name) {
   if (!nodeMap.containsKey(name)) error("No node named " + name);
   return nodeMap[name];
}

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::nodeExists(string name) {
   return nodeMap.containsKey(name);
}

/*
 * Implementation notes: addArc
 * ----------------------------
 * The addArc method appears in three forms, as described in the
 * interface.  The code for each form of the method, however, is
 * quite straightforward.
 */

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(string s1, string s2) {
   return addArc(getNode(s1), getNode(s2));
}

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(NodeType *n1, NodeType *n2) {
   ArcType *arc = new ArcType();
   arc->start = n1;
   arc->finish = n2;
   return addArc(arc);
}

template <typename NodeType,typename ArcType>
ArcType *Graph<NodeType,ArcType>::addArc(ArcType *arc) {
   arc->start->arcs.add(arc);
   arcs.add(arc);
   return arc;
}

/*
 * Implementation notes: removeArc
 * -------------------------------
 * These methods remove arcs from the graph, which is ordinarily simply
 * a matter of removing the arc from two sets: the set of arcs in the
 * graph as a whole and the set of arcs in the starting node.  The
 * methods that remove an arc specified by its endpoints, however,
 * must take account of the fact that there might be more than one
 * such arc and delete all of them.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(string s1, string s2) {
   removeArc(getNode(s1), getNode(s2));
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(NodeType *n1, NodeType *n2) {
   Vector<ArcType *> toRemove;
   foreach (ArcType *arc in arcs) {
      if (arc->start == n1 && arc->finish == n2) {
         toRemove.add(arc);
      }
   }
   foreach (ArcType *arc in toRemove) {
      removeArc(arc);
   }
}

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::removeArc(ArcType *arc) {
   arc->start->arcs.remove(arc);
   arcs.remove(arc);
}

/*
 * Implementation notes: isConnected
 * ---------------------------------
 * Node n1 is connected to n2 if any of the arcs leaving n1 finish at n2.
 * The two versions of this method allow nodes to be specified either as
 * node pointers or by name.
 */

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isConnected(NodeType *n1, NodeType *n2) {
   foreach (ArcType *arc in n1->arcs) {
      if (arc->finish == n2) return true;
   }
   return false;
}

template <typename NodeType,typename ArcType>
bool Graph<NodeType,ArcType>::isConnected(string s1, string s2) {
   return isConnected(getNode(s1), getNode(s2));
}

/*
 * Implementation notes: getNodeSet, getArcSet
 * -------------------------------------------
 * These methods simply return the set requested by the client.  The
 * sets are returned by reference for efficiency, because doing so
 * eliminates the need to copy the set.
 */

template <typename NodeType,typename ArcType>
Set<NodeType *> & Graph<NodeType,ArcType>::getNodeSet() {
   return nodes;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet() {
   return arcs;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet(NodeType *node) {
   return node->arcs;
}

template <typename NodeType,typename ArcType>
Set<ArcType *> & Graph<NodeType,ArcType>::getArcSet(string name) {
   return getArcSet(getNode(name));
}

/*
 * Implementation notes: getNeighbors
 * ----------------------------------
 * This implementation recomputes the set each time, which is reasonably
 * efficient if the degree of the node is small.
 */

template <typename NodeType,typename ArcType>
Set<NodeType *> Graph<NodeType,ArcType>::getNeighbors(NodeType *node) {
   Set<NodeType *> nodes(nodeCompare<NodeType>);
   foreach (ArcType *arc in node->arcs) {
      nodes.add(arc->finish);
   }
   return nodes;
}

template <typename NodeType,typename ArcType>
Set<NodeType *> Graph<NodeType,ArcType>::getNeighbors(string name) {
   return getNeighbors(getNode(name));
}

/*
 * Implementation notes: operator=, copy constructor
 * -------------------------------------------------
 * These methods ensure that copying a graph creates an entirely new
 * parallel structure of nodes and arcs.
 */

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>
           & Graph<NodeType,ArcType>::operator=(const Graph & rhs) {
   if (this != &rhs) {
      clear();
      copyInternalData(rhs);
   }
   return *this;
}

template <typename NodeType,typename ArcType>
Graph<NodeType,ArcType>::Graph(const Graph & rhs) :
                      nodes(nodeCompare<NodeType>),
                      arcs(arcCompare<NodeType,ArcType>) {
   copyInternalData(rhs);
}

/* Private method: copyInternalData
 * --------------------------------
 * Common code factored out of the copy constructor and operator= to
 * copy the contents from the other graph.
 */

template <typename NodeType,typename ArcType>
void Graph<NodeType,ArcType>::copyInternalData(const Graph & other) {
   Set<NodeType *>nodes = other.nodes;
   foreach (NodeType *oldNode in nodes) {
      NodeType *newNode = new NodeType();
      *newNode = *oldNode;
      newNode->arcs.clear();
      addNode(newNode);
   }
   Set<ArcType *> arcs = other.arcs;
   foreach (ArcType *oldArc in arcs) {
      ArcType *newArc = new ArcType();
      *newArc = *oldArc;
      newArc->start = getNode(oldArc->start->name);
      newArc->finish = getNode(oldArc->finish->name);
      addArc(newArc);
   }
}

#endif
