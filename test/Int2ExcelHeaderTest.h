// ExcelTest.cpp

#ifndef EXCELTEST_H
#define EXCELTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ExcelTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ExcelTest );
    CPPUNIT_TEST(testLExcel);
    //CPPUNIT_TEST_EXCEPTION(test_$exception_func, exception);
    CPPUNIT_TEST_SUITE_END();

public: 
   void setUp();
   void tearDown();

   void testLExcel();
   //void test_$exception_func();
};
#endif
