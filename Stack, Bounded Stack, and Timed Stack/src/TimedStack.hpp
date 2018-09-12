/***************************************************************
<Nick Hancher>
<TimedStack.hpp>
<CS210 Project 1>
<Implements all the function from the Interface that could be used to modify a Timed stack>
***************************************************************/
#ifndef _TIMED_STACK_H
#define _TIMED_STACK_H 1

#include <deque>

#include "Stack.hpp"
#include "TimedInterface.hpp"

template <typename T>
class TimedStack : public Stack<T>, public TimedInterface
{
	std::deque<int> _times;

public:
	TimedStack() : Stack<T>{}
	{
	}

	virtual ~TimedStack()
	{
		_times.clear();
	}
	// Increments the time
	// Pushes an item onto the top of this stack.
	// Pushes the currentTime() to the _times deque
	virtual bool push(const T& value = T{})
	{
		increment();
		_container.push_front(value);
		_times.push_front(currentTime());
		return true;
	}
	// add is a synonym for push
	virtual bool add(const T& value = T{})
	{
		increment();
		_container.push_front(value);
		_times.push_front(currentTime());
		return true;
	}
	// Increments the time
	// Removes the object at the top of this stack and returns that
	// object as the value of this function.
	virtual bool pop(T& value = T{})
	{
		/ /checks to see if there items to push in the stack. 
		// if there isn't any items, returns false
		if (size() > 0)
		{
			increment();
			value =_container.front();
			_container.pop_front();
			_times.pop_front();
			return true;
		}
		return false;
	}
	

	//  Remove all values older than (given) time ‘time’; returns the number of items removed
	virtual int sweep(unsigned lowerBoundTime)
	{
		// to count the number of times removed
		int counter = 0;
		// a constant to make sure the size isn't updated in the for loop
		int size = _times.size() -1;
			// loops from the back to the front of _times
			for (int i = size; i > 0; i--)
			{
				// checks to see if the valuse at i is <= lowerBoundTime
				if (_times.at(i) <= lowerBoundTime )
				{
					// pops back _container, _times and adds 1 to counter
					_container.pop_back(); 
					_times.pop_back();
					counter++;
				}
			}
		return counter;
	}

	// Removes all elements from the stack and resets the time.
	virtual void clear()
	{
		//Pops from _container and _times if there are elements within them
		while (size() > 0)
		{
			_container.pop_back();
			_times.pop_back();
		}
		reset();
	}

public:
	// Internal consistency check
	virtual bool check() const
	{
		bool superCheck = Stack::check();
		bool sizeConsistent = isSizeConsistent();
		bool decreasing = isDecreasingTime();

		return superCheck && sizeConsistent && decreasing;
	}

	// Verifies size consistency with times and values
	bool isSizeConsistent() const
	{
		return _times.size() == _container.size();
	}

	// Verifies that all times are "as expected": everywhere decreasing
	bool isDecreasingTime() const
	{
		if (size() <= 1) return true;

		for (int index = 0; index < _times.size() - 1; index++)
		{
			if (_times[index] <= _times[index + 1]) return false;
		}

		return true;
	}
};

#endif