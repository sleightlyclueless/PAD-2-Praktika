#pragma once
#include "Node.h"
#include <iomanip>
#include <sstream>

template<typename T>
class List
{
	Node<T> *first;										// Pointer to first element
	Node<T> *current;									// Pointer to current element
	Node<T> *last;										// Pointer to last element
	int length;											// Length of list (elements)

	public:
		List()											// constructor with defaults
		{
			length = 0;
			first = nullptr;
			current = nullptr;
			last = nullptr;
		}

		// TODO: Destructor shit...
		// ~List() { clear(); }							// destructor
		~List() = default;

	
		int getLength() const { return length; }		// getters and setters for private vars
		Node<T> *getFirst() const { return first; }
		Node<T> *getCurrent() const { return current; }
		Node<T> *getLast() const { return last; }

														// get functions for nodes
		Node<T> get() const;							// return current Node
		Node<T> *getPoint() const;						// return pointer to current node
		int getPositon(Node<T> &n);						// return node position in list (linear search)
		Node<T> *getPointAtPosition(int pos);			// return pointer to node at spec position
	
		Node<T> *getPrev() const;						// return previous to current node
		Node<T> *getNext() const;						// return next to current node
		Node<T> *getParent(Node<T> &child);				// return heap parent of node
		Node<T> *getLeftChild(Node<T> &root);			// return heap left child of node
		Node<T> *getRightChild(Node<T> &root);			// return heap right child of node

														// functions
		bool checkEmpty() const;						// return if list is empty
		bool checkBeginning() const;					// return if your at start of list
		bool checkEnd() const;							// return if your at end of list
		bool adv();										// advance list pointer and return if succeeded
		bool rec();										// recede list pointer and return if succeeded
		void reset();									// set list pointer to beginning
	
		void ins(Node<T> *I);							// insert new element at current pointer
		void insNode(const T &I_new);					// insert new element at pointer position
		void insNodeSorted(const T &I_new);				// insert new element at sorted position (requires sorted list)
		void push_back(const T &I_new);					// insert element at end of list
		void del();										// delete element at pointer position and adv pointer
		void clear();									// linear clear heap elements from entire list

		std::stringstream print();						// print list contents
		std::stringstream print_tree();					// print (first 15) list contents with binary tree view
		void fill(const int &amount, const int &range);	// fill list with n random elements
		bool checkSortedAsc();							// unit tests: Linear check of list is sorted (1<=1<=2<=3<=5...)


		// ========================================Sorting========================================
		static void swap(Node<T>* a, Node<T>* b);									// swap two node pointers values
	
		static std::stringstream selectionSort(List<T> &list);						// selectionsort with list

		static std::stringstream insertionSort(List<T> &list);						// insertionsort with list

		static std::stringstream bubbleSort(List<T> &list);							// insertionsort with list
		
		static std::stringstream mergeSort(List<T> &list);							// mergesort with list
		static void splitList(List<T> &list, List<T> &a, List<T> &b);				// split list into two lists a and b alternatingly
		static List<T> mergeLists(List<T> &list, List<T> &a, List<T> &b);			// merge two (sorted) lists into single sorted list

		static std::stringstream heapSort(List<T> &list);							// heapsort with list (Heap: Ordered binary tree [here: left completed])
		static void heapify(List<T> &list, Node<T> *parent, int &indexLastNotSort); // make root and every knot the biggest in its cluster (biggest el at top, smallest at bottom)

		static std::stringstream quickSort(List<T> &list);							// call quicksort with default vars
		static void quickSortList(List<T> &list, int a, int b);						// quicksort with list

		static std::stringstream quickSortStable(List<T> &list);					// call quicksortstable with default vars
		static void quickSortStableList(List<T> &list);								// quicksortstable with list
		static bool equal(List<T> &list);											// check if all elements in list have same value

};


// return current Node
template<typename T>
Node<T> List<T>::get() const
{
	if (current != nullptr)
		return *current;
	throw std::out_of_range("Error in List<T>::get(): Can not get() on empty pointer.");
}

// return pointer to current node
template<typename T>
Node<T> *List<T>::getPoint() const
{
	if (current != nullptr)
		return current;
	throw std::out_of_range("Error in List<T>::get(): Can not getPoint() on empty pointer.");
}

// return node position in list (linear search)
template <typename T>
int List<T>::getPositon(Node<T> &n)
{
	if (!checkEmpty())
	{
		Node<T> *current_before = current;
		int counter = 0;
		reset();

		do
		{
			if (current == &n)
			{
				current = current_before;
				return counter;
			}
				
			counter++;
		} while (adv());

		current = current_before;
		throw std::out_of_range("Error in List<T>::getPositon(): Node not found in list.");
	}
	throw std::out_of_range("Error in List<T>::getPositon(): Can not getPositon() on empty list.");
}

// return pointer to node at spec position
template<typename T>
Node<T> *List<T>::getPointAtPosition(int pos) {
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

// return previous to current node
template <typename T>
Node<T> *List<T>::getPrev() const
{
	if (current->prev != nullptr)
		return current->prev;
	return nullptr;
}

// return next to current node
template <typename T>
Node<T> *List<T>::getNext() const
{
	if (current->next != nullptr)
		return current->next;
	return nullptr;
}

// return heap parent of node
template <typename T>
Node<T> *List<T>::getParent(Node<T> &child)
{
	if (getPointAtPosition(static_cast<int>(getPositon(child) - 1) / 2) != nullptr)		// Calculate heap level above (binary tree is halved,
		return getPointAtPosition(static_cast<int>(getPositon(child) - 1) / 2);			// meaning moving to parent is - offset 1 then divided by 2)
	return nullptr;
}

// return heap left child of node
template <typename T>
Node<T> *List<T>::getLeftChild(Node<T> &root)
{
	const int adr = (getPositon(root) + 1) * 2 - 1;										// Calculate heap level below left (binary tree is halved,
	if (getPointAtPosition(adr) != nullptr)												// meaning moving to child is + offset 1 then multiplied 2)
		return getPointAtPosition(adr);													// then for left child recede once more and negate offset
	return nullptr;
}

// return heap right child of node
template <typename T>
Node<T> *List<T>::getRightChild(Node<T> &root)
{
	const int adr = (getPositon(root) + 1) * 2;											// Calculate heap level below left (binary tree is halved,
	if (getPointAtPosition(adr) != nullptr)												// meaning moving to child is + offset 1 then multiplied 2)
		return getPointAtPosition(adr);
	return nullptr;
}


// return if list is empty
template<typename T>
bool List<T>::checkEmpty() const
{
	return current == nullptr && first == nullptr && last == nullptr && length == 0;
}

// return if your at start of list
template<typename T>
bool List<T>::checkBeginning() const
{
	return current == first;
}

// return if your at end of list
template<typename T>
bool List<T>::checkEnd() const
{
	return current == last;
}

// advance list pointer and return if succeeded
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

// recede list pointer and return if succeeded
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

// set list pointer to beginning
template<typename T>
void List<T>::reset()
{
	if (!checkEmpty())
		current = first;
	else
		throw std::out_of_range("Error in List<T>::reset(): Can not reset() on empty list.");
}


// insert new element at pointer position
template<typename T>
void List<T>::ins(Node<T> *I)			// Given that our current pointer is at the right slot to insert:
										// insert new element at pointer position (move all other elements back and front)
{
	I->next = current;					// set new current to I
	current = I;

	if (I->next != nullptr)				// adjust prev pointers of new element and next element
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

	if (I->prev != nullptr)				// adjust next pointers of new element and next element
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

// insert new element at pointer position
template<typename T>
void List<T>::insNode(const T &I_new)	// insert new element at pointer position
{
	Node<T> *I = new Node<T>;			// create new node in heap
	I->value = I_new;					// insert node in current and advance current to next
	ins(I);
}

// insert new element at sorted position (requires sorted list)
template<typename T>
void List<T>::insNodeSorted(const T &I_new)
{
	Node<T> *I = new Node<T>;
	I->value = I_new;
	bool flag = true;

	// move pointer on Element equal or bigger than new element -
	// we can then just insert it as usual (except edge case new biggest element)
	// =========================================================================================
	if (current != nullptr)
	{
		if (I->value < current->value)	// if inserted value is smaller recede pointer
		{
			while (I->value < current->value && current->prev != nullptr && flag) {
				flag = rec();
			}
			if (current != first)
				flag = adv();
		}

		if (I->value > current->value)	// if inserted value is bigger advance pointer
		{
			while (I->value > current->value && current->next != nullptr && flag) {
				flag = adv();
			}
		}

		if (I->value > current->value)	// edge case new biggest element
		{
			push_back(I->value);
			return;
		}
	}
	
	ins(I);
}

// insert element at end of list
template <typename T>
void List<T>::push_back(const T &I_new)
{
	Node<T> *I = new Node<T>;
	I->value = I_new;
	
	I->next = nullptr;					// adjust pointers of I
	I->prev = last;
	last = I;

	if (I->prev != nullptr)				// adjust pointers of previous last
		I->prev->next = I;
	else
		first = I;
	
	current = I;						// set new current to I

	length++;
}

// delete element at pointer position and adv pointer
template<typename T>
void List<T>::del()
{
	Node<T> *I = current;								// load current node pointer to be deleted

	if (I == nullptr)
		throw std::out_of_range("Error in List<T>::del(): Can not delete element from empty list.");

														// adjust pointers of prev and next element
	if (I->next != nullptr)
		I->next->prev = I->prev;						// next element prev = prev of current
	if (I->prev != nullptr)
		I->prev->next = I->next;						// prev element next = next of current

	
														// adjust list pointers depending on where we deleted
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

	delete I;											// lastly when evetythings set up delete node
	I = nullptr;
	length--;
}

// linear clear heap elements from entire list
template <typename T>
void List<T>::clear()
{
	if (checkEmpty())
		throw std::out_of_range("Error in List<T>::clear(): List already empty.");

	reset();
	while (length > 0)
	{
		del();
	}
		
}


// print list contents
template<typename T>
std::stringstream List<T>::print()
{
	std::stringstream str;
	Node<T> *current_before = current;

	if (checkEmpty()) {
		str << "List empty!" << std::endl;
		return str;
	}

	reset();
	str << "Your list consists of " << std::to_string(length) << " nodes:" << std::endl;
	int i = 0;
	do														// linear move and print through list
	{
		if (current == current_before)						// show if our list pointer is set to curr el or not
			str << "+ ";
		else
			str << "- ";

		T value = current->print();							// get node value
		if (typeid(value) == typeid(std::string))			// depending on type T print it differently
			str << std::to_string(i) << ": " << value;
		else
			str << std::to_string(i) << ": " << std::to_string(value);
		if (typeid(value) == typeid(char))
			str << " (" << value << ")";

		str << std::endl;

		i++;
	} while (adv());

	current = current_before;
	return str;
}

// print (first 15) list contents with binary tree view
template<typename T>
std::stringstream List<T>::print_tree()
{
	std::stringstream str;
	Node<T> *current_before = current;

	if (checkEmpty())
	{
		str << "List empty!" << std::endl;
		return str;
	}
	
	reset();
	str << "Your list consists of " << std::to_string(length) << " nodes:" << std::endl;
	int i = 0;

	
	while (i <= 15) {

		std::string c{};										// build dynamic output string with T value
		if (std::to_string(current->print()).length() == 1 && typeid(current->print()) == typeid(int))
			c = "0";
		if (typeid(current->print()) != typeid(std::string))
			c += std::to_string(current->print());
		else
			c += current->print();
		
																// use while loop for current node printed to evaluate
		switch (i)												// their level and position through switch - case
		{
			case 0:												// level 0
				str << std::setw(25) << "----------" << c << "----------" << std::endl;
				if (1 < length)
					str << std::setw(15) << "/" << std::setw(23) << "\\" << std::endl;
				break;

			case 1:												// level 1
				str << std::setw(13) << "----" << c << "----";
				break;

			case 2:												// level 1
				str << std::setw(18) << "----" << c << "----" << std::endl;
				if (3 < length)
					str << std::setw(9) << "/" << std::setw(11) << "\\" << std::setw(13) << "/" << std::setw(11) << "\\" << std::endl;
				break;

			case 3:												// level 2
				str << std::setw(7) << "--" << c << "--";
				break;

			case 4:												// level 2
			case 5:												// level 2
				str << std::setw(8) << "--" << c << "--";
				break;

			case 6:												// level 2
				str << std::setw(8) << "--" << c << "--";
				if (7 < length)
				{
					str << std::endl << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::setw(5) << "/" << std::setw(7) << "\\" << std::endl;
				}
				break;

			case 7:												// level 3
				str << std::setw(5) << c;
				break;

			case 8:												// level 3
			case 10:
			case 12:
			case 14:
				str << std::setw(8) << c;
				break;

			case 9:												// level 3
			case 11:
			case 13:
				str << std::setw(4) << c;
				break;
			
			case 15:											// hide all lower elements
				str << std::endl << std::endl << std::to_string(length - 15) << " elements are not displayed.";

			default: 
				break;
		}

		if (checkEnd())											// if we reached end of list end while and switch
			break;
		
		i++;
		adv();													// move to next element for next loop
		
	}
	str << std::endl << std::endl;
	
	current = current_before;
	return str;

}

// fill list with n random elements
template<typename T>
void List<T>::fill(const int &amount, const int &range)
{
	int i = 0;
	
	while(i < amount)
	{
		insNode(rand()%range + 1);
		i++;
	}
}

// unit tests: Linear check of list is sorted (1<=1<=2<=3<=5...)
template<typename T>
bool List<T>::checkSortedAsc()
{
	if (checkEmpty())
		return false;
	
	bool sorted = true;
	current = first;

	if (current != nullptr)
	{
		while (current->next != nullptr)
		{
			if (current->value <= current->next->value)
			{
				current = current->next;
			}
			else
			{
				sorted = false;
				break;
			}
		}
	}

	return sorted;
}


// ========================================Sorting========================================
// swap two node pointers values
template<typename T>
void List<T>::swap(Node<T>* a, Node<T>* b)
{
	T tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

// selectionsort with list
// WC O(n²); AC O(n²); BC O(n²); Not stable; In-Place;
template<typename T>
std::stringstream List<T>::selectionSort(List<T> &list)
{
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::selectionSort(): Can not sort on empty list.");

	std::stringstream str;
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;
	
	for (int i = 0; i <= list.length - 1; i++)										// For each position
	{
		int minpos = i;

		for (int j = 0; j <= list.length; j++)										// Find smallest remaining element
		{
			if (list.getPointAtPosition(j)->value > list.getPointAtPosition(minpos)->value)
				minpos = j;

			swap(list.getPointAtPosition(minpos), list.getPointAtPosition(i));		// Write it to smallest remaining pos
		}
	}

	str << "End:" << std::endl;
	str << list.print().str() << std::endl;

	return str;
}


// insertionsort with list
// WC O(n²); AC O(n²); BC O(n); Stable; In-Place;
template<typename T>
std::stringstream List<T>::insertionSort(List<T> &list)
{
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::insertionSort(): Can not sort on empty list.");

	std::stringstream str;
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;

	for (int i = 1; i < list.length; i++)											// Get element at each asc position
	{
		int val = list.getPointAtPosition(i)->value;
		list.del();
		
		do																			// Sort it into sorted partial list before element
		{
			if (list.current->prev == nullptr) {
				list.insNode(val);
				break;
			}
			if (list.current->prev->value < val)
			{
				list.insNode(val);
				break;
			}
				
		} while (list.rec());
	}

	str << "End:" << std::endl;
	str << list.print().str() << std::endl;

	return str;
}


// bubble with list
// WC O(n²); AC O(n²); BC O(n); Stable; In-Place
template<typename T>
std::stringstream List<T>::bubbleSort(List<T>& list)
{
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::bubbleSort(): Can not sort on empty list.");

	std::stringstream str;
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;

	for (int i = 0; i <= list.length - 1; i++)										// Compare for each element all elements behind and swap if smaller
	{
		for (int j = 0; j <= list.length; j++)
		{
			if (list.getPointAtPosition(j)->value > list.getPointAtPosition(i)->value)
				swap(list.getPointAtPosition(j), list.getPointAtPosition(i));
		}
	}

	str << "End:" << std::endl;
	str << list.print().str() << std::endl;

	return str;
}

// ======================================== Mergesort ========================================
// Master Theorem: Aufteilen, Zusammenfügen   (zweiter Fall)
//					2T(n/2)	+		n		= O(n*log(n))
// Mergesort: 5000 -> 3.22821s
// mergesort with list
// WC O(n * log(n)); AC O(n * log(n)); BC O(n * log(n)); Stable; Not In-Place;
template <typename T>
std::stringstream List<T>::mergeSort(List<T> &list)
{
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::mergeSort(): Can not sort on empty list.");
	
	List<T> a, b;
	std::stringstream str;
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;
	
	list.reset();
	if (!list.checkEnd())								// continue if more than 1 element left to sort
	{
		splitList(list, a, b);							// recursively split list = a, b until single
		mergeSort(a);
		mergeSort(b);

		mergeLists(list, a, b);							// recursive branches: merge (first single, then sorted) lists back together into sorted bigger lists
	}

	str << "End:" << std::endl;
	str << list.print().str() << std::endl;
	return str;
}

// split list into two lists a and b alternatingly
template<typename T>
void List<T>::splitList(List<T> &list, List<T> &a, List<T> &b)
{
	list.reset();
	bool switcher = true;

	while (list.current != nullptr)										// from the start alternate list a and b and switch into two halves
	{
		if (switcher)
		{
			a.push_back(list.current->value);
			list.del();
			switcher = false;
		}
		else
		{
			b.push_back(list.current->value);
			list.del();
			switcher = true;
		}
	}
}

// merge two (sorted) lists into single sorted list
template<typename T>
List<T> List<T>::mergeLists(List<T> &list, List<T> &a, List<T> &b)
{
	if (a.checkEmpty())										// if a is empty just return the sorted list b
		return b;
	if (b.checkEmpty())										// if b is empty just return the sorted list a
		return a;

	a.reset();												// reset pointers of both referenced lists to beginning - hence smallest nums
	b.reset();
	

	while (a.current != nullptr || b.current != nullptr)
	{
		// add a to sorted: (either element a is smaller than b and not already sorted) or (a is not empty but b is (hence only a elements that are bigger remaining))
		if (a.current != nullptr && b.current != nullptr)
		{
			if (a.current->value <= b.current->value)
			{
				list.push_back(a.current->value);			// NOTE: PUSH BACK ALREADY CREATES DEEP COPY IN HEAP
				a.del();
			}
			else												// otherwise only bigger elements in b remaining
			{
				list.push_back(b.current->value);
				b.del();
			}
		}
		else if (a.current == nullptr)
		{
			list.push_back(b.current->value);
			b.del();
		}
		else if (b.current == nullptr)
		{
			list.push_back(a.current->value);
			a.del();
		}
		
	}

	list.reset();										// reset pointer of new list to the start and return it
	return list;
}



// ======================================== Heapsort ========================================
// Master Theorem: Maxheap, Lowest heap rausnehmen  (zweiter Fall)
//					n	  +		log(n)				= O(n*log(n))
// Heapsort: 5000 -> 58.2264s
// heapsort with list (Heap: Ordered binary tree [here: left completed])
// WC O(n * log(n)); AC O(n * log(n)); BC O(n * log(n)); Not stable; In-Place;
template<typename T>
std::stringstream List<T>::heapSort(List<T> &list)
{
	if (list.checkEmpty() || list.length < 2)
		throw std::out_of_range("Error in List<T>::heapSort(): Can not sort on empty / single list.");

	std::stringstream str;
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;
	str << list.print_tree().str() << std::endl;

	for (int i = list.length; i >= 0; --i) {				// first heapify
		int x = -1;
		heapify(list, list.getPointAtPosition(i), x);
	}
	str << "Post heapify:" << std::endl;
	str << list.print_tree().str() << std::endl;
	str << list.print().str() << std::endl;

	for (int i = list.length; i >= 0; --i)					// continueously:
	{
		heapify(list, list.first, i);						// heapify
		swap(list.first, list.getPointAtPosition(i));		// move biggest element at heapified top to last position and not check that one anymore (--i)
	}

	// heapsort done - due to iteration first and last element not checked: swap them if necessary
	if (list.getPointAtPosition(1)->value > list.getPointAtPosition(2)->value)
		swap(list.getPointAtPosition(1), list.getPointAtPosition(2));
	if (list.getPointAtPosition(list.length - 1)->value < list.getPointAtPosition(list.length - 2)->value)
		swap(list.getPointAtPosition(list.length - 1), list.getPointAtPosition(list.length - 2));

	str << "Post sorting:" << std::endl;
	str << list.print_tree().str() << std::endl;
	str << list.print().str() << std::endl;

	return str;
}

// make root and every knot the biggest in its cluster (biggest el at top, smallest at bottom)
template<typename T>
void List<T>::heapify(List<T> &list, Node<T> *parent, int &indexLastNotSort)
{
	Node<T> *leftChild = list.getLeftChild(*parent);		// get left and right child of cluster
	Node<T> *rightChild = list.getRightChild(*parent);

	if (leftChild == nullptr) {								// if left child is empty on left complete heap - cluster empty - return
		return;
	}

	// both exist and one of them is bigger than parent
	if (rightChild != nullptr && (list.getPositon(*rightChild) < indexLastNotSort || indexLastNotSort == -1))
	{
		if (leftChild->value > parent->value || rightChild->value > parent->value) {	
			if (leftChild->value > rightChild->value)
			{															// if left child bigger right child - swap left child and parent and recurse
				swap(leftChild, parent);								/*		 2					6			*/
																		/*		/ \		------>	   / \			*/
				heapify(list, leftChild, indexLastNotSort);				/*	   6   5			 [2]  5			*/
			}
			else
			{
				swap(rightChild, leftChild);							// if left child smaller right child move bigger element to left and switch with parent
				swap(leftChild, parent);								/*		 2					6			*/
																		/*		/ \		------>	   / \			*/
				heapify(list, rightChild, indexLastNotSort);			/*	   5   6			 [2] [5]		*/
				heapify(list, leftChild, indexLastNotSort);				// and recurse for both because both their positions changed
			}
		}
	}
	else																// only left child exists - compare with parent, maybe switch and recurse if so
	{													
		if (leftChild->value > parent->value && (list.getPositon(*leftChild) < indexLastNotSort || indexLastNotSort == -1))
		{
																		/*		 2					5			*/
			swap(leftChild, parent);									/*		/		------>	   /			*/
			heapify(list, leftChild, indexLastNotSort);					/*	   5				 [2]			*/
		}
	}
}


// ======================================== Quicksort ========================================
// Master Theorem: Aufteilen, Tauschen   (zweiter Fall)
//					2T(n/2)	+	 n		 = O(n*log(n))
// Quicksort: 5000 -> 0.509088s
// call quicksort with default vars
// WC O(n²); AC O(n * log(n)); BC O(n * log(n)); Not stable; In-Place;
template<typename T>
std::stringstream List<T>::quickSort(List<T> &list)
{
	std::stringstream str;
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::quickSort(): Can not sort on empty list.");
	
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;
	quickSortList(list, 0, list.length - 1);
	str << "End:" << std::endl;
	str << list.print().str() << std::endl;

	return str;
}

// quicksort with list
template<typename T>																			//    a	->		       <- b
void List<T>::quickSortList(List<T> &list, const int a, const int b)	// sort from a to b           3 3 9 3 [7] 9 8 2 6 4
{
	if (list.checkEmpty() || b <= a)									// if given list is empty or we met at or passed the pivotelement we are done
		return;

	int pivotpos = a + rand() % (b - a);								// calculate random new pivot position between a and b
	
	Node<T> *pivot = list.getPointAtPosition(pivotpos);					// initialize first nodes (pivot, start and end of sorting range)
	Node<T> *i = list.getPointAtPosition(a);
	Node<T> *j = list.getPointAtPosition(b);
	
	while (i != pivot || j != pivot)									// move both nodes towards i-->pivot<--j and sort them by swapping to the correct side (bigger or smaller than pivot)
	{
		
		if (i->value > pivot->value && j->value < pivot->value)         // if i bigger and j smaller than pivot: swap and move both towards pivot
		{
			swap(i, j);
			i = i->next;
			j = j->prev;
		}

		else if (i->value > pivot->value) {								// if i bigger than pivot: move i to the left of pivot
			swap(i, pivot->prev);										// move it to the left of pivot
			swap(pivot->prev, pivot);									// rotate pivot with left
			pivot = pivot->prev;
			--pivotpos;													// pivot element moved one to the right due to asymetrical swap -> equalize offset
		}
			
		else if (j->value < pivot->value) {								// if j smaller than pivot: move i to the left of pivot
			swap(j, pivot->next);										// move it to the right of pivot
			swap(pivot, pivot->next);									// rotate pivot with right
			pivot = pivot->next;
			++pivotpos;													// pivot element moved one to the left due to asymetrical swap -> equalize offset
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

// ====================================== Quicksort stable ======================================
// Master Theorem: Aufteilen, Tauschen   (zweiter Fall)
//					2T(n/2)	+	 n		 = O(n*log(n))
// Quicksort: 5000 -> 0.509088s
// call quicksortstable with default vars
// WC O(n²); AC O(n * log(n)); BC O(n * log(n)); Stable; Not In-Place;
template<typename T>
std::stringstream List<T>::quickSortStable(List<T> &list)
{
	std::stringstream str;
	if (list.checkEmpty())
		throw std::out_of_range("Error in List<T>::quickSortStable(): Can not sort on empty list.");
	
	str << "Start:" << std::endl;
	str << list.print().str() << std::endl;
	quickSortStableList(list);
	str << "End:" << std::endl;
	str << list.print().str() << std::endl;

	return str;
}

// quicksortstable with list
template<typename T>
void List<T>::quickSortStableList(List<T> &list)
{
	if (list.length <= 1 || list.equal(list))								// if list is single element or contains only equal values nothing to sort - return
		return;
	
	Node<T> *pivot = list.getPointAtPosition(rand() % (list.length));		// initialize first nodes (pivot, start and end of sorting range)
	// for stability (elements with same value dont change their sequence) use O(n) lists to push values into
	List<T> listLeft;
	List<T> listRight;

	for (int i = 0; i < list.length; i++) {
		if (list.getPointAtPosition(i) != nullptr)							//	  a ->
		{																	//    3 3 9 3 [7] 9 8 2 6 4	
			if (list.getPointAtPosition(i)->value <= pivot->value) {		//    
				listLeft.push_back(list.getPointAtPosition(i)->value);		//	  a ->
			}																// L: 3 3 3 7 2 6 4
			else {															//	  a ->
				listRight.push_back(list.getPointAtPosition(i)->value);		// R: 9 8 8
			}																// So the sequence of same numbers remains
		}
	}
	
	if (!listLeft.checkEmpty())												// If a list is not empty recursively call and pivot again
	{
		listLeft.reset();
		quickSortStableList(listLeft);
	}
	if (!listRight.checkEmpty())											// If a list is not empty recursively call and pivot again
	{
		listRight.reset();
		quickSortStableList(listRight);
	}

	if (!listRight.checkEmpty())											// If we are done with recursive calls combine all sorted pivoted lists
	{
		listRight.reset();
		while (!listRight.checkEmpty()) {
			listLeft.push_back(listRight.current->value);
			listRight.del();
		}
	}
	
	list = listLeft;
}

// check if all elements in list have same value
template<typename T>
bool List<T>::equal(List<T> &list)
{
	if (list.checkEmpty())
		return false;
	
	bool equal = true;
	list.current = list.first;

	if (list.current != nullptr)
	{
		while (list.current->next != nullptr)
		{
			if (list.current->value == list.current->next->value)
			{
				list.current = list.current->next;
			}
			else
			{
				equal = false;
				break;
			}
		}
	}

	return equal;
}
