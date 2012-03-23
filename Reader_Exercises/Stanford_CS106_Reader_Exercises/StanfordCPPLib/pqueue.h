/*
 * File: pqueue.h
 * --------------
 * This interface exports the <code>PriorityQueue</code> class, a
 * collection in which values are processed in priority order.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "error.h"
#include "vector.h"

/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a linear structure called a <i>priority&nbsp;queue</i>
 * in which values are processed in order of priority.  As in conventional
 * English usage, lower priority numbers correspond to higher effective
 * priorities, so that a priority 1 item takes precedence over a
 * priority 2 item.
 */

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this priority queue.
 */

   ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) . . .
 * ------------------------------
 * Returns <code>true</code> if the priority queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds <code>value</code> to the queue with the specified priority.
 * Lower priority numbers correspond to higher priorities, which
 * means that all priority 1 elements are dequeued before any
 * priority 2 elements.
 */

   void enqueue(ValueType value, double priority);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the highest priority value.  If multiple
 * entries in the queue have the same priority, those values are
 * dequeued in the same order in which they were enqueued.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the value of highest priority in the queue, without
 * removing it.
 */

   ValueType peek() const;

#include "private/pqueuepriv.h"

};

#include "private/pqueueimpl.cpp"

#endif
