/***************************************************************
<Nick Hancher>
<BoundedStack.hpp>
<CS210 Project 1>
<Implements all the function from the Interface that could be used to modify a Bounded stack>
***************************************************************/
#ifndef BOUNDED_STACK_H
#define BOUNDED_STACK_H 1

#include <vector>

#include "Stack.hpp"
#include "BoundedInterface.hpp"

template <typename T>
class BoundedStack : public Stack<T>, public BoundedInterface
{
public:
	BoundedStack(int bound = 10) : Stack(), BoundedInterface{ abs(bound) }
	{
	}
	// Pushes an item onto the top of this stack.
	virtual bool push(const T& val1 = T{})
	{
		// checks to see if the item is at Capacity. it is isnt pushes, to the stack
		if (!atCapacity())
		{
			_container.push_front(val1);
			return true;
		}
		// If it is at Capacity. Pops the oldest item(last item) off the stack then
		// pushes the value to the stack
		else
		{
			_container.pop_back();
			_container.push_front(val1);
			return true;
		}
	}
	// add is a synonym for push
	virtual bool add(const T& val1 = T{})
	{
		if (!atCapacity())
		{
			_container.push_front(val1);
			return true;
		}
		else
		{
			_container.pop_back();
			_container.push_front(val1);
			return true;
		}
	}
	// Checks to see is the stack can hold more data based on the bound
	bool atCapacity() const
	{
		// if the size is greater than the bound(get from capacity()) returns true
		// if it isnt, returns false.
		if (size() >= capacity())
		{
			return true;
		}
		return false;
	}
	//Returns how many items can still be added to the stack
	int available() const
	{
		return capacity() - size();
	}

public:
	// Internal consistency check
	virtual bool check() const
	{
		bool superCheck = Stack::check();
		bool sizeConsistent = isSizeConsistent();

		return superCheck && sizeConsistent;
	}

	// Verifies size <= UPPER BOUND
	bool isSizeConsistent() const
	{
		return size() <= _UPPER_BOUND_NUM_ELEMENTS;
	}
};

#endif
