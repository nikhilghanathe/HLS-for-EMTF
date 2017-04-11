#include <ap_int.h>
#include "spbits.h"



class ph_pattern{
	public:
		ap_uint<3> bx[red_pat_w_st1];
		ph_pattern(void)
		{
		#pragma HLS ARRAY_PARTITION variable=bx complete dim=1
			for(int i=0;i<red_pat_w_st1;i++)
				bx[i]=0;
			}

		void ph_pattern_exec(
		        ap_uint<full_pat_w_st1> st1,
		        ap_uint<1> st2,
		        ap_uint<full_pat_w_st3> st3,
		        ap_uint<full_pat_w_st3> st4,
		        ap_uint<3> drifttime,
		        ap_uint<3> foldn,
		        ap_uint<6> *qcode
		        );
};





