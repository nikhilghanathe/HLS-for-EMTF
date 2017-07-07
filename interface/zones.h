#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"

class zones_class{

public:
	ap_uint<1> pr;
	ap_uint<ph_raw_w> a_ph_zone[4][5];



	void zones_actual(  ap_uint<3> phzvl_in[6][9],
			 ap_uint<ph_hit_w> ph_hit_in[6][9],
		    	 ap_uint<ph_raw_w> ph_zone[4][5]);
};













