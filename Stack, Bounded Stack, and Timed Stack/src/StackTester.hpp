/***************************************************************
<Nick Hancher>
<StackTester.hpp>
<CS210 Project 1>
<Testes the implemention of Stack>
***************************************************************/

#ifndef _STACK_TESTER_H
#define _STACK_TESTER_H 1

#include <map>
#include <iostream>

#include "AbstractTester.hpp"
#include "Stack.hpp"

class StackTester : public AbstractTester
{
public:
	StackTester(const std::string& name = "Stack", std::ostream& out = std::cout) : AbstractTester{ name, out }
	{
	}

	virtual ~StackTester() {}

	virtual void runAll()
	{
		//
		// Run tests and report
		//
		Stack<int>* s = new Stack<int>();

		_errorCountMap["constructor"] = testConstructor(*s);
		delete s;
		s = new Stack<int>();

		_errorCountMap["push"] = testPush(*s);
		delete s;
		s = new Stack<int>();

		_errorCountMap["add"] = testAdd(*s);
		delete s;
		s = new Stack<int>();

		_errorCountMap["clear"] = testClear(*s);
		delete s;
		s = new Stack<int>();

		_errorCountMap["pop"] = testPop(*s);
		delete s;
		s = new Stack<int>();

		_errorCountMap["search"] = testSearch(*s);
		delete s;
	}

	virtual int testConstructor(Stack<int>& s)
	{
		_os << "\t" << "Test constructor..." << std::endl;

		int errors = 0;

		if (s.size() != 0)
		{
			emitError("Constructor error; size not zero");
			errors++;
		}
		if (!s.empty())
		{
			emitError("Constructor error; stack not empty");
			errors++;
		}
		if (s.search(_distribution(_generator)) != -1)
		{
			emitError("Constructor error; search returned something other than -1");
			errors++;
		}
		int popped = -1;
		if (s.pop(popped))
		{
			emitError("Constructor error; pop did not return false for empty stack");
			errors++;
		}
		if (popped != -1)
		{
			emitError("Constructor error; pop overwrote the input value even though it is invalid");
			errors++;
		}
		check(s, errors);

		return errors;
	}

	virtual int testPush(Stack<int>& s)
	{
		_os << "\t" << "Test push..." << std::endl;

		int errors = 0;

		for (int i = 0; i < 10; i++)
		{
			if (s.size() != i)
			{
				emitError("Push error (before): size", s.size(), i);
				errors++;
			}

			///////////////////
			s.push(i);
			///////////////////

			if (s.empty())
			{
				emitError("Push error: empty; stack empty");
				errors++;
			}
			if (s.size() != i + 1)
			{
				emitError("Push error (after): size", s.size(), i + 1);
				errors++;
			}
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
		}

		return errors;
	}

	virtual int testAdd(Stack<int>& s)
	{
		_os << "\t" << "Test add..." << std::endl;

		int errors = 0;

		for (int i = 0; i < 10; i++)
		{
			if (s.size() != i)
			{
				emitError("Add error (before): size", s.size(), i);
				errors++;
			}

			///////////////////
			s.add(i);
			///////////////////

			if (s.empty())
			{
				emitError("Add error: empty; stack empty");
				errors++;
			}
			if (s.size() != i + 1)
			{
				emitError("Add error (after): size", s.size(), i + 1);
				errors++;
			}
			int peeked = -1;
			if (!s.peek(peeked))
			{
				emitError("Add error: peek returned false");
				errors++;
			}
			if (peeked != i)
			{
				emitError("Add error: peek", peeked, i);
				errors++;
			}
			check(s, errors);
		}

		return errors;
	}

	virtual int testClear(Stack<int>& s)
	{
		_os << "\t" << "Test clear..." << std::endl;

		int errors = 0;

		s.clear();
		check(s, errors);

		if (!s.empty())
		{
			emitError("Clear error: empty; stack not empty");
			errors++;
		}
		if (s.size() != 0)
		{
			emitError("Clear error (after): size", s.size(), 0);
			errors++;
		}
		int peeked = -1;
		if (s.peek(peeked))
		{
			emitError("Clear error: peek return true");
			errors++;
		}

		for (int i = 0; i < 10; i++)
		{
			s.push(i);
		}

		check(s, errors);
		s.clear();

		if (!s.empty())
		{
			emitError("Clear error: empty; stack not empty");
			errors++;
		}
		if (s.size() != 0)
		{
			emitError("Clear error (after): size", s.size(), 0);
			errors++;
		}
		peeked = -1;
		if (s.peek(peeked))
		{
			emitError("Clear error: peek returned true on empty");
			errors++;
		}
		if (peeked != -1)
		{
			emitError("Clear error: peek", peeked, -1);
			errors++;
		}
		check(s, errors);

		return errors;
	}

	virtual int testPop(Stack<int>& s)
	{
		_os << "\t" << "Test pop..." << std::endl;
		int errors = 0;

		int popped = -1;
		if (s.pop(popped))
		{
			emitError("Pop error; pop did not return false for empty stack");
			errors++;
		}
		if (popped != -1)
		{
			emitError("Pop error; pop overwrote the input value even though it is invalid");
			errors++;
		}
		check(s, errors);

		//
		// Add a bunch of stuff
		//
		for (int i = 0; i < 10; i++)
		{
			s.push(i);
		}
		check(s, errors);

		// Remove all of it
		for (int i = 9; i >= 0; i--)
		{
			int peeked = -1;
			if (!s.peek(peeked))
			{
				emitError("Pop error: peek returned false");
				errors++;
			}
			if (peeked != i)
			{
				emitError("Pop error: peek", peeked, i);
				errors++;
			}

			int popped = -1;
			s.pop(popped);

			if (popped != i)
			{
				emitError("Pop error: ", popped, i);
				errors++;
			}
			if (s.size() != i)
			{
				emitError("Pop error: size", s.size(), i);
				errors++;
			}
			check(s, errors);
		}

		if (s.size() != 0)
		{
			emitError("Pop error; size not zero");
			errors++;
		}
		if (!s.empty())
		{
			emitError("Pop error; stack not empty");
			errors++;
		}
		if (s.search(_distribution(_generator)) != -1)
		{
			emitError("Pop error; search returned something other than -1");
			errors++;
		}
		popped = -1;
		if (s.pop(popped))
		{
			emitError("Pop error; pop did not return false for empty stack");
			errors++;
		}
		if (popped != -1)
		{
			emitError("Pop error; pop overwrote the input value even though it is invalid");
			errors++;
		}
		check(s, errors);

		return errors;
	}

	virtual int testSearch(Stack<int>& s)
	{
		_os << "\t" << "Test search..." << std::endl;
		int errors = 0;

		//
		// Successful finding
		//
		for (int value = 0; value < 10; value++)
		{
			s.push(value);

			for (int i = 0; i <= value; i++)
			{
				int searchIndex = s.search(i);
				if (searchIndex != s.size() - i)
				{
					emitError("Search error", searchIndex, s.size() - i);
					errors++;
				}
				check(s, errors);
			}
			check(s, errors);
		}

		//
		// Unsuccessful finding
		//
		for (int value = 0; value < 10; value++)
		{
			s.push(value);

			// unsuccessful find
			for (int i = 0; i <= value; i++)
			{
				int searchIndex = s.search(_distribution(_generator) + 11);
				if (searchIndex != -1)
				{
					emitError("Search error", searchIndex, -1);
					errors++;
				}
				check(s, errors);
			}
			check(s, errors);
		}

		return errors;
	}

	virtual void check(Stack<int>& s, int& errors) const
	{
		AbstractTester::check();

		if (!s.check())
		{
			emitError("Verification check failed");
			errors++;
		}
		return;
	}
};

#endif
