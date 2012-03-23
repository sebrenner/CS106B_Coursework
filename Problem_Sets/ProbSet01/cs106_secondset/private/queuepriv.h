/*
 * File: queuepriv.h
 * -----------------
 * This file contains the private section of the queue.h interface.
 */

/*
 * Implementation notes: Queue data structure
 * ------------------------------------------
 * The Queue class is implemented using a ring buffer.
 */

private:

/* Instance variables */

   Vector<ValueType> ringBuffer;
   int count;
   int capacity;
   int head;
   int tail;

/* Private functions */

   void expandRingBufferCapacity();
