#include "pch.h"

#define protected public
#define private public
#include "../Loesung4/List.h"
#undef protected
#undef private

// Google Testing Framework l�dt Klassen etc. rein
// Kein konkretes SetUp oder TearDown ben�tigt
/*template<typename T>
class List_sorted_test : public ::testing::Test
{
	protected:

	List<int>* a;


	virtual void SetUp() {
		a = new List<int>;
	}

	virtual void TearDown() {
		delete a;
	}

};*/

// insert Tests =============================================
TEST(List_sorted_test, InsertToEmptyList) {

	List<int>* a = new List<int>;

	const int n = 10;
	a->ins(n);

	EXPECT_TRUE(a->getCurrent() != nullptr && a->getFirst() != nullptr && a->getLast() != nullptr && a->getCurrent()->value == n && a->getFirst()->value == n && a->getLast()->value == n);

	delete a;

	// ================================================================
	// ASSERT_TRUE(a->get().value == t);	-> Bricht ab, wenn nicht wahr
	// EXPECT_EQ(1, 1);
}

TEST(List_sorted_test, InsertToList) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10);
		i--;
	}

	const int x = rand() % 10;
	a->ins(x);
	EXPECT_TRUE(a->getCurrent() != nullptr && a->getFirst() != nullptr && a->getLast() != nullptr && a->getCurrent()->value == x);

	delete a;
}

TEST(List_sorted_test, InsertToFirstList) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10 + 1);
		i--;
	}

	a->ins(0);
	EXPECT_TRUE(a->getCurrent() != nullptr && a->getFirst() != nullptr && a->getLast() != nullptr && a->getFirst()->value == 0);

	delete a;
}


TEST(List_sorted_test, InsertToLastList) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10);
		i--;
	}

	a->ins(10);
	EXPECT_TRUE(a->getCurrent() != nullptr && a->getFirst() != nullptr && a->getLast() != nullptr && a->getLast()->value == 10);

	delete a;
}


// Delete tests =============================================
TEST(List_sorted_test, DeleteFromEmptyList) {

	List<int>* a = new List<int>;

	a->ins(rand() % 10);
	a->del();

	EXPECT_TRUE(a->getCurrent() == nullptr && a->getFirst() == nullptr && a->getLast() == nullptr && a->empty());

	delete a;
}

TEST(List_sorted_test, DeleteFromSingleElementList) {

	List<int>* a = new List<int>;

	a->ins(rand() % 10);
	a->del();

	EXPECT_TRUE(a->getCurrent() == nullptr && a->getFirst() == nullptr && a->getLast() == nullptr && a->empty());

	delete a;
}

TEST(List_sorted_test, DeleteFromList) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10);
		i--;
	}
	i = rand() % 5 + 1;
	while (i > 0)
	{
		a->rec();
		i--;
	}

	const int length = a->getLength();
	a->del();

	EXPECT_TRUE(a->getCurrent() != nullptr && a->getLength() < length);

	delete a;
}

TEST(List_sorted_test, DeleteFromListFirstElement) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10);
		i--;
	}
	i = 10;
	while (i > 0)
	{
		a->rec();
		i--;
	}

	const int length = a->getLength();
	a->del();

	EXPECT_TRUE(a->getFirst() != nullptr && a->getLength() < length);

	delete a;
}

TEST(List_sorted_test, DeleteFromListLastElement) {

	List<int>* a = new List<int>;

	int i = 10;
	while (i > 0)
	{
		a->ins(rand() % 10);
		i--;
	}

	const int length = a->getLength();
	a->del();

	EXPECT_TRUE(a->getLast() != nullptr && a->getLength() < length);

	delete a;
}