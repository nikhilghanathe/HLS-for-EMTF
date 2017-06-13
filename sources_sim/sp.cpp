#include <ap_int.h>
#include "spbits.h"
///#include "primitive.h"
#include "sp.h"
#include <fstream>
#include <iostream>
#include <ap_utils.h>
//#include <systemc.h>
using namespace std;

/* void sp_c::sp(	ap_uint<4>         q  [5][9][seg_ch],
	    ap_uint<bw_wg>   wg   [5][9][seg_ch],
	    ap_uint<bw_hs>   hstr [5][9][seg_ch],
	    ap_uint<4>  	   cpat [5][9][seg_ch],


		//used for only pcs
		ap_uint<bw_fph> ph[5][9][seg_ch],
		ap_uint<bw_th> th11[2][3][th_ch11],
		ap_uint<bw_th> th[5][9][seg_ch],
		ap_uint<seg_ch> vl[5][9],
		ap_uint<3> phzvl[5][9],
		ap_uint<seg_ch> me11a[2][3],
		ap_uint<4> cpatr[5][9][seg_ch],
		ap_uint<ph_hit_w> ph_hit[5][9],
		ap_uint<th_hit_w> th_hit[5][9],
		//ap_uint<12> *r_out,
		//till here for pcs


		//Used for zns
	    ap_uint<ph_raw_w>  ph_zone [4][5],
		//till here for pcs


	    ap_uint<9>  	   pcs_cs [5],
	    ap_uint<5>  	   pps_cs [3],
	    ap_uint<2>  	   sel,
	    ap_uint<2> 		   sel11,

	    ap_uint<bw_addr>  addr,

	    ap_uint<12>  		r_in, // ap_uint<> data for memory or register
	    ap_uint<12>  		r_out, // ap_uint<> data from memory or register
	    ap_uint<1> 				we, // write enable for memory or register


		//unused for prim_conv_sector,zone image formation


		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph>  bt_phi [3],
		ap_uint<bw_th>  	bt_theta [3],
		// [best_track_num][station]
		ap_uint<4>   	bt_cpattern [3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  bt_delta_ph [3][6],
		ap_uint<bw_th>  	bt_delta_th [3][6],
		ap_uint<6>  		bt_sign_ph[3],
		ap_uint<6>  		bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1>  		bt_rank [3],
		// segment IDs
		// [best_track_num][station 0-3]
		ap_uint<seg_ch>  bt_vi [3][5], // valid
		ap_uint<2>  		bt_hi [3][5], // bx index
		ap_uint<4>  		bt_ci [3][5], // chamber
		ap_uint<5>  		bt_si [3], // segment

	    ap_uint<30>  ptlut_addr [3], // ptlut addresses for best 3 muons
	    ap_uint<32>  ptlut_cs [3], // pre-decoded chip selects
	    ap_uint<3>  ptlut_addr_val, // ptlut address valid flags
		ap_uint<8>  gmt_phi [3], // phi for gmt
	    ap_uint<9>  gmt_eta [3], // eta for gmt



		ap_uint<1> endcap,
		ap_uint<3>  sector,
		ap_uint<1> lat_test,
		ap_uint<1> print_flag
		)*/
void sp_c::sp(
		ap_uint<seg_ch> vpf[6][9],
		ap_uint<4>         q    [6][9][seg_ch],
	    ap_uint<bw_wg>   wg   [6][9][seg_ch],
	    ap_uint<bw_hs>   hstr [6][9][seg_ch],
	    ap_uint<4>  	   cpat [6][9][seg_ch],

	    ap_uint<9>  	   pcs_cs [6],
	    ap_uint<5>  	   pps_cs [3],
	    ap_uint<3>  	   sel,
	    ap_uint<2>		   sel11,
	    ap_uint<bw_addr>  addr,

	    ap_uint<13>  		r_in, // ap_uint<> data for memory or register
	    ap_uint<12>  		r_out, // ap_uint<> data from memory or register
	    ap_uint<1> 				we, // write enable for memory or register
		ap_uint<64> cppf_rxd [7][3], // cppf rx data, 3 frames x 64 bit, for 7 links
		ap_uint<7> cppf_rx_valid, // cppf rx data valid flags


		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph>  bt_phi [3],
		ap_uint<bw_th>  	bt_theta [3],
		// [best_track_num][station]
		ap_uint<4>   	bt_cpattern [3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  bt_delta_ph [3][6],
		ap_uint<bw_th>  	bt_delta_th [3][6],
		ap_uint<6>  		bt_sign_ph[3],
		ap_uint<6>  		bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1>  		bt_rank [3],
		// segment IDs
		// [best_track_num][station 0-3]
		ap_uint<seg_ch>  bt_vi [3][5], // valid
		ap_uint<2>  		bt_hi [3][5], // bx index
		ap_uint<4>  		bt_ci [3][5], // chamber
		ap_uint<5>  		bt_si [3], // segment

	    ap_uint<30>  ptlut_addr [3], // ptlut addresses for best 3 muons
	    ap_uint<32>  ptlut_cs [3], // pre-decoded chip selects
	    ap_uint<3>  ptlut_addr_val, // ptlut address valid flags
		ap_uint<8>  gmt_phi [3], // phi for gmt
	    ap_uint<9>  gmt_eta [3], // eta for gmt
	    ap_uint<4> gmt_qlt [3], // quality for gmt
		ap_uint<3> gmt_crg,

		ap_uint<1> endcap,
		ap_uint<3>  sector,
		ap_uint<1> lat_test,
		ap_uint<1> print_flag
		)

{
//#pragma HLS LATENCY min=1 max=1
/*
#pragma HLS INTERFACE register port=ph
#pragma HLS INTERFACE register port=th
#pragma HLS INTERFACE register port=th11
#pragma HLS INTERFACE register port=vl
#pragma HLS INTERFACE register port=me11a
#pragma HLS INTERFACE register port=phzvl
#pragma HLS INTERFACE register port=cpatr
#pragma HLS INTERFACE register port=ph_hit
#pragma HLS INTERFACE register port=th_hit
#pragma HLS INTERFACE register port=r_out
*/
 // this is for generating registers at outputs

#pragma HLS INTERFACE ap_ctrl_none port=return //this is for registers at input

#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=cpat complete dim=0
#pragma HLS ARRAY_PARTITION variable=hstr complete dim=0
#pragma HLS ARRAY_PARTITION variable=wg complete dim=0
#pragma HLS ARRAY_PARTITION variable=q dim=0
#pragma HLS ARRAY_PARTITION variable=pcs_cs complete dim=0


	// coordinates [station][chamber][segment]
	    ap_uint<bw_fph>  ph_t   [6][9][seg_ch];
	    ap_uint<bw_th>  	th11_t [3][3][th_ch11];
	    ap_uint<bw_th>  	th_t   [6][9][seg_ch];
	    ap_uint<seg_ch>  vl_t   [6][9];

	    ap_uint<3>  			phzvl_t[6][9];
		ap_uint<seg_ch>  	me11a_t [3][3];
	    ap_uint<4>  			cpatr_t [6][9][seg_ch];

		// numbers of best ranks [zone][num]
	/*	ap_uint<bpow+1>  ph_num [4][3];
		// best ranks [zone][num]
		ap_uint<bwr>  ph_q [4][3];*/
		//ap_uint<bwr>  ph_qr [4][3];

	    // ph and th raw hits [station][chamber]
	    ap_uint<ph_hit_w>  ph_hit_t [6][9];
	    ap_uint<th_hit_w>  th_hit_t [6][9];


#pragma HLS ARRAY_PARTITION variable=vl complete dim=0
#pragma HLS ARRAY_PARTITION variable=th complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11 complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_zone complete dim=0


#pragma HLS ARRAY_PARTITION variable=th_hit_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_hit_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpatr_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11a_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=phzvl_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=vl_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11_t complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_t complete dim=0

	    //ap_uint<ph_raw_w>  ph_zone [4][5];
	    // ph zones [zone][station]
/*	    ap_uint<ph_raw_w>  ph_zone [4][5];
	    // ph zones extended [zone][station]
	    ap_uint<ph_raw_w>  ph_ext [4][5];


	    // hardcoded (at this time) inputs
	    // drifttime and th_window have to become inputs eventually
	    ap_uint<3>  			drifttime = 2;
		ap_uint<bw_th>  	th_window = 4;
	    // fold numbers for multiplexed pattern detectors
	    ap_uint<3>  			ph_foldn = 0;
	    ap_uint<3>  			th_foldn = 0;

	    // ph quality codes output [zone][key_strip]
	    ap_uint<6>  		ph_rank [4][ph_raw_w];

	    // coordinate outputs delayed and with history [bx_history][station][chamber][segment]
	    // most recent in bx = 0
	    ap_uint<bw_fph>  	phd   [max_drift][5][9][seg_ch];
	    ap_uint<bw_th>  	th11d [max_drift][2][3][th_ch11];
	    ap_uint<bw_th>  	thd   [max_drift][5][9][seg_ch];
	    ap_uint<seg_ch>  	vld   [max_drift][5][9];
		ap_uint<seg_ch>  	me11ad [max_drift][2][3];
	    ap_uint<4>  			cpatd [max_drift][5][9][seg_ch];

		// find_segment outputs, in terms of segments match in zones [zone][pattern_num][station 0-3]
		ap_uint<seg_ch>  patt_ph_vi [4][3][4]; // valid
		ap_uint<2>  		patt_ph_hi [4][3][4]; // bx index
		ap_uint<3>  		patt_ph_ci [4][3][4]; // chamber
		ap_uint<4>  		patt_ph_si [4][3]; // segment
		ap_uint<bw_fph> 	ph_match [4][3][4]; // matching ph
		ap_uint<bw_th> 	th_match   [4][3][4][seg_ch]; // matching th, 2 segments
		ap_uint<bw_th> 	th_match11 [2][3][th_ch11]; // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
		ap_uint<4>  			cpat_match [4][3][4]; // matching pattern

		ap_uint<bw_fph>  phi [4][3];
		ap_uint<bw_th>  theta [4][3];
		ap_uint<4>  cpattern [4][3][4];
		// ph and th deltas from best stations
		// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  	delta_ph [4][3][6];
		ap_uint<bw_th>  	delta_th [4][3][6];
		ap_uint<6>  			sign_ph[4][3];
		ap_uint<6>  			sign_th[4][3];
		// updated ranks [zone][pattern_num]
		ap_uint<bwr+1>  		rank [4][3];
		//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch>  	vir [4][3][4]; // valid
		ap_uint<2> 			hir [4][3][4]; // bx index
		ap_uint<3>  			cir [4][3][4]; // chamber
		ap_uint<4>  			sir [4][3]; // segment
*/

	    ap_uint<3> phzvl[5][9];
	    ap_uint<seg_ch> me11a[2][3];
	    ap_uint<4> cpatr[5][9][seg_ch];
	    ap_uint<ph_hit_w> ph_hit[5][9];
	    ap_uint<th_hit_w> th_hit[5][9];
	   // ap_uint<6>  		ph_rank [4][ph_raw_w];
	    ap_uint<ph_raw_w>  ph_ext [4][5];

/*
	    //Level 1 pcs
	    	 // coordinates [station][chamber][segment]
	    	    ap_uint<bw_fph>  ph_t   [5][9][seg_ch];
	    	    ap_uint<bw_th>  	th11_t [2][3][th_ch11];
	    	     ap_uint<bw_th>  	th_t   [5][9][seg_ch];
	    	    ap_uint<seg_ch>  vl_t   [5][9];

	    	    ap_uint<3>  			phzvl_t[5][9];
	    	    ap_uint<seg_ch>  	me11a_t [2][3];
	    	    ap_uint<4>  			cpatr_t [5][9][seg_ch];

	    		// numbers of best ranks [zone][num]
	    	    ap_uint<bpow+1>  ph_num [4][3];
	    		// best ranks [zone][num]
	    		ap_uint<bwr>  ph_q [4][3];
	    		ap_uint<bwr>  ph_qr [4][3];

	    	    // ph and th raw hits [station][chamber]
	    		 ap_uint<ph_hit_w>  ph_hit_t [5][9];
	    		 ap_uint<th_hit_w>  th_hit_t [5][9];
	    		 ap_uint<ph_raw_w>  ph_zone_t [4][5];
*/	    		// ap_uint<12> r_out_t;

ap_uint<ph_raw_w>  ph_zone_t [4][5];
ap_uint<ph_raw_w>	ph_ext_t[4][5];
ap_uint<6> ph_rank_t[4][ph_raw_w];
ap_uint<bpow+1>  ph_num_t [4][3];
ap_uint<bwr>  ph_q_t [4][3];
ap_uint<4>	dummy[max_drift][6][9][seg_ch];

ap_uint<12> r_out_t;

/*ap_uint<bw_fph> phd[max_drift][5][9][seg_ch];
ap_uint<bw_th> th11d[max_drift][2][3][th_ch11];
ap_uint<bw_th>	thd[max_drift][5][9][seg_ch];
ap_uint<seg_ch>	vld[max_drift][5][9];
ap_uint<seg_ch>	me11ad[max_drift][2][3];
ap_uint<4>	cpatd[max_drift][5][9][seg_ch];*/




	    //Level 2  zns
	    		    ap_uint<bw_fph>  ph_t1   [5][9][seg_ch];
	    		    ap_uint<bw_th>  	th11_t1 [2][3][th_ch11];
	    		     ap_uint<bw_th>  	th_t1   [5][9][seg_ch];
	    		    ap_uint<seg_ch>  vl_t1   [5][9];

	    		    ap_uint<3>  			phzvl_t1[5][9];
	    		    ap_uint<seg_ch>  	me11a_t1 [2][3];
	    		    ap_uint<4>  			cpatr_t1 [5][9][seg_ch];


	    		    // ph and th raw hits [station][chamber]
	    			 ap_uint<ph_hit_w>  ph_hit_t1 [5][9];
	    			 ap_uint<th_hit_w>  th_hit_t1 [5][9];
	    			 ap_uint<ph_raw_w>  ph_zone_t1 [4][5];
	    			 ap_uint<12> r_out_t1;

	    //Level 3 exts
	    			    ap_uint<bw_fph>  ph_t2   [5][9][seg_ch];
	    			    ap_uint<bw_th>  	th11_t2 [2][3][th_ch11];
	    			     ap_uint<bw_th>  	th_t2   [5][9][seg_ch];
	    			    ap_uint<seg_ch>  vl_t2   [5][9];

	    			    ap_uint<3>  			phzvl_t2[5][9];
	    			    ap_uint<seg_ch>  	me11a_t2 [2][3];
	    			    ap_uint<4>  			cpatr_t2 [5][9][seg_ch];


	    			    // ph and th raw hits [station][chamber]
	    				 ap_uint<ph_hit_w>  ph_hit_t2 [5][9];
	    				 ap_uint<th_hit_w>  th_hit_t2 [5][9];
	    				// ap_uint<ph_raw_w>  ph_zone_t2 [4][5];
	    				 ap_uint<12> r_out_t2;

	    //Level 4 phps
	     			    ap_uint<bw_fph>  ph_t3   [5][9][seg_ch];
	     			    ap_uint<bw_th>  	th11_t3 [2][3][th_ch11];
	               		ap_uint<bw_th>  	th_t3   [5][9][seg_ch];
	     			    ap_uint<seg_ch>  vl_t3   [5][9];
	     			    ap_uint<3>  			phzvl_t3[5][9];
	     			    ap_uint<seg_ch>  	me11a_t3 [2][3];
	     			    ap_uint<4>  			cpatr_t3 [5][9][seg_ch];
	     			    ap_uint<6> ph_rank_t3 [4][ph_raw_w];


	     			    // ph and th raw hits [station][chamber]
	     				 ap_uint<ph_hit_w>  ph_hit_t3 [5][9];
	     				 ap_uint<th_hit_w>  th_hit_t3 [5][9];
	     				 ap_uint<ph_raw_w>  ph_zone_t3 [4][5];
	     				//ap_uint<ph_raw_w>	ph_ext_t3[4][5];
	     				 ap_uint<12> r_out_t3;



	    #pragma HLS ARRAY_PARTITION variable=th_hit complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_hit complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=cpatr complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=me11a complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=phzvl complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=vl complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th11 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_zone complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_ext complete dim=0


	    #pragma HLS ARRAY_PARTITION variable=th_hit_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_hit_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=cpatr_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=me11a_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=phzvl_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=vl_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th11_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_t complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_zone_t complete dim=0

	    #pragma HLS ARRAY_PARTITION variable=th_hit_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_hit_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=cpatr_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=me11a_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=phzvl_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=vl_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th11_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_t1 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_zone_t1 complete dim=0

	    #pragma HLS ARRAY_PARTITION variable=th_hit_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_hit_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=cpatr_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=me11a_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=phzvl_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=vl_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th11_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_t2 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_zone_t2 complete dim=0

	    #pragma HLS ARRAY_PARTITION variable=th_hit_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_hit_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=cpatr_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=me11a_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=phzvl_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=vl_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=th11_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_zone_t3 complete dim=0
	    #pragma HLS ARRAY_PARTITION variable=ph_ext_t3 complete dim=0

	    	    //ap_uint<ph_raw_w>  ph_zone [4][5];
	    	    // ph zones [zone][station]
	    /*	    ap_uint<ph_raw_w>  ph_zone [4][5];
	    	    // ph zones extended [zone][station]
	    	    ap_uint<ph_raw_w>  ph_ext [4][5];


	    	    // hardcoded (at this time) inputs
	    	    // drifttime and th_window have to become inputs eventually
	    	    ap_uint<3>  			drifttime = 2;
	    		ap_uint<bw_th>  	th_window = 4;
	    	    // fold numbers for multiplexed pattern detectors
	    	    ap_uint<3>  			ph_foldn = 0;
	    	    ap_uint<3>  			th_foldn = 0;

	    	    // ph quality codes output [zone][key_strip]
	    	    ap_uint<6>  		ph_rank [4][ph_raw_w];

	    	    // coordinate outputs delayed and with history [bx_history][station][chamber][segment]
	    	    // most recent in bx = 0
	    	    ap_uint<bw_fph>  	phd   [max_drift][5][9][seg_ch];
	    	    ap_uint<bw_th>  	th11d [max_drift][2][3][th_ch11];
	    	    ap_uint<bw_th>  	thd   [max_drift][5][9][seg_ch];
	    	    ap_uint<seg_ch>  	vld   [max_drift][5][9];
	    		ap_uint<seg_ch>  	me11ad [max_drift][2][3];
	    	    ap_uint<4>  			cpatd [max_drift][5][9][seg_ch];

	    		// find_segment outputs, in terms of segments match in zones [zone][pattern_num][station 0-3]
	    		ap_uint<seg_ch>  patt_ph_vi [4][3][4]; // valid
	    		ap_uint<2>  		patt_ph_hi [4][3][4]; // bx index
	    		ap_uint<3>  		patt_ph_ci [4][3][4]; // chamber
	    		ap_uint<4>  		patt_ph_si [4][3]; // segment
	    		ap_uint<bw_fph> 	ph_match [4][3][4]; // matching ph
	    		ap_uint<bw_th> 	th_match   [4][3][4][seg_ch]; // matching th, 2 segments
	    		ap_uint<bw_th> 	th_match11 [2][3][th_ch11]; // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
	    		ap_uint<4>  			cpat_match [4][3][4]; // matching pattern

	    		ap_uint<bw_fph>  phi [4][3];
	    		ap_uint<bw_th>  theta [4][3];
	    		ap_uint<4>  cpattern [4][3][4];
	    		// ph and th deltas from best stations
	    		// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
	    		ap_uint<bw_fph>  	delta_ph [4][3][6];
	    		ap_uint<bw_th>  	delta_th [4][3][6];
	    		ap_uint<6>  			sign_ph[4][3];
	    		ap_uint<6>  			sign_th[4][3];
	    		// updated ranks [zone][pattern_num]
	    		ap_uint<bwr+1>  		rank [4][3];
	    		//[zone][pattern_num][station 0-3]
	    		ap_uint<seg_ch>  	vir [4][3][4]; // valid
	    		ap_uint<2> 			hir [4][3][4]; // bx index
	    		ap_uint<3>  			cir [4][3][4]; // chamber
	    		ap_uint<4>  			sir [4][3]; // segment
	    */

	    ap_uint<3> drifttime=3;
	    ap_uint<3> ph_foldn=0;
	    ap_uint<bw_th> th_window=4;

	    static sp_c pcs;
	   	 static sp_c zns;
	   	static  sp_c exts;
	    static sp_c phps;
	    	static sp_c srts;
	    static sp_c cdl;
	    	static sp_c mphseg;
	    	static sp_c ds;
	    	static sp_c bt;
	    	static sp_c pta;

if(this->pr)pcs.pr=0;
	   /*************************************************************/
	   //#pragma HLS PROTOCOL fixed
	    	{
	    //	#pragma HLS LATENCY min=0 max=0
	   //#pragma HLS PROTOCOL fixed
	   		pcs.prim_conv_sector(
	   				(vpf),
	   				(q),
	   				(wg),
	   				(hstr),
	   				(cpat),
	   				(ph_t),
	   				(th11_t),
	   				(th_t),
	   				(vl_t),
	   				(phzvl_t),
	   				(me11a_t),
	   				(cpatr_t),
	   				(ph_hit_t),
	   				(th_hit_t),
	   				(&r_out_t),
	   				(sel),
	   				(addr),
	   				(r_in),
	   				(we),
	   				(endcap),
	   				(lat_test),
	   				print_flag,
	   				(pcs_cs)
	   				 );

	    	}
	    //	ap_wait();



	    	if(this->pr){
	    		for(int i=0;i<6;i++){
	    			for(int j=0;j<9;j++){
	    				for(int k=0;k<2;k++){
	    					if(ph_t[i][j][k]!=0)
	    					cout<<"ph["<<i<<"]["<<j<<"]["<<k<<"]= "<<ph_t[i][j][k]<<endl;

	    					if(th_t[i][j][k]!=0)
	    					cout<<"th["<<i<<"]["<<j<<"]["<<k<<"]= "<<th_t[i][j][k]<<endl;
	    				}
	    			}
	    		}
	    	}


	    	if(this->pr){
	    		for(int i=0;i<3;i++){
	    			for(int j=0;j<3;j++){
	    				for(int k=0;k<th_ch11;k++){
	//    					cout<<"th11["<<i<<"]["<<j<<"]["<<k<<"]= "<<th11_t[i][j][k]<<endl;
	    				}
	    			}
	    		}
	    	}

	   /*********************************************************/
//
	    	{


	   #pragma HLS PROTOCOL floating

	   //ap_wait_n(4);


	     		{
	     	//#pragma HLS PROTOCOL fixed
	     			cdl.co_ord_delay

	     			(
	     			 ph_t,
	     			 th11_t,
	     			 th_t,
	     			 vl_t,
	     			 me11a_t,
	     			 cpatr_t,
					 cppf_rxd,
					 cppf_rx_valid,


	     			 phd,
	     			 th11d,
	     			 thd,
	     			 vld,
	     			 me11ad,
	     			 cpatd,
	     			 dummy
	     			 );
	     	}

//std::cout<<"sp ph[2][4][0]= "<<ph[2][4][0]<<std::endl;
//std::cout<<"sp ph[4][4][0]= "<<ph[4][4][0]<<std::endl;
//
//cout<<"sp phzvl_t[4][4]= "<<phzvl_t[4][4]<<" phzvl_t[2][4]= "<<phzvl_t[2][4]<<endl;
//cout<<"sp ph_hit_t[4][4]= "<<ph_hit_t[4][4]<<" ph_hit_t[2][4]= "<<ph_hit_t[2][4]<<endl;
	   // 	ap_wait();
	    		{
	   //#pragma HLS PROTOCOL fixed

	    	{

	   //#pragma HLS PROTOCOL fixed

	   		zns.zones(phzvl_t,
	   				  ph_hit_t,
	   				  ph_zone_t
	   				  /*ph_t,
	   				  th11_t,
	   				  th_t,
	   				  vl_t,
	   				  me11a_t,
	   				  cpatr_t,
	   				  th_hit_t,
	   				  ph,
	   				  th11,
	   				  th,
	   				  vl,
	   				  phzvl,
	   				  me11a,
	   				  cpatr,
	   				  ph_hit,
	   				  th_hit*/);
	   		//ap_wait();
	   		ap_wait();
	    	}

//cout<<"zones"<<endl;
//cout<<"sp ph_zone_t[2][4]= "<<ph_zone_t[2][4]<<" ph_zone_t[2][2]= "<<ph_zone_t[2][2]<<endl;
	   /*****************************************************************/
	    {
	    //		#pragma HLS LATENCY min=0 max=0
	   //#pragma HLS PROTOCOL fixed
	   		exts.extend_sector(
	   				ph_zone_t,
	   				ph_ext_t,
	   				drifttime);
	   	 //	ap_wait_n(1);
	   		//ap_wait();
	    	}

    	if(this->pr){
    		for(int i=0;i<4;i++){
    			for(int j=0;j<5;j++){
    		//			cout<<"ph_ext_t["<<i<<"]["<<j<<"]= "<<ph_ext_t[i][j]<<endl;
    				}
    			}
    		}

//	    cout<<"extend"<<endl;
//	    cout<<"sp ph_ext_t[2][4]= "<<ph_ext_t[2][4]<<" ph_ext_t[2][2]= "<<ph_ext_t[2][2]<<endl;
	    	ap_wait_n(3);
	   /*****************************************************************/
	    	{
	   //#pragma HLS LATENCY min=0 max=0
	    //		#pragma HLS PROTOCOL fixed
	   		phps.ph_pattern_sector(ph_ext_reg,
	   				drifttime,
	   				ph_foldn,
	   				ph_rank_t);

	   		ap_wait();
	    	}

	    	for(int i=0;i<4;i++){
	        	for(int j=0;j<5;j++){
	        		ph_ext_reg[i][j]=ph_ext_t[i][j];
				}
			}

	//    	cout<<"ph_patternph_rank_t[2][64]= "<<ph_rank_t[2][64]<<endl;
	    //	ap_wait();
	   /***********************************************************************************/
if(this->pr){
	for(int i=0;i<ph_raw_w;i++){
		//cout<<"ph_rank_t[0]["<<i<<"]= "<<ph_rank_t[0][i]<<endl;
	}
}
	    	{
	   //#pragma HLS LATENCY min=0 max=0
	   //#pragma HLS PROTOCOL fixed
	   		srts.sort_sector(ph_rank_reg,
	   						ph_num_t,
	   						ph_q_t);
	   	 	//ap_ap_wait();
	   		ap_wait();
	    	}

	    	for(int i=0;i<4;i++){
				for(int j=0;j<ph_raw_w;j++){
					ph_rank_reg[i][j]=ph_rank_t[i][j];
					if(ph_rank_reg[i][j]!=0)
						cout<<"ph_rank_reg["<<dec<<i<<"]["<<j<<"]= "<<hex<<ph_rank_reg[i][j]<<endl;
				}
			}


	    	for(int i=0;i<4;i++){
				for(int j=0;j<3;j++){
					if(ph_q_t[i][j]!=0)
					cout<<"ph_q["<<i<<"]["<<j<<"]= "<<ph_q_t[i][j]<<endl;
				}
			}


	    	for(int i=0;i<4;i++){
				for(int j=0;j<3;j++){
					if(ph_num_t[i][j]!=0x7f)
					cout<<"ph_num["<<i<<"]["<<j<<"]= "<<ph_num_t[i][j]<<endl;
				}
			}
	        	}
	    //	ap_wait_n(2);

	   /*	{
	   #pragma HLS PROTOCOL fixed
	   	ap_wait();
	   	}*/

	    	}


	   /***********************************************************************************/

if(this->pr){
//std::cout<<"sp ph_q[0][1]= "<<ph_q_t[0][1]<<std::endl;
//std::cout<<"sp ph_num[0][1]= "<<ph_num_t[0][1]<<std::endl;
}


	   /*

	   	{
	   #pragma HLS LATENCY min=0 max=0
	   //#pragma HLS PROTOCOL fixed
	   	ap_wait();
	   	}
	   */


for(int i=0;i<max_drift;i++){
	#pragma HLS UNROLL
			for(int j=0;j<6;j++){
	#pragma HLS UNROLL
				for(int k=0;k<9;k++){
	#pragma HLS UNROLL
					for(int l=0; l<seg_ch;l++){
						if(thd[i][j][k][l]!=0)
						std::cout<<"thd["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]= "<<thd[i][j][k][l]<<std::endl;

						if(phd[i][j][k][l]!=0)
						std::cout<<"phd["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]= "<<phd[i][j][k][l]<<std::endl;

					}
				}
			}
		}


for(int i=0;i<max_drift;i++){
	#pragma HLS UNROLL
			for(int j=0;j<3;j++){
	#pragma HLS UNROLL
				for(int k=0;k<3;k++){
	#pragma HLS UNROLL
					for(int l=0; l<th_ch11;l++){
						if(th11d[i][j][k][l]!=0)
						std::cout<<"th11d["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]= "<<th11d[i][j][k][l]<<std::endl;


					}
				}
			}
		}
	    /******************************************************************************************/
	    {


	   #pragma HLS PROTOCOL fixed

	    	mphseg.match_ph_seg(
	    		     ph_num_t,
	    			 ph_q_t,

	    		     phd,
	    			 vld,
	    		     th11d,
	    			 thd,
	    			 cpatd,

	    		     vi,
	    			 hi,
	    			 ci,
	    			 si,
	    			 ph_match,
	    			 th_match_t,
	    			 th_match11,
	    			 cpat_match ,
	    			 ph_qr
	    			 );

	    }
    	for(int i=0;i<4;i++){
			for(int j=0;j<3;j++){
				ph_q_reg[i][j]=ph_q_t[i][j];
				ph_num_reg[i][j]=ph_num_t[i][j];
			}
		}

		for(int i=0;i<4;i++){
			#pragma HLS UNROLL
					for(int j=0;j<3;j++){
			#pragma HLS UNROLL
						for(int k=0;k<4;k++){
			#pragma HLS UNROLL
							for(int l=0; l<seg_ch;l++){
								th_match_t1[i][j][k][l]=th_match_t[i][j][k][l];
							//	std::cout<<"sp th_match_t1["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]= "<<th_match_t1[i][j][k][l]<<std::endl;
							}
						}
					}
				}

		if(this->pr){
	//	std::cout<<"sp th_match_t1[0][0][0][0]= "<<th_match_t1[0][0][0][0]<<std::endl;
		}

		{


	    	ds.deltas_sector(
	    	 vi,
	    	 hi,
	    	 ci,
	    	 si,
	    	 ph_match,
	    	 th_match_t1,
	    	 cpat_match,
	    	 ph_qr,
	    	 th_window,

	    	 phi,
	    	 theta,
	    	 cpattern,
	    	 delta_ph,
	    	 delta_th,
	    	 sign_ph,
	    	 sign_th,
	    	 rank,
	    	 vir,
	    	 hir,
	    	 cir,
	    	 sir
	    		);


	    	if(this->pr){
	    		for(int i=0;i<4;i++){
	    			for(int j=0;j<3;j++){
	    					if(phi[i][j]!=0)
	    					cout<<"phi["<<i<<"]["<<j<<"]= "<<phi[i][j]<<endl;
	    				}
	    			}
	    		}




	    }

//if(this->pr) cout<<"sp phi[2][0]= "<<phi[2][0]<<endl;
		{

			#pragma HLS PROTOCOL fixed
			bt.best_tracks(
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


if(this->pr){
	//cout<<"sp bt_phi[0]= "<<bt_phi[0]<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<5;j++){
		//	cout<<"bt_ci["<<i<<"]["<<j<<"]= "<<bt_ci[i][j]<<endl;
		}
	}
}

		{
//		    pta.ptlut_address
//		    (
//		        (bt_phi),
//		        (bt_theta),
//		        (bt_cpattern),
//		        (bt_delta_ph),
//		        (bt_delta_th),
//		        (bt_sign_ph),
//		        (bt_sign_th),
//		        (bt_rank),
//		        (bt_vi),
//		        (bt_hi),
//		        (bt_ci),
//		        (bt_si),
//		        (0),//vl_single
//		        (0),//ph_single
//		         (0),//th_single
//		        (ptlut_addr),
//		        (ptlut_cs),
//		        (ptlut_addr_val),
//		        (bt_rank),
//		        (gmt_phi),
//		        (gmt_eta),
//		        (gmt_qlt),
//		        (gmt_crg),
//		        (sector),
//		        (endcap),
//		        we
//		    );

		}

	   	for(int i=0;i<5;i++){
	   	#pragma HLS UNROLL
	   			for(int j=0;j<9;j++){
	   	#pragma HLS UNROLL
	   				ph_hit[i][j]=ph_hit_t[i][j];
	   				th_hit[i][j]=th_hit_t[i][j];
	   				phzvl[i][j]=phzvl_t[i][j];
	   				vl[i][j]=vl_t[i][j];
	   				for(int k=0;k<seg_ch;k++){
	   	#pragma HLS UNROLL
	   					ph[i][j][k]=ph_t[i][j][k];
	   					th[i][j][k]=th_t[i][j][k];
	   					cpatr[i][j][k]=cpatr_t[i][j][k];
	   				}
	   			}
	   		}

	   		for(int i=0;i<2;i++){
	   	#pragma HLS UNROLL
	   			for(int j=0;j<3;j++){
	   	#pragma HLS UNROLL
	   				me11a[i][j]=me11a_t[i][j];
	   				for(int k=0;k<th_ch11;k++){
	   	#pragma HLS UNROLL
	   					th11[i][j][k]=th11_t[i][j][k];

	   				}
	   			}
	   		}

	   			  for(int i=0;i<4;i++){
	   #pragma HLS UNROLL
	   				for(int j=0;j<5;j++){
	   #pragma HLS UNROLL
	   					ph_zone[i][j]=ph_zone_t[i][j];
	   					ph_ext[i][j]=ph_ext_t[i][j];
	   				}

	   			  }


	   			  for(int i=0;i<4;i++){
	   #pragma HLS UNROLL
	   				for(int j=0;j<ph_raw_w;j++){
	   #pragma HLS UNROLL
	   					ph_rank[i][j]=ph_rank_t[i][j];
	   				}

	   			  }


	   			  for(int i=0;i<4;i++){
	   				for(int j=0;j<3;j++){
	   					ph_num[i][j]=ph_num_t[i][j];
	   					ph_q[i][j]=ph_q_t[i][j];
	   				}

	   			  }







	    	}


