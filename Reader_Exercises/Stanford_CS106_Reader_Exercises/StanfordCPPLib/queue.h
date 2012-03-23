/*
 * File: queue.h
 * -------------
 * This interface exports the <code>Queue</code> class, a collection
 * in which values are ordinarily processed in a first-in/first-out
 * (FIFO) order.
 */

#ifndef _queue_h
#define _queue_h

#include "error.h"
#include "vector.h"

/*
 * Class: Queue<ValueType>
 * -----------------------
 * This class models a linear structure called a <i>queue</i>
 * in which values are added at one end and removed from the other.
 * This discipline gives rise to a first-in/first-out behavior (FIFO)
 * that is the defining feature of queues.
 */

template <typename ValueType>
class Queue {

public:

/*
 * Constructor: Queue
 * Usage: Queue<ValueType> queue;
 * ------------------------------
 * Initializes a new empty queue.
 */

   Queue();

/*
 * Destructor: ~Queue
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this queue.
 */

   ~Queue();

/*
 * Method: size
 * Usage: int n = queue.size();
 * ----------------------------
 * Returns the number of values in the queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (queue.isEmpty()) . . .
 * ---------------------------------
 * Returns <code>true</code> if the queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: queue.clear();
 * ---------------------
 * Removes all elements from the queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: queue.enqueue(value);
 * ----------------------------
 * Adds <code>value</code> to the end of the queue.
 */

   void enqueue(ValueType value);

/*
 * Method: dequeue
 * Usage: ValueType first = queue.dequeue();
 * -----------------------------------------
 * Removes and returns the first item in the queue.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = queue.peek();
 * --------------------------------------
 * Returns the first value in the queue, without removing it.  For
 * compatibility with the STL classes, this method is also exported
 * under the name <code>front</code>, in which case it returns the
 * value by reference.
 */

   ValueType peek() const;

/*
 * Method: front
 * Usage: ValueType first = queue.front();
 * ---------------------------------------
 * Returns the first value in the queue by reference.
 */

   ValueType & front();

/*
 * Method: back
 * Usage: ValueType last = queue.back();
 * -------------------------------------
 * Returns the last value in the queue by reference.
 */

   ValueType & back();

#include "private/queuepriv.h"

};

#include "private/queueimpl.cpp"

#endif
