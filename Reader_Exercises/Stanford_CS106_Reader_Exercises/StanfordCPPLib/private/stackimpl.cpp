/*
 * File: stackimpl.cpp
 * -------------------
 * This file contains the implementation of the stack.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _stack_h

/*
 * Stack class implementation
 * --------------------------
 * The Stack is internally managed using a Vector.  This layered design
 * makes the implementation extremely simple, to the point that most
 * methods can be implemented in as single line.
 */

template <typename ValueType>
Stack<ValueType>::Stack() {
   /* Empty */
}

template <typename ValueType>
Stack<ValueType>::~Stack() {
   /* Empty */
}

template <typename ValueType>
int Stack<ValueType>::size() const {
   return elements.size();
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const {
   return size() == 0;
}

template <typename ValueType>
void Stack<ValueType>::push(ValueType value) {
   elements.add(value);
}

template <typename ValueType>
ValueType Stack<ValueType>::pop() {
   if (isEmpty()) error("pop: Attempting to pop an empty stack");
   ValueType top = elements[elements.size() - 1];
   elements.removeAt(elements.size() - 1);
   return top;
}

template <typename ValueType>
ValueType Stack<ValueType>::peek() const {
   if (isEmpty()) error("peek: Attempting to peek at an empty stack");
   return elements.get(elements.size() - 1);
}

template <typename ValueType>
ValueType & Stack<ValueType>::top() {
   if (isEmpty()) error("top: Attempting to read top of an empty stack");
   return elements[elements.size() - 1];
}

template <typename ValueType>
void Stack<ValueType>::clear() {
   elements.clear();
}

#endif
