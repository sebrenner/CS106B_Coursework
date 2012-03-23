/*
 * File: stack.h
 * -------------
 * This interface file contains the Stack class template, 
 * which provides a linear LIFO collection.
 *
 * Last updated: Tue Jan  2 13:40:51 PST 2007 by zelenski
 */

#ifndef _stack_h
#define _stack_h

#include "vector.h"


/*
 * Class: Stack
 * ------------
 * This interface defines a class template that models a "stack":
 * that is, a linear collection of values stacked one on top of 
 * the other. Values added and removed only from the top of the stack. 
 * The fundamental stack operations are push (add to top) and pop  
 * (remove from top). A stack is said to operate in last-in-first-out 
 * (LIFO) order.  
 * For maximum generality, the Stack is supplied as a class template. 
 * The client specializes the stack to hold values of a specific type,
 * e.g. Stack<string> or Stack<stateT>, as needed.
 */

template <typename ElemType> 
  class Stack {
  
	public:

		/*
		 * Constructor: Stack
		 * Usage: Stack<int> stack;
		 *        Stack<string> *sp = new Stack<string>;
		 * ---------------------------------------------
		 * The constructor initializes a new empty stack.
	     */
		Stack();
			
			
		/*
		 * Destructor: ~Stack
		 * Usage: delete sp;
		 * -----------------
		 * The destructor deallocates storage associated with this stack.
		 */
		~Stack();
		
		
		/*
		 * Member function: size
		 * Usage: nElems = stack.size();
		 * -----------------------------
		 * This member function returns the number of elements in 
		 * this stack.
		 */
		int size();
		
		
		/*
		 * Member function: isEmpty
		 * Usage: if (stack.isEmpty())...
		 * -------------------------------
		 * This member function returns true if this stack contains no
		 * elements, false otherwise.
		 */
		bool isEmpty();
		 
		 
		/*
		 * Member function: push
		 * Usage: stack.push(element);
		 * ----------------------------
		 * This member function pushes the specified element onto this 
		 * stack. That element becomes the top element on the stack. The 
		 * stack's size increases by one.
		 */
		void push(ElemType elem);  
		
		
		/*
		 * Member function: pop
		 * Usage: top = stack.pop();
		 * -------------------------
		 * This member function removes the top element from this stack and 
		 * returns it. The top element is the one that was last pushed. The
		 * stack's size decreases by one. This function raises an error if
		 * called on an empty stack.
		 */
		ElemType pop();


		/*
		 * Member function: peek
		 * Usage: top = stack.peek();
		 * --------------------------
		 * This member function returns the value of top element from this 
		 * stack, without removing it.  The stack's size is unchanged.
		 * Raises an error if peek is called on an empty stack.
		 */
		ElemType peek();


		/*
		 * Member function: clear
		 * Usage: stack.clear();
		 * ---------------------
		 * This member function removes all elements from this stack. The 
		 * stack is made empty and will have size() = 0.
		 */	
		void clear();
		
		
		/*
		 * Deep copying support
		 * --------------------
		 * Because all data members have correct behavior on operator=
		 * and copy constructor, the default as synthesized by
		 * the compiler make a correct copy of the Stack. When pass/return
		 * stacks by value, or assign one to another, the entire contents 
		 * of the stack, including all elements, are copied. Each stack
		 * element is copied from the original stack to the copy using
		 * assignment (operator=). Making copies is generally avoided 
		 * because of the expense and thus, stacks are typically passed by 
		 * reference, however, when a copy is needed, these operations 
		 * correctly are supported.
		 *
		 * const Stack &operator=(const Stack &rhs); 
		 * Stack(const Stack &rhs);
		 */

		private:
			Vector<ElemType> elems;
	};
	

/* 
 * Because of the way C++ templates are compiled, we must put the class implementation in
 * the header file. This is a bit quirky and seems to contradict the principles of
 * encapsulation and abstraction. As a client of this class, you don't need to know
 * anything about the internals and shouldn't depend on any implementation details. In
 * fact, you probably should just stop reading right here!
 */
 
 
 
 
/* 
 * Stack class implementation
 * ---------------------------
 * The Stack is internally managed using a Vector. This layered implementation makes the
 * job quite trivial, most member functions are one-liners.
 */


template <typename ElemType> 
  Stack<ElemType>::Stack()
	{}
	
template <typename ElemType> 
  Stack<ElemType>::~Stack()
	{}

template <typename ElemType> 
  int Stack<ElemType>::size()
	{
		return elems.size();
	}

template <typename ElemType> 
  bool Stack<ElemType>::isEmpty()
	{
		return (size() == 0);
	}
	
template <typename ElemType> 
  void Stack<ElemType>::push(ElemType elem)
	{
		elems.add(elem);
	}
	
template <typename ElemType> 
  ElemType Stack<ElemType>::pop()
	{
		if (isEmpty()) Error("Attempt to pop from empty stack");
		ElemType top = elems[elems.size()-1];
		elems.removeAt(elems.size()-1);
		return top;
	}
	
template <typename ElemType> 
  ElemType Stack<ElemType>::peek()
	{
		if (isEmpty()) Error("Attempt to peek at empty stack");
		return elems[elems.size()-1];
	}
	
template <typename ElemType> 
  void Stack<ElemType>::clear()
	{
		elems.clear();
	}

	
#endif //_stack_h
