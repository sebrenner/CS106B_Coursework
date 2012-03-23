/*
 * File: pqueueimpl.cpp
 * --------------------
 * This file contains the implementation of the pqueue.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _pqueue_h

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class,
 * so no work is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   heap.clear();
   count = 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   if (count == heap.size()) heap.add(HeapEntry());
   int index = count++;
   heap[index].value = value;
   heap[index].priority = priority;
   heap[index].sequence = enqueueCount++;
   while (index > 0) {
      int parent = (index - 1) / 2;
      if (takesPriority(parent, index)) break;
      swapHeapEntries(parent, index);
      index = parent;
   }
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods must check for an empty queue and report an error
 * if there is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   if (count == 0) error("dequeue: Attempting to dequeue an empty queue");
   ValueType value = heap[0].value;
   swapHeapEntries(0, --count);
   int index = 0;
   while (true) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      if (left >= count) break;
      int child = left;
      if (right < count && takesPriority(right, left)) child = right;
      if (takesPriority(index, child)) break;
      swapHeapEntries(index, child);
      index = child;
   }
   return value;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   if (count == 0) error("peek: Attempting to peek at an empty queue");
   return heap.get(0).value;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2) {
   if (heap[i1].priority < heap[i2].priority) return true;
   if (heap[i1].priority > heap[i2].priority) return false;
   return (heap[i1].sequence < heap[i2].sequence);
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
   HeapEntry entry = heap[i1];
   heap[i1] = heap[i2];
   heap[i2] = entry;
}

#endif
