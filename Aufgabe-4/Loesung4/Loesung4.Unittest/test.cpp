#include "pch.h"

#define protected public
#define private public
#include "../Loesung4/List.h"
#undef protected
#undef private

// Selectionsort Test
TEST(List_test, CheckSelectionSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::selectionSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

	// ================================================================
	// ASSERT_TRUE(a->get().value == t);	-> Bricht ab, wenn nicht wahr
	// EXPECT_EQ(1, 1);
}

// Insertionsort Test
TEST(List_test, CheckInsertionSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::insertionSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;
}

// Bubblesort Test
TEST(List_test, CheckBubbleSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::bubbleSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;
}

// Mergesort Test
TEST(List_test, CheckMergeSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand()%50 + 10);
		List<int>::mergeSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;
}

// Heapsort Test
TEST(List_test, CheckHeapSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::heapSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

}

// Quicksort Test
TEST(List_test, CheckQuickSort) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::quickSort(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

}

// Quicksort stabele Test
TEST(List_test, CheckQuickSortStable) {

	List<int> *a = new List<int>;
	int i = 10;
	a->fill(1, rand() % 50 + 10);

	while (i >= 0)
	{
		a->clear();
		a->fill(rand() % 1000 + 5, rand() % 50 + 10);
		List<int>::quickSortStable(*a);

		if (!a->checkSortedAsc())
			break;
		--i;
	}

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

}
