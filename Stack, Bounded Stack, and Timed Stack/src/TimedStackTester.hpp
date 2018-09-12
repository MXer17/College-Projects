/***************************************************************
<Nick Hancher>
<TimedStackTester.hpp>
<CS210 Project 1>
<Testes the implemention of TimedStack>
***************************************************************/
#ifndef _TIMED_STACK_TESTER_H
#define _TIMED_STACK_TESTER_H 1

#include <map>
#include <iostream>

#include "StackTester.hpp"
#include "TimedStack.hpp"

class TimedStackTester : public StackTester
{
public:
	TimedStackTester(const std::string& name = "Timed Stack", std::ostream& out = std::cout) : StackTester{ name, out }
	{
	}

	virtual void runAll()
	{
		//
		// Run tests and report
		//
		TimedStack<int>* s = new TimedStack<int>();

		_errorCountMap["constructor"] = testConstructor(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["push"] = testPush(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["add"] = testAdd(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["pop"] = testPop(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["search"] = testSearch(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["sweep"] = testSweep(*s);
		delete s;
		s = new TimedStack<int>();

		_errorCountMap["current time"] = testCurrentTime(*s);
		delete s;

	}

	virtual int testConstructor(TimedStack<int>& s)
	{
		// Super-test first
		return StackTester::testConstructor(s);
	}

	virtual int testPush(TimedStack<int>& s)
	{
		// Super-test first
		int errors = StackTester::testPush(s);

		// Clear other list
		s.clear();
		check(s, errors);

		//
		// Checking that timing is accurate for a successful addition
		//
		int externalTime = 0;
		for (int i = 0; i < 10; i++)
		{
			if (s.currentTime() != externalTime)
			{
				emitError("Push error (before): timing", s.currentTime(), externalTime);
				errors++;
			}

			s.push(i);
			externalTime++;

			if (s.currentTime() != externalTime)
			{
				emitError("Push error (after): timing", s.currentTime(), externalTime);
				errors++;
			}
			check(s, errors);
		}

		return errors;
	}

	virtual int testAdd(TimedStack<int>& s)
	{
		// Super-test first
		int errors = StackTester::testPush(s);

		// Clear other list
		s.clear();

		//
		// Checking that timing is accurate for a successful addition
		//
		int externalTime = 0;
		for (int i = 0; i < 10; i++)
		{
			if (s.currentTime() != externalTime)
			{
				emitError("Push error (before): timing", s.currentTime(), externalTime);
				errors++;
			}

			s.add(i);
			externalTime++;

			if (s.currentTime() != externalTime)
			{
				emitError("Push error (after): timing", s.currentTime(), externalTime);
				errors++;
			}

			check(s, errors);
		}

		return errors;
	}

	virtual int testClear(TimedStack<int>& s)
	{
		// Super-test first
		return StackTester::testClear(s);
	}

	virtual int testPop(TimedStack<int>& s)
	{
		// Super-test first
		int errors = StackTester::testPop(s);

		check(s, errors);
		s.clear();
		check(s, errors);

		//
		// Checking that timing is accurate for a successful addition
		//
		int externalTime = 0;
		for (int i = 0; i < 10; i++)
		{
			if (s.currentTime() != externalTime)
			{
				emitError("Pop error (before): timing", s.currentTime(), externalTime);
				errors++;
			}

			s.add(i);
			externalTime++;

			int popped = -1;
			if (!s.pop(popped))
			{
				emitError("Pop error: pop failed");
				errors++;
			}
			externalTime++;
			if (s.currentTime() != externalTime)
			{
				emitError("Pop error (after): timing 1", s.currentTime(), externalTime);
				errors++;
			}

			check(s, errors);

			if (popped != i)
			{
				emitError("Pop error (after): timing 2", popped, i);
				errors++;
			}

			if (s.pop(popped))
			{
				emitError("Pop error: pop succeeded when it should have failed");
				errors++;
			}

			if (s.currentTime() != externalTime)
			{
				emitError("Pop error (after): timing 3", s.currentTime(), externalTime);
				errors++;
			}
			check(s, errors);
		}

		return errors;
	}

	virtual int testSearch(TimedStack<int>& s)
	{
		// Super-test first
		return StackTester::testSearch(s);
	}

	virtual int testSweep(TimedStack<int>& s)
	{
		_os << "\t" << "Test sweep()..." << std::endl;

		int errors = 0;

		//
		// Test:
		//  (a) Put 10 items onto the stack
		//  (b) Sequentially push and pop 1 item at a time.
		//  (c) Add 100 elements
		//  (d) Call sweep
		//  (e) Result is 2 items
		//
		int externalTime = 0;
		int size = 0;

		//  (a) Put 10 items onto the stack
		for (int i = 0; i < 10; i++)
		{
			s.push(i);
			externalTime++;
			size++;

			check(s, errors);
		}

		//  (b) Sequentially push and pop 1 item at a time.
		for (int i = 0; i < 1000; i++)
		{
			s.push(i);
			externalTime++;
			size++;

			check(s, errors);

			int popped = -1;
			s.pop(popped);
			externalTime++;
			size--;

			check(s, errors);
		}

		//  (c) Put 100 items onto the stack
		for (int i = 100; i < 200; i++)
		{
			s.push(i);
			externalTime++;
			size++;

			check(s, errors);
		}

		//
		//  (d) Call sweep
		//
		//    (1) Call benign sweep; no impact
		int sweepReturn = s.sweep(0);
		if (sweepReturn != 0)
		{
			emitError("sweep return error 1", sweepReturn, 0);
			errors++;
		}
		if (s.size() != size)
		{
			emitError("sweep error", s.size(), size);
			errors++;
		}
		int peeked = -1;
		if (!s.peek(peeked))
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		if (peeked != 199)
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		check(s, errors);


		//    (2) Sweep oldest: first 10 removed.
		sweepReturn = s.sweep(10);
		if (sweepReturn != 10)
		{
			emitError("sweep return error 2", sweepReturn, 10);
			errors++;
		}
		size -= 10;
		if (s.size() != size)
		{
			emitError("sweep error", s.size(), size);
			errors++;
		}
		peeked = -1;
		if (!s.peek(peeked))
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		if (peeked != 199)
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		check(s, errors);

		//    (3) Sweep last 50
		sweepReturn = s.sweep(externalTime - 50);
		if (sweepReturn != 50)
		{
			emitError("sweep return error 3", sweepReturn, 50);
			errors++;
		}
		size -= 50;
		if (s.size() != size)
		{
			emitError("sweep error", s.size(), size);
			errors++;
		}
		peeked = -1;
		if (!s.peek(peeked))
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		if (peeked != 199)
		{
			emitError("sweep error; peek failed");
			errors++;
		}
		check(s, errors);

		return errors;
	}

	virtual int testCurrentTime(TimedStack<int>& s)
	{
		_os << "\t" << "Test currentTime()..." << std::endl;

		int errors = 0;

		//
		// Test:
		//  Push and pop tracking time externally; checking after each operation 
		//
		int externalTime = 0;
		for (int i = 0; i < 100; i++)
		{
			if (s.currentTime() != externalTime)
			{
				emitError("currentTime error (1)", s.currentTime(), externalTime);
				errors++;
			}

			s.push(i);
			externalTime++;

			if (s.currentTime() != externalTime)
			{
				emitError("currentTime error (2)", s.currentTime(), externalTime);
				errors++;
			}
			check(s, errors);

			int peeked = -1;
			s.peek(peeked);

			if (s.currentTime() != externalTime)
			{
				emitError("currentTime error (3)", s.currentTime(), externalTime);
				errors++;
			}
			check(s, errors);

			s.pop(i);
			externalTime++;

			if (s.currentTime() != externalTime)
			{
				emitError("currentTime error (4)", s.currentTime(), externalTime);
				errors++;
			}
			check(s, errors);
		}

		s.clear();

		if (s.currentTime() != 0)
		{
			emitError("currentTime error; clear", s.currentTime(), 0);
			errors++;
		}
		check(s, errors);

		return errors;
	}
};

#endif