#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/primitive.h"
using namespace std;

void primitive::top_prim_conv(
			ap_uint<seg_ch> vpf,
			ap_uint<4> quality[seg_ch],
			ap_uint<bw_wg> wiregroup[seg_ch],
			ap_uint<bw_hs> hstrip[seg_ch],
			ap_uint<4> clctpat[seg_ch],
			ap_uint<8> station,
			ap_uint<8> cscid,
			ap_uint<13> r_in,
			ap_uint<1> we,
			ap_uint<bw_fph> ph[seg_ch],
			ap_uint<bw_th> th[seg_ch],
			ap_uint<seg_ch> *vl,
			ap_uint<3> *phzvl,
			ap_uint<seg_ch> *me11a,
			ap_uint<4> clctpat_r[seg_ch],
			ap_uint<ph_hit_w> *ph_hit,
			ap_uint<2>  sel,
			ap_uint<bw_addr>  addr,
			ap_uint<1> endcap,
			ap_uint<1> lat_test,
			ap_uint<12> *r_out)

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1


	ap_uint<3> a_phzvl=0;
	ap_uint<ph_hit_w> a_ph_hit;
	ap_uint<th_hit_w> a_th_hit;
if(we==1)
{
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

		this->prim_conv(
					vpf, quality, wiregroup, hstrip, clctpat,
			 		station,cscid,
			 		ph,	th,	vl,	&a_phzvl, me11a, clctpat_r,
					&a_ph_hit, sel, addr,endcap,
			 		lat_test,r_out
			 		);

}

*phzvl=a_phzvl;
*ph_hit=a_ph_hit;
}



