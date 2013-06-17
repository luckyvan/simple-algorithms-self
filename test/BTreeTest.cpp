
#include <cppunit/config/SourcePrefix.h>
#include "../src/BTree.h"
#include "BTreeTest.h"
#include <algorithm>
#include <string>
#include <vector>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( BTreeTest );
// helper functions



void 
BTreeTest::setUp()
{
}


void 
BTreeTest::tearDown()
{
}

void BTreeTest::testDelete(){
	using MyBTree::BTree;
	BTree<char, 2> btree;
	//setup a tree
	// I --> R --> SX
	//       | --> NO
	//   --> E --> GH
	//       | --> AC
	btree.insert('A').insert('S').insert('E').insert('R');
	btree.insert('C').insert('H').insert('I').insert('N');
	btree.insert('G').insert('X').insert('O');

//	std::cout << btree << std::endl;
	// 1. earse a key in a non-empty leaf
	btree.erase('C');
//	CPPUNIT_ASSERT(!btree.contains('C'));
//	std::cout << btree << std::endl;

	// 2. a erase an internal node with nonempty child
	btree.erase('E');
//	std::cout << btree << std::endl;

	btree.erase('G');
//	std::cout << btree << std::endl;

	btree.erase('H').erase('N');
//	std::cout << btree << std::endl;

	btree.erase('O');
//	std::cout << btree << std::endl;

	btree.erase('R');
//	std::cout << btree << std::endl;
}

void BTreeTest::testInsert(){
	using MyBTree::BTree;
	BTree<char, 2> btree;

	btree.insert('A').insert('S').insert('E').insert('R');
	CPPUNIT_ASSERT(btree.contains('A'));
	CPPUNIT_ASSERT(btree.contains('S'));
	CPPUNIT_ASSERT(btree.contains('E'));
	CPPUNIT_ASSERT(btree.contains('R'));
	CPPUNIT_ASSERT(!btree.contains('C'));

	//now E is the root
	CPPUNIT_ASSERT(btree.isLeaf('A'));
	CPPUNIT_ASSERT(btree.isLeaf('S'));
	CPPUNIT_ASSERT(!btree.isLeaf('E'));
	CPPUNIT_ASSERT(btree.isLeaf('R'));
	CPPUNIT_ASSERT(btree.isRoot('E'));
	CPPUNIT_ASSERT(!btree.isRoot('R'));

	btree.insert('C').insert('H').insert('I').insert('N');
	btree.insert('G').insert('X');

	//now I is root, E and R is internal
	//root
	CPPUNIT_ASSERT(btree.isRoot('I'));
	CPPUNIT_ASSERT(btree.isInternal('E'));
	CPPUNIT_ASSERT(btree.isInternal('R'));
	CPPUNIT_ASSERT(btree.isLeaf('A'));
	CPPUNIT_ASSERT(btree.isLeaf('C'));
	CPPUNIT_ASSERT(btree.isLeaf('G'));
	CPPUNIT_ASSERT(btree.isLeaf('H'));
	CPPUNIT_ASSERT(btree.isLeaf('N'));
	CPPUNIT_ASSERT(btree.isLeaf('S'));
	CPPUNIT_ASSERT(btree.isLeaf('X'));
	

}
