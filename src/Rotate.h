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
#include "OrderedAlgebra.h"
#include <cstddef>

namespace EOP{
	template<typename V, typename I, typename F>
		//require Mutable(I) && Transformation(F) && I == Domain(F) && V == source(I))
		void cycle_from(I i, F f)
		{
			//i under f forms an orbit
			//for any n, deref(f^n(i)) has definition
			V tmp = *i;
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



	template<typename V, typename I, typename F>
		//require Mutable(I) && Transformation(F) && I == Domain(F) && V == source(I))
		//require IndexedIterator(I)
		I rotate_cycles(I f, I m, I l, F from)
		{
			// precondition m - f >= 0, l - m >= 0
			size_t d = gcd<size_t>(m - f, l - m);
			while(d--) cycle_from<V>(f + d, from);
			return f + (l - m);
		}

	template<typename V, typename I>
		//require Mutable(I) && V == source(I))
		//require IndexedIterator(I)
		I rotate_indexed_nontrivial(I f, I m, I l)
		{
			k_rotate_from_permutatin_indexed<I> p(f, m, l);
			return rotate_cycles<V>(f, m, l, p);
		}


}
