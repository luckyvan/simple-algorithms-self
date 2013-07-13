// RotateTest.cpp

#ifndef ROTATETEST_H
#define ROTATETEST_H

#include <cppunit/extensions/HelperMacros.h>

class RotateTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( RotateTest );
    CPPUNIT_TEST(testGCD);
    CPPUNIT_TEST(testRotate);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testGCD();
   void testRotate();
   //void test_$exception_func();
};
#endif
