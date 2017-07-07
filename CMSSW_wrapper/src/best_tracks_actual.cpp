#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/best_track.h"
using namespace std;

void best_track::best_tracks_actual(ap_uint<bw_fph> phi[4][3],
		ap_uint<bw_th> theta[4][3],
		// [zone][pattern_num][station]
		ap_uint<4> cpattern[4][3][4],
		// ph and th deltas from best stations
		// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph> delta_ph[4][3][6], ap_uint<bw_th> delta_th[4][3][6],
		ap_uint<6> sign_ph[4][3], ap_uint<6> sign_th[4][3],
		// updated ranks [zone][pattern_num]
		ap_uint<bwr + 1> rank[4][3],
		//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch> vi[4][3][4], // valid
		ap_uint<2> hi[4][3][4], // bx index
		ap_uint<3> ci[4][3][4], // chamber
		ap_uint<4> si[4][3], // segment

		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph> bt_phi[3], ap_uint<bw_th> bt_theta[3],
		// [best_track_num][station]
		ap_uint<4> bt_cpattern[3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph> bt_delta_ph[3][6], ap_uint<bw_th> bt_delta_th[3][6],
		ap_uint<6> bt_sign_ph[3], ap_uint<6> bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr + 1> bt_rank[3],
		//[best_track_num][station 0-3]
		ap_uint<seg_ch> bt_vi[3][5], // valid
		ap_uint<2> bt_hi[3][5], // bx index
		ap_uint<4> bt_ci[3][5], // chamber
		ap_uint<5> bt_si[3] // segment

		) {
//#pragma HLS LOOP_MERGE force
//#pragma HLS EXPRESSION_BALANCE
//#pragma HLS LATENCY max=0
#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=theta complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpattern complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=rank complete dim=0
#pragma HLS ARRAY_PARTITION variable=vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=si complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_theta complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_cpattern complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_delta_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_delta_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_sign_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_sign_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_rank complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_si complete dim=0



	        ap_uint<bw_fph> a_bt_phi[3];
			#ifdef CMSSW_MACRO
				a_bt_phi[0]=0; a_bt_phi[1]=0; a_bt_phi[2]=0;
			#endif
	        ap_uint<bw_th> a_bt_theta[3];
			ap_uint<4> a_bt_cpattern[3][4];
			ap_uint<bw_fph> a_bt_delta_ph[3][6];
			ap_uint<bw_th> a_bt_delta_th[3][6];
			ap_uint<6> a_bt_sign_ph[3];
			ap_uint<6> a_bt_sign_th[3];
			ap_uint<bwr + 1> a_bt_rank[3];
			ap_uint<seg_ch> a_bt_vi[3][5];
			ap_uint<2> a_bt_hi[3][5];
			ap_uint<4> a_bt_ci[3][5];
			ap_uint<5> a_bt_si[3];

	        ap_uint<bw_fph> b_bt_phi[3];
	        ap_uint<bw_th> b_bt_theta[3];
			ap_uint<4> b_bt_cpattern[3][4];
			ap_uint<bw_fph> b_bt_delta_ph[3][6];
			ap_uint<bw_th> b_bt_delta_th[3][6];
			ap_uint<6> b_bt_sign_ph[3];
			ap_uint<6> b_bt_sign_th[3];
			ap_uint<bwr + 1> b_bt_rank[3];
			ap_uint<seg_ch> b_bt_vi[3][5];
			ap_uint<2> b_bt_hi[3][5];
			ap_uint<4> b_bt_ci[3][5];
			ap_uint<5> b_bt_si[3];

	        ap_uint<bw_fph> c_bt_phi[3];
	        ap_uint<bw_th> c_bt_theta[3];
			ap_uint<4> c_bt_cpattern[3][4];
			ap_uint<bw_fph> c_bt_delta_ph[3][6];
			ap_uint<bw_th> c_bt_delta_th[3][6];
			ap_uint<6> c_bt_sign_ph[3];
			ap_uint<6> c_bt_sign_th[3];
			ap_uint<bwr + 1> c_bt_rank[3];
			ap_uint<seg_ch> c_bt_vi[3][5];
			ap_uint<2> c_bt_hi[3][5];
			ap_uint<4> c_bt_ci[3][5];
			ap_uint<5> c_bt_si[3];





	// segment ids reformatted to chamber ids in sector
	//[zone][pattern_num][station 0-4]
	ap_uint<seg_ch> cn_vi[4][3][5];

 // valid
	ap_uint<2> cn_hi[4][3][5]; // bx index
	ap_uint<4> cn_ci[4][3][5]; // chamber
	ap_uint<5> cn_si[4][3][5]; // segment



	int z, n, s, bn, i, j;
	ap_uint<36> larger[36];
	ap_uint<7> ri, rj;
	ap_uint<36> exists, kill1;
	ap_uint<36> kill1_t[36][36];
	ap_uint<1> winner[36][3];
	ap_uint<36> a_winner[36][3];
#pragma HLS ARRAY_RESHAPE variable=winner complete dim=0
	ap_uint<1> gt, eq;
	ap_uint<4> cham;
	ap_uint<6> sum[36];
	ap_uint<3> sh_segs[36][36];


	// [zone][pattern][station]		//	ap_uint<7> zm_addr [4][3][4];
			//ap_uint<4> real_ch [4][3][4];
			//ap_uint<3> real_st [4][3][4];
			ap_uint<4> real_ch;
			ap_uint<3> real_st;

			 ap_uint<7> lut_out [4][3][4];
			// zero segment numbers
			/*
			 ap_uint<bw_fph> phi_r [4][3];
			 ap_uint<bw_th> 	theta_r [4][3];
			 ap_uint<4> 		cpattern_r [4][3][4];
			 ap_uint<bw_fph> delta_ph_r [4][3][6];
			 ap_uint<bw_th> 	delta_th_r [4][3][6];
			 ap_uint<6> 		sign_ph_r[4][3];
			 ap_uint<6> 		sign_th_r[4][3];
			 ap_uint<bwr+1> 		rank_r [4][3];
			 ap_uint<seg_ch> cn_vi_r [4][3][5]; // valid
			 ap_uint<3>		cn_hi_r [4][3][5]; // bx index
			 ap_uint<4> 		cn_ci_r [4][3][5]; // chamber
			 ap_uint<1> 				cn_si_r [4][3][5]; // segment

			 ap_uint<bw_fph> phi_rr [4][3];
			 ap_uint<bw_th> 	theta_rr [4][3];
			 ap_uint<4> 		cpattern_rr [4][3][4];
			 ap_uint<bw_fph> delta_ph_rr [4][3][6];
			 ap_uint<bw_th> 	delta_th_rr [4][3][6];
			 ap_uint<6> 		sign_ph_rr[4][3];
			 ap_uint<6> 		sign_th_rr[4][3];
			 ap_uint<bwr+1>  		rank_rr [4][3];
			 ap_uint<seg_ch> cn_vi_rr [4][3][5]; // valid
			 ap_uint<3> 		cn_hi_rr [4][3][5]; // bx index
			 ap_uint<4> 		cn_ci_rr [4][3][5]; // chamber
			 ap_uint<1> 				cn_si_rr [4][3][5]; // segment
			 */

			ap_uint<seg_ch> cn_vi_i[36][36],	cn_vi_j[36][36];
	ap_uint<3> cn_hi_i[36][36], cn_hi_j[36][36];
	ap_uint<4> cn_ci_i[36][36], cn_ci_j[36][36];
	ap_uint<1> cn_si_i[36][36], cn_si_j[36][36];


	ap_uint<2> cand_bx[4][3];


	ap_uint<3> h1, h2;
	ap_uint<36> good_bx;


	//cout<<"best_tracks check0"<<endl;
	const ap_uint<7> temp [128]= zone_to_meid_init;
			for(int i=0; i<128;i++){
		#pragma HLS UNROLL
			zone_to_meid_00 [i] =  temp[i];
				 zone_to_meid_01 [i] = temp[i];
				 zone_to_meid_02 [i] = temp[i];
				 zone_to_meid_03[i]  = temp[i];
				 zone_to_meid_04 [i] = temp[i];
				 zone_to_meid_05[i]  = temp[i];
				 zone_to_meid_06 [i] = temp[i];
				 zone_to_meid_07 [i] = temp[i];
				 zone_to_meid_08  [i]= temp[i];
				 zone_to_meid_09 [i] = temp[i];
				 zone_to_meid_10 [i] = temp[i];
				 zone_to_meid_11 [i] = temp[i];
				 zone_to_meid_12 [i] = temp[i];
				 zone_to_meid_13 [i] = temp[i];
				 zone_to_meid_14  [i]= temp[i];
				 zone_to_meid_15 [i] = temp[i];
				 zone_to_meid_16 [i] = temp[i];
				 zone_to_meid_17  [i]= temp[i];
				 zone_to_meid_18  [i]= temp[i];
				 zone_to_meid_19  [i]= temp[i];
				 zone_to_meid_20  [i]= temp[i];
				 zone_to_meid_21  [i]= temp[i];
				 zone_to_meid_22  [i]= temp[i];
				 zone_to_meid_23  [i]= temp[i];
				 zone_to_meid_24  [i]= temp[i];
				 zone_to_meid_25  [i]= temp[i];
				 zone_to_meid_26  [i]= temp[i];
				 zone_to_meid_27  [i]= temp[i];
				 zone_to_meid_28  [i]= temp[i];
				 zone_to_meid_29  [i]= temp[i];
				 zone_to_meid_30  [i]= temp[i];
				 zone_to_meid_31  [i]= temp[i];
				 zone_to_meid_32  [i]= temp[i];
				 zone_to_meid_33  [i]= temp[i];
				 zone_to_meid_34 [i] = temp[i];
				 zone_to_meid_35 [i] = temp[i];
				 zone_to_meid_36 [i] = temp[i];
				 zone_to_meid_37  [i]= temp[i];
				 zone_to_meid_38 [i] = temp[i];
				 zone_to_meid_39 [i] = temp[i];
				 zone_to_meid_40 [i] = temp[i];
				 zone_to_meid_41 [i] = temp[i];
				 zone_to_meid_42 [i] = temp[i];
				 zone_to_meid_43 [i] = temp[i];
				 zone_to_meid_44 [i] = temp[i];
				 zone_to_meid_45  [i]= temp[i];
				 zone_to_meid_46 [i] = temp[i];
				 zone_to_meid_47 [i] = temp[i];
			}

	lut_out[0][0][0] = zone_to_meid_00[ap_uint<7>(0x0) |(ap_uint<4>(0),ci[0][0][0](2, 0))];
	lut_out[0][0][1] = zone_to_meid_01[ap_uint<7>(0x8) | (ap_uint<4>(0),ci[0][0][1](2, 0))];
	lut_out[0][0][2] = zone_to_meid_02[ap_uint<7>(0x10) | (ap_uint<4>(0),ci[0][0][2](2, 0))];
	lut_out[0][0][3] = zone_to_meid_03[ap_uint<7>(0x18) | (ap_uint<4>(0),ci[0][0][3](2, 0))];
	lut_out[0][1][0] = zone_to_meid_04[ap_uint<7>(0x0) | (ap_uint<4>(0),ci[0][1][0](2, 0))];
	lut_out[0][1][1] = zone_to_meid_05[ap_uint<7>(0x8) | (ap_uint<4>(0),ci[0][1][1](2, 0))];
	lut_out[0][1][2] = zone_to_meid_06[ap_uint<7>(0x10) | (ap_uint<4>(0),ci[0][1][2](2, 0))];
	lut_out[0][1][3] = zone_to_meid_07[ap_uint<7>(0x18) | (ap_uint<4>(0),ci[0][1][3](2, 0))];
	lut_out[0][2][0] = zone_to_meid_08[ap_uint<7>(0x0) | (ap_uint<4>(0),ci[0][2][0](2, 0))];
	lut_out[0][2][1] = zone_to_meid_09[ap_uint<7>(0x8) | (ap_uint<4>(0),ci[0][2][1](2, 0))];
	lut_out[0][2][2] = zone_to_meid_10[ap_uint<7>(0x10) | (ap_uint<4>(0),ci[0][2][2](2, 0))];
	lut_out[0][2][3] = zone_to_meid_11[ap_uint<7>(0x18) | (ap_uint<4>(0),ci[0][2][3](2, 0))];
	lut_out[1][0][0] = zone_to_meid_12[ap_uint<7>(0x20) | (ap_uint<4>(0),ci[1][0][0](2, 0))];
	lut_out[1][0][1] = zone_to_meid_13[ap_uint<7>(0x28) | (ap_uint<4>(0),ci[1][0][1](2, 0))];
	lut_out[1][0][2] = zone_to_meid_14[ap_uint<7>(0x30) | (ap_uint<4>(0),ci[1][0][2](2, 0))];
	lut_out[1][0][3] = zone_to_meid_15[ap_uint<7>(0x38) | (ap_uint<4>(0),ci[1][0][3](2, 0))];
	lut_out[1][1][0] = zone_to_meid_16[ap_uint<7>(0x20) | (ap_uint<4>(0),ci[1][1][0](2, 0))];
	lut_out[1][1][1] = zone_to_meid_17[ap_uint<7>(0x28) | (ap_uint<4>(0),ci[1][1][1](2, 0))];
	lut_out[1][1][2] = zone_to_meid_18[ap_uint<7>(0x30) | (ap_uint<4>(0),ci[1][1][2](2, 0))];
	lut_out[1][1][3] = zone_to_meid_19[ap_uint<7>(0x38) | (ap_uint<4>(0),ci[1][1][3](2, 0))];
	lut_out[1][2][0] = zone_to_meid_20[ap_uint<7>(0x20) | (ap_uint<4>(0),ci[1][2][0](2, 0))];
	lut_out[1][2][1] = zone_to_meid_21[ap_uint<7>(0x28) | (ap_uint<4>(0),ci[1][2][1](2, 0))];
	lut_out[1][2][2] = zone_to_meid_22[ap_uint<7>(0x30) | (ap_uint<4>(0),ci[1][2][2](2, 0))];
	lut_out[1][2][3] = zone_to_meid_23[ap_uint<7>(0x38) | (ap_uint<4>(0),ci[1][2][3](2, 0))];
	lut_out[2][0][0] = zone_to_meid_24[ap_uint<7>(0x40) | (ap_uint<4>(0),ci[2][0][0](2, 0))];
	lut_out[2][0][1] = zone_to_meid_25[ap_uint<7>(0x48) | (ap_uint<4>(0),ci[2][0][1](2, 0))];
	lut_out[2][0][2] = zone_to_meid_26[ap_uint<7>(0x50) | (ap_uint<4>(0),ci[2][0][2](2, 0))];
	lut_out[2][0][3] = zone_to_meid_27[ap_uint<7>(0x58) | (ap_uint<4>(0),ci[2][0][3](2, 0))];
	lut_out[2][1][0] = zone_to_meid_28[ap_uint<7>(0x40) | (ap_uint<4>(0),ci[2][1][0](2, 0))];
	lut_out[2][1][1] = zone_to_meid_29[ap_uint<7>(0x48) | (ap_uint<4>(0),ci[2][1][1](2, 0))];
	lut_out[2][1][2] = zone_to_meid_30[ap_uint<7>(0x50) | (ap_uint<4>(0),ci[2][1][2](2, 0))];
	lut_out[2][1][3] = zone_to_meid_31[ap_uint<7>(0x58) | (ap_uint<4>(0),ci[2][1][3](2, 0))];
	lut_out[2][2][0] = zone_to_meid_32[ap_uint<7>(0x40) | (ap_uint<4>(0),ci[2][2][0](2, 0))];
	lut_out[2][2][1] = zone_to_meid_33[ap_uint<7>(0x48) | (ap_uint<4>(0),ci[2][2][1](2, 0))];
	lut_out[2][2][2] = zone_to_meid_34[ap_uint<7>(0x50) | (ap_uint<4>(0),ci[2][2][2](2, 0))];
	lut_out[2][2][3] = zone_to_meid_35[ap_uint<7>(0x58) | (ap_uint<4>(0),ci[2][2][3](2, 0))];
	lut_out[3][0][0] = zone_to_meid_36[ap_uint<7>(0x60) | (ap_uint<4>(0),ci[3][0][0](2, 0))];
	lut_out[3][0][1] = zone_to_meid_37[ap_uint<7>(0x68) | (ap_uint<4>(0),ci[3][0][1](2, 0))];
	lut_out[3][0][2] = zone_to_meid_38[ap_uint<7>(0x70) | (ap_uint<4>(0),ci[3][0][2](2, 0))];
	lut_out[3][0][3] = zone_to_meid_39[ap_uint<7>(0x78) | (ap_uint<4>(0),ci[3][0][3](2, 0))];
	lut_out[3][1][0] = zone_to_meid_40[ap_uint<7>(0x60) | (ap_uint<4>(0),ci[3][1][0](2, 0))];
	lut_out[3][1][1] = zone_to_meid_41[ap_uint<7>(0x68) | (ap_uint<4>(0),ci[3][1][1](2, 0))];
	lut_out[3][1][2] = zone_to_meid_42[ap_uint<7>(0x70) | (ap_uint<4>(0),ci[3][1][2](2, 0))];
	lut_out[3][1][3] = zone_to_meid_43[ap_uint<7>(0x78) | (ap_uint<4>(0),ci[3][1][3](2, 0))];
	lut_out[3][2][0] = zone_to_meid_44[ap_uint<7>(0x60) | (ap_uint<4>(0),ci[3][2][0](2, 0))];
	lut_out[3][2][1] = zone_to_meid_45[ap_uint<7>(0x68) | (ap_uint<4>(0),ci[3][2][1](2, 0))];
	lut_out[3][2][2] = zone_to_meid_46[ap_uint<7>(0x70) | (ap_uint<4>(0),ci[3][2][2](2, 0))];
	lut_out[3][2][3] = zone_to_meid_47[ap_uint<7>(0x78) | (ap_uint<4>(0),ci[3][2][3](2, 0))];


	cn_vi[3][2][4] = 0;
	cn_hi[3][2][4] = 0;
	cn_si[3][2][4] = 0;
	cn_ci[3][2][4] = 0;
	// calculate real station and chamber numbers

	// input segment numbers are in terms of chambers in zone
	// convert them back into chamber ids in sector
	for (z = 0; z < 4; z = z + 1) { // zone loop
#pragma HLS UNROLL
#pragma HLS LOOP_FLATTEN
		for (n = 0; n < 3; n = n + 1) { // pattern number//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS LOOP_FLATTEN
			h2 = 0;
			h1 = 0;
			for (s = 0; s < 4; s = s + 1) { // station
#pragma HLS UNROLL
#pragma HLS LOOP_FLATTEN

				(real_st,real_ch) = lut_out[z][n][s];
				//real_ch = lut_out[z][n][s](3, 0);

				cn_vi[z][n][real_st] = vi[z][n][s];
				cn_hi[z][n][real_st] = hi[z][n][s];
				cn_si[z][n][real_st] = si[z][n][s];
				cn_ci[z][n][real_st] = real_ch;

		// analyze stub delays, use each track only at the time of second-earliest stub
				ap_uint<1> temp1,temp2;
				temp1=(vi[z][n][s][1] | vi[z][n][s][0]);
				temp2=(hi[z][n][s][1] & ~hi[z][n][s][0]);
				h2 = (temp1 && temp2) ? ap_uint<3>(h2 + 1) : ap_uint<3>(h2);//(ap_uint<2>(0), (vi[z][n][s] && (hi[z][n][s] == 2)))/*0x1*/; // count stubs delayed by 2 BX
				temp2=(hi[z][n][s][1] || hi[z][n][s][0]);
				h1 = (temp1 && temp2) ? ap_uint<3>(h1 +1) : h1;// (ap_uint<2> (0), (vi[z][n][s] && (hi[z][n][s] >= 1)))/*0x1*/; // count stubs delayed by 1 BX or more

			} // for (s = 0; s < 4; s = s+1)

			// determine proper BX for this track
			cand_bx[z][n] = 2;
			if (h2[2] | h2[1]/*h2 >= 0x2*/)
				cand_bx[z][n] = 0;//(ap_uint<1> (0),~(h2 >= 0x2 && h1 <0x2));;//(0,(h2 >= 0x2 && h1 <0x2)); // two stubs in earliest BX, analyze immediately
			else if (h1[2] | h1[1]/*h1 >= 0x2*/)
				cand_bx[z][n] = 1;// (ap_uint<1> (0) ,(h2 <2 && h1 >= 0x2)); // second-earliest stub one BX late

				 // second-earliest stub two BXs late
		}
	}
//cout<<"best_tracks check1"<<endl;
	if(this->pr){
	cout<<"cn_vi[0][0][4]= "<<cn_vi[0][0][4]<<endl;
	cout<<"cn_vi[0][0][3]= "<<cn_vi[0][0][3]<<endl;
	cout<<"cn_vi[0][0][2]= "<<cn_vi[0][0][2]<<endl;
	}
	// zero outputs initially
	for (n = 0; n < 3; n = n + 1) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
        //winner[n]=0;
		a_bt_rank[n] = 0;b_bt_rank[n] = 0;c_bt_rank[n] = 0;
		a_bt_phi[n] = 0;b_bt_phi[n] = 0;c_bt_phi[n] = 0;
		a_bt_theta[n] = 0;b_bt_theta[n] = 0;c_bt_theta[n] = 0;
		for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			a_bt_cpattern[n][s] = 0;b_bt_cpattern[n][s] = 0;c_bt_cpattern[n][s] = 0;
		}
		for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			a_bt_delta_ph[n][s] = 0;b_bt_delta_ph[n][s] = 0;c_bt_delta_ph[n][s] = 0;
			a_bt_sign_ph[n][s] = 0;b_bt_sign_ph[n][s] = 0;c_bt_sign_ph[n][s] = 0;
			a_bt_delta_th[n][s] = 0;b_bt_delta_th[n][s] = 0;c_bt_delta_th[n][s] = 0;
			a_bt_sign_th[n][s] = 0;b_bt_sign_th[n][s] = 0;c_bt_sign_th[n][s] = 0;
		}

		for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			a_bt_vi[n][s] = 0;b_bt_vi[n][s] = 0;c_bt_vi[n][s] = 0;
			a_bt_hi[n][s] = 0;b_bt_hi[n][s] = 0;c_bt_hi[n][s] = 0;
			a_bt_si[n][s] = 0;b_bt_si[n][s] = 0;c_bt_si[n][s] = 0;
			a_bt_ci[n][s] = 0;b_bt_ci[n][s] = 0;c_bt_ci[n][s] = 0;
		}
	}


	for (i = 0; i < 36; i = i + 1) {
#pragma HLS UNROLL
		larger[i] = 0;
		winner[i][0] = 0;
		winner[i][1] = 0;
		winner[i][2] = 0;


	}



	good_bx = 0;

	//cout<<"best_tracks check2"<<endl;

	// simultaneously compare each rank with each
	for (i = 0; i < 36; i = i+1){
//			larger[i] = 0;
		larger[i][i] = 1; // result of comparison with itself
	   // first index loops zone, second loops candidate. Zone loops faster, so we give equal priority to zones
	    if      (i <  12){
		   ri = rank  [i%4][i/4];
		   if (cand_bx[i%4][i/4] == 0x0 ) good_bx[i] = 1; // kill this rank if it's not the right BX
	    }
	    else if (i >= 24){
		   ri = rank_rr  [(i-24)%4][(i-24)/4];
		   if (cand_bx_rr[(i-24)%4][(i-24)/4] == 2 ) good_bx[i] = 1; // kill this rank if it's not the right BX
	    }
	    else{
           ri = rank_r  [(i-12)%4][(i-12)/4];
		   if (cand_bx_r[(i-12)%4][(i-12)/4] == 1 ) good_bx[i] = 1; // kill this rank if it's not the right BX
	    }

		for (j = i+1; j < 36; j = j+1){
	       if      (j <  12) rj = rank  [j%4][j/4];
	       else if (j >= 24) rj = rank_rr [(j-24)%4][(j-24)/4];
	       else				 rj = rank_r  [(j-12)%4][(j-12)/4];

		   // compare ranks
			if (ri >= rj) larger[i][j] = 1;
			    else          larger[j][i] = 1;
		}
		// "larger" array shows the result of comparison for each rank

		// track exists if quality != 0
		exists[i] = (ri != 0);
}

	//cout<<"best_tracks check3"<<endl;

	kill1 = 0;
	for(int i=0;i<36;i++){
		#pragma HLS UNROLL
			for(int j=0;j<36;j++){
				kill1_t[i][j]=0;
			}
		}
	//cout

	if(this->pr){
for(int i=0;i<4;i++){
	for(int j=0;j<3;j++){
//		cout<<"cand_bx_rr["<<i<<"]["<<j<<"]= "<<cand_bx_rr[i][j]<<endl;
//		cout<<"cand_bx_r["<<i<<"]["<<j<<"]= "<<cand_bx_r[i][j]<<endl;
		cout<<"rank_r["<<i<<"]["<<j<<"]= "<<rank_r[i][j]<<endl;
	}
}
for(int i=0;i<4;i++){
	for(int j=0;j<3;j++){
//		cout<<"cand_bx_rr["<<i<<"]["<<j<<"]= "<<cand_bx_rr[i][j]<<endl;
//		cout<<"cand_bx_r["<<i<<"]["<<j<<"]= "<<cand_bx_r[i][j]<<endl;
		cout<<"cand_bx_r["<<i<<"]["<<j<<"]= "<<cand_bx_r[i][j]<<endl;
	}
}
	}

for(int i=0;i<12;i++){
#pragma HLS UNROLL

	for(int j=0;j<12;j++){

	if(j>i){
		sh_segs[i][j]=count_shsegs(
					cn_vi[i%4][i/4],	cn_ci[i%4][i/4], cn_si[i%4][i/4], cn_hi[i%4][i/4],
				cn_vi[j%4][j/4], cn_ci[j%4][j/4], cn_si[j%4][j/4], cn_hi[j%4][j/4]);

		if(sh_segs[i][j]>0){
				if (larger[i][j]) kill1_t[i][j][j] = 1;
				else kill1_t[i][j][i] = 1;
		}
	}


	}

} // for (i = 0; i < 12; i = i+1)


for(int i=12;i<24;i++){
#pragma HLS UNROLL

	for(int j=0;j<12;j++){

	if(j>i){
		sh_segs[i][j]=count_shsegs(
					cn_vi[(i-12)%4][(i-12)/4],	cn_ci[(i-12)%4][(i-12)/4], cn_si[(i-12)%4][(i-12)/4], cn_hi[(i-12)%4][(i-12)/4],
				cn_vi[(j-12)%4][(j-12)/4], cn_ci[(j-12)%4][(j-12)/4], cn_si[(j-12)%4][(j-12)/4], cn_hi[(j-12)%4][(j-12)/4]);

		if(sh_segs[i][j]>0){
				if (larger[i][j]) kill1_t[i][j][j] = 1;
				else kill1_t[i][j][i] = 1;
		}
	}


	}

} // for (i = 0; i < 12; i = i+1)


for(int i=24;i<36;i++){
#pragma HLS UNROLL

	for(int j=0;j<12;j++){

	if(j>i){
		sh_segs[i][j]=count_shsegs(
					cn_vi[(i-24)%4][(i-24)/4],	cn_ci[(i-24)%4][(i-24)/4], cn_si[(i-24)%4][(i-24)/4], cn_hi[(i-24)%4][(i-24)/4],
				cn_vi[(j-24)%4][(j-24)/4], cn_ci[(j-24)%4][(j-24)/4], cn_si[(j-24)%4][(j-24)/4], cn_hi[(j-24)%4][(j-24)/4]);

		if(sh_segs[i][j]>0){
				if (larger[i][j]) kill1_t[i][j][j] = 1;
				else kill1_t[i][j][i] = 1;
		}
	}


	}

} // for (i = 0; i < 12; i = i+1)

//cout<<"best_tracks check4"<<endl;
for(int i=0;i<36;i++){
	#pragma HLS UNROLL
		for(int j=0;j<36;j++){
			kill1 =kill1 | kill1_t[i][j];
		}
	}
if(this->pr){
//cout<<"best_tracks check5"<<endl;
cout<<"exists_init= "<<exists<<endl;
	// remove ghosts according to kill mask
	exists = exists & (~kill1);

	// remove tracks that are not at correct BX number
	exists = exists & good_bx;
cout<<"exists= "<<exists<<endl;
cout<<"good_bx= "<<good_bx<<endl;
cout<<"kill1= "<<kill1<<endl;
}
	for (i = 0; i <36 ; i = i + 1) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
//#pragma HLS LOOP_MERGE force
#pragma HLS DEPENDENCE false
		if(exists[i]){
		larger[i] = larger[i] | (~exists); // if this track exists make it larger than all non-existing tracks
		}else{
			larger[i] = 0; // else make it smaller than anything

		}
		// count zeros in the comparison results. The best track will have none, the next will have one, the third will have two.
		sum[i] = 0;
		zero_count_36bits(larger[i],&sum[i]);

		if (sum[i] < 3)//CULPRIT
			winner[i][sum[i]] =1;//(~sum[5] & ~sum[4] & ~sum[3] & ~sum[2] & (~sum[1] 	| (sum[1] & ~sum[0])));//1; // assign positional winner codes
	}
	if(this->pr){
	for(int j=0;j<36;j++){
		cout<<"larger["<<j<<"]= "<<larger[j]<<endl;
	}

for(int i=0;i<3;i++){
	cout<<"winner["<<i<<"]= ";
	for(int j=0;j<36;j++){
		cout<<dec<<winner[j][i]<<hex;
	}
	cout<<endl;
}

	}

	// multiplex best tracks to outputs according to winner signals
	for (n = 0; n < 3; n = n + 1) { // output loop !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
		for (i = 0; i < 12; i = i + 1) { // winner bit loop//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
			if(winner[i][n]){
			//if (winner[n][i]) {

				a_bt_rank[n] = a_bt_rank[n] | rank[i % 4][i / 4];
				a_bt_phi[n] = a_bt_phi[n] | phi[i % 4][i / 4];
				a_bt_theta[n] = a_bt_theta[n] | theta[i % 4][i / 4];

				for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					a_bt_cpattern[n][s] =a_bt_cpattern[n][s]
							| cpattern[i % 4][i / 4][s];
				}

				for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					a_bt_delta_ph[n][s] = a_bt_delta_ph[n][s] | delta_ph[i % 4][i / 4][s];
					a_bt_sign_ph[n][s] = a_bt_sign_ph[n][s]   | sign_ph[i % 4][i / 4][s];
					a_bt_delta_th[n][s] = a_bt_delta_th[n][s] | delta_th[i % 4][i / 4][s];
					a_bt_sign_th[n][s] = a_bt_sign_th[n][s]   | sign_th[i % 4][i / 4][s];
				}

				for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					a_bt_vi[n][s] = a_bt_vi[n][s] | cn_vi[i % 4][i / 4][s];
					a_bt_hi[n][s] = a_bt_hi[n][s] | cn_hi[i % 4][i / 4][s];
					a_bt_ci[n][s] = a_bt_ci[n][s] | cn_ci[i % 4][i / 4][s];
					a_bt_si[n][s] = a_bt_si[n][s] | cn_si[i % 4][i / 4][s];
				}
			}
		}



		for (i = 0; i < 12; i = i + 1) { // winner bit loop//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
////#pragma HLS LOOP_FLATTEN

			if(winner[i+12][n]){
				b_bt_rank[n] = b_bt_rank[n] | rank_r[i % 4][i / 4];
				b_bt_phi[n] = b_bt_phi[n] | phi_r[i % 4][i / 4];
				b_bt_theta[n] = b_bt_theta[n] | theta_r[i % 4][i / 4];

				for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					b_bt_cpattern[n][s] = b_bt_cpattern[n][s] | cpattern_r[i % 4][i / 4][s];
				}

				for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					b_bt_delta_ph[n][s] = b_bt_delta_ph[n][s] | delta_ph_r[i % 4][i / 4][s];
					b_bt_sign_ph[n][s] = b_bt_sign_ph[n][s]   | sign_ph_r[i % 4][i / 4][s];
					b_bt_delta_th[n][s] = b_bt_delta_th[n][s] | delta_th_r[i % 4][i / 4][s];
					b_bt_sign_th[n][s] = b_bt_sign_th[n][s]   | sign_th_r[i % 4][i / 4][s];
				}

				for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					b_bt_vi[n][s] = b_bt_vi[n][s] | cn_vi_r[i % 4][i / 4][s];
					b_bt_hi[n][s] = b_bt_hi[n][s] | (cn_hi_r[i % 4][i / 4][s] - 0x1); // correct stub delay back to original value
					b_bt_ci[n][s] = b_bt_ci[n][s] | cn_ci_r[i % 4][i / 4][s];
					b_bt_si[n][s] = b_bt_si[n][s] | cn_si_r[i % 4][i / 4][s];
				}
			}
		}


		for (i = 0; i < 12; i = i + 1) { // winner bit loop//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
#pragma HLS DEPENDENCE false
			if(winner[i+24][n]){//CAN WE DO AWAY WITH THIS OR OPERATION?????
				c_bt_rank[n] = c_bt_rank[n] | rank_rr[i % 4][i / 4];
				c_bt_phi[n] = c_bt_phi[n] | phi_rr[i % 4][i / 4];
				c_bt_theta[n] = c_bt_theta[n] | theta_rr[i % 4][i / 4];

				for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
#pragma HLS DEPENDENCE false
					c_bt_cpattern[n][s] = c_bt_cpattern[n][s] | cpattern_rr[i % 4][i / 4][s];
				}

				for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					c_bt_delta_ph[n][s] = c_bt_delta_ph[n][s] | delta_ph_rr[i % 4][i / 4][s];
					c_bt_sign_ph[n][s] = c_bt_sign_ph[n][s]   | sign_ph_rr[i % 4][i / 4][s];
					c_bt_delta_th[n][s] = c_bt_delta_th[n][s] | delta_th_rr[i % 4][i / 4][s];
					c_bt_sign_th[n][s] = c_bt_sign_th[n][s]   | sign_th_rr[i % 4][i / 4][s];
				}

				for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					c_bt_vi[n][s] = c_bt_vi[n][s] | cn_vi_rr[i % 4][i / 4][s];
					c_bt_hi[n][s] = c_bt_hi[n][s] | (cn_hi_rr[i % 4][i / 4][s] - 0x2); // correct stub delay back to original value
					c_bt_ci[n][s] = c_bt_ci[n][s] | cn_ci_rr[i % 4][i / 4][s];
					c_bt_si[n][s] = c_bt_si[n][s] | cn_si_rr[i % 4][i / 4][s];
				}

		}
	}

}

/*for(n=0;n<3;n++){
	cout<<"winner["<<n<<"]= "<<winner[n]<<endl;
	cout<<"a_bt_phi["<<n<<"] = "<<a_bt_phi[n]<<endl;
	cout<<"b_bt_phi["<<n<<"] = "<<b_bt_phi[n]<<endl;
	cout<<"c_bt_phi["<<n<<"] = "<<c_bt_phi[n]<<endl;

}

*/

	//COMBINE outputs
	for(n=0;n<3;n++){
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
			bt_rank[n] = a_bt_rank[n] | b_bt_rank[n] | c_bt_rank[n] ;
			bt_phi[n] = a_bt_phi[n] | b_bt_phi[n] | c_bt_phi[n];
			bt_theta[n] = a_bt_theta[n]|b_bt_theta[n]|c_bt_theta[n];

			for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				bt_cpattern[n][s] = a_bt_cpattern[n][s]|b_bt_cpattern[n][s]|c_bt_cpattern[n][s];
			}

			for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				bt_delta_ph[n][s] = a_bt_delta_ph[n][s] |b_bt_delta_ph[n][s] |c_bt_delta_ph[n][s] ;
				bt_sign_ph[n][s] = a_bt_sign_ph[n][s]|b_bt_sign_ph[n][s]|c_bt_sign_ph[n][s]   ;
				bt_delta_th[n][s] = a_bt_delta_th[n][s]|b_bt_delta_th[n][s]|c_bt_delta_th[n][s] ;
				bt_sign_th[n][s] = a_bt_sign_th[n][s]| b_bt_sign_th[n][s]| c_bt_sign_th[n][s]   ;
			}

			for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				bt_vi[n][s] = a_bt_vi[n][s]| b_bt_vi[n][s]|c_bt_vi[n][s];
				bt_hi[n][s] = a_bt_hi[n][s]|b_bt_hi[n][s]|c_bt_hi[n][s] ;
				bt_ci[n][s] = a_bt_ci[n][s]| b_bt_ci[n][s]|c_bt_ci[n][s] ;
				bt_si[n][s] = a_bt_si[n][s]|b_bt_si[n][s]|c_bt_si[n][s] ;
			}


}







	{
#pragma HLS DEPENDENCE false

	// keep two-clk history of all inputs
//Second clk
	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			phi_rr[i][j] = phi_r[i][j];
			theta_rr[i][j] = theta_r[i][j];
			sign_ph_rr[i][j] = sign_ph_r[i][j];
			sign_th_rr[i][j] = sign_th_r[i][j];
			rank_rr[i][j] = rank_r[i][j];
			cand_bx_rr[i][j] = cand_bx_r[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 4; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				cpattern_rr[i][j][k] = cpattern_r[i][j][k];
			}
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {

#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 6; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				delta_ph_rr[i][j][k] = delta_ph_r[i][j][k];
				delta_th_rr[i][j][k] = delta_th_r[i][j][k];

			}
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 5; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				cn_vi_rr[i][j][k] = cn_vi_r[i][j][k];
				cn_hi_rr[i][j][k] = cn_hi_r[i][j][k];
				cn_ci_rr[i][j][k] = cn_ci_r[i][j][k];
				cn_si_rr[i][j][k] = cn_si_r[i][j][k];
			}
		}
	}

//First clk

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			phi_r[i][j] = phi[i][j];
			theta_r[i][j] = theta[i][j];
			sign_ph_r[i][j] = sign_ph[i][j];
			sign_th_r[i][j] = sign_th[i][j];
			rank_r[i][j] = rank[i][j];
			cand_bx_r[i][j] = cand_bx[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 4; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				cpattern_r[i][j][k] = cpattern[i][j][k];
			}
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 6; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				delta_ph_r[i][j][k] = delta_ph[i][j][k];
				delta_th_r[i][j][k] = delta_th[i][j][k];

			}
		}
	}

	for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (int k = 0; k < 5; k++) {
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				cn_vi_r[i][j][k] = cn_vi[i][j][k];
				cn_hi_r[i][j][k] = cn_hi[i][j][k];
				cn_ci_r[i][j][k] = cn_ci[i][j][k];
				cn_si_r[i][j][k] = cn_si[i][j][k];
			}
		}
	}

	// history of delays for each stub
	for (z = 0; z < 4; z = z + 1) { // zone loop
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
		for (n = 0; n < 3; n = n + 1) { // pattern number
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (s = 0; s < 5; s = s + 1) { // station
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				// increase delay of each stub to show by how much it was delayed in total
				cn_hi_rr[z][n][s] = cn_hi_r[z][n][s] + 1;
				cn_hi_r[z][n][s] = cn_hi[z][n][s] + 1;
			}
		}
	}

	}

}



