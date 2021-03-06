// OrbitTest.cpp

#ifndef ORBITTEST_H
#define ORBITTEST_H

#include <cppunit/extensions/HelperMacros.h>

class OrbitTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( OrbitTest );
    CPPUNIT_TEST(testCollision);
    CPPUNIT_TEST(testTerminating);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testCollision();
   void testTerminating();
   //void test_$exception_func();
};
#endif
