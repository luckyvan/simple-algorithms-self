
#include <cppunit/config/SourcePrefix.h>
#include "../src/Orbit.h"
#include "../src/SList.h"
#include "OrbitTest.h"
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

using namespace EOP;
using namespace MyList;
// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( OrbitTest );
// helper functions

template<typename D>
struct F{
	D operator()(D x){
		return x->next;
	}
};

template<typename D>
struct P{
	bool operator() ( const D& x) const {
		return x != NULL;
	}
};

void 
OrbitTest::setUp()
{
}


void 
OrbitTest::tearDown()
{
}

void
OrbitTest::testStructure()
{
	SList<int> sl;
	sl.push_front(5);
	Link<int>* tail = sl.begin();
	sl.push_front(4);	
	sl.push_front(3);	
	sl.push_front(2);	
	Link<int>* connection = sl.begin();
	sl.push_front(1);	

	std::tuple<size_t, size_t, Link<int>* >
		s = orbit_structure(sl.begin(), F< Link<int>* >(), P< Link<int>* >());

	CPPUNIT_ASSERT_EQUAL(std::get<0>(s) , size_t(5));
	CPPUNIT_ASSERT_EQUAL(std::get<1>(s) , size_t(0));
	CPPUNIT_ASSERT_EQUAL(std::get<2>(s) , sl.end());


	//form an loop of scale 4
	sl.push_front(0);	
	tail->next = connection;
	s = orbit_structure(sl.begin(), F< Link<int>* >(), P< Link<int>* >());
	CPPUNIT_ASSERT_EQUAL(std::get<0>(s) , size_t(2));
	CPPUNIT_ASSERT_EQUAL(std::get<1>(s) , size_t(3));
	CPPUNIT_ASSERT(std::get<2>(s) != sl.end());

}



void
OrbitTest::testTerminating()
{
	SList<int> sl;
	sl.push_front(5);
	Link<int>* tail = sl.begin();
	sl.push_front(4);	
	sl.push_front(3);	
	sl.push_front(2);	
	sl.push_front(1);	

	CPPUNIT_ASSERT(terminating(sl.begin(), F< Link<int>* >(), P< Link<int>* >()));

	//form a loop
	Link<int>* front = sl.begin();
	tail->next = front;
	CPPUNIT_ASSERT(!terminating(sl.begin(), F< Link<int>* >(), P< Link<int>* >()));
	
}
