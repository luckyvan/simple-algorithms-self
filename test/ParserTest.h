// ParserTest.cpp

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ParserTest );
    CPPUNIT_TEST(testParser);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testParser();
   //void test_$exception_func();
};
#endif
