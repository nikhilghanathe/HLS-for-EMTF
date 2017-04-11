#include <ap_int.h>
#include "spbits.h"
#include "match_seg.h"
using namespace std;


void match_seg::find_segment_stn1(
		 ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
		 ap_uint<6> ph_pat_q_p, // pattern valid

		 /* ph from segments [bx_history][chamber][segment]segments are coming from
		  chambers in the interesting zone onlyfor example, in zone 0 ME1 segments
		  should come from chambers subsector1: 1,2,3, subsector2: 1,2,3*/
		 ap_uint<bw_fph> ph_seg_p[max_drift][zone_cham][seg_ch],

		 // valid flags for segments
		 ap_uint<seg_ch> ph_seg_v_p[max_drift][zone_cham],
		 ap_uint<bw_th> th_seg_p[max_drift][zone_cham][zone_seg],
		 ap_uint<4> cpat_seg_p[max_drift][zone_cham][seg_ch],

		 // indexes of best match
		 ap_uint<seg_ch> *vid, // match valid, each flag shows validity of th coord
		 ap_uint<2> *hid, // history id
		 ap_uint<3> *cid, // chamber id
		 ap_uint<1> *sid, // segment id
		 ap_uint<bw_fph> *ph_match, // ph from matching segment

		 // all th's from matching chamber, we don't know which one will fit best
		 ap_uint<bw_th> th_match[zone_seg],
		 ap_uint<4> *cpat_match // pattern from matching segment
		)
{
#pragma HLS ARRAY_PARTITION variable=th_match complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpat_seg_p complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_seg_p complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_seg_v_p complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_seg_p complete dim=0



   const int tot_diff = max_drift*3/*zone_cham*/*seg_ch;
   const int max_ph_diff=7;
   const int bw_phdiff=4;
   const int nodiff=15;





	int i,j,k,di;
	ap_uint<bpow+1> ph_pat; // ph detected in pattern
	ap_uint<1> ph_pat_v; // pattern valid
	ap_uint<bw_fph> ph_seg [max_drift][zone_cham][seg_ch];
#pragma HLS ARRAY_PARTITION variable=ph_seg complete dim=0
	ap_uint<seg_ch> ph_seg_v [max_drift][zone_cham];
#pragma HLS ARRAY_PARTITION variable=ph_seg_v complete dim=0
	ap_uint<bw_th> th_seg [max_drift][zone_cham][zone_seg];
#pragma HLS ARRAY_PARTITION variable=th_seg complete dim=0
	ap_uint<4> cpat_seg [max_drift][zone_cham][seg_ch];
#pragma HLS ARRAY_PARTITION variable=cpat_seg complete dim=0
	ap_uint<bpow+1> ph_segr;
	ap_uint<bpow+1> ph_diff_tmp;
	ap_uint<bw_phdiff> ph_diff [tot_diff];
#pragma HLS ARRAY_PARTITION variable=ph_diff complete dim=0
	ap_uint<2> rcomp;

	ap_uint<6> diffi0 [tot_diff];
#pragma HLS ARRAY_PARTITION variable=diffi0 complete dim=0
	ap_uint<bw_phdiff> cmp1 [tot_diff/3];
#pragma HLS ARRAY_PARTITION variable=cmp1 complete dim=0
	ap_uint<6> diffi1 [tot_diff/3];
#pragma HLS ARRAY_PARTITION variable=diffi1 complete dim=0
	ap_uint<bw_phdiff> cmp2 [tot_diff/9];
#pragma HLS ARRAY_PARTITION variable=cmp2 complete dim=0
	ap_uint<6> diffi2 [tot_diff/9];
#pragma HLS ARRAY_PARTITION variable=diffi2 complete dim=0
	ap_uint<bw_phdiff> cmp3 [tot_diff/18];
#pragma HLS ARRAY_PARTITION variable=cmp3 complete dim=0
	ap_uint<6> diffi3 [tot_diff/18];
#pragma HLS ARRAY_PARTITION variable=diffi3 complete dim=0
	ap_uint<bw_phdiff> cmp4;
	ap_uint<6> diffi4;
	ap_uint<2> ri;
	ap_uint<3> rj;
	ap_uint<1> rk;

	 ap_uint<seg_ch> a_vid; // match valid, each flag shows validity of th coord
	 ap_uint<2> a_hid; // history id
	 ap_uint<3> a_cid; // chamber id
	 ap_uint<1> a_sid;

/*for(int i=0;i<3;i++){
	for(int j=0;j<3zone_cham;j++){
		for(int k=0;k<2zone_seg;k++){
			  cout<<hex<<"th_seg_p["<<i<<"]["<<j<<"]["<<k<<"]= "<<th_seg_p[i][j][k]<<hex<<endl;
		}

	}
}*/

	 ph_pat = ph_pat_p;
	 	ph_pat_v = ph_pat_q_p != 0; // non-zero quality means valid pattern
	 	find_segment_st1_label0:for(int i=0;i<max_drift;i++){
	 #pragma HLS UNROLL
	 		find_segment_st1_label1:for(int j=0;j<3/*zone_cham*/;j++){
	 #pragma HLS UNROLL
	 			find_segment_st1_label2:for(int k=0;k<seg_ch;k++){
	 #pragma HLS UNROLL
	 				ph_seg[i][j][k] = ph_seg_p[i][j][k];
	 			}

	 			ph_seg_v[i][j] = ph_seg_v_p[i][j];
	 			find_segment_st1_label3:for(int k=0;k<2/*zone_seg*/;k++){
	 #pragma HLS UNROLL
	 				th_seg[i][j][k] = th_seg_p[i][j][k];

	 			}
	 			find_segment_st1_label4:for(int k=0;k<seg_ch;k++){
	 #pragma HLS UNROLL
	 				cpat_seg[i][j][k] = cpat_seg_p[i][j][k];
	 			}
	 		}
	 	}


	 	// calculate abs differences
	 	di = 0;
	 	find_segment_st1_label5:for (i = 0; i < max_drift; i = i+1){ // history loop
	 #pragma HLS UNROLL
	 		find_segment_st1_label6:for (j = 0; j < 3/*zone_cham*/; j = j+1){ // chamber loop
	 #pragma HLS UNROLL
	 			find_segment_st1_label7:for (k = 0; k < seg_ch; k = k+1){ // segment loop
	 #pragma HLS UNROLL
	 				// remove unused low bits from segment ph
	 				ph_segr = ph_seg[i][j][k](bw_fph-1 , bw_fph-bpow-1);

	 				// get abs difference
	 				if (ph_seg_v[i][j][k])
	 					    ph_diff_tmp = (ph_pat > ph_segr) ? ph_pat - ph_segr : ph_segr - ph_pat;
	 				else
	 					ph_diff_tmp = nodiff; // if segment invalid put max value into diff

	 			    if((ph_diff_tmp) > (max_ph_diff))
	 					    ph_diff[i*3/*zone_cham*/*seg_ch + j*seg_ch + k] = nodiff; // difference is too high, cannot be the same pattern
	 			    else
	 			 	    ph_diff[i*3/*zone_cham*/*seg_ch + j*seg_ch + k] = ph_diff_tmp(bw_phdiff-1,0);


	 				ri = i;
	 				rj = j;
	 				rk = k;
	 				// diffi variables carry track indexes
	 				diffi0[i*3/*zone_cham*/*seg_ch + j*seg_ch + k] = (ri, rj, rk);
	 			}
	 		}
	 	} // for (i = 0; i < max_drift; i = i+1)




	 	/*************sort differences*****************/
	 			// first stage
	 			find_segment_st1_label8:for (i = 0; i < tot_diff/3; i = i+1){
	 #pragma HLS UNROLL			// compare 3 values
	 				rcomp = comp3(ph_diff[i*3], ph_diff[i*3+1], ph_diff[i*3+2]);
	 				// fill outputs
	 				switch(rcomp){
	 				case 0: cmp1[i] = ph_diff[i*3+0]; diffi1[i] = diffi0[i*3+0];
	 						break;
	 				case 1: cmp1[i] = ph_diff[i*3+1]; diffi1[i] = diffi0[i*3+1];
	 						break;
	 				case 2: cmp1[i] = ph_diff[i*3+2]; diffi1[i] = diffi0[i*3+2];
	 						break;
	 				default: break;
	 				}
	 			}



	 			// second stage
	 			find_segment_st1_label9:for (i = 0; i < tot_diff/9; i = i+1){
	 #pragma HLS UNROLL	// compare 3 values
	 				rcomp = comp3(cmp1[i*3], cmp1[i*3+1], cmp1[i*3+2]);
	 				// fill outputs
	 				switch(rcomp){
	 				case 0: cmp2[i] = cmp1[i*3+0]; diffi2[i] = diffi1[i*3+0];
	 						break;
	 				case 1: cmp2[i] = cmp1[i*3+1]; diffi2[i] = diffi1[i*3+1];
	 						break;
	 				case 2: cmp2[i] = cmp1[i*3+2]; diffi2[i] = diffi1[i*3+2];
	 						break;
	 				default: break;
	 				}
	 			}




	 			// third stage
	 			find_segment_st1_label10:for (i = 0; i < tot_diff/18; i = i+1){
	 #pragma HLS UNROLL	// compare 2 values
	 				rcomp[0] = cmp2[i*2] >= cmp2[i*2+1];
	 				// fill outputs
	 				switch(int(rcomp[0])){
	 				case 0: cmp3[i] = cmp2[i*2+0]; diffi3[i] = diffi2[i*2+0];
	 						break;
	 				case 1: cmp3[i] = cmp2[i*2+1]; diffi3[i] = diffi2[i*2+1];
	 						break;
	 				default: break;
	 				}
	 			}
	 			// last stage depends on number of input segments
	 			if (tot_diff == 36)
	 			{
	 				// compare 2 values
	 				rcomp[0] = cmp3[0] >= cmp3[1];
	 				// fill outputs
	 				switch(int(rcomp[0])){
	 				case 0: cmp4 = cmp3[0]; diffi4 = diffi3[0];
	 						break;
	 				case 1: cmp4 = cmp3[1]; diffi4 = diffi3[1];
	 						break;
	 				default: break;
	 				}
	 			}
	 			else
	 			{
	 				cmp4 = cmp3[0];
	 				diffi4 = diffi3[0];
	 			}

	 			a_hid=diffi4(5,4);
	 			a_cid=diffi4(3,1);
	 			a_sid = diffi4[0];
	 			a_vid = ph_seg_v[a_hid][a_cid][a_sid];

	 			// if pattern invalid or all differences invalid remove valid flags
	 			if (!ph_pat_v || cmp4 == nodiff) a_vid = 0;

	 			*ph_match = ph_seg[a_hid][a_cid][a_sid]; // route best matching phi to output

	 			find_segment_st1_label11:for(int i=0;i<2/*zone_seg*/;i++)
	 			{
	 			#pragma HLS UNROLL
	 				th_match[i] = th_seg[a_hid][a_cid][i]; // route all th coords from matching chamber to output
	 			}

	 			*cpat_match = cpat_seg[a_hid][a_cid][a_sid]; // route pattern to output
	 			*hid=a_hid;
	 			*cid=a_cid;
	 			*sid=a_sid;
	 			*vid=a_vid;


	 }
