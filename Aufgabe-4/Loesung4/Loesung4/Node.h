#pragma once

// template (generic) T: Node can consist of generic value T (int, string, ...)
template<typename T>
class Node
{
	public:
		T value;        // node
		Node<T>* next;  // node next pointer
		Node<T>* prev;  // node previous pointer

		// constructor
		Node()
		{
			next = nullptr;
			prev = nullptr;
			value = {};
		}

		// print function to return value
		T print() const
		{
			return value;
		}

		
		// overload comparisons between typename T of Nodes
		friend bool operator==(Node<T> a, Node<T> b)
		{
			return a.value == b.value;
		}

		friend bool operator<(Node<T> a, Node<T> b)
		{
			return a.value < b.value;
		}

		friend bool operator>(Node<T> a, Node<T> b)
		{
			return a.value > b.value;
		}

		friend bool operator<=(Node<T> a, Node<T> b)
		{
			return a.value <= b.value;
		}

		friend bool operator>=(Node<T> a, Node<T> b)
		{
			return a.value >= b.value;
		}
};