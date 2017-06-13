#include <ap_int.h>
#include "spbits.h"
#include "extender.h"
#include "sp.h"




void sp_c::extend_sector(   ap_uint<ph_raw_w> ph_zone[4][5],
			  ap_uint<ph_raw_w>	ph_ext[4][5],
			ap_uint<3> drifttime)
			{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

#pragma HLS ARRAY_PARTITION variable=ph_zone complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_ext complete dim=0

 static extend inst[4][5];
#pragma HLS ARRAY_PARTITION variable=inst complete dim=0

	for (int i = 0; i < 4; i = i+1){
#pragma HLS UNROLL
		for (int j = 1; j < 5; j = j+1){
#pragma HLS UNROLL
			inst[i][j].extender(ph_zone[i][j], &ph_ext[i][j]/*,i,j*/, drifttime);
		}
	}



			}
