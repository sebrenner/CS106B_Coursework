/*
 * File: graphpriv.h
 * -----------------
 * This file defines the private data for the Graph class.
 */

/* Instance variables */

private:
   Set<NodeType *> nodes;                 /* The set of nodes in the graph */
   Set<ArcType *> arcs;                   /* The set of arcs in the graph  */
   Map<std::string, NodeType *> nodeMap;  /* A map from names and nodes    */

/*
 * Functions: operator=, copy constructor
 * --------------------------------------
 * These functions are part of the public interface of the class but are
 * defined here to avoid adding confusion to the Graph class.
 */

public:
   Graph & operator=(const Graph & rhs);
   Graph(const Graph & rhs);

private:
   void copyInternalData(const Graph & other);
