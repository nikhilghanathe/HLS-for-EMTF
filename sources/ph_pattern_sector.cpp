#include <ap_int.h>
#include <ap_utils.h>
#include "spbits.h"
#include "ph_pattern.h"
#include "sp.h"

#define pad (ph_raw_w + (padding_w_st1*2))




void sp_c::ph_pattern_sector(/*ap_uint<1> en,*/
		ap_uint<ph_raw_w> st[4][5],
        ap_uint<3> drifttime,
        ap_uint<3> foldn,// number of current fold
        ap_uint<6> qcode[4][ph_raw_w])// quality codes output [zone][key_strip]
									  // quality code pattern numbers [zone][key_strip]
{
	ap_wait();
#pragma HLS PROTOCOL fixed
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=st complete dim=0
#pragma HLS ARRAY_PARTITION variable=qcode complete dim=0

		// copy of stations with padding of zeroes on sides, so it's easier to pass to detectors
		// station numbering is different here:
		// 0 == st1
		// 1 == st3
		// 2 == st4
		// st 2 does not need padding
		ap_uint<pad> stp [4][3];
#pragma HLS ARRAY_PARTITION variable=stp complete dim=0
		int i, z;
		// quality codes from pattern detectors [zone][key_strip]
	    ap_uint<6> qcode_p [4][ph_raw_w];
#pragma HLS ARRAY_PARTITION variable=qcode_p complete dim=0
		// quality code pattern numbers [zone][key_strip]

		int zi, ri;
		// left, right and center qualities
	    ap_uint<6> ql, qr, qc;

	    //static array of objects guarantee persistence
	    static ph_pattern inst[4][ph_raw_w];
	    //Array partition of static objects enable parallel operation
#pragma HLS ARRAY_PARTITION variable=inst complete dim=0






		PAD:for (int z = 0; z < 4; z = z+1){
#pragma HLS UNROLL
			// fill padding with zeroes
			stp [z][0](padding_w_st1-1,0) = 0;
			stp [z][0](ph_raw_w + padding_w_st1*2-1 ,ph_raw_w + padding_w_st1) = 0;

			stp [z][1](padding_w_st3-1,0) = 0;
			stp [z][1](ph_raw_w + padding_w_st3*2-1 , ph_raw_w + padding_w_st3) = 0;

			stp [z][2](padding_w_st3-1, 0) = 0;
			stp [z][2](ph_raw_w + padding_w_st3*2-1 , ph_raw_w + padding_w_st3) = 0;
		}





		ASSIGN:for (z = 0; z < 4; z = z+1){
#pragma HLS UNROLL
					// put station inputs into padded copy
					stp [z][0](ph_raw_w + padding_w_st1-1 , padding_w_st1) = st[z][1];
					stp [z][1](ph_raw_w + padding_w_st3-1 , padding_w_st3) = st[z][3];
					stp [z][2](ph_raw_w + padding_w_st3-1 , padding_w_st3) = st[z][4];
		}




		INSTANTIATE:for (z = 0; z < 4; z = z+1){
#pragma HLS UNROLL
			ph_pattern_sector_label0:for (i = 0; i < ph_raw_w; i = i+1){
#pragma HLS UNROLL
				inst[z][i].ph_pattern_exec(
				 stp [z][0](i+full_pat_w_st1-1 , i),
				 st  [z][2][i],
				 stp [z][1](i+full_pat_w_st3-1 , i),
				 stp [z][2](i+full_pat_w_st3-1 , i),
				 drifttime,
				 foldn,
				 &qcode_p[z][i]

				);
			}
		}




			/*	*****GHOST CANCELLATION****/
		GHOST:for (z = 0; z < 4; z = z+1){
#pragma HLS UNROLL
			ph_pattern_sector_label1:for (i = 0; i < ph_raw_w; i = i+1){
#pragma HLS UNROLL
				qc = qcode_p[z][i]; // center quality is the current one
				if (i == 0) // right end - special case
				{
					ql = qcode_p[z][i+1];
					qr = 0; // nothing to the right
				}
				else if (i == ph_raw_w-1)
				{ // left end - special case
					ql = 0; // nothing to the left
					qr = qcode_p[z][i-1];
				}
				else // all other patterns
				{
					ql = qcode_p[z][i+1];
					qr = qcode_p[z][i-1];
				}
					// cancellation conditions
				if (qc <=  ql || qc <  qr) // this pattern is lower quality than neighbors
				{
					qc = 0; // cancel
				}
					// put the results into outputs
				qcode[z][i] = qc;




			} // block: ph_pat_hit
		}






}
