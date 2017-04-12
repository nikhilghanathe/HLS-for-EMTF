#include <ap_int.h>
#include "spbits.h"
#include "zones.h"
#include "sp.h"

//wrapper for zones module
 void sp_c::zones ( ap_uint<3> phzvl_in[5][9],
		  ap_uint<ph_hit_w> ph_hit_in[5][9],
	    	 ap_uint<ph_raw_w> ph_zone[4][5])
{
#pragma HLS PROTOCOL fixed

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

 	 zones_class inst;

	inst.zones_actual(phzvl_in,ph_hit_in,ph_zone);

}



