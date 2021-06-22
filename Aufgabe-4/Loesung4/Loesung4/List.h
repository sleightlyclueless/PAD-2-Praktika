#pragma once
#include <iomanip>
#include <iostream>


#include "Node.h"
#include <sstream>

template<typename T>
class List
{
	Node<T>* first;
	Node<T>* current;
	Node<T>* last;
	int length;

	public:
		// Constructors
		List()
		{
			first = nullptr;
			current = nullptr;
			last = nullptr;
			length = 0;
		}

		// Destructor
		/*~List()
		{
			current = first;
			Node<T>* next = current;

			while (next != nullptr)
			{
				next = current->next;
				delete current;
				current = next;
			}
		}*/

		// Getters and setters
		int getLength() const { return length; }
		Node<T>* getFirst() const { return first; }
		Node<T>* getCurrent() const { return current; }
		Node<T>* getLast() const { return last; }

		Node<T> get() const;									// Return current Node
		Node<T>* getPoint() const;								// Return pointer to current node
		int getPositon(Node<T>& n);								// Return position in list (linear search)
		Node<T>* getAtPosition(int pos);						// Return pointer to node at spec position
	
		Node<T>* getPrev() const;								// Return previous to current node
		Node<T>* getNext() const;								// Return next to current node
		Node<T>* getParent(Node<T> &child);						// Return binary tree parent of node
		Node<T>* getLeftChild(Node<T> &root);	// Return tree left child of node
		Node<T>* getRightChild(Node<T> &root);	// Return tree right child of node

		

		// Functions
		bool empty() const;										// return if list is empty
		bool beginning() const;									// return if your at start of list
		bool end() const;										// return if your at end of list
		bool adv();												// advance list pointer
		bool rec();												// recede list pointer
		void reset();											// set list pointer to beginning
		void ins(const T &I_new);								// insert new element at pointer position
		void insSorted(const T &I_new);							// insert new element at sorted position (requires sorted list)
		void push_back(const T &I_new);							// insert element at end of list
		void del();												// delete element at pointer position
		void clear();

		std::stringstream print();								// Print list contents
		std::stringstream print_tree();							// Print list contents with binary tree view
		void ini(int n);										// Fill list with n random elements

	
		// ========================================Sorting========================================
		static void mergeSort(List<T> &list);							// Mergesort with list
		static void splitList(List<T> &list, List<T> &a, List<T> &b);	// Split list into two lists a and b alternatingly
		static List<T> mergeLists(List<T> &a, List<T> &b);				// Merge two sorted lists into single sorted list

		static void heapSort(List<T> &list);												// Heapsort with list (Heap: Ordered binary tree [here: left completed])
		static void heapify(List<T> &list, Node<T> *parent, int &indexLastNotSorted);		// Make root and every knot the biggest in its cluster
		static void checkChilds(List<T> &list, Node<T> *parent, int &indexLastNotSorted);	// Fall / Swap through every cluster with the smallest element, leaving smallest el at end and biggest at root
		static void swap(Node<T> *a, Node<T> *b);											// zwei swap two node elements / their values

		static void quickSort(List<T>& list);
		static void quickSortList(List<T>& list, int a, int b);
};


template<typename T>
Node<T> List<T>::get() const
{
	if (current != nullptr)
		return *current;
	throw std::out_of_range("Error in List<T>::get(): Can not get() on empty pointer.");
}

template<typename T>
Node<T>* List<T>::getPoint() const
{
	if (current != nullptr)
		return current;
	throw std::out_of_range("Error in List<T>::get(): Can not getPoint() on empty pointer.");
}


template <typename T>
int List<T>::getPositon(Node<T> &n)
{
	int counter = 0;
	reset();

	do
	{
		if (current == &n)
			return counter;
		counter++;
	} while (adv());

	return -1;
}

template<typename T>
Node<T>* List<T>::getAtPosition(int pos) {
	if (pos <= length || pos == -1)
	{
		reset();
		while (pos > 0) {
			adv();
			pos--;
		}
		return getPoint();
	}
	return nullptr;
}

template <typename T>
Node<T>* List<T>::getPrev() const
{
	if (current->prev != nullptr)
		return current->prev;
	return nullptr;
}

template <typename T>
Node<T>* List<T>::getNext() const
{
	if (current->next != nullptr)
		return current->next;
	return nullptr;
}

template <typename T>
Node<T>* List<T>::getParent(Node<T> &child)
{
	return getAtPosition(static_cast<int>((getPositon(child) + 1) / 2) - 1);
}

template <typename T>
Node<T>* List<T>::getLeftChild(Node<T> &root)
{
	const int adr = (getPositon(root) + 1) * 2 - 1;
	return getAtPosition(adr);
}

template <typename T>
Node<T>* List<T>::getRightChild(Node<T> &root)
{
	const int adr = (getPositon(root) + 1) * 2;
	return getAtPosition(adr);
}


template<typename T>
bool List<T>::empty() const
{
	return current == nullptr && first == nullptr && last == nullptr;
}

template<typename T>
bool List<T>::beginning() const
{
	return current == first;
}

template<typename T>
bool List<T>::end() const
{
	return current == last;
}

template<typename T>
bool List<T>::adv()
{
	if (current != nullptr && current->next != nullptr)
	{
		current = current->next;
		return true;
	}
	return false;
}

template<typename T>
bool List<T>::rec()
{
	if (current != nullptr && current->prev != nullptr)
	{
		current = current->prev;
		return true;
	}
	return false;
}

template<typename T>
void List<T>::reset()
{
	if (first != nullptr)
		current = first;
	else
		throw std::out_of_range("Error in List<T>::reset(): Can not reset() on empty list.");
}

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

template<typename T>
void List<T>::insSorted(const T &I_new)
{
	Node<T>* I = new Node<T>;
	I->value = I_new;
	bool flag = true;

	if (current != nullptr)
	{
		if (I->value < current->value)	// If inserted value is smaller recede pointer
		{
			while (I->value < current->value && current->prev != nullptr && flag) {
				flag = rec();
			}
			if (current != first)
				flag = adv();
		}

		if (I->value > current->value)	// If inserted value is bigger advance pointer
		{
			while (I->value > current->value && current->next != nullptr && flag) {
				flag = adv();
			}
		}

		if (I->value > current->value)	// Edge case new biggest element
		{
			push_back(I->value);
			return;
		}
	}
	
	// Pointer is now on Element equal or bigger than new element -
	// we can squeeze it in and move all elements further (except edge case new biggest element)
	// =========================================================================================
	I->next = current;
	current = I;

	if (I->next != nullptr)			// adjust prev pointers of new current and next element
	{
		I->prev = I->next->prev;
		I->next->prev = I;
	}
	else
	{
		last = I;
		I->next = nullptr;
	}

	if (I->prev != nullptr)			// adjust next pointers of new current and next element
		I->prev->next = I;
	else
	{
		first = I;
		I->prev = nullptr;
	}

	current = I;
	length++;
}

template <typename T>
void List<T>::push_back(const T &I_new)
{
	Node<T>* I = new Node<T>;
	I->value = I_new;
	
	// Adjust pointers of I
	I->next = nullptr;
	I->prev = last;
	last = I;

	// Adjust pointers of previous last (and edge cases if list was empty in the first place)
	if (I->prev != nullptr)
		I->prev->next = I;
	else
		first = I;
	
	if (current != nullptr)
		current = I;

	length++;
}


template<typename T>
void List<T>::del()
{
	Node<T>* I = current;			// load current node pointer to be deleted

	if (I == nullptr)
		throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.");

	if (I->next != nullptr)
		I->next->prev = I->prev;	// next element prev = prev of current
	if (I->prev != nullptr)
		I->prev->next = I->next;	// prev element next = next of current

	// Adjust pointers of prev and next
	if (I->prev != nullptr && I->next != nullptr)		// delete between elements (mostly)
		current = I->next;
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

	delete I;						// lastly when evetythings set up delete node
	length--;
}

template <typename T>
void List<T>::clear()
{
	current = first;
	Node<T>* next = current;

	if (current != nullptr)
	{
		while (next != nullptr)
		{
			next = current->next;
			delete current;
			current = next;
		}
	}
}


template<typename T>
std::stringstream List<T>::print()
{
	std::stringstream str;
	Node<T>* current_before = current;
	current = first;

	if (current == nullptr) {
		str << "List empty!" << std::endl;
		return str;
	}

	str << "Your list consists of " << std::to_string(length) << " nodes:" << std::endl;
	int i = 0;
	do
	{
		if (current == current_before)
			str << "+ ";
		else
			str << "- ";

		T value = current->print();
		if (typeid(value) == typeid(std::string))
			str << std::to_string(i) << ": " << value;
		else
			str << std::to_string(i) << ": " << std::to_string(value);

		if (typeid(value) == typeid(char))
			str << " (" << value << ")";

		str << std::endl;

		i++;
	} while (adv() == true);

	current = current_before;
	return str;
}

template<typename T>
std::stringstream List<T>::print_tree()
{
	std::stringstream str;
	Node<T>* current_before = current;			// Element aktuell vorher merken

	current = first;

	if (current == nullptr)
	{
		str << "List empty!" << std::endl;
		return str;
	}
		
	str << "Your list consists of " << std::to_string(length) << " nodes:" << std::endl;
	int i = 0;
	while (i <= 15) {

		std::string c = std::to_string(current->print());
		if (c.length() == 1)
			c.insert(0, "0");
		
		switch (i)
		{
			case 0:
				str << std::setw(25) << "----------" << c << "----------" << std::endl;
				if (1 < length)
					str << std::setw(15) << "/" << std::setw(23) << "\\" << std::endl;
				break;

			case 1:
				str << std::setw(13) << "----" << c << "----";
				break;

			case 2:
				str << std::setw(18) << "----" << c << "----" << std::endl;
				if (3 < length)
					str << std::setw(9) << "/" << std::setw(11) << "\\" << std::setw(13) << "/" << std::setw(11) << "\\" << std::endl;
				break;

			case 3:
				str << std::setw(7) << "--" << c << "--";
				break;

			case 4:
			case 5:
				str << std::setw(8) << "--" << c << "--";
				break;

			case 6:
				str << std::setw(8) << "--" << c << "--";
				if (7 < length)
				{
					str << std::endl << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::endl;
				}
				break;

			case 7:
				str << std::setw(5) << c;
				break;

			case 8:
			case 10:
			case 12:
			case 14:
				str << std::setw(8) << c;
				break;

			case 9:
			case 11:
			case 13:
				str << std::setw(4) << c;
				break;
			
			case 15:
				str << std::endl << std::endl << std::to_string(length - 15) << " elements are not displayed.";

			default: 
				break;
		}

		if (end())
			break;
		
		i++;
		adv();
		
	}
	str << std::endl << std::endl;
	
	current = current_before;
	return str;

}

template<typename T>
void List<T>::ini(const int n)
{
	int i = 0;
	
	while(i < n)
	{
		ins(rand()%15);
		i++;
	}
}


// ======================================== Mergesort ========================================
template <typename T>
void List<T>::mergeSort(List<T> &list)
{
	List<T> a, b;

	list.reset();
	if (!list.end()) // Mehr als 1 Element übrig zu sortieren
	{
		splitList(list, a, b);
		mergeSort(a);
		mergeSort(b);

		list = mergeLists(a, b);
	}

	std::cout << list.print().str() << std::endl;
}

template<typename T>
void List<T>::splitList(List<T> &list, List<T> &a, List<T> &b)
{
	list.reset();
	bool notend = true;
	bool switcher = true;

	while (notend)
	{
		if (switcher)
		{
			a.push_back(list.current->value);
			notend = list.adv();
			switcher = false;
		}
		else
		{
			b.push_back(list.current->value);
			notend = list.adv();
			switcher = true;
		}
	}
}

template<typename T>
List<T> List<T>::mergeLists(List<T> &a, List<T> &b)
{
	std::cout << a.print().str() << std::endl;
	std::cout << b.print().str() << std::endl;
	
	if (a.empty() && b.empty())				// If both lists are empty throw error
		throw std::out_of_range("Error in List<T>::mergeLists(): Both given lists empty.");
	if (b.empty())							// If b is empty just return the sorted list a
		return a;
	if (a.empty())							// If a is empty just return the sorted list b
		return b;

	List<T> sortedList;						// Initialize new List to save sorted pointer to deep copy elements to
	a.reset();								// Reset pointers of both referenced lists to beginning - hence smallest nums
	b.reset();
	
	bool anotempty = true;					// Flags to check if we can still advance in lists
	bool bnotempty = true;
	
	while (anotempty && bnotempty)
	{
		if (a.current->value <= b.current->value)	// El in a smaller or equal than b -> push back smaller number a to list and move to next bigger el
													// NOTE: PUSH BACK ALREADY CREATES DEEP COPY IN HEAP
		{
			sortedList.push_back(a.current->value);
			anotempty = a.adv();
		}
		else										// Otherwise if el b is smaller push back el b and move b list to next bigger el
		{
			sortedList.push_back(b.current->value);
			bnotempty = b.adv();
		}
	}

	// Done with while loop: one of both lists reached empty state / last element -> remaining el from other list are all bigger -- add to sorted list
	if (anotempty == true)
	{
		sortedList.push_back(a.current->value);
		while (a.adv())
		{
			sortedList.push_back(a.current->value);
		} 
	}
	if (bnotempty == true)
	{
		sortedList.push_back(b.current->value);
		while (b.adv())
		{
			sortedList.push_back(b.current->value);
		}
	}

	// Reset pointer of new list to the start and return it
	sortedList.reset();
	return sortedList;
}



// ======================================== Heapsort ========================================
template<typename T>
void List<T>::heapSort(List<T> &list)
{
	std::cout << "Start:" << std::endl;
	std::cout << list.print().str() << std::endl;
	std::cout << list.print_tree().str() << std::endl;

	// Heapify
	for (int i = list.length - 1; i>=0; --i)
	{
		heapify(list, list.first, i);
		swap(list.first, list.getAtPosition(i));
	}
	std::cout << "Post heapify:" << std::endl;
	std::cout << list.print_tree().str() << std::endl;

	// Sort descending
	for (int i = list.length - 1; i >= 0; --i)
	{
		checkChilds(list, list.first, i);
		swap(list.first, list.getAtPosition(i));
	}
	std::cout << "Post checkChilds / sorting:" << std::endl;
	std::cout << list.print_tree().str() << std::endl;
	std::cout << list.print().str() << std::endl;
}

template<typename T>
void List<T>::heapify(List<T>& list, Node<T>* parent, int& indexLastNotSorted)
{
	Node<T>* leftChild = list.getLeftChild(*parent);
	Node<T>* rightChild = list.getRightChild(*parent);

	if (leftChild == nullptr) {
		return;
	}

	if (rightChild != nullptr && list.getPositon(*rightChild) < indexLastNotSorted)
	{
		if (leftChild->value < parent->value || rightChild->value < parent->value) {
			if (leftChild->value < rightChild->value) {																	/*		 5					6			*/
				swap(leftChild, parent);																				/*		/ \		------>	   / \			*/
				heapify(list, leftChild, indexLastNotSorted);															/*	   6   2			  5   2			*/
			}
			else {																										/*		 5					6			*/
				swap(rightChild, parent);																				/*		/ \		------>	   / \			*/
				heapify(list, rightChild, indexLastNotSorted);															/*	   2   6			  2   5			*/
			}
		}
	}
	else {
		if (leftChild->value < parent->value && list.getPositon(*leftChild) < indexLastNotSorted) {						/*		 5					2			*/
			swap(leftChild, parent);																					/*		/		------>	   /			*/
			heapify(list, leftChild, indexLastNotSorted);																/*	   2				  5				*/
		}
	}
}

template<typename T>
void List<T>::checkChilds(List<T> &list, Node<T> *parent, int &indexLastNotSorted)
{	
	Node<T>* leftChild = list.getLeftChild(*parent);
	Node<T>* rightChild = list.getRightChild(*parent);

	if (leftChild == nullptr) {
		return;
	}

	if (rightChild != nullptr && list.getPositon(*rightChild) < indexLastNotSorted)
	{
		if (leftChild->value > parent->value || rightChild->value > parent->value) {
			if (leftChild->value > rightChild->value) {																	/*		 5					2			*/
				swap(leftChild, parent);																				/*		/ \		------>	   / \			*/
				checkChilds(list, leftChild, indexLastNotSorted);														/*	   6   2			  5   6			*/
			}
			else {																										/*		 5					2			*/
				swap(rightChild, parent);																				/*		/ \		------>	   / \			*/
				checkChilds(list, rightChild, indexLastNotSorted);														/*	   2   6			  6   5			*/
			}
		}
	}
	else {
		if (leftChild->value > parent->value && list.getPositon(*leftChild) < indexLastNotSorted) {						/*		 2					5			*/
			swap(leftChild, parent);																					/*		/		------>	   /			*/
			checkChilds(list, leftChild, indexLastNotSorted);															/*	   5				  2				*/
		}
	}
}

template<typename T>
void List<T>::swap(Node<T>* a, Node<T>* b)
{
	T tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}


// ======================================== Quicksort ========================================

template<typename T>
void List<T>::quickSort(List<T> &list)
{
	quickSortList(list, 0, list.length - 1);
}

template<typename T>
void List<T>::quickSortList(List<T> &list, const int a, const int b)	// sort from a to b
{
	if (list.empty() || b <= a)											// if list is empty or we met at or passed the pivotelement we are done
		return;

	int pivotpos = a + rand() % (b - a);								// calculate pivot position between a and b
	
	Node<T> *pivot = list.getAtPosition(pivotpos);						// initialize first nodes (pivot, start and end of sorting range)
	Node<T> *i = list.getAtPosition(a);
	Node<T> *j = list.getAtPosition(b);
	
	while (i != pivot || j != pivot)									// move both nodes towards i-->pivot<--j and sort them by swapping to the correct side (bigger or smaller than pivot)
	{
		
		if (i->value > pivot->value && j->value < pivot->value)         // if i bigger and j smaller than pivot: swap and move both towards pivot
		{
			swap(i, j);
			i = i->next;
			j = j->prev;
		}

		else if (i->value > pivot->value) {								// if i bigger than pivot: move i to the left of pivot
			swap(i, pivot->prev);
			swap(pivot->prev, pivot);
			pivot = pivot->prev;
			--pivotpos;													// pivot element moved one to the right due to asymetrical swap -> equalize
		}
			
		else if (j->value < pivot->value) {								// if j smaller than pivot: move i to the left of pivot
			swap(j, pivot->next);
			swap(pivot, pivot->next);
			pivot = pivot->next;
			++pivotpos;													// pivot element moved one to the left due to asymetrical swap -> equalize
		}
		
		else															// if all elements on their right side just move and move on
		{
			if (i != pivot)
				i = i->next;
			if (j != pivot)
				j = j->prev;
		}
	}

	quickSortList(list, a, pivotpos - 1);								// Recursive call with new partial list pivot elements for left and right side
	quickSortList(list, pivotpos + 1, b);

}