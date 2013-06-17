
#include <cppunit/config/SourcePrefix.h>
#include "../src/LList.h"
#include "../src/SList.h"
#include "../src/DList.h"
#include "ListTest.h"
#include <algorithm>
#include <string>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ListTest );
// helper functions



void 
ListTest::setUp()
{
}


void 
ListTest::tearDown()
{
}

void ListTest::testLList(){
	using MyList::List;
	using MyList::LList;
	List<int>* plist = new LList<int>();

	// insert
	plist->insert(1);
	plist->insert(2);
	plist->insert(3);
	plist->insert(4);
	plist->insert(5);
	plist->insert(6);
	CPPUNIT_ASSERT_EQUAL(6, plist->rightLength());


	int temp;
	plist->getValue(temp);
	CPPUNIT_ASSERT_EQUAL(6, temp);
	
	plist->next();
	plist->getValue(temp);
	CPPUNIT_ASSERT_EQUAL(5, temp);
//	plist->print();

	plist->setEnd();
	CPPUNIT_ASSERT_EQUAL(0, plist->rightLength());
//	plist->print();

	plist->clear();
	CPPUNIT_ASSERT_EQUAL(0, plist->rightLength());
	CPPUNIT_ASSERT_EQUAL(0, plist->leftLength());
}
 
void ListTest::testDList(){
	using MyList::DList;

	DList<char> dl;
	CPPUNIT_ASSERT(dl.empty());
	CPPUNIT_ASSERT_EQUAL(dl.size(),size_t(0));

	dl.push_front('A');
	dl.push_back('B');
	CPPUNIT_ASSERT_EQUAL(dl.size(),size_t(2));
	CPPUNIT_ASSERT_EQUAL(dl.front(),'A');
	CPPUNIT_ASSERT_EQUAL(dl.back(),'B');

	int iv[5] = {1,2,3,4,5};
	DList<int> dli1(iv, iv+5);
	CPPUNIT_ASSERT_EQUAL(dli1.size(),size_t(5));
	CPPUNIT_ASSERT_EQUAL(dli1.front(),int(1));
	CPPUNIT_ASSERT_EQUAL(dli1.back(),int(5));

	dli1.reverse();
	CPPUNIT_ASSERT_EQUAL(dli1.size(),size_t(5));
	CPPUNIT_ASSERT_EQUAL(dli1.front(),int(5));
	CPPUNIT_ASSERT_EQUAL(dli1.back(),int(1));

}

void ListTest::testSList(){
	using MyList::SList;
	SList<int> sl;
	CPPUNIT_ASSERT(sl.empty());

	sl.push_front(5);
	int value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(5));
	CPPUNIT_ASSERT_EQUAL(sl.size(), size_t(1));
	CPPUNIT_ASSERT_EQUAL(false, sl.empty());

	sl.pop_front();
	CPPUNIT_ASSERT(sl.empty());
	CPPUNIT_ASSERT_EQUAL(sl.size(), size_t(0));

	sl.push_front(5);
	sl.push_front(4);
	sl.push_front(3);
	sl.push_front(2);
	sl.push_front(1);
	CPPUNIT_ASSERT_EQUAL(sl.size(), size_t(5));
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(1));

	
	sl.reverse();
	CPPUNIT_ASSERT_EQUAL(sl.size(), size_t(5));
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(5));
	sl.pop_front();
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(4));
	sl.pop_front();
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(3));
	sl.pop_front();
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(2));
	sl.pop_front();
	value = sl.front();
	CPPUNIT_ASSERT_EQUAL(value, int(1));
	sl.pop_front();
	CPPUNIT_ASSERT(sl.empty());

}
