#pragma once
#include "node.h"
#include <sstream>

template<typename T>
class List_sorted
{
	Node<T>* first;
	Node<T>* current;
	Node<T>* last;
	int length;

	public:
		List_sorted()
		{
			first = nullptr;
			current = nullptr;
			last = nullptr;
			length = 0;
		}

		~List_sorted()
		{
			current = first;
			Node<T>* next = current;
			
			while (next != nullptr)
			{
				next = current->next;
				delete current;
				current = next;
			}
		}

		Node<T>* getFirst() const { return first; }
		Node<T>* getCurrent() const { return current; }
		Node<T>* getLast() const { return last; }
		int getLength() const { return length; }
	
		Node<T> get();					// get node from current pointer
		bool empty();					// return if list is empty
		bool beginning();				// return if your at start of list
		bool end();						// return if your at end of list
		bool adv();						// advance list pointer
		bool rec();						// New for sorted list: recede list pointer
		void reset();					// set list pointer to beginning
		void ins(const T& I_new);		// insert new element at pointer position
		void del();						// delete element at pointer position
		std::stringstream print();
};

template<typename T>
Node<T> List_sorted<T>::get()
{
	if (current != nullptr)
		return *current;
	throw std::out_of_range("Error in List<T>::get(): Can not get() on empty pointer.");
}

template<typename T>
bool List_sorted<T>::empty()
{
	return current == nullptr && first == nullptr && last == nullptr;
}

template<typename T>
bool List_sorted<T>::beginning()
{
	return current == first;
}

template<typename T>
bool List_sorted<T>::end()
{
	return current == last;
}

template<typename T>
bool List_sorted<T>::adv()
{
	if (current != nullptr && current->next != nullptr)
	{
		current = current->next;
		return true;
	}
	return false;
}

template<typename T>
bool List_sorted<T>::rec()		// New for sorted list: Recede by one
{
	if (current != nullptr && current->prev != nullptr)
	{
		current = current->prev;
		return true;
	}
	return false;
}

template<typename T>
void List_sorted<T>::reset()
{
	current = first;
}

template<typename T>
void List_sorted<T>::ins(const T& I_new)
{
	Node<T>* I = new Node<T>;
	I->value = I_new;

	// NEW == Move current to position where it can be inserted in a sorted manner
	// Find insert position (first larger than I cause I gets pushed back)
	if (current != nullptr)
	{
		if (I->value < current->value)	// If inserted value is smaller recede
		{
			while (I->value < current->value && current->prev != nullptr) {
				rec();
			}
			if (current != first)
				adv();
		}

		if (I->value > current->value)	// If inserted value is bigger advance
		{
			while (I->value > current->value && current->next != nullptr) {
				adv();
			}
		}


		// Edge case new biggest element
		if (I->value > current->value)
		{
			// Adjust pointers of I
			I->next = nullptr;
			I->prev = last;
			last = I;

			// Adjust pointers of previous last (and edge cases if list was empty in the first place)
			if (I->prev != nullptr)	
				I->prev->next = I;
			else
				first = I;
			if (current == nullptr)
				current = I;
			return;
		}
	}
	// Pointer is now on Element equal or bigger than new element (except edge case new biggest element)
	// ============================================================================

	
	// If not edge case our current pointer is at the right position for an sorted insert
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

	current = I;
	length++;
}


template<typename T>
void List_sorted<T>::del()
{
	Node<T>* I = current;

	if (I == nullptr)
		throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.");

	if (I->next != nullptr)
		I->next->prev = I->prev;
	if (I->prev != nullptr)
		I->prev->next = I->next;

	if (I->prev != nullptr && I->next != nullptr)
		current = I->next;
	else if (I->prev == nullptr && I->next != nullptr)
	{
		first = I->next;
		current = I->next;
	}
	else if (I->prev != nullptr && I->next == nullptr)
	{
		current = I->prev;
		last = I->prev;
	}
	else if (I->prev == nullptr && I->next == nullptr)
	{
		first = nullptr;
		current = nullptr;
		last = nullptr;
	}

	delete I;
	length--;
}

template<typename T>
std::stringstream List_sorted<T>::print()
{
	std::stringstream str;
	Node<T>* current_before = current;
	current = first;

	if (current == nullptr) {
		str << "List empty!" << std::endl;
		return str;
	}

	int i = 0;
	do
	{
		if (current == current_before)
			str << "+ ";
		else
			str << "- ";

		str << std::to_string(i) << ": " << current->print() << std::endl;

		i++;
	} while (adv() == true);

	current = current_before;
	return str;
}