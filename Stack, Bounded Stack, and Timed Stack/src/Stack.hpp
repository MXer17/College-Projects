/***************************************************************
<Nick Hancher>
<Stack.hpp>
<CS210 Project 1>
<Implements all the function from the Interface that could be used to modify a stack>
***************************************************************/
#ifndef _STACK_H
#define _STACK_H 1

#include <deque>

#include "StackInterface.h"

template <typename T>
class Stack : public StackInterface<T>
{
protected:
	std::deque<T> _container;

public:
	
	// Returns the number of components in this container.
	virtual int size() const
	{
		return _container.size();
	}
	// Tests if this stack is empty.
	virtual bool empty() const
	{
		return size() == 0;
	}
	// Pushes an item onto the top of this stack.
	virtual bool push(const T& val = T{})
	{
		//adds the item to the front of the deque
		_container.push_front(val);
		return true;
	}
	// add is a synonym for push
	virtual bool add(const T& val = T{})
	{
		_container.push_front(val);
		return true;
	}
	// Removes the object at the top of this stack and returns that
	// object as the value of this function.
	bool pop(T& val = T{})
	{
		// checks to see if there are items in the stack
		if (size() > 0)
		{
			val = _container.front();
			_container.pop_front();
			return true;
		}
		else
		{
			return false;
		}
	
	}
	// Looks at the object at the top of this stack without removing it from the stack.
	// Return true / false based on non-empty, successful access
	virtual bool peek(T& val = T{}) const
	{
		// checks to see if there are items in the stack
		if (size() > 0)
		{
			val = _container.front();
			return true;
		}
		else
		{
			return false;
		}
		
	}
	// Removes all elements from the stack
	virtual void clear() 
	{
		while (size() != 0)
		{
			_container.pop_back();
		}
	}
	// Seaches to the target; if the target is found,  returns the distance from
	// the top of the stack to the target nearst to the top. If the item is not in
	// the stack, returns -1
	virtual int search(const T& target = T{}) const
	{
		for (int i = 0; i < size(); i++)
		{
			if (_container.at(i) == target)
			{
				return i + 1;
			}
		}
		return -1;
	}

	// Overloaded output operator
	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Stack<U>& s)
	{
		//for (std::vector<U>::const_iterator itr = s._container.begin(); itr != s._container.end(); )
		for (Stack<U>::const_iterator itr = s._begin(); itr != s.end(); )
		{
			os << *itr;
			itr++;
			if (itr != s._container.end()) os << ", ";
		}

		return os;
	}

public:
	// Consistency check for this container; nothing to verify
	virtual bool check() const { return true; }
};

#endif