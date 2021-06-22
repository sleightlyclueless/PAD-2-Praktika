#include "pch.h"

#define protected public
#define private public
#include "../Loesung4/List.h"
#undef protected
#undef private


// Mergesort Test
TEST(List_test, CheckMergeSort) {

	List<int>* a = new List<int>;
	a->ini(rand()%1000);
	List<int>::mergeSort(*a);

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

	// ================================================================
	// ASSERT_TRUE(a->get().value == t);	-> Bricht ab, wenn nicht wahr
	// EXPECT_EQ(1, 1);
}

// Heapsort Test
TEST(List_test, CheckHeapSort) {

	List<int>* a = new List<int>;
	a->ini(rand() % 1000);
	List<int>::heapSort(*a);

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;
	
}

// Quicksort Test
TEST(List_test, CheckQuickSort) {

	List<int>* a = new List<int>;
	a->ini(rand() % 1000);
	List<int>::quickSort(*a);

	EXPECT_TRUE(a->checkSortedAsc());

	delete a;

}
