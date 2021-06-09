#pragma once
#include "node.h"
#include <sstream>

template<typename T>
class List
{
	private:
	    Node<T>* first;						// pointer first element
	    Node<T>* current;					// pointer current element
	    Node<T>* last;						// pointer last element
		int length;

	public:
		// Constructor
	    List()
	    {
	        first = nullptr;
	        current = nullptr;
	        last = nullptr;
			length = 0;
	    }

		// specific destructor to delete pointers and objects in heap
	    ~List()
	    {
	        current = first;				// start at beginning
			Node<T>* tmp = current;

	    	while (tmp != nullptr)			// while there is a next element delete current and advance
	    	{
				tmp = current->next;
				delete current;
				current = tmp;
	    	}
	    }

		// Getters and Setters for unittests
		Node<T>* getFirst() const { return first; }
		Node<T>* getCurrent() const { return current; }
		Node<T>* getLast() const	{ return last; }
		int getLength() const { return length; }
	
		// Linked List - Functions
		Node<T> get();					// get node from current pointer
		bool empty();					// return if list is empty
		bool beginning();				// return if your at start of list
		bool end();						// return if your at end of list
		bool adv();						// advance list pointer
		bool rec();						// New for sorted list: recede list pointer
		void reset();					// set list pointer to beginning
		void ins(const T &I_new);		// insert new element at pointer position
		void del();						// delete element at pointer position


		// General Functions
	    std::stringstream print();		// print all nodes values from element
};


template<typename T>
Node<T> List<T>::get()					// get node from current pointer
{
	if (current != nullptr)
		return *current;
	throw std::out_of_range("Error in List<T>::get(): Can not get() on empty pointer.");
}

template<typename T>
bool List<T>::empty()					// return if list is empty
{
	return current == nullptr && first == nullptr && last == nullptr;			
}

template<typename T>
bool List<T>::beginning()				// return if your at start of list
{
	return current == first;
}

template<typename T>
bool List<T>::end()						// return if your at end of list
{
	return current == last;
}

template<typename T>
bool List<T>::adv()						// advance list pointer
{
	if (current != nullptr && current->next != nullptr)
	{
		current = current->next;
		return true;
	}
	return false;
}

template<typename T>
bool List<T>::rec()						// New for sorted list: recede list pointer
{
	if (current != nullptr && current->prev != nullptr)
	{
		current = current->prev;
		return true;
	}
	return false;
}

template<typename T>
void List<T>::reset()					// set list pointer to beginning
{
	current = first;
}


// Runtime: Best case -> O(1)
//			Average case -> O(1)
//			Worst case -> O(1)
template<typename T>
void List<T>::ins(const T &I_new)		// insert new element at pointer position
{
	Node<T>* I = new Node<T>;			// create new node in heap
	I->value = I_new;					// insert node in current and advance current to next
	I->next = current;
	current = I;

	
	if (I->next != nullptr)				// adjust prev pointers of new current and next element
	{
		I->prev = I->next->prev;
		I->next->prev = I;
	}
	else								// edge case: no next -> I is inserted last element
	{
		last = I;
		I->next = nullptr;
	}
	// 1 - 2 - [4] - 3
	// 1 - 2 - 3 - [4]
	

	if (I->prev != nullptr)				// adjust next pointers of new current and next element
		I->prev->next = I;
	else								// edge case: no prev -> I is inserted first element
	{
		first = I;
		I->prev = nullptr;
	}
	// 1 - [4] - 2 - 3
	// [4] - 1 - 2 - 3

	length++;
}


// Runtime: Best case -> O(1)
//			Average case -> O(1)
//			Worst case -> O(1)
template<typename T>
void List<T>::del()						// delete element at pointer position
{
	Node<T>* I = current;				// load current node pointer to be deleted

	// catch empty node to be deleted
	if (I == nullptr || empty())
		return;
		

	// pointer of next and prev element
	if (I->next != nullptr)
		I->next->prev = I->prev;	// next element prev = prev of current
	
	if (I->prev != nullptr)
		I->prev->next = I->next;	// prev element next = next of current


	// pointer of list
	if (I->prev != nullptr && I->next != nullptr)		// delete between elements (mostly)
	{
		current = I->next;
	}
	else if (I->prev == nullptr && I->next != nullptr)	// delete first element
	{
		first = I->next;
		current = I->next;
	}
	else if (I->prev != nullptr && I->next == nullptr)	// delete last element
	{
		current = I->prev;
		last = I->prev;
	}
	else if (I->prev == nullptr && I->next == nullptr)	// edge case: delete single element
	{
		first = nullptr;
		current = nullptr;
		last = nullptr;
	}

	delete I;											// lastly when evetythings set up delete node
	length--;
}



template<typename T>
std::stringstream List<T>::print()						// print all nodes values from element
{
	std::stringstream str;								// stringstream
	Node<T>* current_before = current;					// save current pointer
	
	current = first;									// start from beginning
	
	if (current == nullptr) {							// if list empty
		str << "List empty!" << std::endl;
		return str;
	}

	str << "Your list consists of " << std::to_string(length) << " nodes:" << std::endl;
	int i = 0;
	do													// do while, so first element is printed as well
	{
		if (current == current_before)
			str << "+ ";
		else
			str << "- ";

		// Be dynamic for datatype int and string of list
		T value = current->print();
		if (typeid(value) == typeid(std::string))
			str << std::to_string(i) << ": " << value;
		else
			str << std::to_string(i) << ": " << std::to_string(value);

		if (typeid(value) == typeid(char))
			str << " (" << value << ")";
		
		i++;
	} while (adv() == true);

	current = current_before;					// reset saved pointer
	return str;
}