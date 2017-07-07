#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
 #include "../include/ap_int.h"
#endif
#include "../interface/spbits.h"
#define zone_cham  7 // 6 chambers in this zone and station
#define zone_seg  th_ch11 // segments per chamber in this zone and station

class sp_c{

public:

ap_uint<1> pr;
	ap_uint<bw_fph>  ph   [6][9][seg_ch];
		    ap_uint<bw_th>  	th11 [3][3][th_ch11];
		    ap_uint<bw_th>  	th   [6][9][seg_ch];
		    ap_uint<seg_ch>  vl   [6][9];

		    ap_uint<ph_raw_w>  ph_zone [4][5];
		    ap_uint<ph_raw_w>  		ph_ext_t3 [4][5];
		    ap_uint<6>  		ph_rank [4][ph_raw_w];
		    ap_uint<6> qcode_p [4][ph_raw_w];
		    ap_uint<ph_raw_w>  ph_zone_t2 [4][5];
			ap_uint<bpow+1>  ph_num [4][3];
			ap_uint<bwr>  ph_q [4][3];
			ap_uint<bpow+1>  ph_num_reg [4][3];
				ap_uint<bwr>  ph_q_reg [4][3];
				// best ranks [zone][num]

				ap_uint<ph_raw_w>	ph_ext_reg[4][5];
				ap_uint<6> ph_rank_reg[4][ph_raw_w];



		   static int iev;
		   ap_uint<bw_fph> phd[max_drift][6][9][seg_ch];
		   ap_uint<bw_th> th11d[max_drift][3][3][th_ch11];
		   ap_uint<bw_th>	thd[max_drift][6][9][seg_ch];
		   ap_uint<seg_ch>	vld[max_drift][6][9];
		   ap_uint<seg_ch>	me11ad[max_drift][3][3];
		   ap_uint<4>	cpatd[max_drift][6][9][seg_ch];
		//   ap_uint<bwr>  ph_qr [4][3];
			 //match_ph_seg
			 ap_uint<seg_ch> vi [4][3][4]; // valid (for each segment in chamber, so we can identify which th to use later)
			 ap_uint<2> 		hi [4][3][4]; // bx index
			 ap_uint<3> 		ci [4][3][4]; // chamber
			 ap_uint<4> 		si [4][3]; // segment which has matching ph
			 ap_uint<bw_fph> ph_match [4][3][4]; // matching phi
			 ap_uint<bw_th>	th_match   [4][3][4][2*2/*zone_seg*/]; // matching th, 2 segments
			 	ap_uint<bw_th> 	th_match_t   [4][3][4][4]; // matching th, 2 segments
			 	ap_uint<bw_th> 	th_match_t1   [4][3][4][seg_ch]; // matching th, 2 segments

			 ap_uint<bw_th>	th_match11 [2][3][th_ch11]; // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
			 ap_uint<4> 		cpat_match [4][3][4]; // matching patterns
			 ap_uint<6> 	ph_qr [4][3];



			 ap_uint<seg_ch>  patt_ph_vi [4][3][4]; // valid
			 ap_uint<2>  		patt_ph_hi [4][3][4]; // bx index
			 ap_uint<3> 		patt_ph_ci [4][3][4]; // chamber
			 ap_uint<4>  		patt_ph_si [4][3]; // segment

			 	ap_uint<bw_fph> phi [4][3];
			 	ap_uint<bw_th>  theta [4][3];
			 	ap_uint<4> cpattern [4][3][4];
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
			 	ap_uint<2>  			hir [4][3][4]; // bx index
			 	ap_uint<3>  			cir [4][3][4]; // chamber
			 	ap_uint<4>  			sir [4][3]; // segment

			 	ap_uint<bw_fph>  	bt_phi_1 [3];

//Primitive Converter
			 	void prim_conv_sector(/*inputs*/
			 			ap_uint<seg_ch> vpf [6][9],
			 			ap_uint<4> q[6][9][seg_ch],
			 			ap_uint<bw_wg> wg[6][9][seg_ch],
			 			ap_uint<bw_hs> hstr[6][9][seg_ch],
			 			ap_uint<4> cpat[6][9][seg_ch],

			 			/*outputs*/
			 			 ap_uint<bw_fph> ph[6][9][seg_ch],

			 			 // special th outputs for ME11 because of duplication
			 			 // [station][chamber][segment with duplicates], station 2 = neighbor segment
			 			 ap_uint<bw_th> th11[3][3][th_ch11],
			 			 ap_uint<bw_th> th[6][9][seg_ch],
			 			 ap_uint<seg_ch> vl[6][9],
			 			 ap_uint<3> phzvl[6][9],
			 			// me11a flags only for ME11 (stations 1,0, chambers 2:0)
			 			// [station][chamber][segment], station 2 = neighbor segment
			 			 ap_uint<seg_ch> me11a[3][3],
			 			 ap_uint<4> cpatr[6][9][seg_ch],
			 			 ap_uint<ph_hit_w> ph_hit[6][9],
			 			 ap_uint<th_hit_w> th_hit[6][9],
			 			 ap_uint<12> *r_out,

			 			/*inputs*/
			 			ap_uint<2> sel,
			 			ap_uint<bw_addr> addr,
			 			ap_uint<13> r_in,
			 			ap_uint<1> we,
			 			ap_uint<1> endcap,
			 			ap_uint<1> lat_test,
			 			ap_uint<9> cs[6]

			 			);



//Zone image formation
	 void zones ( ap_uint<3> phzvl_in[6][9],
			  ap_uint<ph_hit_w> ph_hit_in[6][9],
		    	 ap_uint<ph_raw_w> ph_zone[4][5]/*,
				ap_uint<bw_fph> ph_in[5][9][seg_ch],
						ap_uint<bw_th> th11_in[2][3][th_ch11],
						ap_uint<bw_th> th_in[5][9][seg_ch],
						ap_uint<seg_ch> vl_in[5][9],
						ap_uint<seg_ch> me11a_in[2][3],
						ap_uint<4> cpatr_in[5][9][seg_ch],
						ap_uint<th_hit_w> th_hit_in[5][9],
						ap_uint<bw_fph> ph[5][9][seg_ch],
						ap_uint<bw_th> th11[2][3][th_ch11],
						ap_uint<bw_th> th[5][9][seg_ch],
						ap_uint<seg_ch> vl[5][9],
						ap_uint<3> phzvl[5][9],
						ap_uint<seg_ch> me11a[2][3],
						ap_uint<4> cpatr[5][9][seg_ch],
						ap_uint<ph_hit_w> ph_hit[5][9],
						ap_uint<th_hit_w> th_hit[5][9]*/) ;


	 //Zone hit Extender
	 void extend_sector(   ap_uint<ph_raw_w> ph_zone[4][5],
	 			  ap_uint<ph_raw_w>	ph_ext[4][5],
	 			ap_uint<3> drifttime);

     //Phi Pattern Detectors
	 void ph_pattern_sector(/*ap_uint<1> en,*/
	 		ap_uint<ph_raw_w> st[4][5],
	         ap_uint<3> drifttime,
	         ap_uint<3> foldn,// number of current fold
	         ap_uint<6> qcode[4][ph_raw_w]);// quality codes output [zone][key_strip]
	 									  // quality code pattern numbers [zone][key_strip]

	 //Sorter module
	 void sort_sector(ap_uint<bwr> ph_rank[4][ph_raw_w],
	 				 ap_uint<bpow+1> ph_num[4][3],
	 				 ap_uint<bwr> ph_q[4][3]);



	 //Coord_delay module
	 void co_ord_delay	(ap_uint<bw_fph> phi[6][9][seg_ch],
	 		ap_uint<bw_th> th11i[3][3][th_ch11],
	 		ap_uint<bw_th> thi[6][9][seg_ch],
	 		ap_uint<seg_ch> vli[6][9],
	 		ap_uint<seg_ch> me11ai[3][3],
	 		ap_uint<4> cpati[6][9][seg_ch],
			ap_uint<64> cppf_rxd [7][3], // cppf rx data, 3 frames x 64 bit, for 7 links
			ap_uint<7> cppf_rx_valid, // cppf rx data valid flags

	 		/*outputs*/
	 		ap_uint<bw_fph> pho[max_drift][6][9][seg_ch],
	 		ap_uint<bw_th> th11o[max_drift][3][3][th_ch11],
	 		ap_uint<bw_th>	tho[max_drift][6][9][seg_ch],
	 		ap_uint<seg_ch>	vlo[max_drift][6][9],
	 		ap_uint<seg_ch>	me11ao[max_drift][3][3],
	 		ap_uint<4>	cpato[max_drift][6][9][seg_ch],
	 		ap_uint<4>	dummy[max_drift][6][9][seg_ch]);


	 //match_ph_seg module
		ap_uint<bw_fph> ph_seg___z0_s0_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z0_s0_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z0_s1_reg [max_drift][4][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z0_s1_reg [max_drift][4];
		ap_uint<bw_fph> ph_seg___z0_s2_reg [max_drift][4][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z0_s2_reg [max_drift][4];
		ap_uint<bw_fph> ph_seg___z0_s3_reg [max_drift][4][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z0_s3_reg [max_drift][4];

		ap_uint<bw_fph> ph_seg___z1_s0_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z1_s0_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z1_s1_reg [max_drift][4][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z1_s1_reg [max_drift][4];
		ap_uint<bw_fph> ph_seg___z1_s2_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z1_s2_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z1_s3_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z1_s3_reg [max_drift][7];

		ap_uint<bw_fph> ph_seg___z2_s0_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z2_s0_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z2_s1_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z2_s1_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z2_s2_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z2_s2_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z2_s3_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z2_s3_reg [max_drift][7];

		ap_uint<bw_fph> ph_seg___z3_s0_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z3_s0_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z3_s1_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z3_s1_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z3_s2_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z3_s2_reg [max_drift][7];
		ap_uint<bw_fph> ph_seg___z3_s3_reg [max_drift][7][seg_ch];
		ap_uint<seg_ch> ph_seg_v_z3_s3_reg [max_drift][7];


		ap_uint<bw_th> th_seg___z0_s0_reg [max_drift][7][th_ch11];
		ap_uint<bw_th> th_seg___z0_s1_reg [max_drift][4][seg_ch];
		ap_uint<bw_th> th_seg___z0_s2_reg [max_drift][4][seg_ch];
		ap_uint<bw_th> th_seg___z0_s3_reg [max_drift][4][seg_ch];

		ap_uint<bw_th> th_seg___z1_s0_reg [max_drift][7][th_ch11];
		ap_uint<bw_th> th_seg___z1_s1_reg [max_drift][4][seg_ch];
		ap_uint<bw_th> th_seg___z1_s2_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z1_s3_reg [max_drift][7][seg_ch];

		ap_uint<bw_th> th_seg___z2_s0_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z2_s1_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z2_s2_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z2_s3_reg [max_drift][7][seg_ch];

		ap_uint<bw_th> th_seg___z3_s0_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z3_s1_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z3_s2_reg [max_drift][7][seg_ch];
		ap_uint<bw_th> th_seg___z3_s3_reg [max_drift][7][seg_ch];

		ap_uint<4> cpat_seg___z0_s0_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z0_s1_reg [max_drift][4][seg_ch];
		ap_uint<4> cpat_seg___z0_s2_reg [max_drift][4][seg_ch];
		ap_uint<4> cpat_seg___z0_s3_reg [max_drift][4][seg_ch];

		ap_uint<4> cpat_seg___z1_s0_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z1_s1_reg [max_drift][4][seg_ch];
		ap_uint<4> cpat_seg___z1_s2_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z1_s3_reg [max_drift][7][seg_ch];

		ap_uint<4> cpat_seg___z2_s0_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z2_s1_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z2_s2_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z2_s3_reg [max_drift][7][seg_ch];

		ap_uint<4> cpat_seg___z3_s0_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z3_s1_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z3_s2_reg [max_drift][7][seg_ch];
		ap_uint<4> cpat_seg___z3_s3_reg [max_drift][7][seg_ch];
	 void match_ph_seg(
	 		   // numbers of best ranks [zone][rank number]
	 		    ap_uint<bpow+1> ph_num [4][3],
	 		    // best ranks [zone][rank number]
	 		    ap_uint<6> 	ph_q [4][3],

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
	 			ap_uint<6> 	ph_qr [4][3]);


	//Deltas sector
		void deltas_sector(
				//[zone][pattern_num][station 0-3]
				ap_uint<seg_ch> vi [4][3][4], // valid
				ap_uint<2> 	   hi [4][3][4], // bx index
				ap_uint<3>   ci [4][3][4], // chamber
				ap_uint<4>   si [4][3], // segment
				ap_uint<bw_fph> ph_match [4][3][4], // matching ph
				ap_uint<bw_th>  th_match   [4][3][4][seg_ch], // matching th, 2 segments
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


							);

		//best tracks selector
			void best_tracks(
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


			void ptlut_address(
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
					ap_uint<3> *ptlut_addr_val,
					ap_uint<bwr+1> bt_rank_o [3],

					ap_uint<8> gmt_phi [3],
					ap_uint<9> gmt_eta [3],
					ap_uint<4> gmt_qlt [3],
					ap_uint<3> *gmt_crg,

					ap_uint<3> sector,
					ap_uint<1> endcap,
					ap_uint<1> we);

	void sp(
			ap_uint<seg_ch> vpf[6][9],
			ap_uint<4>         q    [6][9][seg_ch],
		    ap_uint<bw_wg>   wg   [6][9][seg_ch],
		    ap_uint<bw_hs>   hstr [6][9][seg_ch],
		    ap_uint<4>  	   cpat [6][9][seg_ch],

		    ap_uint<9>  	   pcs_cs [6],
		    ap_uint<3>  	   sel,
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
		    ap_uint<3>  *ptlut_addr_val, // ptlut address valid flags
			ap_uint<8>  gmt_phi [3], // phi for gmt
		    ap_uint<9>  gmt_eta [3], // eta for gmt
		    ap_uint<4> gmt_qlt [3], // quality for gmt
			ap_uint<3> *gmt_crg,

			ap_uint<1> endcap,
			ap_uint<3>  sector,
			ap_uint<1> lat_test
			);


};
