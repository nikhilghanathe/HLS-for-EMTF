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
//INLINE enables optimized implementation
#pragma HLS INLINE

	ap_uint<bwr> temp;


	if(a>=b && a>=c && a>=d){
		temp=a; *index=0;
	}
	else if(b>=a && b>=c && b>=d){
		temp=b; *index=1;
	}
	else if(c>=a && c>=b && c>=d){
		temp=c; *index=2;
	}
	else{
		temp=d; *index=3;
	}



	return temp;
}
