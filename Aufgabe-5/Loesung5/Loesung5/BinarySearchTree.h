#pragma once
#include <iomanip>
#include <sstream>
#include <cmath>
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
		~BinarySearchTree()
		{
			clear(root);
		}

		int getLength() const { return length; }		// getters and setters for private vars
		Node<T>* getRoot() const { return root; }
		Node<T>* getCurrent() const { return current; }

		Node<T>* get() const;
	
		bool checkEmpty();
		bool insRoot(T &data);
		bool insLeft(Node<T>* parent, T& data);
		bool insRight(Node<T>* parent, T& data);
		bool del();
	
		void print_tree(const Node<T>* node, std::stringstream& str);
		void clear(Node<T>* node);
};


template<typename T>
Node<T>* BinarySearchTree<T>::get() const
{
	if (current != nullptr)
		return current;
	throw std::out_of_range("Error in get(): Can not get() on empty pointer.");
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
		return false;
	
	root = new Node<T>;
	root->key = 1.0;
	root->data = data;

	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::insLeft(Node<T>* parent, T& data)
{
	if (parent == nullptr)
		return false;
	if (parent->childLeft != nullptr)
		return false;

	Node<T>* child = new Node<T>;
	double whole;
	if (std::modf(parent->key, &whole) == 0.1)
		child->key = parent->key + 1;
	else
		child->key = parent->key + 0.9 + std::modf(parent->key, &whole) * 2;
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
	if (parent == nullptr)
		return false;
	if (parent->childRight != nullptr)
		return false;

	Node<T>* child = new Node<T>;
	double whole;
	child->key = parent->key + 1 + std::modf(parent->key, &whole) * 2;
	child->data = data;
	child->parent = parent;
	parent->childRight = child;

	current = child;
	length++;
	return true;
}

template<typename T>
bool BinarySearchTree<T>::del()
{
	return true;
}



template<typename T>
void BinarySearchTree<T>::print_tree(const Node<T>* node, std::stringstream& str)
{
	
	if (checkEmpty())
	{
		str << "Tree empty!" << std::endl;
	}

	for (int i = 0; i < static_cast<int>(node->key); ++i)
	{
		str << "| ";
	}
	str << node->data << std::endl;

	if (node->childLeft != nullptr)
		print_tree(node->childLeft, str);
	if (node->childRight != nullptr)
		print_tree(node->childRight, str);

}

template<typename T>
void BinarySearchTree<T>::clear(Node<T>* node)
{
	if (checkEmpty())
		throw std::out_of_range("Error in clear() - tree already empty");
	if (node->childLeft != nullptr)
		clear(node->childLeft);
	if (node->childRight != nullptr)
		clear(node->childRight);

	delete node;
}
