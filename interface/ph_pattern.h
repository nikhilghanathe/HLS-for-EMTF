#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"



class ph_pattern{
	public:
	ap_uint<1> pr;
	ap_uint<3>  bx [5][fold];


	void ph_pattern_exec(
			ap_uint<full_pat_w_st1> st1,
			ap_uint<1> st2,
			int station,
			int cscid,
			ap_uint<full_pat_w_st3> st3,
			ap_uint<full_pat_w_st3> st4,
			ap_uint<3> drifttime,
			ap_uint<3> foldn,
			ap_uint<6> *qcode
	);
};





