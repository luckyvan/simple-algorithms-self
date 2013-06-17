
#include <cppunit/config/SourcePrefix.h>
#include "../src/Int2ExcelHeader.cpp"
#include "Int2ExcelHeaderTest.h"
#include <algorithm>
#include <string>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ExcelTest );
// helper functions



void 
ExcelTest::setUp()
{
}


void 
ExcelTest::tearDown()
{
}

void ExcelTest::testLExcel(){
	CPPUNIT_ASSERT_EQUAL(convertNum2ExcelHeader(0), string("A"));
	CPPUNIT_ASSERT_EQUAL(string("Z"), convertNum2ExcelHeader(25));
	CPPUNIT_ASSERT_EQUAL(string("AA"), convertNum2ExcelHeader(26));
	CPPUNIT_ASSERT_EQUAL(string("AAA"), convertNum2ExcelHeader(27*26));
	CPPUNIT_ASSERT_EQUAL(string("AAAA"), convertNum2ExcelHeader(27*27*26));
}

