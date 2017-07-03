#include <ap_int.h>
#include "spbits.h"
#include "sort.h"
#define num_levels 4


ap_uint<bwr> min_elem(ap_uint<bwr> a,
		ap_uint<bwr> b,
		ap_uint<bwr> c,
		ap_uint<bwr> d,
		ap_uint<bpow+1> *index)
{
#pragma HLS INLINE

	ap_uint<bwr> temp; ap_uint<bwr> temp1;
//Use of conditional operators make the delay longer. Instead use if-else ladder for more parallelism
	/*temp = (a+b)/2 + std::abs(int(a-b))/2;
	temp = (temp+c)/2 +std::abs(int(temp-c))/2;
	temp = (temp+d)/2 + std::abs(int(temp-d))/2;


	*index = temp==a ? 0: temp==b ? 1 : temp==c ? 2:3;*/

			temp=d; *index=3;


	if(a>=b && a>=c && a>=d){
		temp=a; *index=0;
	}

	if(b>=a && b>=c && b>=d){
		temp=b; *index=1;
	}

	if(c>=a && c>=b && c>=d){
		temp=c; *index=2;
	}



	return temp;
}
