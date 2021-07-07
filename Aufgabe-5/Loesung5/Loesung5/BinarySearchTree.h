#pragma once
#include <iomanip>
#include <sstream>
#include "Node.h"

template<typename T>
class BinarySearchTree
{
	Node<T>* root;
	Node<T>* current;
	int length;

	public:
		BinarySearchTree()
		{
			root = nullptr;
			current = nullptr;
			length = 0;
		}
	
		~BinarySearchTree() { clear(root); }

		int getLength() const { return length; }

		Node<T>* getRoot() const;									// Get node at root
		Node<T>* getCurrent() const;								// Get node at current
		Node<T>* getNode(long key);									// Get node by its key
		int getDepthLeft(Node<T>* node);
		int getDepthRight(Node<T>* node);
		void moveToRoot();											// Move current to root
		void moveToParent();										// Move current to parent
		void moveToChildLeft();										// Move current to child left
		void moveToChildRight();									// Move current to child right
	
		bool checkEmpty();											// Check if tree is empty
		bool ins(const T& data);									// Ins node with value
		bool insNode(const T& data);								// Recursively find ins spot and ins node
		bool insNodeRoot(const T& data);							// Node in Root hinzufügen
		bool insNodeLeft(const T& data);							// Node links hinzufügen
		bool insNodeRight(const T& data);							// Node rechts hinzufügen
		bool del(const long &key);									// Delete node from tree
		void correctKeys(const Node<T>* node);						// Move through all elements and set their keys recursively
		void clear(Node<T>* node);									// Delete all elements from tree
		void ini();													// Initialize Tree with values
		void rotateLeft(const long& key);							// Rotate left though node
		void rotateRight(const long& key);							// Rotate right through node
		void balance(Node<T>* node);
	
		void printPreOrder(const Node<T>* node, std::stringstream& str);	// Print pre order (middle - left - right)
		void printInOrder(const Node<T>* node, std::stringstream& str);		// Print in order (left - middle - right)
		void printPostOrder(const Node<T>* node, std::stringstream& str);	// Print post oder (left - right - middle)
		
};

template<typename T>
Node<T>* BinarySearchTree<T>::getRoot() const
{
	if (root != nullptr)
		return root;
	throw std::out_of_range("Error in getRoot(): Can not getRoot() on nullptr.");
}

template<typename T>
Node<T>* BinarySearchTree<T>::getCurrent() const
{
	if (current != nullptr)
		return current;
	throw std::out_of_range("Error in getCurrent(): Can not getCurrent() on nullptr.");
}

template<typename T>
Node<T>* BinarySearchTree<T>::getNode(const long key)
{
	moveToRoot();
	std::string keystr = std::to_string(key);
	if (keystr.length() == 1 && key != 1)
		throw std::out_of_range("Error in getNode(): Key does not exist.");
	
	keystr.erase(keystr.begin());
	while (keystr.length() > 0)
	{
		if (keystr.front() != '0' && keystr.front() != '1')
			throw std::out_of_range("Error in getNode(): Valid key only consists of 1 and 0.");
		
		try
		{
			if (keystr.front() == '0')
				moveToChildLeft();
			if (keystr.front() == '1')
				moveToChildRight();
			keystr.erase(keystr.begin());
		}
		catch (std::out_of_range &e) 
		{
			throw std::out_of_range("Error in getNode(): Key does not exist.");
		}
	}

	return current;
}

template<typename T>
int BinarySearchTree<T>::getDepthLeft(Node<T>* node)
{
	if (!checkEmpty())										// Check if tree is not empty
	{
		while (node->childLeft != nullptr)
			node = node->childLeft;
		return std::to_string(node->key).length();
	}

	return 0;
}

template<typename T>
int BinarySearchTree<T>::getDepthRight(Node<T>* node)
{
	if (!checkEmpty())										// Check if tree is not empty
	{
		while (node->childRight != nullptr)
			node = node->childRight;
		return std::to_string(node->key).length();
	}

	return 0;
}


template<typename T>
void BinarySearchTree<T>::moveToRoot()
{
	if (root == nullptr)
		throw std::out_of_range("Error in moveToRoot(): Root is nullptr.");

	current = root;
}

template<typename T>
void BinarySearchTree<T>::moveToParent()
{
	if (current == root)
		throw std::out_of_range("Error in moveToParent(): Already on root.");
	if (current->parent == nullptr)
		throw std::out_of_range("Error in moveToParent(): Parent is nullptr.");

	current = current->parent;
}

template<typename T>
void BinarySearchTree<T>::moveToChildRight()
{
	if (current == nullptr)
		throw std::out_of_range("Error in moveToChildRight(): Current is nullptr");
	if (current->childRight == nullptr)
		throw std::out_of_range("Error in moveToChildRight(): Child is nullptr.");

	current = current->childRight;
}

template<typename T>
void BinarySearchTree<T>::moveToChildLeft()
{
	if (current == nullptr)
		throw std::out_of_range("Error in moveToChildLeft(): Current is nullptr");
	if (current->childLeft == nullptr)
		throw std::out_of_range("Error in moveToChildLeft(): Child is nullptr.");

	current = current->childLeft;
}


template<typename T>
bool BinarySearchTree<T>::checkEmpty()
{
	return root == nullptr && current == nullptr && length == 0;
}

template<typename T>
bool BinarySearchTree<T>::ins(const T& data)
{
	// Move current to root beforehand
	if (!checkEmpty())
		moveToRoot();

	// Call recursive insNode function to find insert spot and insert
	return insNode(data);
}

template<typename T>
bool BinarySearchTree<T>::insNode(const T& data)
{
	// Tree empty - add to root
	if (checkEmpty())
		return insNodeRoot(data);

	// If data is smaller than current data move to left subtree recursively until nullptr
	if (data <= current->data)
	{
		if (current->childLeft != nullptr)
		{
			moveToChildLeft();
			insNode(data);
		}
		else
			return insNodeLeft(data);
	}
	// If data is bigger than current data move to right subtree recursively until nullptr
	else
	{
		if (current->childRight != nullptr)
		{
			moveToChildRight();
			insNode(data);
		}
		else
			return insNodeRight(data);
	}
		
	return false;
}


template<typename T>
bool BinarySearchTree<T>::insNodeRoot(const T& data)
{
	if (root != nullptr)
		throw std::out_of_range("Error in insNodeRoot(): Root already exists.");

	// Create new node
	root = new Node<T>;
	root->key = 1;
	root->data = data;

	// Change tree specs
	current = root;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insNodeLeft(const T& data)
{
	// Exceptions
	if (root == nullptr)
		throw std::out_of_range("Error in insNodeLeft(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insNodeLeft(): Current is nullptr.");
	if (current->childLeft != nullptr)
		throw std::out_of_range("Error in insNodeLeft(): ChildLeft already exists.");

	// Create new node
	Node<T>* child = new Node<T>;
	child->key = current->key * 10;
	child->data = data;
	child->parent = current;
	current->childLeft = child;

	// Change tree specs
	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insNodeRight(const T& data)
{
	// Exceptions
	if (root == nullptr)
		throw std::out_of_range("Error in insNodeRight(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insNodeRight(): Current is nullptr.");
	if (current->childRight != nullptr)
		throw std::out_of_range("Error in insNodeRight(): ChildRight already exists.");

	// Create new node
	Node<T>* child = new Node<T>;
	child->key = current->key * 10 + 1;
	child->data = data;
	child->parent = current;
	current->childRight = child;

	// Change tree specs
	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::del(const long &key)
{
	// Try to find node user wants to delete by key
	try
	{
		current = getNode(key);
	}
	catch (...)
	{
		throw std::invalid_argument("Error in del(): Invalid key.");
	}

	// Edge case only node
	if (current->childLeft == nullptr && current->childRight == nullptr && length == 1)
	{
		// Delete node
		delete current;
		current = nullptr;
		length--;
		return true;
	}


	// Case 0 : 0 Childs
	if (current->childLeft == nullptr && current->childRight == nullptr)    
	{
		// Change parents pointers
		// if node was left - left now nullptr
		if (current->parent->childLeft != nullptr && current->parent->childLeft->key == current->key)
			current->parent->childLeft = nullptr;
		// if node was right - right now nullptr
		else if (current->parent->childRight != nullptr && current->parent->childRight->key == current->key)
			current->parent->childRight = nullptr;
		else
			throw std::invalid_argument("Error in del(): Invalid key.");
	}

	// Case 1 : 1 Child
	if (current->childLeft != nullptr && current->childRight == nullptr || current->childLeft == nullptr && current->childRight != nullptr)
	{
		// If child is right
		if (current->childRight != nullptr)
		{
			// Change child pointers
			current->childRight->parent = current->parent;
			// Change parents pointers
			current->parent->childRight = current->childRight;
		}
		else if (current->childLeft != nullptr)
		{
			// Change child pointers
			current->childLeft->parent = current->parent;
			// Change parents pointers
			current->parent->childLeft = current->childLeft;
		}
		else
			throw std::invalid_argument("Error in del(): Invalid key.");
	}

	// Case 2 : 2 Childs
	if (current->childLeft != nullptr && current->childRight != nullptr)
	{
		// Tmp save deleted node (will dangle after move)
		Node<T>* deleteNode = current;
		// Subtree right of deleted node
		Node<T>* tmp = current->childRight;
		
		// 1. Move left child up
		if (current == root)
		{
			current->childLeft->key = 1;
			current->childLeft->parent = nullptr;
			root = current->childLeft;
		}
		else
		{
			current->parent->childRight = current->childLeft;
			current->childLeft->parent = current->parent;
		}
			

		// 2. Move current to left child, laving old parent dangling
		current = current->childLeft;

		// 3. Get lowest childright to append right subtree onto
		while (current->childRight != nullptr)
			current = current->childRight;
		current->childRight = tmp;
		tmp->parent = current->childRight;

		// 4. Move current to dangling parent to delete it
		current = deleteNode;
	}

	// Delete node
	delete current;
	current = nullptr;
	length--;
	correctKeys(root);
	return true;
}

template<typename T>
void BinarySearchTree<T>::correctKeys(const Node<T>* node)
{
	if (node->childLeft != nullptr)
	{
		node->childLeft->key = node->key * 10;
		correctKeys(node->childLeft);
	}
	
	if (node->childRight!= nullptr)
	{
		node->childRight->key = node->key * 10 + 1;
		correctKeys(node->childRight);
	}

}

template<typename T>
void BinarySearchTree<T>::clear(Node<T>* node)
{
	if (checkEmpty())
		return;
	if (node->childLeft != nullptr)
		clear(node->childLeft);
	if (node->childRight != nullptr)
		clear(node->childRight);

	delete node;
	current = nullptr;
	root = nullptr;
	length--;
}

template<typename T>
void BinarySearchTree<T>::ini()
{
	// Binary Tree
	// T n1 = 4;
	// T n2 = 2;
	// T n3 = 6;
	// T n4 = 1;
	// T n5 = 3;
	// T n6 = 5;
	// T n7 = 7;
	// T n8 = 3;
	// T n9 = 1;
	// T n10 = 1;

	// Weird tree
	T n1 = 1;
	T n2 = 2;
	T n3 = 3;
	T n4 = 4;
	T n5 = 5;
	T n6 = 6;
	T n7 = 7;
	T n8 = 8;
	T n9 = 9;
	T n10 = 1;
	
	ins(n1);
	ins(n2);
	ins(n3);
	ins(n4);
	ins(n5);
	ins(n6);
	ins(n7);
	ins(n8);
	ins(n9);
	ins(n10);
}

template<typename T>
void BinarySearchTree<T>::rotateLeft(const long& key)
{
	if (checkEmpty())
		throw std::out_of_range("Error in rotateLeft(): Can not rotate on empty tree.");

	
	Node<T>* center = getNode(key);					// center of rotation
	if (center->childRight == nullptr)
		throw std::out_of_range("Error in rotateLeft(): Can not rotate if right subtree is empty.");

	Node<T>* top;									// top of rotation
	if (center != root)
		top = getNode(center->parent->key);
	else
		top = nullptr;

	Node<T>* bottom = center->childRight;			// bottom of rotation (right side)
	Node<T>* sub = bottom->childLeft;				// sub of bottom left side (will be appended on left side)


	// ========================================Rotieren=========================================
	center->childRight = sub;						// append sub to childRight of center
	if (sub != nullptr)
		sub->parent = center;
	bottom->childLeft = center;						// append center to left of bottom (will be rotated up) forming new cluster
	center->parent = bottom;

													// Change parent pointers
	if (top == nullptr) {							// when center was root bottom rotated up to new root
		root = bottom;
		root->key = 1;
	}
	else if (center == top->childLeft)				// if center was on left side - bottom rotate up to left of top
		top->childLeft = bottom;
	else if (center == top->childRight)				// if center was on right side - bottom rotate up to right of top
		top->childRight = bottom;			
	else
		throw std::runtime_error("Error in rotateLeft(): Something went wrong.");

	correctKeys(root);				//Schlüssel aktualiseren

}


template<typename T>
void BinarySearchTree<T>::rotateRight(const long& key)
{
	// Exceptions
	if (checkEmpty())
		throw std::out_of_range("Error in rotateRight(): Can not rotate on empty tree.");

	
	Node<T>* center = getNode(key);				// right side of rotation
	if (center->childLeft == nullptr)
		throw std::out_of_range("Error in rotateRight(): Can not rotate if left subtree is empty.");

	Node<T>* top;								// top of rotation
	if (center != root)
		top = getNode(center->parent->key);			
	else
		top = nullptr;

	Node<T>* bottom = center->childLeft;		// bottom of rotation (left side)
	Node<T>* sub = bottom->childRight;			// sub of left side (will be appended on right side)

	
	// ========================================Rotieren=========================================
	center->childLeft = sub;					// append sub to childLeft of center
	if (sub!=nullptr)
		sub->parent = center;
	bottom->childRight = center;				// append center to right side of bottom (will be rotated up) forming new cluster
	center->parent = bottom;
												// Change parent pointers
	if (top == nullptr) {						// when center was root bottom rotated up to new root
		root = bottom;
		root->key = 1;
	}
	else if (center == top->childRight)			// if center was on right side - bottom rotate up to right of top
		top->childRight = bottom;
	else if (center == top->childLeft)			// if center was on left side - bottom rotate up to left of top
		top->childLeft = bottom;
	else
		throw std::runtime_error("Error in rotateLeft(): Something went wrong.");

	correctKeys(root);							// refresh keys from root down
}

template<typename T>
void BinarySearchTree<T>::balance(Node<T>* node)
{
	const int heightdiff = getDepthLeft(node) - getDepthRight(node);

	if (heightdiff != 0)
	{
		if (heightdiff < -1)
		{
			rotateLeft(node->key);
			balance(node->parent);
		}
		else if (heightdiff > 1)
		{
			rotateRight(node->key);
			balance(node->parent);
		}
	}

	if (node->childRight != nullptr)
		balance(node->parent);
	if (node->childLeft != nullptr)
		balance(node->parent);
}


template<typename T>
void BinarySearchTree<T>::printPreOrder(const Node<T>* node, std::stringstream& str)
{

	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
		return;
	}

	for (int i = 1; i < std::to_string(node->key).length(); ++i)
	{
		str << "| ";
	}
	str << "> " << node->key << ": " << node->data << std::endl;
	if (node->childLeft != nullptr)
		printPreOrder(node->childLeft, str);
	if (node->childRight != nullptr)
		printPreOrder(node->childRight, str);

}

template<typename T>
void BinarySearchTree<T>::printInOrder(const Node<T>* node, std::stringstream& str)
{

	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
		return;
	}

	if (node->childLeft != nullptr)
		printInOrder(node->childLeft, str);
	
	for (int i = 1; i < std::to_string(node->key).length(); ++i)
	{
		str << "| ";
	}
	str << "> " << node->key << ": " << node->data << std::endl;
	
	if (node->childRight != nullptr)
		printInOrder(node->childRight, str);

}

template<typename T>
void BinarySearchTree<T>::printPostOrder(const Node<T>* node, std::stringstream& str)
{

	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
		return;
	}

	if (node->childLeft != nullptr)
		printPostOrder(node->childLeft, str);
	if (node->childRight != nullptr)
		printPostOrder(node->childRight, str);

	for (int i = 1; i < std::to_string(node->key).length(); ++i)
	{
		str << "| ";
	}
	str << "> " << node->key << ": " << node->data << std::endl;

}