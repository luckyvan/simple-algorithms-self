#include <stdlib.h>
namespace MyAl{
	void inplaceMerge(int * des, const int * src, size_t m, size_t n){
		size_t len = m + n;
		while( m != 0 && n != 0){
			if(des[m-1] > src[n-1]){
				des[m+n-1] = des[m-1]; m--;
			}else{
				des[m+n-1] = src[n-1]; n--;
			}
		}
		if(n != 0){
			for(size_t i = 0; i<n; i++)
				des[i] = src[i];
		}
	}
}
