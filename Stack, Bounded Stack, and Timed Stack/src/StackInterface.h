/***************************************************************
<Nick Hancher>
<StackInterface.h>
<CS210 Project 1>
<THe interface for Stack. Gives the function to be carried out in Stack.hpp>
***************************************************************/
#ifndef STACK_INTERFACE_H
#define STACK_INTERFACE_H

template <typename T>
class StackInterface
{
	// Returns the number of components in this container.
	virtual int size() const = 0;

	// Tests if this stack is empty.
	virtual bool empty() const = 0;

	// Pushes an item onto the top of this stack.
	virtual bool push(const T& val = T{}) = 0;

	// add is a synonym for push
	virtual bool add(const T& val = T{}) = 0;

	// Removes the object at the top of this stack and returns that
	// object as the value of this function.
	virtual bool pop(T& val = T{}) = 0;

	// Looks at the object at the top of this stack without removing it from the stack.
	// Return true / false based on non-empty, successful access
	virtual bool peek(T& val = T{}) const = 0;

	// Removes all elements from the stack
	virtual void clear() = 0;

	// Returns the 1-based position where an object is on this stack.
	// If the object target occurs as an item in this stack, this function
	// returns the distance from the top of the stack of the occurrence
	// nearest the top of the stack; the topmost item on the stack is
	// considered to be at distance 1. The overloaded == function is used to
	// compare target to the items in this stack.
	virtual int search(const T& target = T{}) const = 0;
};

#endif
