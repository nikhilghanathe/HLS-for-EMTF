#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
#include "best_track.h"

//wrapper function for best_tracks module
void sp_c::best_tracks(
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

			)
{
#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return
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


static best_track inst;

inst.best_tracks_actual(
				phi ,
				theta ,
				cpattern ,
				delta_ph ,
				delta_th,
		 	    sign_ph,
			    sign_th,
			    rank ,
			    vi ,
			    hi ,
				ci ,
				si ,
				bt_phi,
				bt_theta,
				bt_cpattern ,
				bt_delta_ph,
				bt_delta_th ,
				bt_sign_ph,
				bt_sign_th,
				bt_rank ,
				bt_vi ,
				bt_hi ,
				bt_ci,
				bt_si
				);


	}
