#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/zones.h"
#include "../interface/sp.h"

 void sp_c::zones ( ap_uint<3> 		  phzvl_in[6][9],
					ap_uint<ph_hit_w> ph_hit_in[6][9],
					ap_uint<ph_raw_w> ph_zone[4][5])
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

 	 
	 ap_uint<3> temp=phzvl_in[0][0];
	 #ifndef CMSSW_MACRO
		zones_class zone_inst;
		zone_inst.zones_actual(phzvl_in,ph_hit_in,ph_zone);
	 #else
		zones_class *zone_inst= new zones_class();
		zone_inst->zones_actual(phzvl_in,ph_hit_in,ph_zone);
	 #endif


}



