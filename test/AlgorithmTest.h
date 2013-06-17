// AlgorithmTest.cpp

#ifndef ALGORITHMTEST_H
#define ALGORITHMTEST_H

#include <cppunit/extensions/HelperMacros.h>

class AlgorithmTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( AlgorithmTest );
    CPPUNIT_TEST(testPartition);
    CPPUNIT_TEST(testQSort);
    CPPUNIT_TEST(testReverse);
    CPPUNIT_TEST(testHeap);
    CPPUNIT_TEST(testRotate);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testPartition();
   void testQSort();
   void testReverse();
   void testHeap();
   void testRotate();
   //void test_$exception_func();
};
#endif
