/***************************************************************
<Nick Hancher>
<BoundedInterface.hpp>
<CS210 Project 1>
<THe interface for BoundedStack. Gives the function to be carried out in BoundedStack.hpp>
***************************************************************/
#ifndef BOUNDED_INTERFACE_H
#define BOUNDED_INTERFACE_H 1

#include <cmath>

class BoundedInterface
{
protected:
	const int _UPPER_BOUND_NUM_ELEMENTS;

public:

	BoundedInterface(int upper = 10) : _UPPER_BOUND_NUM_ELEMENTS{ abs(upper) }
	{
	}

	// Returns the maximum number of allowable elements in this container.
	virtual int capacity() const
	{
		return _UPPER_BOUND_NUM_ELEMENTS;
	}

	// Can this container hold more data?
	virtual bool atCapacity() const = 0;

	// How many more items can be added?
	virtual int available() const = 0;
};

#endif