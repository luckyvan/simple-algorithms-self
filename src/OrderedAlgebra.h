/*
 * =====================================================================================
 *
 *       Filename:  OrderedAlgebra.h
 *
 *    Description:	Elements of Programming Ch5
 *
 *        Version:  1.0
 *        Created:  07/01/2013 09:26:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fanc
 *   Organization: 	family of functions of 
 *                  - remainder
 *                  - gcd
 *
 * =====================================================================================
 */

namespace EOP{
	template <typename T>
	//requires AchimedeanMonoid(T)
	T remainder_recursive(T a, T b){
		// a >= b > 0
		if (a - b >= b) {
			a = remainder_recursive(a, b + b);
			if (a < b) return a;
		}

		return a - b;
	}


	template <typename T>
	//requires AchimedeanMonoid(T)
	T remainder_nonnegative(T a, T b){
		// a >= 0 && b > 0
		if (a < b) return a;
		return remainder_recursive(a, b);
	}

	template <typename T>
	//requires AchimedeanMonoid(T)
	T _largest_doubling(T a, T b){
		// a >= b > 0
		while (b <= a - b) b = b + b;
		return b;
	}

	template <typename T>
	//requires HalvableMonoid(T)
	T remainder_nonnegative_iterative(T a, T b){
		// a >= 0 && b > 0	
		if (a < b) return a;
		T c = _largest_doubling(a, b);
		a = a - c;
		while (c != b){
			c = c/2;
			if (c <= a) a = a - c;
		}
		return a;
	}



	template <typename T>
	//requires AchimedeanMonoid(T)
	T gcd(T a, T b){
		// a >= 0 && b >= 0 && !( a == 0 && b == 0)
		while (true) {
			if (b == T(0)) return a;
			a = remainder_nonnegative(a, b);
			if (a == T(0)) return b;
			b = remainder_nonnegative(b, a);
		}
	}
}

