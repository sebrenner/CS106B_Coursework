/*
 * File: queue.h
 * -------------
 * This interface file contains the Queue class template, 
 * which provides a linear FIFO collection.
 *
 * Last updated: Tue Jan  2 13:51:36 PST 2007 by zelenski
 */

#ifndef _queue_h
#define _queue_h

/*
 * Class: Queue
 * ------------
 * This interface defines a class that models a queue, or waiting 
 * line. It is a linear collection managed in first-in-first-out 
 * order. Values are added to the end and removed from the front. 
 * The queue operations are enqueue (add to end) and dequeue (remove 
 * from front).  
 * For maximum generality, the Queue is supplied as a class template. 
 * The client specializes the queue to hold values of a specific type,
 * e.g. Queue<customerT> or Queue<string>, as needed
 */
template <typename ElemType> 
  class Queue {
	
	public:

		/*
		 * Constructor: Queue
		 * Usage: Queue<int> queue;
		 *        Queue<string> *qp = new Queue<string>;
		 * ---------------------------------------------
		 * The constructor initializes a new empty queue.
	     */
		Queue();


		/*
		 * Destructor: ~Queue
		 * Usage: delete qp;
		 * -----------------
		 * The destructor deallocates storage associated with this queue.
		 */
		~Queue();
		
		
	
		/*
		 * Member function: size
		 * Usage: nElems = queue.size();
		 * -----------------------------
		 * This member function returns the number of elements in 
		 * this queue.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (queue.isEmpty())...
		 * -------------------------------
		 * This member function returns true if this queue contains no
		 * elements, false otherwise.
		 */
		 bool isEmpty();


		/*
		 * Member function: enqueue
		 * Usage: queue.enqueue(element);
		 * -------------------------------
		 * This member function adds element to the end of this queue. That
		 * element becomes the last element in the queue. The queue's size 
		 * increases by one.
		 */
		void enqueue(ElemType elem);  
		
		/*
		 * Member function: dequeue
		 * Usage: first = queue.dequeue();
		 * -------------------------------
		 * This member function removes the front element from this queue
		 * and returns it. The front element is the one that was first 
		 * enqueued. The queue's size decreases by one. This function 
		 * raises an error if called on an empty queue.
		 */
		ElemType dequeue();

		/*
		 * Member function: peek
		 * Usage: first = queue.peek();
		 * --------------------------
		 * This member function returns the value of front element in this 
		 * queue, without removing it.  The queue's size is unchanged.
		 * Raises an error if peek is called on an empty queue.
		 */
		ElemType peek();
			

		/*
		 * Member function: clear
		 * Usage: queue.clear();
		 * ---------------------
		 * This member function removes all elements from this queue. The 
		 * queue is made empty and will have size() = 0.
		 */	
		void clear();


		/*
		 * Deep copying support
		 * --------------------
		 * This copy constructor and operator= are defined to make a
		 * deep copy, making it possible to pass/return queues by value
		 * and assign from one queue to another. The entire contents of 
		 * the queue, including all elements, are copied. Each queue
		 * element is copied from the original queue to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, queues are typically passed 
		 * by reference, however, when a copy is needed, these operations 
		 * are supported.
		 */
		const Queue &operator=(const Queue &rhs); 
		Queue(const Queue &rhs);
		
		
		private:
			struct cell {
				ElemType elem;
				cell *next;
			};
			cell *head, *tail;
			void deleteCells();
			void copyOtherData(const Queue &rhs);
	};
	
/* 
 * Because of the way C++ templates are compiled, we must put the class implementation in
 * the header file. This is a bit quirky and seems to contradict the principles of
 * encapsulation and abstraction. As a client of this class, you don't need to know
 * anything about the internals and shouldn't depend on any implementation details. In
 * fact, you probably should just stop reading right here!
 */
 
 
 
 
/* 
 * Queue class implementation
 * ---------------------------
 * The Queue is internally managed as a singly linked list of cells, with a head and
 * tali pointer.  The front of the queue is at the head, the end is at the tail.
 */
#include "genlib.h" // for Error
#include <cstdlib> // for NULL


template <typename ElemType> 
  Queue<ElemType>::Queue()
	{
		head = tail = NULL;
	}
	
template <typename ElemType> 
  Queue<ElemType>::~Queue()
	{
		deleteCells();
	}

template <typename ElemType> 
  int Queue<ElemType>::size()
	{
		int count = 0;
		for (cell *cur = head; cur != NULL; cur = cur->next)
			count++;
		return count;
	}

template <typename ElemType> 
  bool Queue<ElemType>::isEmpty()
	{
		return (head == NULL);
	}
	
template <typename ElemType> 
  void Queue<ElemType>::enqueue(ElemType elem)
	{
		cell *newOne = new cell;
		newOne->elem = elem;
		newOne->next = NULL;
		if (head != NULL)
			tail->next = newOne;
		else
			head = newOne;
		tail = newOne;
	}
	
template <typename ElemType> 
  ElemType Queue<ElemType>::dequeue()
	{
		if (isEmpty()) Error("Attempt to dequeue from empty queue");
		ElemType first = head->elem;
		cell *toDelete = head;
		head = head->next;
		delete toDelete;
		return first;
	}
	
template <typename ElemType> 
  ElemType Queue<ElemType>::peek()
	{
		if (isEmpty()) Error("Attempt to peek at empty queue");
		return head->elem;
	}

template <typename ElemType> 
  void Queue<ElemType>::clear()
	{
		deleteCells();
	}

template <typename ElemType> 
  void Queue<ElemType>::deleteCells()
	{
		while (head != NULL) {
			cell *next = head->next;
			delete head;
			head = next;
		}
		tail = NULL;
	}

template <typename ElemType> 
  const Queue<ElemType> &Queue<ElemType>::operator=(const Queue &rhs) 
	{
		if (this != &rhs) {
			clear();
			copyOtherData(rhs);
		}
		return *this;
	}		 

template <typename ElemType> 
  Queue<ElemType>::Queue(const Queue &rhs)
	{
		head = tail = NULL;
		copyOtherData(rhs);
	}	
	
template <typename ElemType> 
  void Queue<ElemType>::copyOtherData(const Queue &rhs) 
	{
		for (cell *cur = rhs.head; cur != NULL; cur = cur->next)
			enqueue(cur->elem);
	}


	
#endif //_queue_h
