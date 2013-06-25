
/*
 * =====================================================================================
 *
 *       Filename:  Orbit.h
 *
 *    Description:  <Element of Programming> Ch2.
 *    				This file is to develop an algorithm, which relys on the regulation and
 *    				finite nature of an orbit,  to decide its structure. It could be used to
 *    				determine wheter a list has circle, or to analyze a Random Number 
 *    				Generator. 
 *
 *        Version:  1.0
 *        Created:  06/24/2013 09:00:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fanc
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ORBIT
#define ORBIT
#include <cstddef>

namespace EOP{
	
	template<typename F>
		//requires(Transformation(F))
	size_t	distance(typename F::domain x, typename F::domain y, F f){
				typedef size_t N;
				N n(0);
				while( x != y ){
					x = f(x);
					n = n + N(1);
				}
				return n;
			}

	template<typename F, typename P, typename D>
		//requires(Transformation(F) && UnaryPredicate(P) &&
		//F::domain == P::domain == D)
		D collosion_point(const D& x, F f, P p){
			if(!p(x)) return x;

			D slow = x;		// slow = f^(0)(x)
			D fast = f(x);  // fast = f^(1)(x)
			while(fast != slow){    // slow = f^(n)(x) && fast = f^(2n+1)(x)
				slow = f(slow);		// slow = f^(n+1)(x) && fast = f^(2n+1)(x)
				if(!p(fast)) return fast;
				fast = f(fast);		// slow = f^(n+1)(x) && fast = f^(2n+2)(x)
				if(!p(fast)) return fast;
				fast = f(fast);		// slow = f^(n+1)(x) && fast = f^(2n+3)(x)
			}						// n = n + 1

			return fast;
		}


	template<typename F, typename P, typename D>
		//requires(Transformation(F) && UnaryPredicate(P) &&
		//F::domain == P::domain == D)
		bool terminating(const D& x, F f, P p){
			D y = collosion_point(x, f, p);
			bool result = p(y);
			return !result;
		}
}//end of EOP
#endif
