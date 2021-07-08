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
		BinarySearchTree()											// Constructor
		{
			root = nullptr;
			current = nullptr;
			length = 0;
		}
	
		~BinarySearchTree() { clear(root); }						// Destructor

		int getLength() const { return length; }					// Get length of tree (amount of nodes)

		Node<T>* getRoot() const;									// Get node at root
		Node<T>* getCurrent() const;								// Get node at current
		Node<T>* getNode(const long& key);							// Get node by its key
		long getLowestNode(Node<T>* node, long& lowestkey);			// Recustively find and return key of lowest childnode
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
		bool del(const long& key);									// Delete node from tree
		void correctKeys(const Node<T>* node);						// Move through all elements and set their keys recursively
		void clear(Node<T>* node);									// Delete all elements from tree
		void ini();													// Initialize Tree with values
		void rotateLeft(const long& key);							// Rotate left though node
		void rotateRight(const long& key);							// Rotate right through node
		void balance(Node<T>* node);								// Balance tree by recursively rotating through to same level
	
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
Node<T>* BinarySearchTree<T>::getNode(const long& key)
{
	moveToRoot();
	std::string keystr = std::to_string(key);
	if (keystr.length() == 1 && key != 1)
		throw std::out_of_range("Error in getNode(): Key does not exist.");
	
	keystr.erase(keystr.begin());								// keys are long ints with *10 or *10 + 1
	while (keystr.length() > 0)										// -> we follow that path marking left (0) and right(1)
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
long BinarySearchTree<T>::getLowestNode(Node<T>* node, long& lowestkey)
{
	if (!checkEmpty() && node != nullptr)							// check if tree is not empty
	{
		if (node->key > lowestkey)
			lowestkey = node->key;
		if (node->childRight != nullptr)
			getLowestNode(node->childRight, lowestkey);
		if (node->childLeft !=  nullptr)
			getLowestNode(node->childLeft, lowestkey);

		return lowestkey;
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
	// move current to root beforehand
	if (!checkEmpty())
		moveToRoot();

	// call recursive insNode function to find insert spot and insert
	return insNode(data);
}

template<typename T>
bool BinarySearchTree<T>::insNode(const T& data)
{
	// tree empty - add to root
	if (checkEmpty())
		return insNodeRoot(data);

	// if data is smaller than current data move to left subtree recursively until nullptr
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
	// if data is bigger than current data move to right subtree recursively until nullptr
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

	// create new node
	root = new Node<T>;
	root->key = 1;
	root->data = data;

	// change tree specs
	current = root;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insNodeLeft(const T& data)
{
	// exceptions
	if (root == nullptr)
		throw std::out_of_range("Error in insNodeLeft(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insNodeLeft(): Current is nullptr.");
	if (current->childLeft != nullptr)
		throw std::out_of_range("Error in insNodeLeft(): ChildLeft already exists.");

	// create new node
	Node<T>* child = new Node<T>;
	child->key = current->key * 10;
	child->data = data;
	child->parent = current;
	current->childLeft = child;

	// change tree specs
	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insNodeRight(const T& data)
{
	// exceptions
	if (root == nullptr)
		throw std::out_of_range("Error in insNodeRight(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insNodeRight(): Current is nullptr.");
	if (current->childRight != nullptr)
		throw std::out_of_range("Error in insNodeRight(): ChildRight already exists.");

	// create new node
	Node<T>* child = new Node<T>;
	child->key = current->key * 10 + 1;
	child->data = data;
	child->parent = current;
	current->childRight = child;

	// change tree specs
	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::del(const long& key)
{
	// try to find node user wants to delete by key
	try
	{
		current = getNode(key);
	}
	catch (...)
	{
		throw std::invalid_argument("Error in del(): Invalid key - node does not exist.");
	}

	// case X : edge case only node
	if (current->childLeft == nullptr && current->childRight == nullptr && length == 1)
	{
		// delete node
		delete current;
		current = nullptr;
		length--;
		return true;
	}

	// case 0 : 0 childs
	if (current->childLeft == nullptr && current->childRight == nullptr)
	{																											 /*	1		1		*/
		// change parents pointers																				 /*	 \		 \		*/
		// if node was left - left now nullptr																	 /*	   2	 [10]	*/
		if (current->parent->childLeft != nullptr && current->parent->childLeft->key == current->key)			 /*	    \			*/
			current->parent->childLeft = nullptr;																 /*	     [10]		*/
		// if node was right - right now nullptr																 
		else if (current->parent->childRight != nullptr && current->parent->childRight->key == current->key)	 /*   	 1		1	*/
			current->parent->childRight = nullptr;																 /*	    / 	   /	*/
		else																									 /*	   2	  2		*/
			throw std::invalid_argument("Error in del(): Invalid key.");									 /*   /				*/
	}																											 /* [10]			*/

	// case 1 : 1 child
	if (current->childLeft != nullptr && current->childRight == nullptr || current->childLeft == nullptr && current->childRight != nullptr)
	{
		// if child is right
		if (current->childRight != nullptr)
		{																										 /*   2	      2		*/
			// change child pointers																			 /*  /  \	 / \	*/
			current->childRight->parent = current->parent;														 /* 6   [8]	6	10	*/
			// change parents pointers																			 /*		  \			*/
			current->parent->childRight = current->childRight;													 /*		  10		*/
		}
		else if (current->childLeft != nullptr)
		{																										 /*     2	   2	*/
			// change child pointers																			 /*    / \	  / \	*/
			current->childLeft->parent = current->parent;														 /*  [8]  6	 10	 6	*/
			// change parents pointers																			 /*	 /				*/
			current->parent->childLeft = current->childLeft;													 /* 10				*/
		}
		else
			throw std::invalid_argument("Error in del(): Invalid key.");
	}

	// case 2 : 2 childs
	if (current->childLeft != nullptr && current->childRight != nullptr)
	{
		// tmp save deleted node (will dangle after move)
		Node<T>* deleteNode = current;
		// Subtree right of deleted node
		Node<T>* tmp = current->childRight;

		// 1. move left child up
		if (current == root)																		  /*		If Root:			*/
		{																							  /*     [3]		   1		*/
			current->childLeft->key = 1;															  /*    /   \		  / \		*/
			current->childLeft->parent = nullptr;													  /*   1     5		 0	 2		*/
			root = current->childLeft;																  /*  / \   / \			  \		*/
		}																							  /* 0	 2 4   6		   5	*/
		else																						  /*					  / \	*/
		{																							  /*					 4   6	*/
			current->parent->childRight = current->childLeft;
			current->childLeft->parent = current->parent;
		}
																									  /*          No Root:			*/
																									  /*       5			5		*/
		// 2. move current to left child, laving old parent dangling								  /*      / \		   / \		*/
		current = current->childLeft;																  /*     3  [8]		  3   6		*/
																									  /*    /  /   \	 /	 / \	*/
		// 3. get lowest childright to append right subtree onto									  /*   1  6		11	1	6	7	*/
		while (current->childRight != nullptr)														  /*  / \		/\			 \	*/
			current = current->childRight;															  /* 6   7	   9  12		 11	*/
		current->childRight = tmp;																	  /*						 /\	*/
		tmp->parent = current->childRight;															  /*						9 12*/

		// 4. move current to dangling parent to delete it
		current = deleteNode;
	}

	// delete node
	delete current;
	current = nullptr;
	length--;
	correctKeys(root);
	return true;
}

template<typename T>
void BinarySearchTree<T>::correctKeys(const Node<T>* node)
{
	if (checkEmpty())
		return;
	
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
	// binary Tree
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

	// random tree
	for (int i = 1; i <= 15; i++)
	{
		T n = rand() % 30;
		ins(n);
	}
	
}

template<typename T>
void BinarySearchTree<T>::rotateLeft(const long& key)
{
	if (checkEmpty())
		throw std::out_of_range("Error in rotateLeft(): Can not rotate on empty tree.");

	
	Node<T>* center = getNode(key);				// center of rotation
	if (center->childRight == nullptr)
		throw std::out_of_range("Error in rotateLeft(): Can not rotate if left subtree is empty.");

	Node<T>* top;								// top of rotation
	if (center != root)
		top = center->parent;
	else
		top = nullptr;

	Node<T>* bottom = center->childRight;		// bottom of rotation (right side)
	Node<T>* sub = bottom->childLeft;			// sub of bottom left side (will be appended on left side)

	// ========================================Rotieren=========================================
	//	  T							 T					
	//	  |							 |					
	// 	 [C]						[B]					
	// 	 / \		====>			/ \
	// 	1   B					   C   5					
	// 	   / \					  / \
	// 	  S   5					 1   S
	
	center->childRight = sub;					// append sub to childRight of center
	if (sub != nullptr)
		sub->parent = center;
	bottom->childLeft = center;					// append center to left of bottom (will be rotated up) forming new cluster
	center->parent = bottom;

												// change parent pointers
	if (top == nullptr) {						// when center was root bottom rotated up to new root
		root = bottom;
		root->key = 1;
	}
	else if (center == top->childLeft)			// if center was on left side - bottom rotate up to left of top
		top->childLeft = bottom;
	else if (center == top->childRight)			// if center was on right side - bottom rotate up to right of top
		top->childRight = bottom;			
	else
		throw std::runtime_error("Error in rotateLeft(): Something went wrong.");

	correctKeys(root);							// refresh keys

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
		top = center->parent;			
	else
		top = nullptr;

	Node<T>* bottom = center->childLeft;		// bottom of rotation (left side)
	Node<T>* sub = bottom->childRight;			// sub of left side (will be appended on right side)

	// ========================================Rotieren=========================================
	//	   T						  T	
	//	   |						  |
	//    [C]						 [B]
	//    / \			====>		 / \
	//   B   5						1   C
	//  / \							   / \
	// 1   S						  S   5
	
	center->childLeft = sub;					// append sub to childLeft of center
	if (sub!=nullptr)
		sub->parent = center;
	bottom->childRight = center;				// append center to right side of bottom (will be rotated up) forming new cluster
	center->parent = bottom;
												// change parent pointers
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
	long lowestLeft = 0;
	lowestLeft = getLowestNode(node->childLeft, lowestLeft);
	long lowestRight = 0;
	lowestRight = getLowestNode(node->childRight, lowestRight);
	const long heightdiff = std::to_string(lowestLeft).length() - std::to_string(lowestRight).length();

	if (heightdiff < -1)				// left bigger than right - recursively rotate left
	{
		rotateLeft(node->key);
		balance(node->parent);
	}
	else if (heightdiff > 1)			// right bigger than left - recursively rotate right
	{
		rotateRight(node->key);
		balance(node->parent);
	}
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
		str << "| ";
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
		str << "| ";
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
		str << "| ";
	str << "> " << node->key << ": " << node->data << std::endl;
}