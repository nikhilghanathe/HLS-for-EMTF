#include <ap_int.h>
#include "spbits.h"
#include "match_seg.h"
#include "sp.h"


void match_ph_seg(
		   // numbers of best ranks [zone][rank number]
		    ap_uint<bpow+1> ph_num [4][3],
		    // best ranks [zone][rank number]
		    ap_uint<6> 		ph_q [4][3],

		    // ph outputs delayed and extended [bx_history][station][chamber][segment]
		    // most recent in bx = 0
		    ap_uint<bw_fph>	ph  [max_drift][6][9][seg_ch],
			// valid flags
		    ap_uint<seg_ch> vl  [max_drift][6][9],
			// thetas
		    ap_uint<bw_th> 	th11 [max_drift][3][3][th_ch11],
			ap_uint<bw_th> 	th   [max_drift][6][9][seg_ch],
			ap_uint<4> 		cpat [max_drift][6][9][seg_ch],

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
			ap_uint<6> 		ph_qr [4][3])
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

	static match_seg  fs_00[3],fs_01[3],fs_02[3] ,fs_03[3] ,fs_10[3] ,fs_11[3] ,fs_12[3] ,fs_13[3] ,fs_20[3] ,fs_21[3],
				fs_22[3] ,	fs_23[3] , fs_30[3] ,fs_31[3] ,fs_32[3] ,fs_33[3] ;


	ap_uint<1> 		a_si;// [4][3][3];

	// segments rerouted for find_segment inputs
	// see find_segment_reroute.xlsx for details
	// indexes are: [bx_history][chamber][segment]
	ap_uint<bw_fph> ph_seg___z0_s0 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z0_s0 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z0_s1 [max_drift][4][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z0_s1 [max_drift][4];
	ap_uint<bw_fph> ph_seg___z0_s2 [max_drift][4][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z0_s2 [max_drift][4];
	ap_uint<bw_fph> ph_seg___z0_s3 [max_drift][4][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z0_s3 [max_drift][4];

	ap_uint<bw_fph> ph_seg___z1_s0 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z1_s0 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z1_s1 [max_drift][4][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z1_s1 [max_drift][4];
	ap_uint<bw_fph> ph_seg___z1_s2 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z1_s2 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z1_s3 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z1_s3 [max_drift][7];

	ap_uint<bw_fph> ph_seg___z2_s0 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z2_s0 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z2_s1 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z2_s1 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z2_s2 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z2_s2 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z2_s3 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z2_s3 [max_drift][7];

	ap_uint<bw_fph> ph_seg___z3_s0 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z3_s0 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z3_s1 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z3_s1 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z3_s2 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z3_s2 [max_drift][7];
	ap_uint<bw_fph> ph_seg___z3_s3 [max_drift][7][seg_ch];
	ap_uint<seg_ch> ph_seg_v_z3_s3 [max_drift][7];


	ap_uint<bw_th> th_seg___z0_s0 [max_drift][7][th_ch11];
	ap_uint<bw_th> th_seg___z0_s1 [max_drift][4][seg_ch];
	ap_uint<bw_th> th_seg___z0_s2 [max_drift][4][seg_ch];
	ap_uint<bw_th> th_seg___z0_s3 [max_drift][4][seg_ch];

	ap_uint<bw_th> th_seg___z1_s0 [max_drift][7][th_ch11];
	ap_uint<bw_th> th_seg___z1_s1 [max_drift][4][seg_ch];
	ap_uint<bw_th> th_seg___z1_s2 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z1_s3 [max_drift][7][seg_ch];

	ap_uint<bw_th> th_seg___z2_s0 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z2_s1 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z2_s2 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z2_s3 [max_drift][7][seg_ch];

	ap_uint<bw_th> th_seg___z3_s0 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z3_s1 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z3_s2 [max_drift][7][seg_ch];
	ap_uint<bw_th> th_seg___z3_s3 [max_drift][7][seg_ch];

	ap_uint<4> cpat_seg___z0_s0 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z0_s1 [max_drift][4][seg_ch];
	ap_uint<4> cpat_seg___z0_s2 [max_drift][4][seg_ch];
	ap_uint<4> cpat_seg___z0_s3 [max_drift][4][seg_ch];

	ap_uint<4> cpat_seg___z1_s0 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z1_s1 [max_drift][4][seg_ch];
	ap_uint<4> cpat_seg___z1_s2 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z1_s3 [max_drift][7][seg_ch];

	ap_uint<4> cpat_seg___z2_s0 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z2_s1 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z2_s2 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z2_s3 [max_drift][7][seg_ch];

	ap_uint<4> cpat_seg___z3_s0 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z3_s1 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z3_s2 [max_drift][7][seg_ch];
	ap_uint<4> cpat_seg___z3_s3 [max_drift][7][seg_ch];


	int i,j,k;
	// segments rerouted for find_segment inputs
		// see find_segment_reroute.xlsx for details
		// indexes are: [bx_history][chamber][segment]
		// excel file line shown at the end of each code line
	for (i = 0; i < max_drift; i = i+1) // bx_history loop
	{
		for (j = 0; j < 7; j = j+1) // chamber loop for 7-chamber finders
		{
			// j = 0 is neighbor sector chamber
			// j = 1,2,3 are subsector 1 chambers
			// j = 4,5,6 are subsector 2 chambers
			for (k = 0; k < th_ch11; k = k+1) // segment loop for ME11 only
			{
				th_seg___z0_s0[i][j][k] = (j == 0) ? th11[i][2][0][k] : (j < 4) ? th11[i][0][j-1][k] : th11[i][1][j-4][k]; // 2
				th_seg___z1_s0[i][j][k] = (j == 0) ? th11[i][2][0][k] : (j < 4) ? th11[i][0][j-1][k] : th11[i][1][j-4][k]; // 7
			}

			for (k = 0; k < seg_ch; k = k+1) // segment loop all other chambers
			{
				ph_seg___z0_s0[i][j][k] = (j == 0) ? ph[i][5][0][k] : (j < 4) ? ph[i][0][j-1][k] : ph[i][1][j-4][k]; // 2
				ph_seg_v_z0_s0[i][j][k] = (j == 0) ? vl[i][5][0][k] : (j < 4) ? vl[i][0][j-1][k] : vl[i][1][j-4][k];

				ph_seg___z1_s0[i][j][k] = (j == 0) ? ph[i][5][0][k] : (j < 4) ?	ph[i][0][j-1][k] : ph[i][1][j-4][k]; // 7
				ph_seg_v_z1_s0[i][j][k] = (j == 0) ? vl[i][5][0][k] : (j < 4) ?	vl[i][0][j-1][k] : vl[i][1][j-4][k];
				ph_seg___z1_s2[i][j][k] = (j == 0) ? ph[i][5][6][k] : ph[i][3][j+2][k]; // 9
				ph_seg_v_z1_s2[i][j][k] = (j == 0) ? vl[i][5][6][k] : vl[i][3][j+2][k];
				ph_seg___z1_s3[i][j][k] = (j == 0) ? ph[i][5][8][k] : ph[i][4][j+2][k]; // 10
				ph_seg_v_z1_s3[i][j][k] = (j == 0) ? vl[i][5][8][k] : vl[i][4][j+2][k];

				ph_seg___z2_s0[i][j][k] = (j == 0) ? ph[i][5][1][k] : (j < 4) ? ph[i][0][j+2][k] : ph[i][1][j-1][k]; // 12
				ph_seg_v_z2_s0[i][j][k] = (j == 0) ? vl[i][5][1][k] : (j < 4) ? vl[i][0][j+2][k] : vl[i][1][j-1][k];
				ph_seg___z2_s1[i][j][k] = (j == 0) ? ph[i][5][4][k] : ph[i][2][j+2][k]; // 13
				ph_seg_v_z2_s1[i][j][k] = (j == 0) ? vl[i][5][4][k] : vl[i][2][j+2][k];
				ph_seg___z2_s2[i][j][k] = (j == 0) ? ph[i][5][6][k] : ph[i][3][j+2][k]; // 14
				ph_seg_v_z2_s2[i][j][k] = (j == 0) ? vl[i][5][6][k] : vl[i][3][j+2][k];
				ph_seg___z2_s3[i][j][k] = (j == 0) ? ph[i][5][8][k] : ph[i][4][j+2][k]; // 15
				ph_seg_v_z2_s3[i][j][k] = (j == 0) ? vl[i][5][8][k] : vl[i][4][j+2][k];

				ph_seg___z3_s0[i][j][k] = (j == 0) ? ph[i][5][2][k] : (j < 4) ? ph[i][0][j+5][k] : ph[i][1][j+2][k]; // 18
				ph_seg_v_z3_s0[i][j][k] = (j == 0) ? vl[i][5][2][k] : (j < 4) ? vl[i][0][j+5][k] : vl[i][1][j+2][k];
				ph_seg___z3_s1[i][j][k] = (j == 0) ? ph[i][5][4][k] : ph[i][2][j+2][k]; // 19
				ph_seg_v_z3_s1[i][j][k] = (j == 0) ? vl[i][5][4][k] : vl[i][2][j+2][k];
				ph_seg___z3_s2[i][j][k] = (j == 0) ? ph[i][5][6][k] : ph[i][3][j+2][k]; // 20
				ph_seg_v_z3_s2[i][j][k] = (j == 0) ? vl[i][5][6][k] : vl[i][3][j+2][k];
				ph_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3
				ph_seg_v_z3_s3[i][j][k] = 0; // no station 4 in zone 3

				cpat_seg___z0_s0[i][j][k] = (j == 0) ? cpat[i][5][0][k] : (j < 4) ? cpat[i][0][j-1][k] : cpat[i][1][j-4][k]; // 2

				cpat_seg___z1_s0[i][j][k] = (j == 0) ? cpat[i][5][0][k] : (j < 4) ? cpat[i][0][j-1][k] : cpat[i][1][j-4][k]; // 7
				cpat_seg___z1_s2[i][j][k] = (j == 0) ? cpat[i][5][6][k] : cpat[i][3][j+2][k]; // 9
				cpat_seg___z1_s3[i][j][k] = (j == 0) ? cpat[i][5][8][k] : cpat[i][4][j+2][k]; // 10

				cpat_seg___z2_s0[i][j][k] = (j == 0) ? cpat[i][5][1][k] : (j < 4) ? cpat[i][0][j+2][k] : cpat[i][1][j-1][k]; // 12
				cpat_seg___z2_s1[i][j][k] = (j == 0) ? cpat[i][5][4][k] : cpat[i][2][j+2][k]; // 13
				cpat_seg___z2_s2[i][j][k] = (j == 0) ? cpat[i][5][6][k] : cpat[i][3][j+2][k]; // 14
				cpat_seg___z2_s3[i][j][k] = (j == 0) ? cpat[i][5][8][k] : cpat[i][4][j+2][k]; // 15

				cpat_seg___z3_s0[i][j][k] = (j == 0) ? cpat[i][5][2][k] : (j < 4) ? cpat[i][0][j+5][k] : cpat[i][1][j+2][k]; // 18
				cpat_seg___z3_s1[i][j][k] = (j == 0) ? cpat[i][5][4][k] : cpat[i][2][j+2][k]; // 19
				cpat_seg___z3_s2[i][j][k] = (j == 0) ? cpat[i][5][6][k] : cpat[i][3][j+2][k]; // 20
				cpat_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3

				th_seg___z1_s2[i][j][k] = (j == 0) ? th[i][5][6][k] : th[i][3][j+2][k]; // 9
				th_seg___z1_s3[i][j][k] = (j == 0) ? th[i][5][8][k] : th[i][4][j+2][k]; // 10

				th_seg___z2_s0[i][j][k] = (j == 0) ? th[i][5][1][k] : (j < 4) ?	 th[i][0][j+2][k] : th[i][1][j-1][k]; // 12
				th_seg___z2_s1[i][j][k] = (j == 0) ? th[i][5][4][k] : th[i][2][j+2][k]; // 13
				th_seg___z2_s2[i][j][k] = (j == 0) ? th[i][5][6][k] : th[i][3][j+2][k]; // 14
				th_seg___z2_s3[i][j][k] = (j == 0) ? th[i][5][8][k] : th[i][4][j+2][k]; // 15

				th_seg___z3_s0[i][j][k] = (j == 0) ? th[i][5][2][k] : (j < 4) ?	 th[i][0][j+5][k] : th[i][1][j+2][k]; // 18
				th_seg___z3_s1[i][j][k] = (j == 0) ? th[i][5][4][k] : th[i][2][j+2][k]; // 19
				th_seg___z3_s2[i][j][k] = (j == 0) ? th[i][5][6][k] : th[i][3][j+2][k]; // 20
				th_seg___z3_s3[i][j][k] = 0; // no station 4 in zone 3


			}
		}


	for (j = 0; j < 4; j = j+1) // chamber loop for 4-chamber finders
	{
		// j = 0 is neighbor sector chamber
		// j = 1,2,3 are native sector chambers
		for (k = 0; k < seg_ch; k = k+1) // segment loop
		{
			ph_seg___z0_s1[i][j][k] = (j == 0) ? ph[i][5][3][k] : ph[i][2][j-1][k]; // 3
			ph_seg_v_z0_s1[i][j][k] = (j == 0) ? vl[i][5][3][k] : vl[i][2][j-1][k];
			ph_seg___z0_s2[i][j][k] = (j == 0) ? ph[i][5][5][k] : ph[i][3][j-1][k]; // 4
			ph_seg_v_z0_s2[i][j][k] = (j == 0) ? vl[i][5][5][k] : vl[i][3][j-1][k];
			ph_seg___z0_s3[i][j][k] = (j == 0) ? ph[i][5][7][k] : ph[i][4][j-1][k]; // 5
			ph_seg_v_z0_s3[i][j][k] = (j == 0) ? vl[i][5][7][k] : vl[i][4][j-1][k];

			ph_seg___z1_s1[i][j][k] = (j == 0) ? ph[i][5][3][k] : ph[i][2][j-1][k]; // 8
			ph_seg_v_z1_s1[i][j][k] = (j == 0) ? vl[i][5][3][k] : vl[i][2][j-1][k];

			cpat_seg___z0_s1[i][j][k] = (j == 0) ? cpat[i][5][3][k] : cpat[i][2][j-1][k]; // 3
			cpat_seg___z0_s2[i][j][k] = (j == 0) ? cpat[i][5][5][k] : cpat[i][3][j-1][k]; // 4
			cpat_seg___z0_s3[i][j][k] = (j == 0) ? cpat[i][5][7][k] : cpat[i][4][j-1][k]; // 5

			cpat_seg___z1_s1[i][j][k] = (j == 0) ? cpat[i][5][3][k] : cpat[i][2][j-1][k]; // 8


			th_seg___z0_s1[i][j][k] = (j == 0) ? th[i][5][3][k] : th[i][2][j-1][k]; // 3
			th_seg___z0_s2[i][j][k] = (j == 0) ? th[i][5][5][k] : th[i][3][j-1][k]; // 4
			th_seg___z0_s3[i][j][k] = (j == 0) ? th[i][5][7][k] : th[i][4][j-1][k]; // 5

			th_seg___z1_s1[i][j][k] = (j == 0) ? th[i][5][3][k] : th[i][2][j-1][k]; // 8
			}
		}
	} // for (i = 0; i < max_drift; i = i+1)



	// just propagate ranks to outputs
	for(int i=0;i<4;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
#pragma HLS UNROLL
			ph_qr[i][j] =ph_q[i][j];
		}
	}


for(int ki=0;ki<3;ki++){
#pragma HLS UNROLL


	fs_00[2].pr=0;
	fs_00[ki].find_segment_st1_7_4(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s0, ph_seg_v_z0_s0,
					th_seg___z0_s0, cpat_seg___z0_s0,
					&vi[0][ki][0], &hi[0][ki][0],
					&ci[0][ki][0], &a_si, &ph_match[0][ki][0],
					th_match[0][ki][0] , &cpat_match[0][ki][0]);
	si[0][ki][0]=a_si;
/*
	std::cout<<std::endl;
	fs_00[0].pr=0;
	fs_01[2].pr=1;
	fs_01[ki].find_segment_stn1_4_2(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s1, ph_seg_v_z0_s1,
					th_seg___z0_s1, cpat_seg___z0_s1,
					&vi[0][ki][1], &hi[0][ki][1],
					&ci[0][ki][1], &a_si, &ph_match[0][ki][1],
					th_match[0][ki][1] , &cpat_match[0][ki][1]);
	si[0][ki][1]=a_si;

	fs_02[2].pr=0;
	fs_02[ki].find_segment_stn1_4_2(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s2, ph_seg_v_z0_s2,
					th_seg___z0_s2, cpat_seg___z0_s2,
					&vi[0][ki][2], &hi[0][ki][2],
					&ci[0][ki][2], &a_si, &ph_match[0][ki][2],
					th_match[0][ki][2] , &cpat_match[0][ki][2]);
	si[0][ki][2]=a_si;
	std::cout<<std::endl;
	fs_03[2].pr=0;
	fs_03[ki].find_segment_stn1_4_2(ph_num[0][ki],ph_q[0][ki],
					ph_seg___z0_s3, ph_seg_v_z0_s3,
					th_seg___z0_s3, cpat_seg___z0_s3,
					&vi[0][ki][3], &hi[0][ki][3],
					&ci[0][ki][3], &a_si, &ph_match[0][ki][3],
					th_match[0][ki][3] , &cpat_match[0][ki][3]);
	si[0][ki][3]=a_si;




	fs_10[ki].find_segment_st1_7_4(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s0, ph_seg_v_z1_s0,
					th_seg___z1_s0, cpat_seg___z1_s0,
					&vi[1][ki][0], &hi[1][ki][0],
					&ci[1][ki][0], &a_si, &ph_match[1][ki][0],
					th_match[1][ki][0] , &cpat_match[1][ki][0]);
	si[1][ki][0]=a_si;
	fs_11[ki].find_segment_stn1_4_2(ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s1, ph_seg_v_z1_s1,
					th_seg___z1_s1, cpat_seg___z1_s1,
					&vi[1][ki][1], &hi[1][ki][1],
					&ci[1][ki][1], &a_si, &ph_match[1][ki][1],
					th_match[1][ki][1] , &cpat_match[1][ki][1]);
	si[1][ki][1]=a_si;
	fs_12[ki].find_segment_stn1_7_2(ki,ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s2, ph_seg_v_z1_s2,
					th_seg___z1_s2, cpat_seg___z1_s2,
					&vi[1][ki][2], &hi[1][ki][2],
					&ci[1][ki][2], &a_si, &ph_match[1][ki][2],
					th_match[1][ki][2] , &cpat_match[1][ki][2]);
	si[1][ki][2]=a_si;
	fs_13[ki].find_segment_stn1_7_2(ki,ph_num[1][ki],ph_q[1][ki],
					ph_seg___z1_s3, ph_seg_v_z1_s3,
					th_seg___z1_s3, cpat_seg___z1_s3,
					&vi[1][ki][3], &hi[1][ki][3],
					&ci[1][ki][3], &a_si, &ph_match[1][ki][3],
					th_match[1][ki][3] , &cpat_match[1][ki][3]);

	si[1][ki][3]=a_si;



	if(ki==2)fs_20[2].pr=0;
	fs_20[ki].find_segment_st1_7_2(ki,ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s0, ph_seg_v_z2_s0,
					th_seg___z2_s0, cpat_seg___z2_s0,
					&vi[2][ki][0], &hi[2][ki][0],
					&ci[2][ki][0], &a_si, &ph_match[2][ki][0],
					th_match[2][ki][0] , &cpat_match[2][ki][0]);
	si[2][ki][0]=a_si;
	if(ki==2)fs_20[2].pr=0;
	if(ki==0)fs_21[0].pr=0;
//	std::cout<<"ph_q[2]["<<ki<<"]= "<<ph_q[2][ki]<<std::endl;
	fs_21[ki].find_segment_stn1_7_2(ki,ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s1, ph_seg_v_z2_s1,
					th_seg___z2_s1, cpat_seg___z2_s1,
					&vi[2][ki][1], &hi[2][ki][1],
					&ci[2][ki][1], &a_si, &ph_match[2][ki][1],
					th_match[2][ki][1] , &cpat_match[2][ki][1]);
	si[2][ki][1]=a_si;
	fs_21[1].pr=0;
	fs_22[ki].find_segment_stn1_7_2(ki,ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s2, ph_seg_v_z2_s2,
					th_seg___z2_s2, cpat_seg___z2_s2,
					&vi[2][ki][2], &hi[2][ki][2],
					&ci[2][ki][2], &a_si, &ph_match[2][ki][2],
					th_match[2][ki][2] , &cpat_match[2][ki][2]);
	si[2][ki][2]=a_si;
	fs_23[ki].find_segment_stn1_7_2(ki,ph_num[2][ki],ph_q[2][ki],
					ph_seg___z2_s3, ph_seg_v_z2_s3,
					th_seg___z2_s3, cpat_seg___z2_s3,
					&vi[2][ki][3], &hi[2][ki][3],
					&ci[2][ki][3], &a_si, &ph_match[2][ki][3],
					th_match[2][ki][3] , &cpat_match[2][ki][3]);
	si[2][ki][3]=a_si;



	fs_30[ki].find_segment_st1_7_2(ki,ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s0, ph_seg_v_z3_s0,
					th_seg___z3_s0, cpat_seg___z3_s0,
					&vi[3][ki][0], &hi[3][ki][0],
					&ci[3][ki][0], &a_si, &ph_match[3][ki][0],
					th_match[3][ki][0] , &cpat_match[3][ki][0]);
	si[3][ki][0]= a_si;
	fs_31[ki].find_segment_stn1_7_2(ki,ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s1, ph_seg_v_z3_s1,
					th_seg___z3_s1, cpat_seg___z3_s1,
					&vi[3][ki][1], &hi[3][ki][1],
					&ci[3][ki][1], &a_si, &ph_match[3][ki][1],
					th_match[3][ki][1] , &cpat_match[3][ki][1]);
	si[3][ki][1]= a_si;
	fs_32[ki].find_segment_stn1_7_2(ki,ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s2, ph_seg_v_z3_s2,
					th_seg___z3_s2, cpat_seg___z3_s2,
					&vi[3][ki][2], &hi[3][ki][2],
					&ci[3][ki][2], &a_si, &ph_match[3][ki][2],
					th_match[3][ki][2] , &cpat_match[3][ki][2]);
	si[3][ki][2]= a_si;
	fs_33[ki].find_segment_stn1_7_2(ki,ph_num[3][ki],ph_q[3][ki],
					ph_seg___z3_s3, ph_seg_v_z3_s3,
					th_seg___z3_s3, cpat_seg___z3_s3,
					&vi[3][ki][3], &hi[3][ki][3],
					&ci[3][ki][3], &a_si, &ph_match[3][ki][3],
					th_match[3][ki][3] , &cpat_match[3][ki][3]);
	si[3][ki][3]= a_si;

*/

	}




}

