
#include <cppunit/config/SourcePrefix.h>
#include "../src/Orbit.h"
#include "../src/SList.h"
#include "OrbitTest.h"
#include <algorithm>
#include <string>
#include <functional>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( OrbitTest );
// helper functions

using MyList::Link;

void 
OrbitTest::setUp()
{
}


void 
OrbitTest::tearDown()
{
}

void
OrbitTest::testCollision()
{

}



void
OrbitTest::testTerminating()
{
	using EOP::terminating;
	using MyList::SList;
	SList<int> sl;

	sl.push_front(5);
	sl.push_front(4);
	sl.push_front(3);
	sl.push_front(2);
	sl.push_front(1);

//	CPPUNIT_ASSERT(terminating(sl.begin(), sl.end()));
}
