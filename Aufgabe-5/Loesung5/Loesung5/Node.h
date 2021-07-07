#pragma once

template<typename T>
class Node
{
	public:
		T data;					// Data of Node
		long key;				// Key of Node
		Node<T>* childLeft;		// ChildLeft pointer of Node
		Node<T>* childRight;	// ChildRight pointer of Node
		Node<T>* parent;		// Parent pointer of Node

		Node()					// Constructor
		{
			data = {};
			key = 0;
			parent = nullptr;
			childLeft = nullptr;
			childRight = nullptr;
		}

		~Node() = default;		// Destructor

		T print() const			// Print to return data
		{
			return data;
		}
};