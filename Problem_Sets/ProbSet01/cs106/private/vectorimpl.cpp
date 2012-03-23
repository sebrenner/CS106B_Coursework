/*
 * File: vecimpl.cpp
 * -----------------
 * This file contains the implementation of the vector.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _vector_h

/*
 * Implementation notes: Vector constructor and destructor
 * -------------------------------------------------------
 * The constructor allocates storage for the dynamic array
 * and initializes the other fields of the object.  The
 * destructor frees the memory used for the array.
 */

template <typename ValueType>
Vector<ValueType>::Vector() {
   count = 0;
   capacity = INITIAL_CAPACITY;
   elements = new ValueType[capacity];
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) {
   count = capacity = n;
   elements = new ValueType[n];
   for (int i = 0; i < n; i++) {
      elements[i] = value;
   }
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
   delete[] elements;
}

/*
 * Implementation notes: Vector methods
 * ------------------------------------
 * The basic Vector methods are straightforward and should require
 * no detailed documentation.
 */

template <typename ValueType>
int Vector<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
   delete[] elements;
   count = 0;
   capacity = INITIAL_CAPACITY;
   elements = new ValueType[capacity];
}

template <typename ValueType>
ValueType Vector<ValueType>::get(int index) const {
   if (index < 0 || index >= count) error("get: index out of range");
   return elements[index];
}

template <typename ValueType>
void Vector<ValueType>::set(int index, ValueType value) {
   if (index < 0 || index >= count) error("set: index out of range");
   elements[index] = value;
}

/*
 * Implementation notes: insertAt, removeAt, add
 * ---------------------------------------------
 * These methods must shift the existing elements in the array to
 * make room for a new element or to close up the space left by a
 * deleted one.
 */

template <typename ValueType>
void Vector<ValueType>::insertAt(int index, ValueType value) {
   if (count == capacity) expandCapacity();
   if (index < 0 || index > count) {
      error("insertAt: index out of range");
   }
   for (int i = count; i > index; i--) {
      elements[i] = elements[i - 1];
   }
   elements[index] = value;
   count++;
}

template <typename ValueType>
void Vector<ValueType>::removeAt(int index) {
   if (index < 0 || index >= count) error("removeAt: index out of range");
   for (int i = index; i < count - 1; i++) {
      elements[i] = elements[i + 1];
   }
   count--;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
   insertAt(count, value);
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType value) {
   insertAt(count, value);
}

/*
 * Implementation notes: Vector selection
 * --------------------------------------
 * The following code implements traditional array selection using
 * square brackets for the index.
 */

template <typename ValueType>
ValueType & Vector<ValueType>::operator[](int index) {
   if (index < 0 || index >= count) error("Selection index out of range");
   return elements[index];
}
template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator+(const Vector & v2) const {
   Vector<ValueType> vec = *this;
   foreach (ValueType value in v2) {
      vec.add(value);
   }
   return vec;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const Vector & v2) {
   foreach (ValueType value in v2) {
      *this += value;
   }
   return *this;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const ValueType & value) {
   this->add(value);
   return *this;
}

/*
 * Implementation notes: mapAll
 * ----------------------------
 * The mapAll implementations simply iterate through the vector
 * elements in ascending index order.
 */

template <typename ValueType>
void Vector<ValueType>::mapAll(void (*fn)(ValueType)) {
   for (int i = 0; i < count; i++) {
      fn(elements[i]);
   }
}

template <typename ValueType>
template <typename ClientDataType>
void Vector<ValueType>::mapAll(void (*fn)(ValueType, ClientDataType &),
                              ClientDataType & data) {
   for (int i = 0; i < count; i++) {
      fn(elements[i], data);
   }
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This private method doubles the capacity of the elements array
 * whenever it runs out of space.  To do so, it must allocate a new
 * array, copy all the elements from the old array to the new one,
 * and free the old storage.
 */

template <typename ValueType>
void Vector<ValueType>::expandCapacity() {
   capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
   ValueType *array = new ValueType[capacity];
   for (int i = 0; i < count; i++) {
      array[i] = elements[i];
   }
   delete[] elements;
   elements = array;
}

#endif
