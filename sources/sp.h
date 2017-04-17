#include <ap_int.h>
#include "spbits.h"

class sp_c{

public:


	ap_uint<bw_fph>  ph   [5][9][seg_ch];
		    ap_uint<bw_th>  	th11 [2][3][th_ch11];
		    ap_uint<bw_th>  	th   [5][9][seg_ch];
		    ap_uint<seg_ch>  vl   [5][9];

		    ap_uint<ph_raw_w>  ph_zone [4][5];


	//Primitive Converter
	void prim_conv_sector(/*inputs*/
							ap_uint<4>  q[5][9][seg_ch],
							ap_uint<bw_wg> wg[5][9][seg_ch],
							ap_uint<bw_hs> hstr[5][9][seg_ch],
							ap_uint<4>  cpat[5][9][seg_ch],

							/*outputs*/
							 ap_uint<bw_fph> ph[5][9][seg_ch],
							 ap_uint<bw_th> th11[2][3][th_ch11],
							 ap_uint<bw_th> th[5][9][seg_ch],
							 ap_uint<seg_ch>  vl[5][9],
							 ap_uint<3>  phzvl[5][9],
							 ap_uint<seg_ch>   me11a[2][3],
							 ap_uint<4>  cpatr[5][9][seg_ch],
							 ap_uint<ph_hit_w>	ph_hit[5][9],
							 ap_uint<th_hit_w> th_hit[5][9],
							 ap_uint<12> *r_out,

							/*inputs*/
							ap_uint<2> sel,
							ap_uint<bw_addr> addr,
							ap_uint<12> r_in,
							ap_uint<1> we,
							ap_uint<1> endcap,
							ap_uint<1> lat_test,
							ap_uint<1> print_flag,
							ap_uint<9> cs[5]
							  );



	//Zone image formation
	 void zones ( ap_uint<3> phzvl_in[5][9],
			  ap_uint<ph_hit_w> ph_hit_in[5][9],
		    	 ap_uint<ph_raw_w> ph_zone[4][5]) ;


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
	 void co_ord_delay(ap_uint<bw_fph> phi[5][9][seg_ch],
				ap_uint<bw_th> th11i[2][3][th_ch11],
				ap_uint<bw_th> thi[5][9][seg_ch],
				ap_uint<seg_ch> vli[5][9],
				ap_uint<seg_ch> me11ai[2][3],
				ap_uint<4> cpati[5][9][seg_ch],
				/*outputs*/
				ap_uint<bw_fph> pho[max_drift][5][9][seg_ch],
				ap_uint<bw_th> th11o[max_drift][2][3][th_ch11],
				ap_uint<bw_th>	tho[max_drift][5][9][seg_ch],
				ap_uint<seg_ch>	vlo[max_drift][5][9],
				ap_uint<seg_ch>	me11ao[max_drift][2][3],
				ap_uint<4>	cpato[max_drift][5][9][seg_ch],
				ap_uint<4>	dummy[max_drift][5][9][seg_ch]);


	 //match_ph_seg module
		void match_ph_seg(
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
					ap_uint<bw_th>	th_match   [4][3][4][2*2/*zone_seg*/], // matching th, 2 segments
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
				ap_uint<bw_th>  th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
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


		//ptlut address
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



};

