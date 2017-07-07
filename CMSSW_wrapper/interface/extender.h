#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"


class extend {

public:
	ap_uint<1> pr;


	ap_uint<ph_raw_w>	 bx1, bx2;
	ap_uint<ph_raw_w>	temp1, temp2;

	void extender(
			ap_uint<ph_raw_w>  inp,
			ap_uint<ph_raw_w>  *outp,
			ap_uint<3> 		   drifttime);

};
