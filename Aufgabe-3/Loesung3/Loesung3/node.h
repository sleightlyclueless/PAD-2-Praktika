#pragma once
#include <string>

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
	    std::string print() const
	    {
	        return std::to_string(value);
	    }
};



// =================== Task 4 =====================
// overload comparisons between typename T of Nodes
template<typename T>
bool operator==(Node<T> a, Node<T> b)
{
    return a.value == b.value;
}

template<typename T>
bool operator<(Node<T> a, Node<T> b)
{
    return a.value < b.value;
}

template<typename T>
bool operator>(Node<T> a, Node<T> b)
{
    return a.value > b.value;
}

template<typename T>
bool operator<=(Node<T> a, Node<T> b)
{
    return a.value <= b.value;
}

template<typename T>
bool operator>=(Node<T> a, Node<T> b)
{
    return a.value >= b.value;
}
