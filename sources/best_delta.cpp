#include <ap_int.h>
#include "spbits.h"
#include "deltas.h"
#define bw_num  2


void delta::best_delta_seg_ch(
					ap_uint<bw_th> dth [seg_ch*seg_ch], //change this when nseg value is changed
					ap_uint<seg_ch*seg_ch>  sth,//change this when nseg value is changed
					ap_uint<seg_ch*seg_ch>  dvl,//change this when nseg value is changed
					ap_uint<bw_th> *bth, // smallest delta
					ap_uint<1>   *bsg, // sign of bth
					ap_uint<1>  *bvl, // valid flag
					ap_uint<2> *bnm // winner number//change this when bnum value is changed

			)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=dth complete dim=1


	const int nseg = seg_ch * seg_ch;

		ap_uint<1>		   one_val;

		int i;
		ap_uint<bw_th> cmp1 [nseg/2];
#pragma HLS ARRAY_PARTITION variable=cmp1 complete dim=1

		ap_uint<bw_th>  cmp2 [nseg/4];
#pragma HLS ARRAY_PARTITION variable=cmp2 complete dim=1

		ap_uint<nseg/2> sig1;
		ap_uint<nseg/4> sig2;

		ap_uint<bw_num> num1 [nseg/2];
#pragma HLS ARRAY_PARTITION variable=num1 complete dim=1

		ap_uint<bw_num> num2 [nseg/4];
#pragma HLS ARRAY_PARTITION variable=num2 complete dim=1



		ap_uint<bw_th> a_bth; // smallest delta
		ap_uint<1>   a_bsg; // sign of bth
		ap_uint<1>  a_bvl; // valid flag
		ap_uint<bw_num> a_bnm; // winner number

		ap_uint<seg_ch * seg_ch>  a_dvl;
				a_dvl=dvl;



			// first comparator stage
		best_delta_label0:for (i = 0; i < nseg/2; i = i+1){
	#pragma HLS UNROLL
		if (((dth[i*2] < dth[i*2+1]) && (a_dvl((i*2)+2-1,i*2) == 0x3)) || (a_dvl((i*2)+2-1,i*2) == 0x1)){
				cmp1[i] = dth[i*2];
				sig1[i] = sth[i*2];
				num1[i] = i*2;
		}
		else
		{
				cmp1[i] = dth[i*2+1];
				sig1[i] = sth[i*2+1];
				num1[i] = i*2+1;
		}
			if (a_dvl((i*2)+2-1,i*2) == 0x0) cmp1[i] = nodiff; // if one of the inputs invalid, output = max
	}
		// second comparator stage
		best_delta_label1:for (i = 0; i < nseg/4; i = i+1){
		#pragma HLS UNROLL
			if (cmp1[i*2] < cmp1[i*2+1]){
				cmp2[i] = cmp1[i*2];
				sig2[i] = sig1[i*2];
				num2[i] = num1[i*2];
			}
			else{
				cmp2[i] = cmp1[i*2+1];
				sig2[i] = sig1[i*2+1];
				num2[i] = num1[i*2+1];
			}
		}

			// third comparator stage if needed
		if (nseg/4 > 1){
			if (cmp2[0] < cmp2[1]){
				a_bth = cmp2[0];
				a_bsg = sig2[0];
				a_bnm = num2[0];
			}
			else{
				a_bth = cmp2[1];
				a_bsg = sig2[1];
				a_bnm = num2[1];
			}
		}
		else{
			a_bth = cmp2[0];
			a_bsg = sig2[0];
			a_bnm = num2[0];
		}

					// output valid if one or more inputs are valid
		a_bvl =a_dvl.or_reduce();

*bth=a_bth;
*bsg=a_bsg;
*bnm=a_bnm;
*bvl=a_bvl;


}
