/***************************************************************
<Nick Hancher>
<BasicSymbolTable.hpp>
<CS210 Project 2>
<Creates a ordered deque of nodes and preforms operations on those nodes like adding,
 deleting, seeing if the node is on the deque, finding the number of keys and the rank
 of some of the keys, and also clearing the whole deque>
***************************************************************/
#ifndef BASIC_SYMBOL_TABLE_H
#define BASIC_SYMBOL_TABLE_H

#include <algorithm>
#include <deque>

#include "SymbolTable.hpp"

template <typename Key, typename Value>
class BasicSymbolTable : public SymbolTable<Key, Value>
{
protected:

	struct NodePair
	{
		Key _key;
		Value _value;

		NodePair(const Key& key = Key{}, const Value& value = Value{}) : _key{ key }, _value{ value } {}
	};

	// The container of the <key, value> pairs
	std::deque<NodePair> _pairs;

	// Key value comparison (less than)
	bool keyLessThan(const NodePair& lhs, const NodePair& rhs) const { return lhs._key < rhs._key; }
	bool keyLessThan(const Key& lhs, const Key& rhs) const { return lhs < rhs; }

	// Equality of key values
	bool keyEquals(const NodePair& lhs, const NodePair& rhs) const { return lhs._key == rhs._key; }
	bool keyEquals(const Key& lhs, const Key& rhs) const { return lhs == rhs; }

	// Equality of key values
	bool keyLessThanOrEquals(const NodePair& lhs, const NodePair& rhs) const
	{
		return keyEquals(lhs, rhs) || keyLessThan(lhs, rhs);
	}
	bool keyLessThanOrEquals(const Key& lhs, const Key& rhs) const
	{
		return keyEquals(lhs, rhs) || keyLessThan(lhs, rhs);
	}

public:

	//Default constructor
	BasicSymbolTable()
	{
		_pairs;
	}
	//Overloaded constructor
	BasicSymbolTable(const BasicSymbolTable& pair) : _pairs(pair)
	{

	}
	//Destructor
	~BasicSymbolTable()
	{
		_pairs.clear();
	}
	// Puts key-value pair into the table
	virtual void put(const Key& key, const Value& val = Value{})
	{
		//creates and iterator to iterate across the deque
		std::deque<NodePair>::iterator it = _pairs.begin();
		NodePair addNode(key, val);
		//pushed Node to the front if the deque is empty
		if (_pairs.empty())
		{
			_pairs.push_front(addNode);
			return;
		}
		//pushes the node to the back is the key is bigger than the last key
		if (key > _pairs.back()._key)
		{

			_pairs.push_back(addNode);
			return;
		}
		//if they key is less then the front key, pushes the node to the front
		if (key < _pairs.front()._key)
		{

			_pairs.push_front(addNode);
			return;

		}
		//To inset in the middle of the deque, so loops across the deque
		for (NodePair node : _pairs)
		{
			// if the key is less then the nodes key in the middle, it will insert the node and
			//push all the rest of the nodes over one position  (is an 'n' operation and can be done quicker if needed)
			if (key < node._key)
			{
				_pairs.insert(it, addNode);
				return;
			}
			++it;
		}


	}
	// acquire the value paired with key
	virtual bool get(const Key& key, Value& val = Value{}) const
	{
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//if the key is with the deque of nodes, will return true and set val to equal that key
			if (key == node._key)
			{
				val = node._value;
				return true;
			}
		}
		return false;
	}


	// remove key (and its value) from table
	virtual void remove(const Key& key)
	{
		//iterator
		std::deque<NodePair>::iterator it = _pairs.begin();
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//if they key is found within the deque it is removed
			if (node._key == key)
			{
				_pairs.erase(it);
				return;
			}
			++it;
		}
	}

	//checks to see if the key to the node is withing the deque, if it is return true, if not, false
	virtual bool contains(const Key& key) const
	{
		for (NodePair node : _pairs)
		{
			if (key == node._key)
			{
				return true;
			}
		}
		return false;
	}

	//Checks to see if the deque is empty
	virtual bool empty() const
	{
		return _pairs.size() == 0;
	}

	// Number of key-value pairs.
	virtual int size() const
	{
		return _pairs.size();
	}

	// returns true if the smallest key is found if not, false
	virtual bool min(Key& key = Key{}) const
	{
		//checks to see if the deque is empty
		if (!empty())
		{
			//makes a node to the front node (smallest) since in order
			NodePair node = _pairs.front();
			//then sets key to equal that node
			key = node._key;
			return true;
		}
		return false;
	}

	// returns true if the largest key is found if not, false
	virtual bool max(Key& key = Key{}) const
	{
		//checks to see if the deque is empty
		if (!empty())
		{
			//makes a node to the rear node (biggest) since in order
			NodePair node = _pairs.back();
			//then sets key to equal that node
			key = node._key;
			return true;
		}
		return false;
	}

	// Largest key less than or equal to key (the floor)
	virtual bool floor(const Key& key, Key& floorKey) const
	{
		int counter = 0;
		//if the deque is empty returns false;
		if (_pairs.size() == 0)
		{
			return false;
		}
		//Returns false also if the key is less then the smallest key
		if (key < _pairs.at(0)._key)
		{
			return false;
		}
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//if the key is greater then the nodes key, add 1 to counter
			//(finds the largest key less the or equal to the key)
			if (key >= node._key)
			{
				counter++;
			}
		}
		//sets the floor key equal to the largest key
		floorKey = _pairs.at(counter - 1)._key;
		return true;

	}

	// Smallest key greater than or equal to key (the ceiling)
	virtual bool ceiling(const Key& key, Key& ceilingKey) const
	{
		int counter = 0;
		//checks to see if the deque is empty
		if (_pairs.size() == 0)
		{
			return false;
		}
		//checks to see if the key is less than the smallest key, if so ceiling is 0
		if (key < _pairs.at(0)._key)
		{
			ceilingKey = 0;
			return true;
		}
		//checks to see if the key is greater than the largest key in the deque
		if (key > _pairs.at(_pairs.size()-1)._key)
		{
			return false;
		}
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//if the key is less then the nodes key, add 1 to counter
			//(finds the smallest key less the or equal to the key)
			if (key <= node._key)
			{
				counter++;
			}
		
		}
		//sets the ceiling key equal to the position of that key
		ceilingKey = _pairs.at(_pairs.size() - counter)._key;
		return true;

	}


	// Returns the Number of keys less than key
	virtual int rank(const Key& key) const
	{
		int counter = 0;
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//adds one to counter if the node found is less than the key
			if (node._key < key)
			{
				counter++;
			}
		}
		return counter;
	}


	// finds the key of rank k
	virtual bool select(int k = 0, Key& key = Key{}) const
	{
		int counter = 0;
		//iterates through the  dequee
		for (NodePair node : _pairs)
		{
			//if counter equals key set key equal to the found node key
			if (counter == k)
			{
				key = node._key;
				return true;
			}
			counter++;
		}
		return false;
	}

	// Deletes the smallest key
	virtual bool deleteMin()
	{
		//checks to see if the deque is empty
		if (_pairs.size() != 0)
		{
			//removes the front node of the deque(samllest key)
			_pairs.pop_front();
			return true;
		}
		return false;
	}

	// Deletes the largest key
	virtual bool deleteMax()
	{
		//checks to see if the deqe is empty
		if (_pairs.size() != 0)
		{
			//removes the last node of the deque(largest key
			_pairs.pop_back();
			return true;
		}
		return false;
	}

	//returns the number of keys in [low, high] (including low, high)
	virtual int size(const Key& low, const Key& high) const
	{
		int counter = 0;
		//iterates through the deque
		for (NodePair node : _pairs)
		{
			//if the found node is greater than or equal to low and less than or equal to the high
			// add 1 to counter, once done, return counter
			if (node._key >= low && node._key <= high)
			{
				counter++;
			}
		}
		return counter;
	}

	// keys in [low, high] (including low, high), in sorted order
	virtual std::vector<Key> keys(const Key& low, const Key& high) const
	{
		//create a vector of keys
		std::vector<Key> theKeys;
		//iterate through the deque
		for (NodePair node: _pairs)
		{
			//if the found node is greater than or equal to low and less than or equal to the high
			//push onto the vector. once all of them are added, return the vector
			if (node._key >= low && node._key <= high)
			{
				theKeys.push_back(node._key);
			}
		}
		return theKeys;
	}

	// all keys in the table, in sorted order
	virtual std::vector<Key> keys() const
	{
		//create a vecotr of keys
		std::vector<Key> allKeys;
		//iterate through the deque
		for (NodePair node : _pairs)
		{
			//pushes all keys onto the vector, sine they are in order
			allKeys.push_back(node._key);
		}
		return allKeys;
	}

	// Removes all elements from the table
	virtual void clear()
	{
		//while the deque is not empty, pop off the last node
		while (!empty())
		{
			_pairs.pop_back();
		}
	}

	//
	///////////////////////////////////////////////////////////////////////////////
	// Check integrity of the vector data structure.
	///////////////////////////////////////////////////////////////////////////////
	//
	bool check() const
	{
		bool ordered = isOrdered();
		bool rankConsistent = isRankConsistent();

		if (!ordered)        std::cout << "Not in symmetric order" << std::endl;
		if (!rankConsistent) std::cout << "Ranks inconsistent" << std::endl;

		return ordered && rankConsistent;
	}

private:
	//
	// does this container satisfy symmetric order?
	//
	bool isOrdered() const
	{
		if (size() <= 1) return true;

		for (unsigned index = 0; index < _pairs.size() - 1; index++)
		{
			if (keyLessThan(_pairs[index + 1], _pairs[index])) return false;
		}
		return true;
	}

	// check that ranks are consistent
	bool isRankConsistent() const
	{
		// The i th node should be rank i
		for (int i = 0; i < size(); i++)
		{
			Key key;
			select(i, key);
			if (i != rank(key)) return false;
		}

		// All keys must equate to the key acquired at its rank 
		for (Key key : keys())
		{
			Key acquired;
			select(rank(key), acquired);

			if (!keyEquals(key, acquired)) return false;
		}

		return true;
	}
};

#endif
