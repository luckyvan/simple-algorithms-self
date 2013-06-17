/*
 * =====================================================================================
 *
 *       Filename:  AlgorithmInterview.cpp
 *
 *    Description:  Specific AlgorihtmsSolution to Interviews.
 *
 *        Version:  1.0
 *        Created:  04/26/2013 02:29:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Algorithm.h"

namespace MyAl{
	void reverse_sentence(char * first, char * last)
	{
		MyAl::reverse(first, last);
		while(first != last){
			char * l = std::find_if(first, last, std::bind2nd(std::equal_to<char>(), ' '));
			MyAl::reverse(first, l);
			first = std::find_if(l, last, std::bind2nd(std::not_equal_to<char>(), ' '));	
		}
	}

	template <class RandomAccessIterator>
		void rotate_dp(RandomAccessIterator first, RandomAccessIterator last, 
				size_t step, bool clockwise)
		{
			size_t len = last - first;
			size_t s = step % len;
			if( len == 1 || s == 0) return;

			bool shrink_head = true;
			if( len < 2*s){
				clockwise = !clockwise; s = len - s;	
			}

			for(size_t i = 0; i<s; i++){
				std::swap(*(first+i), *(last - s + i ));
			}

			(clockwise)? first += s: last -= s;
			rotate_dp(first, last, s, clockwise);

		}
}
