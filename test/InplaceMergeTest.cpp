
#include <cppunit/config/SourcePrefix.h>
#include "../src/InplaceMerge.h"
#include "InplaceMergeTest.h"
#include <algorithm>
#include <string>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( InplaceMergeTest );
// helper functions



void 
InplaceMergeTest::setUp()
{
}


void 
InplaceMergeTest::tearDown()
{
}

 
void InplaceMergeTest::testInplaceMerge(){
	using MyAl::inplaceMerge;

	// only first five elements effective
	int a[] = {2, 3, 4, 7, 8, 0, 0, 0, 0, 0};
	int b[] = {1,5,6,9,10};


	inplaceMerge(a, b, 5, 5);
	CPPUNIT_ASSERT_EQUAL(int(1), a[0]);
	CPPUNIT_ASSERT_EQUAL(int(3), a[2]);
	CPPUNIT_ASSERT_EQUAL(int(5), a[4]);
	CPPUNIT_ASSERT_EQUAL(int(7), a[6]);
	CPPUNIT_ASSERT_EQUAL(int(9), a[8]);
}

