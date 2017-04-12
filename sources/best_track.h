#include <ap_int.h>
#include "spbits.h"
#define zone_to_meid_init {0xA,0x1,0x2,0x3,0x11,0x12,0x13,0x70,0x2A,0x21,0x22,0x23,0x70,0x70,0x70,0x70,0x3A,0x31,0x32,0x33,0x70,0x70,0x70,0x70,0x4A,0x41,\
0x42,0x43,0x70,0x70,0x70,0x70,0xA,0x1,0x2,0x3,0x11,0x12,0x13,0x70,0x2A,0x21,0x22,0x23,0x70,0x70,0x70,0x70,0x3B,0x34,0x35,0x36,0x37,\
0x38,0x39,0x70,0x4B,0x44,0x45,0x46,0x47,0x48,0x49,0x70,0xB,0x4,0x5,0x6,0x14,0x15,0x16,0x70,0x2B,0x24,0x25,0x26,0x27,0x28,0x29,0x70,\
0x3B,0x34,0x35,0x36,0x37,0x38,0x39,0x70,0x4B,0x44,0x45,0x46,0x47,0x48,0x49,0x70,0xC,0x7,0x8,0x9,0x17,0x18,0x19,0x70,0x2B,0x24,0x25,\
0x26,0x27,0x28,0x29,0x70,0x3B,0x34,0x35,0x36,0x37,0x38,0x39,0x70,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x70}

class best_track{
public:


	//function to count shared isegment and jsegment
	ap_uint<3> count_shsegs(ap_uint<2> ai[5],ap_uint<4> bi[5],ap_uint<5> ci,ap_uint<2> di[5],
			ap_uint<2> aj[5],ap_uint<4> bj[5],ap_uint<5> cj,ap_uint<2> dj[5]){
	 #pragma HLS INLINE off
	#pragma HLS LATENCY max=0
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS PIPELINE II=1

		ap_uint<4> bxor[5];
		ap_uint<5> cxor;
		ap_uint<2> dxor[5];
		ap_uint<2> aor[5];
		ap_uint<4> comp[5];
		ap_uint<3> sh_segs=0;

		//xor operation result is 0 when both operands are equal
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


