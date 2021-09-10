#pragma once

// template (generic) T: Node can consist of generic value T (int, string, ...)
template<typename T>
class Node													// smartpointer / node combination
{
	T value = {};											// node
	Node<T>* next = nullptr;								// node next pointer
	Node<T>* prev = nullptr;								// node previous pointer
	
	public:
		Node() = default;									// constructor
		Node(T& x) : value(x) {}

		~Node() = default;									// destructor

		T getValue() const { return value; }				// getters
		Node* getPrev() const { return prev; }
		Node* getNext() const { return next; }

		void setValue(const T& x) { value = x; }					// setters
		void setPrev(Node* n) { prev = n; }
		void setNext(Node* n) { next = n; }

		T print() const	{ return value; }					// methods
		bool hasValue() const { return value != nullptr; }
		bool hasPrev() const { return prev; }
		bool hasNext() const { return next; }
		void clear() { prev = nullptr; next = nullptr; }
		
		// overload comparisons between typename T values of Nodes
		// friend: defined outside of class scope and access to all private and protected
		friend bool operator==(Node<T> a, Node<T> b) { return a.value == b.value; }
		friend bool operator!=(Node<T> a, Node<T> b) { return a.value != b.value; }
		friend bool operator<(Node<T> a, Node<T> b)  { return a.value < b.value; }
		friend bool operator>(Node<T> a, Node<T> b)  { return a.value > b.value; }
		friend bool operator<=(Node<T> a, Node<T> b) { return a.value <= b.value; }
		friend bool operator>=(Node<T> a, Node<T> b) { return a.value >= b.value; }
};