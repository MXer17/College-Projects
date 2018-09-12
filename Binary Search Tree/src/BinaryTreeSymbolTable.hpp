/***************************************************************
<Nick Hancher>
<BinaryTreeSymbolTable.hpp>
<CS210 Project 3>
<Creates a Binary Search Tree of nodes and acts upon those nodes in certain ways, like 
 by removing a node from the tree, find and or deleting the min and or max of the tree,
 checks if the size and to see if it is empty, finds a node's rank in the tree or just
 a node, and will also return the number of nodes within a range or the nodes that are 
 within that range.>
***************************************************************/
#ifndef TREE_SYMBOL_TABLE_H
#define TREE_SYMBOL_TABLE_H

#include <algorithm>

#include "SymbolTable.hpp"

template <typename Key, typename Value>
class BinaryTreeSymbolTable : public SymbolTable<Key, Value>
{
protected:

	struct BinaryTreeNode
	{
		Key _key;
		Value _value;
		BinaryTreeNode* _left;
		BinaryTreeNode* _right;
		unsigned _size;

		BinaryTreeNode(const Key& key = Key{},
			const Value& value = Value{},
			unsigned size = 0,
			BinaryTreeNode* ell = nullptr,
			BinaryTreeNode* r = nullptr)
			: _key{ key }, _value{ value }, _size{ size }, _left{ ell }, _right{ r } {}

		BinaryTreeNode(const BinaryTreeNode& that)
			: _key{ that._key }, _value{ that._value }, _size{ that._size }, _left{ that._left }, _right{ that._right } {}

		~BinaryTreeNode()
		{
			if (_left != nullptr)
			{
				delete _left;
				_left = nullptr;
			}
			if (_right != nullptr)
			{
				delete _right;
				_right = nullptr;
			}
			_size = 0;
		}
	};

	// Key value comparison (less than)
	bool keyLessThan(const Key& lhs, const Key& rhs) const { return lhs < rhs; }

	// Equality of key values
	bool keyEquals(const Key& lhs, const Key& rhs) const { return lhs == rhs; }

	// Equality of key values
	bool keyLessThanOrEquals(const Key& lhs, const Key& rhs) const
	{
		return keyEquals(lhs, rhs) || keyLessThan(lhs, rhs);
	}

	// The container of the <key, value> pairs
	BinaryTreeNode* _root;


private:
	int size(const BinaryTreeNode* const node) const { return node == nullptr ? 0 : node->_size; }

public:

	BinaryTreeSymbolTable() : _root{ nullptr } {}

	virtual ~BinaryTreeSymbolTable() { delete _root; }

	// Puts key-value pair into the table
	virtual void put(const Key& key, const Value& val = Value{})
	{
		_root = putHelper(_root, key, val);
	}
private:
	BinaryTreeNode* putHelper(BinaryTreeNode* node, const Key& key, const Value& value)
	{
		if (node == nullptr) return new BinaryTreeNode(key, value, 1);

		else if (keyLessThan(key, node->_key)) node->_left = putHelper(node->_left, key, value);

		else if (keyLessThan(node->_key, key)) node->_right = putHelper(node->_right, key, value);

		else node->_value = value; // Duplicate: overwrite the value

		node->_size = 1 + size(node->_left) + size(node->_right);

		return node;
	}

public:

	// acquire the value paired with key
	virtual bool get(const Key& key, Value& val = Value{}) const
	{
		BinaryTreeNode* node = getHelper(key, _root);
		//If the node is a nullptr returns false
		if (node == NULL)
		{
			return false;
		}
		//otherwise sets val equal to the nodes vala dn returns true
		else
		{
			val = node->_value;
			return true;
		}
	}
private:
	
	BinaryTreeNode* getHelper(const Key& key, BinaryTreeNode* node) const
	{
		//If the node is not nullptr goes into the if
		if (node != nullptr)
		{
			//if the key and the node key equal, returns the node
			if (keyEquals(key, node->_key))
			{
				return node;
			}
			//if the key is less than the nodes key, recursively calls the function and goes left
			else if (keyLessThan(key, node->_key))
			{
				return getHelper(key, node->_left);
			}
			//if the key is more than the nodes key, recursively calls the function and goes right
			else
			{
				return getHelper(key, node->_right);
			}
		}
		else
		{
			return NULL;
		}
	}
public:
	// remove key (and its value) from table
	virtual void remove(const Key& key)
	{	
		_root = removeHelper(key, _root);
		
	}
private:

	BinaryTreeNode* removeHelper(const Key& key, BinaryTreeNode* node)
	{
		//the the node is nullptr just returns nullptr
		if (node == nullptr)
		{
			return nullptr;
		}
		//finds the node and fixes the children of the removed node
		if (keyLessThan(key, node->_key)) node->_left = removeHelper(key, node->_left);
	
		else if (keyLessThan(node->_key, key)) node->_right = removeHelper(key, node->_right);

		else
		{
			//no children
			if(node->_right == nullptr && node->_left == nullptr)
			{
				// delete the node
				Delete(node);
				return nullptr;
			}
			//1 shild
			else if (node->_right == nullptr || node->_left == nullptr)
			{
				//The node is to the left
				if (node->_right == nullptr)
				{
					BinaryTreeNode* temp = node;
					node = node->_left;
					Delete(temp);
				}
				//Node is to the right
				else
				{
					BinaryTreeNode* temp = node;
					node = node->_right;
					Delete(temp);
				}
			}
			else
			{
				//Gets the max of the left subtree. Sets the node equal to that node
				BinaryTreeNode* temp = getMax(node->_left);
				node->_key = temp->_key;
				node->_value = temp->_value;
				//Fixes the left subtree
				node->_left = removeHelper(temp->_key, node->_left);
			}
		}
		//Updates the node's size
		node->_size = 1 + size(node->_left) + size(node->_right);
		return node;
	}

public:
	// Is there a value paired with key?
	virtual bool contains(const Key& key) const //
	{
		//Calls get helper to see if the node is in the tree, if it isnt returns false, else returns true
		BinaryTreeNode* node = getHelper(key, _root);
		if (node == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
		
	}

	// Is the table empty?
	virtual bool empty() const
	{
		//If the size of the root is 0; the tree is empty
		if (size(_root) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Number of key-value pairs.
	virtual int size() const
	{
		//Returns the size of the tree because the size is the number of keys in the left and right subtrees
		return size(_root);
	}

	// Smallest key
	virtual bool min(Key& key = Key{}) const
	{
		BinaryTreeNode* current = _root;
		//if there are no nodes in the tree
		if (current == nullptr)
		{
			return false;
		}
		else
		{
			//loops left while left is not nullptr and updates the node to that node
			while (current->_left != nullptr)
			{
				current = current->_left;
			}
			//Sets the key equal to that min key
			key = current->_key;
			return true;
		}
		
	}

	// Largest key
	virtual bool max(Key& key = Key{}) const
	{
		BinaryTreeNode* node = getMax(_root);
		if (node == NULL)
		{
			return false;
		}
		else
		{
			//Set the key equal to the max key
			key = node->_key;
			return true;
		}
		
	}
private:
	//Gets the max
	BinaryTreeNode* getMax(BinaryTreeNode* node) const
	{
		if (node == nullptr)
		{
			return NULL;
		}
		else
		{
			//Loops right until right is nullptr and updates the node to that node
			while (node->_right != nullptr)
			{
				node = node->_right;
			}
			return node;
		}
	}


public:

	// Largest key less than or equal to key
	virtual bool floor(const Key& key, Key& floorKey) const
	{
		if (empty())
		{
			return false;
		}
		else
		{
			//Gets the mininum key
			Key minimum;
			min(minimum);
			// if the ke is less than the minimum returns false
			if (keyLessThan(key, minimum))
			{
				return false;
			}
			//set floorkey equal to the floor key found in floorHelper
			floorKey = floorHelper(key, _root)->_key;
			return true;
			
		}
		
	}
private:
	BinaryTreeNode* floorHelper(const Key& key, BinaryTreeNode* node) const
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//left sub-tree
		if (keyLessThan(key, node->_key))
		{
			return floorHelper(key, node->_left);
		}
		//right sub-tree
		if (keyLessThan(node->_key, key))
		{
			//Set temp equal to the recursive call of the right node
			BinaryTreeNode* temp = floorHelper(key, node->_right);
			//returns temp if node is nullptr if not just returns the node
			return (temp != nullptr) ? temp : node;
			
		}
		else
		{
			return node;
		}
		
	}
	
public:

	// Smallest key greater than or equal to key
	virtual bool ceiling(const Key& key, Key& ceilingKey) const
	{
		if (empty())
		{
			return false;
		}
		else
		{
			//gets the maximum of the tree
			BinaryTreeNode* maximum = getMax(_root);
			//If the key maximum key is less than the key passed in returns false
			if (keyLessThan(maximum->_key, key))
			{
				return false;
			}
			//Calls ceiling helper and sets ceilingKey equal to the found node's key
			ceilingKey = ceilingHelper(key, _root)->_key;
			return true;
		}
	}
private:
	BinaryTreeNode* ceilingHelper(const Key& key, BinaryTreeNode* node) const
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		//left sub-tree
		if (keyLessThan(key, node->_key))
		{
			//sets temp equal to the recursive call of the nodes left node
			BinaryTreeNode* temp = ceilingHelper(key, node->_left);
			//if temp is not equal to nullptr returns temp otherwise returns the node
			return (temp != nullptr) ? temp : node;
		}
		//right sub-tree
		if (keyLessThan(node->_key, key))
		{
			return ceilingHelper(key, node->_right);
		}
		else
		{
			return node;
		}
	}

public:
	// Number of keys less than key
	virtual int rank(const Key& key) const
	{
		return getRank(key, _root);
	}
private:
	int getRank(const Key& key, BinaryTreeNode* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}
		//If the key is less than the node's key goes left in the tree
		if (keyLessThan(key, node->_key))
		{
			return getRank(key, node->_left);
		}
		//if the nodes key is less than the key returns the size of the left plus 1 plus the rank of the right key
		else if (keyLessThan(node->_key, key))
		{
			return size(node->_left) + 1 + getRank(key, node->_right);
		}
		else
		{
			//returns the size of the node's left node
			return size(node->_left);
		}
	}

public:
	// key of rank k
	virtual bool select(int k = 0, Key& key = Key{}) const
	{
		//Sets the node equal to the function of selectHelper
		BinaryTreeNode* node = selectHelper(k, _root);
		if (node == NULL)
		{
			return false;
		}
		else
		{
			//Sets key equal to the found node's key
			key = node->_key;
			return true;
		}
	}
private:
	BinaryTreeNode* selectHelper(int k, BinaryTreeNode* node) const
	{
		if (node != nullptr)
		{
			//If the rank of the nodes key is greater than the int k goes left
			if (rank(node->_key) > k)
			{
				return selectHelper(k, node->_left);
			}
			//If the rank of the nodes key is less than the int k, goes right
			else if (rank(node->_key) < k)
			{
				return selectHelper(k, node->_right);
			}
			//otherwise returns the node
			else
			{
				return node;
			}
		}
		else
		{
			return NULL;
		}
	}
public:
	// Delete the smallest key
	virtual bool deleteMin()
	{
		BinaryTreeNode* node = _root;
		if (node == nullptr)
		{
			return false;
		}
		//Goes left in the tree, updating the node until the node's left is nullptr
		while (node->_left != nullptr)
		{
			node = node->_left;
		}
		//calls remove to remove the node
		remove(node->_key);
		return true;
	}

	// Delete the largest key
	virtual bool deleteMax()
	{
		BinaryTreeNode* node = _root;
		if (node == nullptr)
		{
			return false;
		}
		//Goes right in the tree, updating the node until the node's right is nullptr
		while (node->_right != nullptr)
		{
			node = node->_right;
		}
		//calls remove to remove the node
		remove(node->_key);
		return true;
	}

	// number of keys in [low, high] (including low, high)
	virtual int size(const Key& low, const Key& high) const
	{
		if (_root == nullptr)
		{
			return 0;
		}
		//If the low and high node are not null returns the rank of the high minus the low plus 1
		if (getHelper(low, _root) != NULL && getHelper(high, _root) != NULL)
		{
			return rank(high) - rank(low) + 1;
		}
		//If the low node is null and the high node is not, returns the rank of the high minus the low plus 1
		if (getHelper(low, _root) == NULL && getHelper(high, _root) != NULL)
		{
			return rank(high) - rank(low) + 1;
		}
		//Else just return the rank of the high minus the rank of the low
		else
		{
			return rank(high) - rank(low);
		}
	}

	// keys in [low, high] (including low, high), in sorted order
	virtual std::vector<Key> keys(const Key& low, const Key& high) const
	{
		//Makes a vector to be used as a reference to be added to in the Helper
		std::vector<Key> theKeys;
		return keysHelper(low, high, _root, theKeys);
	}
private:
	std::vector<Key> keysHelper(const Key& low, const Key& high, BinaryTreeNode* node, std::vector<Key>& theKeys) const
	{
		//If the node is not nullptr and betweent he high and low
		if (node != nullptr && node->_key >= low && node->_key <= high)
		{
			//In-Order treversal of the tree adding the nodes to a vector
			keysHelper(low, high, node->_left, theKeys);
			theKeys.push_back(node->_key);
			keysHelper(low, high, node->_right, theKeys);
		}
		return theKeys;
	}

public:
	// all keys in the table, in sorted order
	virtual std::vector<Key> keys() const
	{
		Key minimum, maximum;
		min(minimum);
		max(maximum);
		return keys(minimum, maximum);
	}

public:
	// Removes all elements from the table
	virtual void clear()
	{
		if (_root != nullptr) delete _root;
		_root = nullptr;
	}

private:
	// Returns the height of the BST (for debugging).
	// @return the height of the BST (a 1-node tree has height 0)
	int height() const { return height(root); }
	int height(BinaryTreeNode* node) const
	{
		if (node == nullptr) return -1;

		return 1 + std::max(height(node->_left), height(node->_right));
	}

	// Non-recursive node deletion.
	BinaryTreeNode* Delete(BinaryTreeNode* node) const
	{
		node->_left = nullptr;
		node->_right = nullptr;
		delete node;
		node = nullptr;
		return node;
	}

	//
	///////////////////////////////////////////////////////////////////////////////
	// Check integrity of BST data structure.
	///////////////////////////////////////////////////////////////////////////////
	//
	bool check() const
	{
		if (!isBST())            std::cout << "Not in symmetric order" << std::endl;
		if (!isSizeConsistent()) std::cout << "Subtree counts not consistent" << std::endl;
		if (!isRankConsistent()) std::cout << "Ranks not consistent" << std::endl;

		return isBST() && isSizeConsistent() && isRankConsistent();
	}

	//
	// does this binary tree satisfy symmetric order?
	// Note: this test also ensures that data structure is a binary tree since order is strict
	//
	bool isBST() const { return isBST(_root, nullptr, nullptr); }
	// is the tree rooted at x a BST with all keys strictly between min and max
	// (if min or max is null, treat as empty constraint)
	bool isBST(BinaryTreeNode* node, Key* min, Key* max) const
	{
		if (node == nullptr) return true;

		if (min != nullptr && keyLessThanOrEquals(node->_key, *min)) return false;

		if (max != nullptr && keyLessThanOrEquals(*max, node->_key)) return false;

		return isBST(node->_left, min, &(node->_key)) && isBST(node->_right, &(node->_key), max);
	}
	// are the size fields correct?
	bool isSizeConsistent() const { return isSizeConsistent(_root); }
	bool isSizeConsistent(BinaryTreeNode* node) const
	{
		if (node == nullptr) return true;

		// The size of this need must equate to the sum of its children (plus itself)
		if (node->_size != size(node->_left) + size(node->_right) + 1) return false;

		return isSizeConsistent(node->_left) && isSizeConsistent(node->_right);
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