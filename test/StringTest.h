// StringTest.cpp

#ifndef STRINGTEST_H
#define STRINGTEST_H

#include <cppunit/extensions/HelperMacros.h>

class StringTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( StringTest );
    CPPUNIT_TEST(testLString);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testLString();
   //void test_$exception_func();
};
#endif
