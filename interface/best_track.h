#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "spbits.h"
#define zone_to_meid_init {0xA,0x1,0x2,0x3,0x11,0x12,0x13,0x70,0x2A,0x21,0x22,0x23,0x70,0x70,0x70,0x70,0x3A,0x31,0x32,0x33,0x70,0x70,0x70,0x70,0x4A,0x41,\
0x42,0x43,0x70,0x70,0x70,0x70,0xA,0x1,0x2,0x3,0x11,0x12,0x13,0x70,0x2A,0x21,0x22,0x23,0x70,0x70,0x70,0x70,0x3B,0x34,0x35,0x36,0x37,\
0x38,0x39,0x70,0x4B,0x44,0x45,0x46,0x47,0x48,0x49,0x70,0xB,0x4,0x5,0x6,0x14,0x15,0x16,0x70,0x2B,0x24,0x25,0x26,0x27,0x28,0x29,0x70,\
0x3B,0x34,0x35,0x36,0x37,0x38,0x39,0x70,0x4B,0x44,0x45,0x46,0x47,0x48,0x49,0x70,0xC,0x7,0x8,0x9,0x17,0x18,0x19,0x70,0x2B,0x24,0x25,\
0x26,0x27,0x28,0x29,0x70,0x3B,0x34,0x35,0x36,0x37,0x38,0x39,0x70,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x70}

using namespace std;
class best_track{
public:
	ap_uint<1> pr;


   ap_uint<bw_fph> phi_r [4][3];
   ap_uint<bw_th> 	theta_r [4][3];
   ap_uint<4> 		cpattern_r [4][3][4];
   ap_uint<bw_fph> delta_ph_r [4][3][6];
   ap_uint<bw_th> 	delta_th_r [4][3][6];
   ap_uint<6> 		sign_ph_r[4][3];
   ap_uint<6> 		sign_th_r[4][3];
   ap_uint<bwr+1> 		rank_r [4][3];
   ap_uint<seg_ch> cn_vi_r [4][3][5]; // valid
   ap_uint<3> 		cn_hi_r [4][3][5]; // bx index
   ap_uint<4> 		cn_ci_r [4][3][5]; // chamber
   ap_uint<1> 		cn_si_r [4][3][5]; // segment


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

   ap_uint<2> cand_bx_r [4][3];
   ap_uint<2> cand_bx_rr [4][3];
   ap_uint<7> zone_to_meid_00[128];
   ap_uint<7> zone_to_meid_01 [128];
   ap_uint<7> zone_to_meid_02 [128];
   ap_uint<7> zone_to_meid_03 [128];
   ap_uint<7> zone_to_meid_04 [128];
   ap_uint<7> zone_to_meid_05 [128];
   ap_uint<7> zone_to_meid_06 [128];
   ap_uint<7> zone_to_meid_07 [128];
   ap_uint<7> zone_to_meid_08 [128];
   ap_uint<7> zone_to_meid_09 [128];
   ap_uint<7> zone_to_meid_10 [128];
   ap_uint<7> zone_to_meid_11 [128];
   ap_uint<7> zone_to_meid_12 [128];
   ap_uint<7> zone_to_meid_13 [128];
   ap_uint<7> zone_to_meid_14 [128];
   ap_uint<7> zone_to_meid_15 [128];
   ap_uint<7> zone_to_meid_16 [128];
   ap_uint<7> zone_to_meid_17 [128];
   ap_uint<7> zone_to_meid_18 [128];
   ap_uint<7> zone_to_meid_19 [128];
   ap_uint<7> zone_to_meid_20 [128];
   ap_uint<7> zone_to_meid_21 [128];
   ap_uint<7> zone_to_meid_22 [128];
   ap_uint<7> zone_to_meid_23 [128];
   ap_uint<7> zone_to_meid_24 [128];
   ap_uint<7> zone_to_meid_25 [128];
   ap_uint<7> zone_to_meid_26 [128];
   ap_uint<7> zone_to_meid_27 [128];
   ap_uint<7> zone_to_meid_28 [128];
   ap_uint<7> zone_to_meid_29 [128];
   ap_uint<7> zone_to_meid_30 [128];
   ap_uint<7> zone_to_meid_31 [128];
   ap_uint<7> zone_to_meid_32 [128];
   ap_uint<7> zone_to_meid_33 [128];
   ap_uint<7> zone_to_meid_34 [128];
   ap_uint<7> zone_to_meid_35 [128];
   ap_uint<7> zone_to_meid_36 [128];
   ap_uint<7> zone_to_meid_37 [128];
   ap_uint<7> zone_to_meid_38 [128];
   ap_uint<7> zone_to_meid_39 [128];
   ap_uint<7> zone_to_meid_40 [128];
   ap_uint<7> zone_to_meid_41 [128];
   ap_uint<7> zone_to_meid_42 [128];
   ap_uint<7> zone_to_meid_43 [128];
   ap_uint<7> zone_to_meid_44 [128];
   ap_uint<7> zone_to_meid_45 [128];
   ap_uint<7> zone_to_meid_46 [128];
   ap_uint<7> zone_to_meid_47 [128];


ap_uint<3> count_shsegs(ap_uint<2> ai[5],ap_uint<4> bi[5],ap_uint<5> ci,ap_uint<2> di[5],
			ap_uint<2> aj[5],ap_uint<4> bj[5],ap_uint<5> cj,ap_uint<2> dj[5]){
#pragma HLS INLINE off
#pragma HLS LATENCY max=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

ap_uint<4> bxor[5];
ap_uint<5> cxor=0;
ap_uint<2> dxor[5];
ap_uint<2> aor[5];
ap_uint<4> comp[5];
ap_uint<3> sh_segs=0;

for(int i=0;i<5; i++){
#pragma HLS UNROLL
	bxor[i]=bi[i] ^ bj[i];
	cxor[i]=ci[i] ^ cj[i];
	dxor[i]=di[i] ^ dj[i];
	aor[i]=ai[i] | aj[i];
	comp[i]= bxor[i]^ cxor[i] ^ dxor[i];


	if((comp[i]==0) && aor[i]){
		sh_segs++;
	}
}

	return sh_segs;
}

	void best_tracks_actual(
		ap_uint<bw_fph>  phi [4][3],
		ap_uint<bw_th>  theta [4][3],
			// [zone][pattern_num][station]
		ap_uint<4>	cpattern [4][3][4],
			// ph and th deltas from best stations
			// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>	  delta_ph [4][3][6],
		ap_uint<bw_th>	   delta_th [4][3][6],
		ap_uint<6>	  	   sign_ph[4][3],
		ap_uint<6>	 	   sign_th[4][3],
			// updated ranks [zone][pattern_num]
		ap_uint<bwr+1>	   rank [4][3],
			//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch>	  vi [4][3][4], // valid
		ap_uint<2>	  	   hi [4][3][4], // bx index
		ap_uint<3>		   ci [4][3][4], // chamber
		ap_uint<4>	  	   si [4][3], // segment

			// precise phi and theta of best tracks
			// [best_track_num]
		ap_uint<bw_fph>	    bt_phi [3],
		ap_uint<bw_th>	   	bt_theta [3],
			// [best_track_num][station]
		ap_uint<4>	   		bt_cpattern [3][4],
			// ph and th deltas from best stations
			// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  bt_delta_ph [3][6],
		ap_uint<bw_th> 	bt_delta_th [3][6],
		ap_uint<6>    	bt_sign_ph[3],
		ap_uint<6>	  	bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1> 		bt_rank [3],
		//[best_track_num][station 0-3]
		ap_uint<seg_ch>	   bt_vi [3][5], // valid
		ap_uint<2>	   		bt_hi [3][5], // bx index
		ap_uint<4>   	    bt_ci [3][5], // chamber
		ap_uint<5>   		bt_si [3] // segment
	);

	ap_uint<4> zero_count(ap_uint<12> larger);
	void zero_count_36bits(ap_uint<36> larger, ap_uint<6> *sum);
	ap_uint<4> mod3 (ap_uint<4> input);

};


