// BTreeTest.cpp

#ifndef BTREETEST_H
#define BTREETEST_H

#include <cppunit/extensions/HelperMacros.h>

class BTreeTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( BTreeTest );
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testDelete);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testInsert();
   void testDelete();
   //void test_$exception_func();
};
#endif
