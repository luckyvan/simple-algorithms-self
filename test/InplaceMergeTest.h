// InplaceMergeTest.cpp

#ifndef INPLACEMERGETEST_H
#define INPLACEMERGETEST_H

#include <cppunit/extensions/HelperMacros.h>

class InplaceMergeTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InplaceMergeTest );
    CPPUNIT_TEST(testInplaceMerge);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testInplaceMerge();
   //void test_$exception_func();
};
#endif
