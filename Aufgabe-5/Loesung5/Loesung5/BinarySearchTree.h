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
	
		Node<T>* getRoot() const;
		Node<T>* getCurrent() const;
		Node<T>* searchNode(const long key);
		Node<T>* searchLowestNode(Node<T>* node, Node<T>* lowest);
		void moveToRoot();
		void moveToParent();
		void moveToChildLeft();
		void moveToChildRight();
	
		bool checkEmpty();
		bool insRoot(T &data);
		bool insLeft(T& data);
		bool insRight(T& data);
		bool del(const long &key);
		void correctKeys(const Node<T>* node);

		void clear(Node<T>* node);
		void ini();
		void print(const Node<T>* node, std::stringstream& str);
		void printPreOrder(const Node<T>* node, std::stringstream& str);
		void printInOrder(const Node<T>* node, std::stringstream& str);
		void printPostOrder(const Node<T>* node, std::stringstream& str);
		
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
Node<T>* BinarySearchTree<T>::searchNode(const long key)
{
	current = root;
	std::string keystr = std::to_string(key);
	if (keystr.length() == 1 && key != 1)
		throw std::out_of_range("Error in searchNode(): Key does not exist.");
	
	keystr.erase(keystr.begin());
	while (keystr.length() > 0)
	{
		try
		{
			if (keystr.front() == '0')
				moveToChildLeft();
			if (keystr.front() == '1')
				moveToChildRight();
		}

		catch (std::out_of_range &e) 
		{
			throw std::out_of_range("Error in searchNode(): Key does not exist.");
		}
		
		if (keystr.front() != '0' && keystr.front() != '1')
			throw std::out_of_range("Error in searchNode(): Valid key only consists of 1 and 0.");
		keystr.erase(keystr.begin());
	}

	return current;
}

template<typename T>
Node<T>* BinarySearchTree<T>::searchLowestNode(Node<T>* node, Node<T>* lowest)
{
	if (node->key < lowest->key)
		lowest = node;
	if (node->childLeft != nullptr)
		searchLowestNode(node->childLeft, lowest);
	if (node->childRight != nullptr)
		searchLowestNode(node->childRight, lowest);
	
	return lowest;
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
bool BinarySearchTree<T>::insRoot(T& data)
{
	if (root != nullptr)
		throw std::out_of_range("Error in insRoot(): Root already exists.");
	
	root = new Node<T>;
	root->key = 1;
	root->data = data;

	current = root;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insLeft(T& data)
{
	if (root == nullptr)
		throw std::out_of_range("Error in insLeft(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insLeft(): Parent is nullptr.");
	if (current->childLeft != nullptr)
		throw std::out_of_range("Error in insLeft(): ChildLeft already exists.");

	Node<T>* child = new Node<T>;
	child->key = current->key * 10;
	child->data = data;
	child->parent = current;
	current->childLeft = child;

	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insRight(T& data)
{
	if (root == nullptr)
		throw std::out_of_range("Error in insRight(): Root is still nullptr.");
	if (current == nullptr)
		throw std::out_of_range("Error in insRight(): Parent is nullptr.");
	if (current->childRight != nullptr)
		throw std::out_of_range("Error in insRight(): ChildRight already exists.");

	Node<T>* child = new Node<T>;
	child->key = current->key * 10 + 1;
	child->data = data;
	child->parent = current;
	current->childRight = child;

	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::del(const long &key)
{

	Node<T>* node;
	try
	{
		node = searchNode(key);
	}
	catch (...)
	{
		throw std::invalid_argument("Error in del(): Invalid key.");
	}

	//wenn Kinderanzahl 0: Vaters Zeiger umbiegen
	if (node->childLeft == nullptr && node->childRight == nullptr)    
	{
		// Vaters Zeiger umbiegen
		// wenn Element links war:
		if (node->parent->childLeft != nullptr && node->parent->childLeft->key == node->key)
			node->parent->childLeft = nullptr;
		// wenn Element rechts war:
		else if (node->parent->childRight != nullptr && node->parent->childRight->key == node->key)
			node->parent->childRight = nullptr;
		else
			throw std::invalid_argument("Error in del(): Invalid key.");
	}

	//wenn Kinderanzahl 1:  Vaters Zeiger und folgezeiger umbiegen
	if (node->childLeft != nullptr && node->childRight == nullptr || node->childLeft == nullptr && node->childRight != nullptr)
	{
		// Zeiger von childs umbiegen
		if (node->childRight != nullptr)
		{
			node->childRight->parent = node->parent;
			node->childRight->key = node->key;

			// Vaters Zeiger umbiegen
			if (node->parent->childLeft != nullptr && node->parent->childLeft->key == node->key)
				node->parent->childLeft = node->childRight;
			else if (node->parent->childRight != nullptr && node->parent->childRight->key == node->key)
				node->parent->childRight = node->childRight;
			else
				throw std::invalid_argument("Error in del(): Invalid key.");
		}
		else if (node->childLeft != nullptr)
		{
			node->childLeft->parent = node->parent;
			node->childLeft->key = node->key;
			
			// Vaters Zeiger umbiegen
			if (node->parent->childLeft != nullptr && node->parent->childLeft->key == node->key)
				node->parent->childLeft = node->childLeft;
			else if (node->parent->childRight != nullptr && node->parent->childRight->key == node->key)
				node->parent->childRight = node->childLeft;
			else
				throw std::invalid_argument("Error in del(): Invalid key.");
		}
		else
			throw std::invalid_argument("Error in del(): Invalid key.");


	}

	//wenn Kinderanzahl 2: löschen, Vaters Zeiger umbiegen
	if (node->childLeft != nullptr && node->childRight != nullptr)
	{
		// Zeiger von childs umbiegen
		if (node->childRight->childLeft != nullptr && node->childRight->childRight != nullptr)
		{
			node->childRight->childRight->childLeft = node->childRight->childLeft;
			node->childRight->childRight->childLeft->parent = node->childRight->childRight;
			node->childRight->childLeft = node->childLeft;
			node->childRight->childLeft->parent = node->childRight;
		}
		else
		{
			node->childRight->childLeft = node->childLeft;
		}
		
		if (node != root)
		{
			node->childRight->parent = node->parent;

			// Vaters Zeiger umbiegen
			if (node->parent->childRight != nullptr && node->parent->childRight->key == node->key)
				node->parent->childRight = node->childRight;
			else
				throw std::invalid_argument("Error in del(): Invalid key.");
		}
		else
		{
			node->childRight->parent = nullptr;
			node->childRight->key = 1;
			root = node->childRight;
		}

		
		
	}
	
	delete node;    //Element löschen
	node = nullptr;
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
	T n1 = 1;
	T n2 = 2;
	T n3 = 3;
	T n4 = 4;
	T n5 = 5;
	T n6 = 6;
	T n7 = 7;
	T n8 = 8;
	insRoot(n1);
	insLeft(n2);
	insLeft(n4);
	moveToParent();
	insRight(n5);
	moveToRoot();
	insRight(n3);
	insRight(n7);
	moveToParent();
	insLeft(n6);
	insRight(n8);
	moveToRoot();
}

template<typename T>
void BinarySearchTree<T>::print(const Node<T>* node, std::stringstream& str)
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
	str << "> " << node->data << std::endl;

	if (node->childLeft != nullptr)
		print(node->childLeft, str);
	if (node->childRight != nullptr)
		print(node->childRight, str);

}

template<typename T>
void BinarySearchTree<T>::printPreOrder(const Node<T>* node, std::stringstream& str)
{

	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
		return;
	}

	str << node->key << ": " << node->data << std::endl;
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
	
	str << node->key << ": " << node->data << std::endl;
	
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

	str << node->key << ": " << node->data << std::endl;

}