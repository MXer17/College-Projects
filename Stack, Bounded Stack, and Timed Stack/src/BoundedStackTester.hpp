/***************************************************************
<Nick Hancher>
<BoundedStackTester.hpp>
<CS210 Project 1>
<Testes the implemention of Bounded Stack>
***************************************************************/
#ifndef _BOUNDED_STACK_TESTER_H
#define _BOUNDED_STACK_TESTER_H 1

#include <map>
#include <iostream>

#include "StackTester.hpp"
#include "BoundedStack.hpp"

class BoundedStackTester : public StackTester
{
public:
	BoundedStackTester(const std::string& name = "Bounded Stack", std::ostream& out = std::cout) : StackTester{ name, out }
	{
	}

	virtual void runAll()
	{
		//
		// Run tests and report
		//
		BoundedStack<int>* s = new BoundedStack<int>(10);

		_errorCountMap["constructor"] = testConstructor(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["push"] = testPush(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["add"] = testAdd(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["clear"] = testClear(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["pop"] = testPop(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["search"] = testSearch(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["atCapacity"] = testAtCapacity(*s);
		delete s;
		s = new BoundedStack<int>(10);

		_errorCountMap["available"] = testAvailable(*s);
		delete s;

	}

	virtual int testConstructor(BoundedStack<int>& s)
	{
		// Super-test first
		return StackTester::testConstructor(s);
	}

	virtual int testPush(BoundedStack<int>& s)
	{
		// Super-test first
		int errors = StackTester::testPush(s);

		s.clear();
		check(s, errors);

		for (int i = 0; i < 10; i++)
		{
			s.push(i);
		}
		check(s, errors);

		int SIZE = s.size();
		for (int i = 11; i < 20; i++)
		{
			if (s.size() != 10)
			{
				emitError("Push error (before): size", s.size(), 10);
				errors++;
			}

			///////////////////
			s.push(i);
			check(s, errors);
			///////////////////

			if (s.size() != 10)
			{
				emitError("Push error (before): size", s.size(), 10);
				errors++;
			}

			check(s, errors);
			int peeked = -1;
			if (!s.peek(peeked))
			{
				emitError("Push error: peek returned false");
				errors++;
			}
			if (peeked != i)
			{
				emitError("Push error: peek", peeked, i);
				errors++;
			}
			check(s, errors);

			// Search for the removed element
			if (s.search(i - 11) != -1)
			{
				emitError("Pop error; search found the element that should have been purged (not -1)");
				errors++;
			}
			check(s, errors);
		}

		return errors;
	}

	virtual int testAdd(BoundedStack<int>& s)
	{
		// Super-test first
		int errors = StackTester::testAdd(s);

		s.clear();
		check(s, errors);
		for (int i = 0; i < 10; i++)
		{
			s.add(i);
		}

		int SIZE = s.size();
		for (int i = 11; i < 20; i++)
		{
			if (s.size() != 10)
			{
				emitError("Push error (before): size", s.size(), 10);
				errors++;
			}

			///////////////////
			s.add(i);
			check(s, errors);
			///////////////////

			if (s.size() != 10)
			{
				emitError("Push error (before): size", s.size(), 10);
				errors++;
			}
			check(s, errors);

			int peeked = -1;
			if (!s.peek(peeked))
			{
				emitError("Push error: peek returned false");
				errors++;
			}
			if (peeked != i)
			{
				emitError("Push error: peek", peeked, i);
				errors++;
			}
			check(s, errors);

			// Search for the removed element
			if (s.search(i - 11) != -1)
			{
				emitError("Pop error; search found the element that should have been purged (not -1)");
				errors++;
			}
			check(s, errors);
		}

		return errors;
	}

	virtual int testClear(BoundedStack<int>& s)
	{
		// Super-test first
		return StackTester::testClear(s);
	}

	virtual int testPop(BoundedStack<int>& s)
	{
		// Super-test first
		return StackTester::testPop(s);
	}

	virtual int testSearch(BoundedStack<int>& s)
	{
		// Super-test first
		return StackTester::testSearch(s);
	}

	virtual int testAtCapacity(BoundedStack<int>& s)
	{
		_os << "\t" << "Test atCapacity()..." << std::endl;

		int errors = 0;

		for (int i = 0; i < 10; i++)
		{
			if (s.atCapacity())
			{
				emitError("atCapacity error; stack should not be at capacity");
				errors++;
			}
			check(s, errors);

			///////////
			s.push(i);
			check(s, errors);
			///////////
		}

		if (!s.atCapacity())
		{
			emitError("atCapacity error; stack should be at capacity");
			errors++;
		}
		check(s, errors);

		for (int i = 10; i < 20; i++)
		{
			if (!s.atCapacity())
			{
				emitError("atCapacity error; stack should be at capacity");
				errors++;
			}
			check(s, errors);

			///////////
			s.push(i);
			check(s, errors);
			///////////
		}

		return errors;
	}

	virtual int testAvailable(BoundedStack<int>& s)
	{
		_os << "\t" << "Test available()..." << std::endl;

		int errors = 0;

		for (int i = 0; i < 10; i++)
		{
			int avail = s.available();
			if (avail != 10 - i)
			{
				emitError("available error", avail, 10 - i);
				errors++;
			}
			check(s, errors);

			///////////
			s.push(i);
			check(s, errors);
			///////////
		}

		int avail = s.available();
		if (avail != 0)
		{
			emitError("available error", avail, 0);
			errors++;
		}
		check(s, errors);

		for (int i = 10; i < 20; i++)
		{
			if (avail != 0)
			{
				emitError("available error", avail, 0);
				errors++;
			}

			///////////
			s.push(i);
			check(s, errors);
			///////////
		}

		return errors;
	}
};

#endif
