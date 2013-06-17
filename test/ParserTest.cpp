
#include <cppunit/config/SourcePrefix.h>
#include "../src/Parser.h"
#include "ParserTest.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest );
// helper functions



void 
ParserTest::setUp()
{
}


void 
ParserTest::tearDown()
{
}

void ParserTest::testParser(){
	Parser parser;
	CPPUNIT_ASSERT_EQUAL(int(1), parser.eval("1"));

	CPPUNIT_ASSERT_EQUAL(int(123), parser.eval("123"));
	CPPUNIT_ASSERT_EQUAL(int(3), parser.eval("1+2"));
	CPPUNIT_ASSERT_EQUAL(int(2), parser.eval("1*2"));
	CPPUNIT_ASSERT_EQUAL(int(3), parser.eval("(1+2)"));
	CPPUNIT_ASSERT_EQUAL(int(9), parser.eval("(1+2)*3"));
}
