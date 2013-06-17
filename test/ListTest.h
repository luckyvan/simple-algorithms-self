// ListTest.cpp

#ifndef LISTTEST_H
#define LISTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ListTest );
    CPPUNIT_TEST(testLList);
    CPPUNIT_TEST(testDList);
    CPPUNIT_TEST(testSList);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testLList();
   void testDList();
   void testSList();
   //void test_$exception_func();
};
#endif
