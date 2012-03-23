/*
 * File: queueimpl.cpp
 * -------------------
 * This file contains the implementation of the queue.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _queue_h

/*
 * Implementation notes: Queue data structure
 * ------------------------------------------
 * The array-based queue stores the elements in successive index
 * positions in a vector, just as a stack does.  What makes the
 * queue structure more complex is the need to avoid shifting
 * elements as the queue expands and contracts.  In the array
 * model, this goal is achieved by keeping track of both the
 * head and tail indices.  The tail index increases by one each
 * time an element is enqueued, and the head index increases by
 * one each time an element is dequeued.  Each index therefore
 * marches toward the end of the allocated vector and will
 * eventually reach the end.  Rather than allocate new memory,
 * this implementation lets each index wrap around back to the
 * beginning as if the ends of the array of elements were joined
 * to form a circle.  This representation is called a ring buffer.
 */

const int INITIAL_CAPACITY = 10;

/*
 * Implementation notes: Queue constructor
 * ---------------------------------------
 * The constructor must allocate the array storage for the queue
 * elements and initialize the fields of the object.
 */

template <typename ValueType>
Queue<ValueType>::Queue() {
   clear();
}

/*
 * Implementation notes: ~Queue destructor
 * ---------------------------------------
 * All of the dynamic memory is allocated in the Vector class,
 * so no work is required at this level.
 */

template <typename ValueType>
Queue<ValueType>::~Queue() {
   /* Empty */
}

template <typename ValueType>
int Queue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void Queue<ValueType>::clear() {
   capacity = INITIAL_CAPACITY;
   ringBuffer = Vector<ValueType>(capacity);
   head = 0;
   tail = 0;
   count = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(ValueType value) {
   if (count >= capacity - 1) expandRingBufferCapacity();
   ringBuffer[tail] = value;
   tail = (tail + 1) % capacity;
   count++;
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods must check for an empty queue and report an error
 * if there is no first element.
 */

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
   if (count == 0) error("dequeue: Attempting to dequeue an empty queue");
   ValueType result = ringBuffer[head];
   head = (head + 1) % capacity;
   count--;
   return result;
}

template <typename ValueType>
ValueType Queue<ValueType>::peek() const {
   if (count == 0) error("peek: Attempting to peek at an empty queue");
   return ringBuffer.get(head);
}

template <typename ValueType>
ValueType & Queue<ValueType>::front() {
   if (count == 0) error("front: Attempting to read front of an empty queue");
   return ringBuffer[head];
}

template <typename ValueType>
ValueType & Queue<ValueType>::back() {
   if (count == 0) error("back: Attempting to read back of an empty queue");
   return ringBuffer[(tail + capacity - 1) % capacity];
}

/*
 * Implementation notes: expandRingBufferCapacity
 * ----------------------------------------------
 * This private method doubles the capacity of the ringBuffer vector.
 * Note that this implementation also shifts all the elements back to
 * the beginning of the vector.
 */

template <typename ValueType>
void Queue<ValueType>::expandRingBufferCapacity() {
   Vector<ValueType> copy = ringBuffer;
   ringBuffer = Vector<ValueType>(2 * capacity);
   for (int i = 0; i < count; i++) {
      ringBuffer[i] = copy[(head + i) % capacity];
   }
   head = 0;
   tail = count;
   capacity *= 2;
}

#endif
