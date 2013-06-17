
#include <cppunit/config/SourcePrefix.h>
#include "../src/Algorithm.h"
#include "../src/AlgorithmInterview.cpp"
#include "AlgorithmTest.h"
#include <algorithm>
#include <string>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( AlgorithmTest );
// helper functions


bool IsOdd(int i) {return (i%2) == 0; }

void 
AlgorithmTest::setUp()
{
}


void 
AlgorithmTest::tearDown()
{
}

void
AlgorithmTest::testPartition()
{
	typedef std::vector<int>::iterator iterator;

	std::vector<int> myvector;
	for(int i = 1; i<10; i++)
		myvector.push_back(i);	//1-9

	iterator bound = MyAl::partition(myvector.begin(), myvector.end(), IsOdd);

	for(iterator it = myvector.begin(); it != bound; it++)
		CPPUNIT_ASSERT(IsOdd(*it));

	for(iterator it = bound ; it != myvector.end(); it++)
		CPPUNIT_ASSERT(!IsOdd(*it));
}

void
AlgorithmTest::testQSort()
{
	int myints[] = {32,71,12,45,26,80,53,33};

	MyAl::qsort(myints, myints+4);
	int myints1[] = {12,32,45,71,26,80,53,33};
	CPPUNIT_ASSERT(std::equal(myints, myints+8, myints1));

	MyAl::qsort(myints+4, myints+8);
	int myints2[] = {12,32,45,71,26,33,53,80};
	CPPUNIT_ASSERT(std::equal(myints, myints+8, myints2));

	MyAl::qsort(myints, myints+8);
	int myints3[] = {12,26, 32, 33, 45, 53, 71,80};
	CPPUNIT_ASSERT(std::equal(myints, myints+8, myints3));
}


void
AlgorithmTest::testReverse()
{
	//original reverse
	int myints[] = {32,71,12,45,26,80,53,33};

	MyAl::reverse(myints, myints + 8);
	int myints1[] = { 33, 53, 80, 26, 45, 12, 71, 32};
	CPPUNIT_ASSERT(std::equal(myints, myints+8, myints1));


	//string reverse
	std::string str = "this is a cat";
	MyAl::reverse(str.begin(), str.end());
	CPPUNIT_ASSERT_EQUAL(std::string("tac a si siht"), str);
		
	char str1[] = "this is a cat";
	MyAl::reverse_sentence(str1, str1+sizeof(str1)/sizeof(char) - 1); // for end '\0'
	CPPUNIT_ASSERT_EQUAL(std::string("cat a is this"), std::string(str1));
}

void 
AlgorithmTest::testHeap()
{
	int myints[] = {10,20,30,5,15};
	std::vector<int> v(myints, myints + 5);

	CPPUNIT_ASSERT(!MyAl::is_heap(v.begin(), v.end()));

	MyAl::make_heap(v.begin(), v.end());
	//assert max heap
	CPPUNIT_ASSERT_EQUAL(30, v[0]);
	// mannually test is heap property
	CPPUNIT_ASSERT(v[1]>v[3]);
	CPPUNIT_ASSERT(v[1]>v[4]);

	CPPUNIT_ASSERT(MyAl::is_heap(v.begin(), v.end()));


	// heap insert operation
	v.push_back(99);
	CPPUNIT_ASSERT(!MyAl::is_heap(v.begin(), v.end()));
	// last element excluded
	CPPUNIT_ASSERT(MyAl::is_heap(v.begin(), v.begin()+5));
	MyAl::insert_heap(v.begin(), v.end());
	CPPUNIT_ASSERT(MyAl::is_heap(v.begin(), v.end()));

	
	// heap extract operation
	MyAl::extract_heap(v.begin(), v.end());
	CPPUNIT_ASSERT_EQUAL(99, v[5]);
	CPPUNIT_ASSERT(MyAl::is_heap(v.begin(), v.begin() + 5));
}


void 
AlgorithmTest::testRotate()
{
	int myints[] = {10,20,30,5,15};
	int myints1[] = {5, 15, 10,20,30};

	MyAl::rotate(myints, myints+5, 2);
	CPPUNIT_ASSERT(std::equal(myints, myints+5, myints1));

	int myints2[] = {1, 2, 3, 4,5,6,7};
	int myints3[] = {5, 6, 7, 1, 2, 3, 4};
	int myints4[] = {3, 4, 5, 6, 7, 1, 2};
	MyAl::rotate_dp(myints2, myints2 + 7, 3, true);
	CPPUNIT_ASSERT(std::equal(myints2, myints2+7, myints3));

	MyAl::rotate_dp(myints2, myints2 + 7, 2, true);
	CPPUNIT_ASSERT(std::equal(myints2, myints2+7, myints4));

}
