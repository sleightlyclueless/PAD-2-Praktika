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
		void moveToRoot();
		void moveToParent();
		void moveToChildLeft();
		void moveToChildRight();
	
		bool checkEmpty();
		bool insRoot(T &data);
		bool insLeft(Node<T>* parent, T& data);
		bool insRight(Node<T>* parent, T& data);
		bool del();

		void clear(Node<T>* node);
		void print(const Node<T>* node, std::stringstream& str);
		
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
	if (current->childRight == nullptr)
		throw std::out_of_range("Error in moveToChildRight(): Child is nullptr.");

	current = current->childRight;
}

template<typename T>
void BinarySearchTree<T>::moveToChildLeft()
{
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
bool BinarySearchTree<T>::insLeft(Node<T>* parent, T& data)
{
	if (root == nullptr)
		throw std::out_of_range("Error in insLeft(): Root is still nullptr.");
	if (parent == nullptr)
		throw std::out_of_range("Error in insLeft(): Parent is nullptr.");
	if (parent->childLeft != nullptr)
		throw std::out_of_range("Error in insLeft(): ChildLeft already exists.");

	Node<T>* child = new Node<T>;
	child->key = parent->key * 10;
	child->data = data;
	child->parent = parent;
	parent->childLeft = child;

	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insRight(Node<T>* parent, T& data)
{
	if (root == nullptr)
		throw std::out_of_range("Error in insRight(): Root is still nullptr.");
	if (parent == nullptr)
		throw std::out_of_range("Error in insRight(): Parent is nullptr.");
	if (parent->childRight != nullptr)
		throw std::out_of_range("Error in insRight(): ChildRight already exists.");

	Node<T>* child = new Node<T>;
	child->key = parent->key * 10 + 1;
	child->data = data;
	child->parent = parent;
	parent->childRight = child;

	current = child;
	length++;
	return true;
}

// TODO: DELETE
template<typename T>
bool BinarySearchTree<T>::del()
{
	return true;
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
void BinarySearchTree<T>::print(const Node<T>* node, std::stringstream& str)
{
	
	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
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
