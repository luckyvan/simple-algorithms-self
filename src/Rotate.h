/*
 * =====================================================================================
 *
 *       Filename:  Rotate.h
 *
 *    Description:	Elements of Programming Ch10
 *
 *        Version:  1.0
 *        Created:  07/11/2013 09:26:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fanc
 *   Organization: 	family of functions of 
 *                  - rotate
 *
 * =====================================================================================
 */

#ifndef ROTATE_H
#define ROTATE_H

#include "OrderedAlgebra.h"
#include "Swap.h"
#include <iostream>
#include <cstddef>
#include <iterator>

namespace EOP{
	template< typename I, typename F>
		//require Mutable(I) && Transformation(F) && I == Domain(F) && V == source(I))
		void cycle_from(I i, F f)
		{
			//i under f forms an orbit
			//for any n, deref(f^n(i)) has definition
			typename std::iterator_traits<I>::value_type tmp = *i;
			I j = i;
			I k = f(i);
			while(k != i){
				*j = *k;
				j = k;
				k = f(k);
			}
			*j = tmp;
		}

	template<typename I>
		//requires IndexedIterator(I)
		struct k_rotate_from_permutatin_indexed
		{
			size_t k;
			size_t n_minus_k;
			I f;
			k_rotate_from_permutatin_indexed(I ff, I m, I l):
				k(l - m), n_minus_k(m - ff), f(ff)
			{}

			I operator()(I x){
				// x belongs to [f, l)
				size_t i = x - f;
				if (i < k) return x + n_minus_k;
				else 	   return f + (i - k);
			}

		};



	template<typename I, typename F>
		//require Mutable(I) && Transformation(F) && I == Domain(F) && V == source(I))
		//require IndexedIterator(I)
		I rotate_cycles(I f, I m, I l, F from)
		{
			// precondition m - f >= 0, l - m >= 0
			size_t d = gcd<size_t>(m - f, l - m);
			while(d--) cycle_from(f + d, from);
			return f + (l - m);
		}

	template<typename I>
		//require Mutable(I) && V == source(I))
		//require IndexedIterator(I)
		I rotate_indexed_nontrivial(I f, I m, I l)
		{
			k_rotate_from_permutatin_indexed<I> p(f, m, l);
			return rotate_cycles(f, m, l, p);
		}

 	template<typename I>
		//require Mutable(I) && ForwardIterator(I))
		void rotate_forward_annotated(I f, I m, I l)
		{
			// mutable_bounded_range(f, l) && f < m < l
			size_t a = m - f;
			size_t b = l - m;

			while (true) {
				std::pair<I, I> p = swap_ranges_bounded(f, m, m, l);
				if (p.first == m && p.second == l){
					//assert(a == b);
					return;
				}
				f = p.first;
				if(f == m){
					//assert(b > a);
					m = p.second;
					b -= a;
				}else{
					//assert(a > b);
					a -= b;
				}
			}
		}

}

#endif
