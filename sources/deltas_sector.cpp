#include <ap_int.h>
#include "spbits.h"
#include "deltas.h"
#include "sp.h"

void sp_c::deltas_sector(
		//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch> vi [4][3][4], // valid
		ap_uint<2> 	   hi [4][3][4], // bx index
		ap_uint<3>   ci [4][3][4], // chamber
		ap_uint<4>   si [4][3], // segment
		ap_uint<bw_fph> ph_match [4][3][4], // matching ph
		ap_uint<bw_th>  th_match   [4][3][4][seg_ch], // matching th, 2 segments
		ap_uint<bw_th>  th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
		ap_uint<4> 	   cpat_match [4][3][4], // matching pattern
		// best ranks [zone][num]
		ap_uint<bwr>   ph_q [4][3],

		ap_uint<bw_th>   th_window, // max th diff

		// precise phi and theta of candidates
		// [zone][pattern_num]
		ap_uint<bw_fph>  phi [4][3],
		ap_uint<bw_th>   theta [4][3],
		// [zone][pattern_num][station]
		ap_uint<4> cpattern [4][3][4],
		// ph and th deltas from best stations
		// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  delta_ph [4][3][6],
		ap_uint<bw_th>  	delta_th [4][3][6],
		ap_uint<6> 	sign_ph[4][3],
		ap_uint<6> 	sign_th[4][3],
		// updated ranks [zone][pattern_num]
		ap_uint<bwr+1> 	rank [4][3],
		//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch> vir [4][3][4], // valid
		ap_uint<2>  	hir [4][3][4], // bx index
		ap_uint<3>  	cir [4][3][4], // chamber
		ap_uint<4>  	sir [4][3] // segment


					)
{
#pragma HLS INTERFACE ap_ctrl_none port=return


#pragma HLS ARRAY_PARTITION variable=vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=si complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_match11 complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpat_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_q complete dim=0
#pragma HLS ARRAY_PARTITION variable=phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=theta complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpattern complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=rank complete dim=0
#pragma HLS ARRAY_PARTITION variable=vir complete dim=0
#pragma HLS ARRAY_PARTITION variable=hir complete dim=0
#pragma HLS ARRAY_PARTITION variable=cir complete dim=0
#pragma HLS ARRAY_PARTITION variable=sir complete dim=0






delta inst[4][3];
#pragma HLS ARRAY_PARTITION variable=inst complete dim=0

	ap_uint<bw_th> dummy [2][3][th_ch11];
#pragma HLS ARRAY_PARTITION variable=dummy complete dim=0
	int i,j;




	delta_sector_actual_label0:for (i = 0; i < 2; i = i+1){
#pragma HLS UNROLL
 // zone loop
			for (j = 0; j < 3; j = j+1){ // pattern loop

#pragma HLS UNROLL
					inst[i][j].deltas_m1
					(
					 (vi[i][j]),
					 (hi[i][j]),
					 (ci[i][j]),
					 (si[i][j]),
					 (ph_match[i][j]),
					 (th_match[i][j]),
					 (th_match11[i][j]),
					 (cpat_match[i][j]),
					 (ph_q[i][j]),
					 (th_window),

					 (&phi[i][j]),
					 (&theta[i][j]),
					 (cpattern[i][j]),
					 (delta_ph[i][j]),
					 (delta_th[i][j]),
					 (&sign_ph[i][j]),
					 (&sign_th[i][j]),
					 (&rank[i][j]),
					 (vir[i][j]),
					 (hir[i][j]),
					 (cir[i][j]),
					 (&sir[i][j])

					 );
			}
	}


			for (i = 2; i < 4; i = i+1){
#pragma HLS UNROLL
 // zone loop
				for (j = 0; j < 3; j = j+1){ // pattern loop
#pragma HLS UNROLL
					inst[i][j].deltas_m0
					(
					 (vi[i][j]),
					 (hi[i][j]),
					 (ci[i][j]),
					 (si[i][j]),
					 (ph_match[i][j]),
					 (th_match[i][j]),
					 (dummy[i-2][j]),
					 (cpat_match[i][j]),
					 (ph_q[i][j]),
					 (th_window),

					 (&phi[i][j]),
					 (&theta[i][j]),
					 (cpattern[i][j]),
					 (delta_ph[i][j]),
					 (delta_th[i][j]),
					 (&sign_ph[i][j]),
					 (&sign_th[i][j]),
					 (&rank[i][j]),
					 (vir[i][j]),
					 (hir[i][j]),
					 (cir[i][j]),
					 (&sir[i][j])
					 );
				}
			}//block: zl




}
