#include <ap_int.h>
#include "spbits.h"
#include "ptlut_address.h"
#include "sp.h"

//wrapper function for ptlut
void sp_c::ptlut_address(
		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph>  bt_phi_i [3],
		ap_uint<bw_th>  	bt_theta_i [3],
		// [best_track_num][station 0-3]
		ap_uint<4> 		bt_cpattern [3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph> bt_delta_ph [3][6],
		ap_uint<bw_th>  	bt_delta_th [3][6],
		ap_uint<6> 		bt_sign_ph[3],
		ap_uint<6>  		bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1> 	bt_rank_i [3],
		//[best_track_num][station 0-4]
		ap_uint<seg_ch>  bt_vi [3][5], // valid
		ap_uint<2> 		bt_hi [3][5], // bx index
		ap_uint<4>  		bt_ci [3][5], // chamber
		ap_uint<5> 		bt_si [3], // segment

	    ap_uint<1> vl_single,
	    ap_uint<bw_fph> ph_single,
	    ap_uint<bw_th> th_single,

		ap_uint<30> ptlut_addr [3],
		ap_uint<32> ptlut_cs [3],
		ap_uint<3> ptlut_addr_val,
		ap_uint<bwr+1> bt_rank_o [3],

		ap_uint<8> gmt_phi [3],
		ap_uint<9> gmt_eta [3],
		ap_uint<4> gmt_qlt [3],
		ap_uint<3> gmt_crg,

		ap_uint<3> sector,
		ap_uint<1> endcap,
		ap_uint<1> we)
{


#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1



	static ptlut inst;


		inst.ptlut_address_actual(
				bt_phi_i ,
				bt_theta_i ,
				bt_cpattern ,
				bt_delta_ph,
				bt_delta_th ,
				bt_sign_ph,
				bt_sign_th,
				bt_rank_i ,
				bt_vi,
				bt_hi,
				bt_ci ,
				bt_si,
			    vl_single,
			    ph_single,
			    th_single,
				ptlut_addr ,
				ptlut_cs ,
				ptlut_addr_val,
				bt_rank_o ,
				gmt_phi ,
				gmt_eta,
				gmt_qlt ,
				gmt_crg,
			    sector,
				endcap
				);

	}




