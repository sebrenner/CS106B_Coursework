/*
 * File: graph.h
 * -------------
 * This interface exports a parameterized <code>Graph</code> class used
 * to represent <i>graphs,</i> which consist of a set of <i>nodes</i>
 * and a set of <i>arcs</i>.
 */

#ifndef _graph_h
#define _graph_h

#include <string>
#include "error.h"
#include "map.h"
#include "set.h"

/*
 * Function: nodeCompare
 * ---------------------
 * Standard comparison function for nodes.
 */

template <typename NodeType>
int nodeCompare(NodeType *n1, NodeType *n2);

/*
 * Function: arcCompare
 * --------------------
 * Standard comparison function for arcs.
 */

template <typename NodeType,typename ArcType>
int arcCompare(ArcType *a1, ArcType *a2);

/*
 * Class: Graph<NodeType,ArcType>
 * ------------------------------
 * This class represents a graph with the specified node and arc types.
 * The <code>NodeType</code> and <code>ArcType</code> parameters indicate
 * the structure type or class used for nodes and arcs, respectively.
 * These types can contain any fields or methods required by the client,
 * but must contain the following public fields required by the
 * <code>Graph</code> package itself:
 *
 * The <code>NodeType</code> definition must include:
 *   - A <code>string</code> field called <code>name</code>
 *   - A <code>Set&lt;ArcType *&gt;</code> field called <code>arcs</code>
 *
 * The <code>ArcType</code> definition must include:
 *   - A <code>NodeType *</code> field called <code>start</code>
 *   - A <code>NodeType *</code> field called <code>finish</code>
 */

template <typename NodeType,typename ArcType>
class Graph {

public:

/*
 * Constructor: Graph
 * Usage: Graph<NodeType,ArcType> g;
 * ---------------------------------
 * Creates an empty <code>Graph</code> object.
 */

   Graph();

/*
 * Destructor: ~Graph
 * Usage: (usually implicit)
 * -------------------------
 * Frees the internal storage allocated to represent the graph.
 */

   ~Graph();

/*
 * Method: size
 * Usage: int size = g.size();
 * ---------------------------
 * Returns the number of nodes in the graph.
 */

   int size();

/*
 * Method: isEmpty
 * Usage: if (g.isEmpty()) . . .
 * -----------------------------
 * Returns <code>true</code> if the graph is empty.
 */

   bool isEmpty();

/*
 * Method: clear
 * Usage: g.clear();
 * -----------------
 * Reinitializes the graph to be empty, freeing any heap storage.
 */

   void clear();

/*
 * Method: addNode
 * Usage: NodeType *node = g.addNode(name);
 *        NodeType *node = g.addNode(node);
 * ----------------------------------------
 * Adds a node to the graph.  The first version of this method
 * creates a new node of the appropriate type and initializes its
 * fields; the second assumes that the client has already created
 * the node and simply adds it to the graph.  Both versions of this
 * method return a pointer to the node.
 */

   NodeType *addNode(std::string name);
   NodeType *addNode(NodeType *node);

/*
 * Method: removeNode
 * Usage: g.removeNode(name);
 *        g.removeNode(node);
 * --------------------------
 * Removes a node from the graph, where the node can be specified
 * either by its name or as a pointer value.  Removing a node also
 * removes all arcs that contain that node.
 */

   void removeNode(std::string name);
   void removeNode(NodeType *node);

/*
 * Method: getNode
 * Usage: NodeType *node = g.getNode(name);
 * ----------------------------------------
 * Looks up a node in the name table attached to the graph and
 * returns a pointer to that node.  If no node with the specified
 * name exists, <code>getNode</code> signals an error.
 */

   NodeType *getNode(std::string name);

/*
 * Method: nodeExists
 * Usage: if (g.nodeExists(name)) . . .
 * ------------------------------------
 * Returns <code>true</code> if a node with the given name exists.
 */

   bool nodeExists(std::string name);

/*
 * Method: addArc
 * Usage: g.addArc(s1, s2);
 *        g.addArc(n1, n2);
 *        g.addArc(arc);
 * ---------------------
 * Adds an arc to the graph.  The endpoints of the arc can be specified
 * either as strings indicating the names of the nodes or as pointers
 * to the node structures.  Alternatively, the client can create the arc
 * structure explicitly and pass that pointer to the <code>addArc</code>
 * method.  All three of these versions return a pointer to the arc in
 * case the client needs to capture this value.
 */

   ArcType *addArc(std::string s1, std::string s2);
   ArcType *addArc(NodeType *n1, NodeType *n2);
   ArcType *addArc(ArcType *arc);

/*
 * Method: removeArc
 * Usage: g.removeArc(s1, s2);
 *        g.removeArc(n1, n2);
 *        g.removeArc(arc);
 * ------------------------
 * Removes an arc from the graph, where the arc can be specified in any
 * of three ways: by the names of its endpoints, by the node pointers
 * at its endpoints, or as an arc pointer.  If more than one arc
 * connects the specified endpoints, all of them are removed.
 */

   void removeArc(std::string s1, std::string s2);
   void removeArc(NodeType *n1, NodeType *n2);
   void removeArc(ArcType *arc);

/*
 * Method: isConnected
 * Usage: if (g.isConnected(n1, n2)) . . .
 *        if (g.isConnected(s1, s2)) . . .
 * ---------------------------------------
 * Returns <code>true</code> if the graph contains an arc from
 * <code>n1</code> to <code>n2</code>.  As in the <code>addArc</code>
 * method, nodes can be specified either as node pointers or by name.
 */

   bool isConnected(NodeType *n1, NodeType *n2);
   bool isConnected(std::string s1, std::string s2);

/*
 * Method: getNodeSet
 * Usage: foreach (NodeType *node in g.getNodeSet()) . . .
 * -------------------------------------------------------
 * Returns the set of all nodes in the graph.
 */

   Set<NodeType *> & getNodeSet();

/*
 * Method: getArcSet
 * Usage: foreach (ArcType *arc in g.getArcSet()) . . .
 *        foreach (ArcType *arc in g.getArcSet(node)) . . .
 *        foreach (ArcType *arc in g.getArcSet(name)) . . .
 * --------------------------------------------------------
 * Returns the set of all arcs in the graph or, in the second and
 * third forms, the arcs that start at the specified node, which
 * can be indicated either as a pointer or by name.
 */

   Set<ArcType *> & getArcSet();
   Set<ArcType *> & getArcSet(NodeType *node);
   Set<ArcType *> & getArcSet(std::string name);

/*
 * Method: getNeighbors
 * Usage: foreach (NodeType *node in g.getNeighbors(node)) . . .
 *        foreach (NodeType *node in g.getNeighbors(name)) . . .
 * -------------------------------------------------------------
 * Returns the set of nodes that are neighbors of the specified
 * node, which can be indicated either as a pointer or by name.
 */

   Set<NodeType *> getNeighbors(NodeType *node);
   Set<NodeType *> getNeighbors(std::string node);

#include "private/graphpriv.h"

};

#include "private/graphimpl.cpp"

#endif
