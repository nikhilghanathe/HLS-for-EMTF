#include <ap_int.h>
#include "spbits.h"
#include "match_seg.h"
#include "sp.h"



void sp_c::match_ph_seg(
		   // numbers of best ranks [zone][rank number]
		    ap_uint<bpow+1> ph_num [4][3],
		    // best ranks [zone][rank number]
		    ap_uint<6> 	ph_q [4][3],

		    // ph outputs delayed and extended [bx_history][station][chamber][segment]
		    // most recent in bx = 0
		    ap_uint<bw_fph>	ph  [max_drift][5][9][seg_ch],
			// valid flags
		    ap_uint<seg_ch> vl  [max_drift][5][9],
			// thetas
		    ap_uint<bw_th> 	th11 [max_drift][2][3][th_ch11],
			ap_uint<bw_th> 	th   [max_drift][5][9][seg_ch],
			ap_uint<4> 		cpat [max_drift][5][9][seg_ch],

			// find_segment outputs, in terms of segments match in zones [zone][pattern_num][station 0-3]
			ap_uint<seg_ch> vi [4][3][4], // valid (for each segment in chamber, so we can identify which th to use later)
			ap_uint<2> 		hi [4][3][4], // bx index
			ap_uint<3> 		ci [4][3][4], // chamber
			ap_uint<4> 		si [4][3], // segment which has matching ph
			ap_uint<bw_fph> ph_match [4][3][4], // matching phi
			// suspected matching th coordinates, all taken from chambers where ph comes from
			// [zone][pattern_num][station 0-3][segment]
			ap_uint<bw_th>	th_match   [4][3][4][zone_seg], // matching th, 2 segments
			ap_uint<bw_th>	th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
			ap_uint<4> 		cpat_match [4][3][4], // matching patterns
		    // best ranks [zone][rank number]
			ap_uint<6> 	ph_qr [4][3])
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=cpat complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_num complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_q complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=vl complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11 complete dim=0
#pragma HLS ARRAY_PARTITION variable=th complete dim=0
#pragma HLS ARRAY_PARTITION variable=vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=si complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_match11 complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpat_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_qr complete dim=0

	ap_uint<4> 		si_tmp [4][3];
#pragma HLS ARRAY_RESHAPE variable=si_tmp complete dim=0
	//array of objects to achieve concurrency
	static match_seg  fs_00[3],fs_01[3],fs_02[3] ,fs_03[3] ,fs_10[3] ,fs_11[3] ,fs_12[3] ,fs_13[3] ,fs_20[3] ,fs_21[3],
				fs_22[3] ,	fs_23[3] , fs_30[3] ,fs_31[3] ,fs_32[3] ,fs_33[3] ;


	ap_uint<1> 		a_si;// [4][3][3];

	// segments rerouted for find_segment inputs
	// see find_segment_reroute.xlsx for details
	// indexes are: [bx_history][chamber][segment]
	ap_uint<bw_fph>  ph_seg___z0_s0 [max_drift ][6][seg_ch ];

#pragma HLS ARRAY_PARTITION variable=ph_seg___z0_s0 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z0_s0 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z0_s0 complete dim=0

	ap_uint<bw_fph>  ph_seg___z0_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z0_s1 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z0_s1 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z0_s1 complete dim=0

	ap_uint<bw_fph>  ph_seg___z0_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z0_s2 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z0_s2 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z0_s2 complete dim=0

	ap_uint<bw_fph>  ph_seg___z0_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z0_s3 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z0_s3 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z0_s3 complete dim=0


	ap_uint<bw_fph>  ph_seg___z1_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z1_s0 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z1_s0 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z1_s0 complete dim=0

	ap_uint<bw_fph>  ph_seg___z1_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z1_s1 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z1_s1 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z1_s1 complete dim=0

	ap_uint<bw_fph>  ph_seg___z1_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z1_s2 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z1_s2 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z1_s2 complete dim=0

	ap_uint<bw_fph>  ph_seg___z1_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z1_s3 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z1_s3 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z1_s3 complete dim=0


	ap_uint<bw_fph>  ph_seg___z2_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z2_s0 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z2_s0 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z2_s0 complete dim=0

	ap_uint<bw_fph>  ph_seg___z2_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z2_s1 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z2_s1 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z2_s1 complete dim=0

	ap_uint<bw_fph>  ph_seg___z2_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z2_s2 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z2_s2 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z2_s2 complete dim=0

	ap_uint<bw_fph>  ph_seg___z2_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z2_s3 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z2_s3 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z2_s3 complete dim=0


	ap_uint<bw_fph>  ph_seg___z3_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z3_s0 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z3_s0 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z3_s0 complete dim=0

	ap_uint<bw_fph>  ph_seg___z3_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z3_s1 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z3_s1 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z3_s1 complete dim=0

	ap_uint<bw_fph>  ph_seg___z3_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z3_s2 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z3_s2 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z3_s2 complete dim=0

	ap_uint<bw_fph>  ph_seg___z3_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=ph_seg___z3_s3 complete dim=0

	ap_uint<seg_ch> ph_seg_v_z3_s3 [max_drift ][6];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_z3_s3 complete dim=0



	ap_uint<bw_th> th_seg___z0_s0 [max_drift ][6][th_ch11 ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z0_s0 complete dim=0

	ap_uint<bw_th> th_seg___z0_s1 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z0_s1 complete dim=0

	ap_uint<bw_th> th_seg___z0_s2 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z0_s2 complete dim=0

	ap_uint<bw_th> th_seg___z0_s3 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z0_s3 complete dim=0



	ap_uint<bw_th> th_seg___z1_s0 [max_drift ][6][th_ch11 ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z1_s0 complete dim=0

	ap_uint<bw_th> th_seg___z1_s1 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z1_s1 complete dim=0

	ap_uint<bw_th> th_seg___z1_s2 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z1_s2 complete dim=0

	ap_uint<bw_th> th_seg___z1_s3 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z1_s3 complete dim=0


	ap_uint<bw_th> th_seg___z2_s0 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z2_s0 complete dim=0

	ap_uint<bw_th> th_seg___z2_s1 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z2_s1 complete dim=0

	ap_uint<bw_th> th_seg___z2_s2 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z2_s2 complete dim=0

	ap_uint<bw_th> th_seg___z2_s3 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z2_s3 complete dim=0


	ap_uint<bw_th> th_seg___z3_s0 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z3_s0 complete dim=0

	ap_uint<bw_th> th_seg___z3_s1 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z3_s1 complete dim=0

	ap_uint<bw_th> th_seg___z3_s2 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z3_s2 complete dim=0

	ap_uint<bw_th> th_seg___z3_s3 [max_drift ][6][zone_seg ];
#pragma HLS ARRAY_PARTITION variable=th_seg___z3_s3 complete dim=0


	ap_uint<4>  cpat_seg___z0_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z0_s0 complete dim=0

	ap_uint<4>  cpat_seg___z0_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z0_s1 complete dim=0

	ap_uint<4>  cpat_seg___z0_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z0_s2 complete dim=0

	ap_uint<4>  cpat_seg___z0_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z0_s3 complete dim=0


	ap_uint<4>  cpat_seg___z1_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z1_s0 complete dim=0

	ap_uint<4>  cpat_seg___z1_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z1_s1 complete dim=0

	ap_uint<4>  cpat_seg___z1_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z1_s2 complete dim=0

	ap_uint<4>  cpat_seg___z1_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z1_s3 complete dim=0



	ap_uint<4>  cpat_seg___z2_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z2_s0 complete dim=0

	ap_uint<4>  cpat_seg___z2_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z2_s1 complete dim=0

	ap_uint<4>  cpat_seg___z2_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z2_s2 complete dim=0

	ap_uint<4>  cpat_seg___z2_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z2_s3 complete dim=0



	ap_uint<4>  cpat_seg___z3_s0 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z3_s0 complete dim=0

	ap_uint<4>  cpat_seg___z3_s1 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z3_s1 complete dim=0

	ap_uint<4>  cpat_seg___z3_s2 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z3_s2 complete dim=0

	ap_uint<4>  cpat_seg___z3_s3 [max_drift ][6][seg_ch ];
#pragma HLS ARRAY_PARTITION variable=cpat_seg___z3_s3 complete dim=0




	int i,j,k;
	// segments rerouted for find_segment inputs
			// see find_segment_reroute.xlsx for details
			// indexes are: [bx_history][chamber][segment]
			// excel file line shown at the end of each code line
			match_ph_seg_label0:for (i = 0; i < max_drift; i = i+1){ // bx_history loop
				match_ph_seg_label1:for (j = 0; j < 6; j = j+1){ // chamber loop for 6-chamber finders
#pragma HLS UNROLL

					match_ph_seg_label2:for (k = 0; k < th_ch11; k = k+1){ // segment loop for ME11 only
#pragma HLS UNROLL

						th_seg___z0_s0[i][j][k] = (j < 3) ?	 th11[i][0][j][k] : th11[i][1][j-3][k]; // 2
						th_seg___z1_s0[i][j][k] = (j < 3) ?	 th11[i][0][j][k] : th11[i][1][j-3][k]; // 7
					}

					match_ph_seg_label3:for (k = 0; k < seg_ch; k = k+1){ // segment loop all other chambers
#pragma HLS UNROLL

						ph_seg___z0_s0[i][j][k] = (j < 3) ?	 ph[i][0][j][k] : ph[i][1][j-3][k]; // 2
						ph_seg_v_z0_s0[i][j][k] = (j < 3) ?	 vl[i][0][j][k] : vl[i][1][j-3][k];
						ph_seg___z1_s0[i][j][k] = (j < 3) ?	 ph[i][0][j][k] : ph[i][1][j-3][k]; // 7
						ph_seg_v_z1_s0[i][j][k] = (j < 3) ?	 (vl[i][0][j][k]) : (vl[i][1][j-3][k]);
						ph_seg___z1_s2[i][j][k] = ph[i][3][j+3][k]; // 9
						ph_seg_v_z1_s2[i][j][k] = vl[i][3][j+3][k];
						ph_seg___z1_s3[i][j][k] = ph[i][4][j+3][k]; // 10
						ph_seg_v_z1_s3[i][j][k] = vl[i][4][j+3][k];

						ph_seg___z2_s0[i][j][k] = (j < 3) ?	 ph[i][0][j+3][k] : ph[i][1][j][k]; // 12
						ph_seg_v_z2_s0[i][j][k] = (j < 3) ?	 vl[i][0][j+3][k] : vl[i][1][j][k];
						ph_seg___z2_s1[i][j][k] = ph[i][2][j+3][k]; // 13
						ph_seg_v_z2_s1[i][j][k] = vl[i][2][j+3][k];
						ph_seg___z2_s2[i][j][k] = ph[i][3][j+3][k]; // 14
						ph_seg_v_z2_s2[i][j][k] = vl[i][3][j+3][k];
						ph_seg___z2_s3[i][j][k] = ph[i][4][j+3][k]; // 15
						ph_seg_v_z2_s3[i][j][k] = vl[i][4][j+3][k];

						ph_seg___z3_s0[i][j][k] = (j < 3) ?	 ph[i][0][j+6][k] : ph[i][1][j+3][k]; // 18
						ph_seg_v_z3_s0[i][j][k] = (j < 3) ?	 vl[i][0][j+6][k] : vl[i][1][j+3][k];
						ph_seg___z3_s1[i][j][k] = ph[i][2][j+3][k]; // 19
						ph_seg_v_z3_s1[i][j][k] = vl[i][2][j+3][k];
						ph_seg___z3_s2[i][j][k] = ph[i][3][j+3][k]; // 20
						ph_seg_v_z3_s2[i][j][k] = vl[i][3][j+3][k];
					    ph_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3
					    ph_seg_v_z3_s3[i][j][k] = 0; // no station 4 in zone 3

						cpat_seg___z0_s0[i][j][k] = (j < 3) ?	 cpat[i][0][j][k] : cpat[i][1][j-3][k]; // 2

						cpat_seg___z1_s0[i][j][k] = (j < 3) ?	 cpat[i][0][j][k] : cpat[i][1][j-3][k]; // 7
						cpat_seg___z1_s2[i][j][k] = cpat[i][3][j+3][k]; // 9
						cpat_seg___z1_s3[i][j][k] = cpat[i][4][j+3][k]; // 10

						cpat_seg___z2_s0[i][j][k] = (j < 3) ?	 cpat[i][0][j+3][k] : cpat[i][1][j][k]; // 12
						cpat_seg___z2_s1[i][j][k] = cpat[i][2][j+3][k]; // 13
						cpat_seg___z2_s2[i][j][k] = cpat[i][3][j+3][k]; // 14
						cpat_seg___z2_s3[i][j][k] = cpat[i][4][j+3][k]; // 15

						cpat_seg___z3_s0[i][j][k] = (j < 3) ?	 cpat[i][0][j+6][k] : cpat[i][1][j+3][k]; // 18
						cpat_seg___z3_s1[i][j][k] = cpat[i][2][j+3][k]; // 19
						cpat_seg___z3_s2[i][j][k] = cpat[i][3][j+3][k]; // 20
					    cpat_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3

						th_seg___z1_s2[i][j][k] = th[i][3][j+3][k]; // 9
						th_seg___z1_s3[i][j][k] = th[i][4][j+3][k]; // 10

						th_seg___z2_s0[i][j][k] = (j < 3) ?	 th[i][0][j+3][k] : th[i][1][j][k]; // 12
						th_seg___z2_s1[i][j][k] = th[i][2][j+3][k]; // 13
						th_seg___z2_s2[i][j][k] = th[i][3][j+3][k]; // 14
						th_seg___z2_s3[i][j][k] = th[i][4][j+3][k]; // 15

						th_seg___z3_s0[i][j][k] = (j < 3) ?	 th[i][0][j+6][k] : th[i][1][j+3][k]; // 18
						th_seg___z3_s1[i][j][k] = th[i][2][j+3][k]; // 19
						th_seg___z3_s2[i][j][k] = th[i][3][j+3][k]; // 20
					    th_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3


					}
				}
				match_ph_seg_label4:for (j = 0; j < 3; j = j+1){ // chamber loop for 3-chamber finders
#pragma HLS UNROLL

					match_ph_seg_label5:for (k = 0; k < seg_ch; k = k+1){ // segment loop

#pragma HLS UNROLL
			ph_seg___z0_s1[i][j][k] = ph[i][2][j][k]; // 3
						ph_seg_v_z0_s1[i][j][k] = vl[i][2][j][k];
						ph_seg___z0_s2[i][j][k] = ph[i][3][j][k]; // 4
						ph_seg_v_z0_s2[i][j][k] = vl[i][3][j][k];
						ph_seg___z0_s3[i][j][k] = ph[i][4][j][k]; // 5
						ph_seg_v_z0_s3[i][j][k] = vl[i][4][j][k];

						ph_seg___z1_s1[i][j][k] = ph[i][2][j][k]; // 8
						ph_seg_v_z1_s1[i][j][k] = vl[i][2][j][k];

						cpat_seg___z0_s1[i][j][k] = cpat[i][2][j][k]; // 3
						cpat_seg___z0_s2[i][j][k] = cpat[i][3][j][k]; // 4
						cpat_seg___z0_s3[i][j][k] = cpat[i][4][j][k]; // 5

						cpat_seg___z1_s1[i][j][k] = cpat[i][2][j][k]; // 8


						th_seg___z0_s1[i][j][k] = th[i][2][j][k]; // 3
						th_seg___z0_s2[i][j][k] = th[i][3][j][k]; // 4
						th_seg___z0_s3[i][j][k] = th[i][4][j][k]; // 5

						th_seg___z1_s1[i][j][k] = th[i][2][j][k]; // 8
					}
				}
			} // for (i = 0; i < max_drift; i = i+1)



			// just propagate ranks to outputs
			match_ph_seg_label011:for(int i=0;i<4;i++){
#pragma HLS UNROLL
				match_ph_seg_label122:for(int j=0;j<3;j++){
#pragma HLS UNROLL
					ph_qr[i][j] =ph_q[i][j];
				}
			}



match_ph_seg_label110:for(int ki=0;ki<3;ki++)
{
#pragma HLS UNROLL


	fs_00[ki].find_segment_st1(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s0, ph_seg_v_z0_s0,
					th_seg___z0_s0, cpat_seg___z0_s0,
					&vi[0][ki][0], &hi[0][ki][0],
					&ci[0][ki][0], &a_si, &ph_match[0][ki][0],
					th_match11[0][ki] , &cpat_match[0][ki][0]);
	si_tmp[0][ki][0]=a_si;


	fs_01[ki].find_segment_stn1(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s1, ph_seg_v_z0_s1,
					th_seg___z0_s1, cpat_seg___z0_s1,
					&vi[0][ki][1], &hi[0][ki][1],
					&ci[0][ki][1], &a_si, &ph_match[0][ki][1],
					th_match[0][ki][1] , &cpat_match[0][ki][1]);

	si_tmp[0][ki][1]=a_si;
	fs_02[ki].find_segment_stn1(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s2, ph_seg_v_z0_s2,
					th_seg___z0_s2, cpat_seg___z0_s2,
					&vi[0][ki][2], &hi[0][ki][2],
					&ci[0][ki][2], &a_si, &ph_match[0][ki][2],
					th_match[0][ki][2] , &cpat_match[0][ki][2]);
	si_tmp[0][ki][2]=a_si;
	fs_03[ki].find_segment_stn1(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s3, ph_seg_v_z0_s3,
					th_seg___z0_s3, cpat_seg___z0_s3,
					&vi[0][ki][3], &hi[0][ki][3],
					&ci[0][ki][3], &a_si, &ph_match[0][ki][3],
					th_match[0][ki][3] , &cpat_match[0][ki][3]);
	si_tmp[0][ki][3]=a_si;




	fs_10[ki].find_segment_st1(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s0, ph_seg_v_z1_s0,
					th_seg___z1_s0, cpat_seg___z1_s0,
					&vi[1][ki][0], &hi[1][ki][0],
					&ci[1][ki][0], &a_si, &ph_match[1][ki][0],
					th_match11[1][ki] , &cpat_match[1][ki][0]);
	si_tmp[1][ki][0]=a_si;
	fs_11[ki].find_segment_stn1(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s1, ph_seg_v_z1_s1,
					th_seg___z1_s1, cpat_seg___z1_s1,
					&vi[1][ki][1], &hi[1][ki][1],
					&ci[1][ki][1], &a_si, &ph_match[1][ki][1],
					th_match[1][ki][1] , &cpat_match[1][ki][1]);
	si_tmp[1][ki][1]=a_si;
	fs_12[ki].find_segment_n1_62(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s2, ph_seg_v_z1_s2,
					th_seg___z1_s2, cpat_seg___z1_s2,
					&vi[1][ki][2], &hi[1][ki][2],
					&ci[1][ki][2], &a_si, &ph_match[1][ki][2],
					th_match[1][ki][2] , &cpat_match[1][ki][2]);
	si_tmp[1][ki][2]=a_si;
	fs_13[ki].find_segment_n1_62(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s3, ph_seg_v_z1_s3,
					th_seg___z1_s3, cpat_seg___z1_s3,
					&vi[1][ki][3], &hi[1][ki][3],
					&ci[1][ki][3], &a_si, &ph_match[1][ki][3],
					th_match[1][ki][3] , &cpat_match[1][ki][3]);

	si_tmp[1][ki][3]=a_si;




	fs_20[ki].find_segment_1_62(ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s0, ph_seg_v_z2_s0,
					th_seg___z2_s0, cpat_seg___z2_s0,
					&vi[2][ki][0], &hi[2][ki][0],
					&ci[2][ki][0], &a_si, &ph_match[2][ki][0],
					th_match[2][ki][0] , &cpat_match[2][ki][0]);
	si_tmp[2][ki][0]=a_si;

	fs_21[ki].find_segment_n1_62(ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s1, ph_seg_v_z2_s1,
					th_seg___z2_s1, cpat_seg___z2_s1,
					&vi[2][ki][1], &hi[2][ki][1],
					&ci[2][ki][1], &a_si, &ph_match[2][ki][1],
					th_match[2][ki][1] , &cpat_match[2][ki][1]);
	si_tmp[2][ki][1]=a_si;

	fs_22[ki].find_segment_n1_62(ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s2, ph_seg_v_z2_s2,
					th_seg___z2_s2, cpat_seg___z2_s2,
					&vi[2][ki][2], &hi[2][ki][2],
					&ci[2][ki][2], &a_si, &ph_match[2][ki][2],
					th_match[2][ki][2] , &cpat_match[2][ki][2]);
	si_tmp[2][ki][2]=a_si;
	fs_23[ki].find_segment_n1_62(ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s3, ph_seg_v_z2_s3,
					th_seg___z2_s3, cpat_seg___z2_s3,
					&vi[2][ki][3], &hi[2][ki][3],
					&ci[2][ki][3], &a_si, &ph_match[2][ki][3],
					th_match[2][ki][3] , &cpat_match[2][ki][3]);
	si_tmp[2][ki][3]=a_si;



	fs_30[ki].find_segment_1_62(ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s0, ph_seg_v_z3_s0,
					th_seg___z3_s0, cpat_seg___z3_s0,
					&vi[3][ki][0], &hi[3][ki][0],
					&ci[3][ki][0], &a_si, &ph_match[3][ki][0],
					th_match[3][ki][0] , &cpat_match[3][ki][0]);
	si_tmp[3][ki][0]= a_si;
	fs_31[ki].find_segment_n1_62(ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s1, ph_seg_v_z3_s1,
					th_seg___z3_s1, cpat_seg___z3_s1,
					&vi[3][ki][1], &hi[3][ki][1],
					&ci[3][ki][1], &a_si, &ph_match[3][ki][1],
					th_match[3][ki][1] , &cpat_match[3][ki][1]);
	si_tmp[3][ki][1]= a_si;
	fs_32[ki].find_segment_n1_62(ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s2, ph_seg_v_z3_s2,
					th_seg___z3_s2, cpat_seg___z3_s2,
					&vi[3][ki][2], &hi[3][ki][2],
					&ci[3][ki][2], &a_si, &ph_match[3][ki][2],
					th_match[3][ki][2] , &cpat_match[3][ki][2]);
	si_tmp[3][ki][2]= a_si;
	fs_33[ki].find_segment_n1_62(ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s3, ph_seg_v_z3_s3,
					th_seg___z3_s3, cpat_seg___z3_s3,
					&vi[3][ki][3], &hi[3][ki][3],
					&ci[3][ki][3], &a_si, &ph_match[3][ki][3],
					th_match[3][ki][3] , &cpat_match[3][ki][3]);
	si_tmp[3][ki][3]= a_si;


}

for(int i=0;i<4;i++){
	for(int j=0;j<3;j++)
		si[i][j]=si_tmp[i][j];
}


}
