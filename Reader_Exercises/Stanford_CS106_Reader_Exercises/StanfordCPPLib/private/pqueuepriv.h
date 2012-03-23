/*
 * File: pqueuepriv.h
 * ------------------
 * This file contains the private section of the pqueue.h interface.
 */

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The PriorityQueue class is implemented using a data structure called
 * a heap.
 */

private:

/* Type used for each heap entry */

   struct HeapEntry {
      ValueType value;
      double priority;
      long sequence;
   };

/* Instance variables */

   Vector<HeapEntry> heap;
   long enqueueCount;
   int count;
   int capacity;

/* Private function prototypes */

   void enqueueHeap(ValueType & value, double priority);
   ValueType dequeueHeap();
   bool takesPriority(int i1, int i2);
   void swapHeapEntries(int i1, int i2);
