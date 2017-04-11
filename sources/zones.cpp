#include <ap_int.h>
#include "spbits.h"
#include "zones.h"
#include "sp.h"

 void sp_c::zones ( ap_uint<3> phzvl_in[5][9],
		  ap_uint<ph_hit_w> ph_hit_in[5][9],
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
#pragma HLS PROTOCOL fixed

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

 	 zones_class inst;

	inst.zones_actual(phzvl_in,ph_hit_in,ph_zone);

/*	for(int i=0;i<5;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
#pragma HLS UNROLL
			ph_hit[i][j]=ph_hit_in[i][j];
			th_hit[i][j]=th_hit_in[i][j];
			phzvl[i][j]=phzvl_in[i][j];
			vl[i][j]=vl_in[i][j];
			for(int k=0;k<seg_ch;k++){
#pragma HLS UNROLL
				ph[i][j][k]=ph_in[i][j][k];
				th[i][j][k]=th_in[i][j][k];
				cpatr[i][j][k]=cpatr_in[i][j][k];
			}
		}
	}

	for(int i=0;i<2;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
#pragma HLS UNROLL
			me11a[i][j]=me11a_in[i][j];
			for(int k=0;k<th_ch11;k++){
#pragma HLS UNROLL
				th11[i][j][k]=th11_in[i][j][k];

			}
		}
	}*/


}



