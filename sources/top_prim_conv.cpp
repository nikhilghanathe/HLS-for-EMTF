#include "spbits.h"
#include <ap_int.h>
#include "primitive.h"
#include <fstream>
#include <iostream>

//wrapper func for prim_conv
void primitive::top_prim_conv(
			ap_uint<4> quality[seg_ch],
					ap_uint<bw_wg> wiregroup[seg_ch],
					ap_uint<bw_hs> hstrip[seg_ch],
					ap_uint<4> clctpat[seg_ch],
					ap_uint<8> station,
					ap_uint<8> cscid,
					ap_uint<12> r_in,
					ap_uint<1> we,
					ap_uint<bw_fph> ph[seg_ch],
					ap_uint<bw_th> th[seg_ch],
					ap_uint<seg_ch> *vl,
					ap_uint<3> *phzvl,
					ap_uint<seg_ch> *me11a,
					ap_uint<4> clctpat_r[seg_ch],
					ap_uint<ph_hit_w> *ph_hit,
					ap_uint<th_hit_w> *th_hit,
					ap_uint<2>  sel,
					ap_uint<bw_addr>  addr,
					ap_uint<1> endcap,
					ap_uint<1> lat_test,
					ap_uint<1> print_flag,
					ap_uint<12> *r_out)

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=quality complete dim=0
#pragma HLS ARRAY_PARTITION variable=wiregroup complete dim=0
#pragma HLS ARRAY_PARTITION variable=hstrip complete dim=0
#pragma HLS ARRAY_PARTITION variable=clctpat complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=th complete dim=0
#pragma HLS ARRAY_PARTITION variable=clctpat_r complete dim=0

#pragma HLS ARRAY_PARTITION variable=params complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0



	ap_uint<3> a_phzvl;
		ap_uint<ph_hit_w> a_ph_hit;
		ap_uint<th_hit_w> a_th_hit;

if(we==1)
{
	//load LUTS
	this->mem( 	r_in,
			 we,
			 addr,
			 sel,
			 station,
			 cscid
			 );

}

else
{
	//primitive converter
		this->prim_conv1(
			 		quality,
			 		wiregroup,
			 		hstrip,
			 		clctpat,
			 		station,
			 		cscid,
			 		ph,
			 		th,
			 		vl,
			 		&a_phzvl,
			 		me11a,
			 		clctpat_r,
					&a_ph_hit,
					&a_th_hit,
			 		sel,
			 		addr,
			 		endcap,
			 		lat_test,
			 		r_out
			 		);

}



*phzvl=a_phzvl;
*ph_hit=a_ph_hit;
*th_hit=a_th_hit;
}



