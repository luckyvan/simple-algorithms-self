
/*
 * =====================================================================================
 *
 *       Filename:  Swap.h
 *
 *    Description:	Elements of Programming. Ch9
 *
 *        Version:  1.0
 *        Created:  07/13/2013 09:26:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fanc
 *   Organization: 	family of functions of 
 *                  - swap
 * =====================================================================================
 */

#ifndef SWAP_H
#define SWAP_H
#include <algorithm>
#include <functional>

namespace EOP{

	template<typename I0, typename I1>
		//requires (Mutable(I0) && ForwardIterator(I0) &&
		//         (Mutable(I1) && ForwardIterator(I1) &&
		//         ValueType(I0) == Value(I1)
		void swap_step(I0& f0, I1& f1)
		{
			std::swap(*f0, *f1);
			f0++;
			f1++;
		}

	template<typename I0, typename I1>
		//requires (Mutable(I0) && ForwardIterator(I0) &&
		//         (Mutable(I1) && ForwardIterator(I1) &&
		//         ValueType(I0) == Value(I1)
		std::pair<I0, I1> swap_ranges_bounded(I0 f0, I0 l0, I1 f1, I1 l1)
		{
			// mutable_bounded_range(f0, l0)
			// mutable_bounded_range(f1, l1)
			while( (f0 != l0) && (f1 != l1)) swap_step(f0, f1);
			return std::make_pair(f0, f1);
		}
}

#endif
