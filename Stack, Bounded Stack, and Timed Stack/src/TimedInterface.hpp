/***************************************************************
<Nick Hancher>
<TimedInterface.hpp>
<CS210 Project 1>
<THe interface for TimedStack. Gives the function to be carried out in TimedStack.hpp>
***************************************************************/
#ifndef TIMED_INTERFACE_H
#define TIMED_INTERFACE_H

class TimedInterface
{
protected:
	const unsigned _START_TIME;
	unsigned _currentTime;

public:
	// Default and overloaded constructor based on time
	TimedInterface(unsigned start = 0) : _START_TIME{ start }, _currentTime{ start } {}

	// Default and overloaded constructor based on time
	int increment() { return ++_currentTime; }

	// get for the current time
	int currentTime() { return _currentTime; }

	// Remove all values older than (given) time t
	virtual int sweep(unsigned time) = 0;

	// Reset the current time
	void reset()
	{
		_currentTime = _START_TIME;
	}
};

#endif
