
/*
 * =====================================================================================
 *
 *       Filename:  Algorithm.h
 *
 *    Description:	Basic Algorithms
 *
 *        Version:  1.0
 *        Created:  07/13/2013 09:26:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fanc
 *   Organization: 	family of functions of 
 *                  - partition
 *                  - qsort
 *                  - reverse
 *                  - heap
 *
 * =====================================================================================
 */
#include <functional>
#include <algorithm>
#include <iostream>

#ifndef MYALGORITHM_H
#define MYALGORITHM_H
namespace MyAl{

	template <class BidirectionalIterator, class UnaryPredicate>
		BidirectionalIterator partition(BidirectionalIterator first, 
				BidirectionalIterator last, UnaryPredicate pred){
			while(first != last){
				while(pred(*first)){
					first++;
					if(first == last) return first;
				}
				do{
					--last;
					if(first == last) return first;
				}while(!pred(*last));
				std::swap(*first, *last);
				++first;

			}
			return first;
		}

	template <class RandomAccessIterator>
		void qsort(RandomAccessIterator first, RandomAccessIterator last){
			if( first < last ){
				RandomAccessIterator it = MyAl::partition(first, last, 
											std::bind2nd(std::less<int>(), *(last-1)));
				std::swap(*it, *(last-1));
				qsort(first, it);
				qsort(it+1,last);
			}
		}

	template <class BidirectionalIterator>
		void reverse(BidirectionalIterator first, 
				BidirectionalIterator last){
			while((first != last) && (first+1) != last){
				--last;	
				std::swap(*first, *last);
				++first;
			}
		}

	//helper
	size_t _parent(size_t i){
		return (i-1)/2;
	}

	size_t _left(size_t i){
		return 2*i+1;
	}

	size_t _right(size_t i){
		return 2*i+2;
	}

	template <class RandomAccessIterator>
	void _max_heapify(RandomAccessIterator first, 
			RandomAccessIterator last, size_t i){
		size_t size = last - first;

		size_t l = _left(i);
		size_t r = _right(i);

		size_t largest = 0;
		if( l < size && *(first+l) > *(first+i)){
			largest = l;
		}else{
			largest = i;
		}

		if( r < size && *(first+r) > *(first+i)){
			largest = r;
		}

		if( largest != i){
			std::swap( *(first + i), *(first + largest));
			_max_heapify(first, last, largest);
		}
	}
	// heap like operation
	template <class RandomAccessIterator>
		void make_heap(RandomAccessIterator first,
				RandomAccessIterator last){
			size_t len = last - first;
			for( int i = len/2; i>=0; i--){
				_max_heapify(first, last, i);
			}
		}

	template <class RandomAccessIterator>
		bool is_heap(RandomAccessIterator first,
				RandomAccessIterator last){
			size_t len = last - first;
			for( int i = len/2; i>=0; i--){
				size_t l = _left(i);
				size_t r = _right(i);
				if( l < len && *(first+l) > *(first+i)){
					return false;
				}
				if( r < len && *(first+r) > *(first+i)){
					return false;
				}
			}

			return true;
		}

	template <class RandomAccessIterator>
		void extract_heap(RandomAccessIterator first,
				RandomAccessIterator last){
			if(first == last || (first + 1) == last) return;

			std::swap(*(first), *(last - 1));

			_max_heapify(first, last-1,0);
		}

	template <class RandomAccessIterator>
		void insert_heap(RandomAccessIterator first,
				RandomAccessIterator last){
			if(first == last || (first + 1) == last) return;
			size_t l = last - first - 1;
			size_t parent = 0;
			do{
				parent = _parent(l);
				if(*(first + parent) < *(first + l)){
					std::swap(*(first+parent), *(first + l));
					l = parent;
				}else
					break;
			}while(parent != 0);
		}

	template <class BidirectionalIterator>
		void rotate(BidirectionalIterator first, BidirectionalIterator last,
				size_t step){
			size_t len = last - first;
			size_t s = step % len;

			MyAl::reverse(first, last);
			MyAl::reverse(first, first + s);
			MyAl::reverse(first + s, last);

		}

}

#endif
