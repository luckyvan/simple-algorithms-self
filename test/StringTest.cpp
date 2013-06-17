
#include <cppunit/config/SourcePrefix.h>
#include "../src/String.h"
#include "StringTest.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( StringTest );
// helper functions



void 
StringTest::setUp()
{
}


void 
StringTest::tearDown()
{
}

String nrvOp(){
	String t("temp");

	return t;
}

void StringTest::testLString(){
	String s;
	CPPUNIT_ASSERT_EQUAL(s.length(), size_t(0));

	String s1("1");
	CPPUNIT_ASSERT_EQUAL(s1.length(), size_t(1));

	String s2("2");
	String s3(s2);

	nrvOp();
}
