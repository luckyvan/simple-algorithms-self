
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
#include <tuple>

namespace EOP{
	
	template<typename F, typename D>
		//requires(Transformation(F))
	size_t	distance(D x, D y, F f){
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
		D collision_point(const D& x, F f, P p){
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
			D y = collision_point(x, f, p);
			bool result = p(y);
			return !result;
		}


	template<typename F, typename P, typename D>
		//requires(Transformation(F) && UnaryPredicate(P) &&
		//F::domain == P::domain == D)
		bool circular(const D& x, F f, P p){
			D y = collision_point(x, f, p);
			return p(y) && x == f(y);
		}


	template<typename F, typename D>
		//requires(Transformation(F) &&
		//F::domain == D)
		D _convergent_point(D x0, D x1, F f){
			while ( x0 != x1 ){
				x0 = f(x0);
				x1 = f(x1);
			}
			return x0;
		}

	template<typename F, typename P, typename D>
		//requires(Transformation(F) && UnaryPredicate(P) &&
		//F::domain == P::domain == D)
		D connection_point(const D& x, F f, P p){
			D y = collision_point(x, f, p);
			if(!p(y)) return y;
			return _convergent_point(x, f(y), f);
		}

	template<typename F, typename P, typename D>
		//requires(Transformation(F) && UnaryPredicate(P) &&
		//F::domain == P::domain == D)
		std::tuple<size_t, size_t, D>
		orbit_structure(const D& x, F f, P p){
			D y = connection_point(x, f, p);
			size_t m = distance(x, y, f);
			size_t n = 0;
			if(p(y)) n = distance(f(y), y, f);

			// m == h-1 , n == 0 ,y == terminating point
			// or m == h, n == c-1, y == connection point
			return std::tuple<size_t, size_t, D>(m, n, y);
		}





}//end of EOP
#endif
