#include <ap_int.h>
#include "spbits.h"
#include "zones.h"
#include "sp.h"

 void sp_c::zones ( ap_uint<3> phzvl_in[6][9],
		  ap_uint<ph_hit_w> ph_hit_in[6][9],
	    	 ap_uint<ph_raw_w> ph_zone[4][5]/*,
			ap_uint<bw_fph> ph_in[5][9][seg_ch],
					ap_uint<bw_th> th11_in[2][3][th_ch11],
					ap_uint<bw_th> th_in[5][9][seg_ch],
					ap_uint<seg_ch> vl_in[5][9],
					ap_uint<seg_ch> me11a_in[2][3],
					ap_uint<4> cpatr_in[5][9][seg_ch],
					ap_uint<th_hit_w> th_hit_in[5][9],
					ap_uint<bw_fph> ph[5][9][seg_ch],
					ap_uint<bw_th> th11[2][3][th_ch11],
					ap_uint<bw_th> th[5][9][seg_ch],
					ap_uint<seg_ch> vl[5][9],
					ap_uint<3> phzvl[5][9],
					ap_uint<seg_ch> me11a[2][3],
					ap_uint<4> cpatr[5][9][seg_ch],
					ap_uint<ph_hit_w> ph_hit[5][9],
					ap_uint<th_hit_w> th_hit[5][9]*/)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

 	 zones_class inst;

	inst.zones_actual(phzvl_in,ph_hit_in,ph_zone);


}



