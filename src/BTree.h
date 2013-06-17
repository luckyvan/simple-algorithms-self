

#ifndef MYBTREE_H
#define MYBTREE_H
#include <utility>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>

namespace MyBTree{
	template <typename Key, size_t degree>
	class BTree{
		//inner class for B-Tree Node definition
		class BNode{
			public:
				bool leaf;
				size_t num;
				std::vector<BNode*> childs;
				std::vector<Key> keys;

				BNode* leftSibling;
				BNode* rightSibling;
				BNode* parent;
				
				BNode(bool isLeaf, size_t childNum):
					leaf(isLeaf), num(childNum),
					childs(std::vector<BNode*>(2*degree+1)),
					keys(std::vector<Key>(2*degree)),
					leftSibling(NULL),rightSibling(NULL), parent(NULL)
					{}

				void print(std::ostream& o, size_t offset = 0){
					if(leaf){
						for(int i = 1; i<=num; i++)
							o<<keys[i];
					}else{
						o << keys[1]<<"--->";
						childs[1]->print(o, offset+1);
						for(size_t i = 2; i<=num; i++){
							o << keys[i] << "--->";
							for(size_t j = 0; j<offset; j++)
								o<<"      ";	
						   	childs[i]->print(o, offset+1);			
						}
						for(size_t j = 0; j<offset; j++)
							o<<"     ";	
						o<<" --->";
						childs[num+1]->print(o, offset+1);			
					}
					o<<std::endl;
				}
			
			template<class V, size_t t>
			friend	std::ostream& operator<<(std::ostream&,  BNode&);

		};

		BNode* root;
		public:
			//except for root, all nodes in B tree should contain [degree - 1, 2*degree - 1] keys
			//Create an empty B-tree
			BTree(){
				root = new BNode(true,0);
			}

			BTree& insert(const Key& k);
			BTree& erase(const Key& k);

			bool contains(Key k){
				std::pair<BNode*, size_t> pair = searchBTree(root, k);
				if(pair.first != NULL)
					return true;
				return false;
			}

			bool isLeaf(Key k){
				std::pair<BNode*, size_t> pair = searchBTree(root, k);
				return (NULL != pair.first) && isLeaf(pair.first);
			}

			bool isRoot(Key k){
				std::pair<BNode*, size_t> pair = searchBTree(root, k);
				return (NULL != pair.first) && isRoot(pair.first);
			}

			bool isInternal(Key k){
				std::pair<BNode*, size_t> pair = searchBTree(root, k);
				return (NULL != pair.first) && isInternal(pair.first);
			}

			template<class V, size_t d>
			friend  
			std::ostream& operator<< (std::ostream& o, BTree<V,d>&);

		private:
			bool isLeaf(BNode* n){
				return n->leaf;
			}

			bool isRoot(BNode* n){
				return n == root;
			}

			bool isInternal(BNode* n){
				return !isLeaf(n) && !isRoot(n);
			}


			bool isFull(BNode* node){
				return node->num == 2*degree - 1;
			}

			bool isEmpty(BNode* node){
				return !isRoot(node) && (node->num == degree - 1);
			}


			void expandEmptyNode(BNode* x){
				using std::copy_backward;
				assert(isEmpty(x));
				assert(!isRoot(x));
				BNode* parent = x->parent;

				size_t index = 1;
				while(parent->childs[index] != x)
					index++;

				if( NULL != x->rightSibling ){
					if(isEmpty(x->rightSibling)){
						mergeChild(parent, index);
					}else{
						//rotate
						BNode* rightSibling = x->rightSibling;
						x->keys[degree] = parent->keys[index];
						parent->keys[index] =rightSibling->keys[1];
						x->childs[degree+1] = rightSibling->childs[1];
						x->num++;
						
						std::vector<Key>& keys = rightSibling->keys;
						std::vector<BNode*>& childs = rightSibling->childs;
						size_t num = rightSibling->num;

						copy_backward(&(keys[2]), &(keys[num+1]), &(keys[num]));
						copy_backward(&(childs[2]), &(childs[num+2]), &(childs[num]));
						rightSibling->num--;
					}//empty right sibling

				}else{ // use left sibling
					if(isEmpty(x->leftSibling)){
						mergeChild(parent, index-1);
					}else{
						BNode* leftSibling = x->leftSibling;
						std::vector<Key>& keys = x->keys;
						std::vector<BNode*>& childs = x->childs;
						size_t num = x->num;

						copy_backward(&(keys[1]), &(keys[num+1]), &(keys[num+2]));
						copy_backward(&(childs[1]), &(childs[num+2]), &(childs[num+3]));

						x->keys[1] = parent->keys[index];
						parent->keys[index] = leftSibling->keys[leftSibling->num];
						x->childs[1] = leftSibling->childs[leftSibling->num+1];
						leftSibling->num--;
						x->num++;
					}

				}//right and left sibling
			}// end of expand

			//helpers
			//recursivly search in a BNode
			//return a pair of <BNode*, size_t>. The ptr is NULL if none found 
			std::pair<BNode*, size_t> searchBTree(BNode* x, Key key, bool expand = false){
				if(expand && isEmpty(x)){ 
					expandEmptyNode(x);
				}

				size_t i = 1;
				while( i <= x->num && key > x->keys[i] ){
					i++;
				}

				bool isFound = (i <= x->num && key == x->keys[i]);
				if(isFound){
					return std::make_pair(x, i);
				}
				else if(!isFound && x->leaf){
					return std::make_pair((BNode*)NULL, 0);
				}else{
					return searchBTree(x->childs[i], key, expand);
				}
			}

			std::pair<BNode*, size_t> searchAndExpand(BNode* x, Key key){
				if(isEmpty(x)){ 
					expandEmptyNode(x);
				}

				size_t i = 1;
				while( i <= x->num && key > x->keys[i] ){
					i++;
				}

				bool isFound = (i <= x->num && key == x->keys[i]);
				if(isFound){
					return std::make_pair(x, i);
				}
				else if(!isFound && x->leaf){
					return std::make_pair((BNode*)NULL, 0);
				}else{
					return searchAndExpand(x->childs[i], key);
				}
				
			}

			void mergeChild(BNode* x, size_t i){
				using std::copy;
				using std::copy_backward;
				assert((i <= x->num )&&(i>=1));
				assert(!isEmpty(x));
				assert(isEmpty(x->childs[i]) && isEmpty(x->childs[i+1]));


				BNode* y = x->childs[i];
				BNode* z = x->childs[i+1];

				copy(&(z->keys[1]), &(z->keys[degree]), &(y->keys[degree+1]));
				copy(&(z->childs[1]), &(z->childs[degree+1]), &(y->childs[degree+1]));

				y->rightSibling = z->rightSibling;

				delete z;

				y->keys[degree] = x->keys[i];
				y->num = 2*degree - 1;

				if(isRoot(x) && (x->num == 1)){
					root = y;
					y->parent = NULL;
					delete x;
				}else{
					for(size_t j = i+1; j <= (x->num); j++){
						x->keys[j-1] = x->keys[j];
						x->childs[j] = x->childs[j+1];
					}
					x->num--;
				}

			}


			void splitChild(BNode* x, size_t i){
				using std::copy;
				using std::copy_backward;
				//from a top-down traverse, the node x should not be full at this moment.
				assert(!isFull(x));
				assert(isFull(x->childs[i]));

				// 1. split y to y and z
				BNode* y = x->childs[i];
				BNode* z = new BNode(y->leaf, degree - 1);

				// copy keys from [t+1, 2*t)
				copy(&(y->keys[degree+1]), &(y->keys[2*degree]), 
						&(z->keys[1]));
				if(!(y->leaf)){
					copy(&(y->childs[degree+1]), &(y->childs[2*degree+1]), 
							&(z->childs[1]));	
				}
				y->num = degree - 1;

				// 2. adjust ptrs
				if(y->rightSibling != NULL)
					z->rightSibling = y->rightSibling;
				y->rightSibling = z;
				z->leftSibling = y;
				z->parent = x;

				// 3. upload middle key and child
				size_t xnum = x->num;	
				//[i+1, num+2) --> [i+2, num+3)
				copy_backward(&(x->childs[i+1]), &(x->childs[xnum+2]),
						&(x->childs[xnum+3]));

				x->childs[i+1] = z;

				copy_backward(&(x->keys[i]), &(x->keys[xnum+1]),
						&(x->keys[xnum+2]));
				x->keys[i] = y->keys[degree];
				x->num++;
			}	


			
			void insertNonFull(BNode* x, Key k){
				int index = x->num;
				if(x->leaf){
					while((index >= 1) && (k < x->keys[index]) ){
						x->keys[index+1] = x->keys[index];
						index--;
					}
					x->keys[index+1] = k;
					x->num++;
				}else{
					while((index >= 1) && (k < x->keys[index])){
						index--;
					}
					index++;
					BNode* c = x->childs[index];
					if(isFull(c)){
						splitChild(x, index);
						if(k > x->keys[index])
							index++;

					}
					insertNonFull(c, k);
				}
			}
			


			void erase(const Key& k, BNode* x){

				std::pair<BNode*, size_t> pair = searchBTree(x, k, true);
				BNode* node = pair.first;
				size_t index = pair.second;
				if(NULL != node){
					//1
					if(isLeaf(node)){
						//1
						for(size_t i = index; i <= (node->num-1); i++){
							node->keys[i] = node->keys[i+1];
						}
						node->num--;
					}else if(!isLeaf(node)){
						// 2.a right child not empty
						BNode* rightChild = node->childs[index+1];
						BNode* leftChild = node->childs[index];
						if(!isEmpty(rightChild)){
							Key succ = rightChild->keys[1];
							node->keys[index] = succ;
							erase(succ, rightChild);
						}else if(!isEmpty(leftChild)){
						// 2.b a left child not empty
							Key pred = leftChild->keys[leftChild->num];
							node->keys[index] = pred;
							erase(pred, leftChild);
						}else{
						// 2.c two childs are both empty
							mergeChild(node, index);
							erase(k, node->childs[index]);
						}
					}
				}
			}
	}; // class BTree

	/* *
	 * Insert Invariant:
	 *    1. The height of the tree will only increase when split a full root
	 *    2. Since it is a top-down traverse, each time ecounting a full node, its parent 
	 *    is guaranteed not to be full. 
	 * */
	template<class Key,size_t size>
	BTree<Key, size>& BTree<Key, size>::insert(const Key& k){
		typedef BTree<Key, size>::BNode BNode;
		BNode* r = root;
		if(isFull(r)){
			BNode* s = new BNode(false, 0);
			this->root = s;	
			s->childs[1] = r;
			r->parent = root;
			splitChild(s, 1);
			insertNonFull(s, k);
		}else{
			insertNonFull(r, k);
		}
		return *this;
	}

	template<class Key,size_t size>
	BTree<Key, size>& BTree<Key, size>::erase(const Key& k){
		erase(k, root);
		return *this;
	}

	template<class Key, size_t degree>
	std::ostream& operator<<(std::ostream& o, BTree<Key,degree>& btree){
		typedef typename BTree<Key, degree>::BNode BNode;
		o << std::endl;
		BNode* head = btree.root;
		head->print(o);
		return o;	
	}
	
	template<class Key, size_t degree>
	std::ostream& operator<<(std::ostream& o, typename BTree<Key, degree>::BNode& node){
		typedef typename BTree<Key, degree>::BNode BNode;
		for(int i = 1; i <= node.num; i++)
			o << node.keys[i];
	}
}// namespace

#endif

