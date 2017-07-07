#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/extender.h"
void extend::extender(
		ap_uint<ph_raw_w> inp,
		ap_uint<ph_raw_w>	*outp,
		ap_uint<3> drifttime){

#pragma HLS INTERFACE ap_stable port=inp  //This directive optimizes unnecessary registers
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

 ap_uint<ph_raw_w> temp;


temp=inp;
temp= ap_uint<ph_raw_w>(temp) | ap_uint<ph_raw_w>(temp1) | temp2;
temp2=temp1;
temp1=inp;
*outp=temp;


}
