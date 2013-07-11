
#include <cppunit/config/SourcePrefix.h>
#include "../src/Rotate.h"
#include "RotateTest.h"
#include <iostream>


using namespace std;
using namespace EOP;
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( RotateTest );
// helper functions


void 
RotateTest::setUp()
{
}


void 
RotateTest::tearDown()
{
}

void
RotateTest::testGCD()
{
	CPPUNIT_ASSERT_EQUAL(size_t(3), gcd<size_t>(3,3));
	CPPUNIT_ASSERT_EQUAL(size_t(3), gcd<size_t>(3,6));
	CPPUNIT_ASSERT_EQUAL(size_t(2), gcd<size_t>(4,6));
	CPPUNIT_ASSERT_EQUAL(size_t(3), gcd<size_t>(15,21));
}



void
RotateTest::testRotateIndex()
{
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	rotate_indexed_nontrivial<int>(array, array+5, array+7);

	for(int i: array){
		cout << i;
	}
	cout << endl;

}
