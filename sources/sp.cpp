#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/sp.h"
#define MY_CONTROL_MACRO
using namespace std;

#ifndef __SYNTHESIS__
#ifdef MY_CONTROL_MACRO

 void sp_c::sp(ap_uint<seg_ch> vpf[6][9],
		ap_uint<4>         q  [6][9][seg_ch],
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


/////////////////////////////////////USED if need to debug each module outputs//////////////////////////////////////////////////////////////
//		//used for only pcs
//		ap_uint<bw_fph> ph[6][9][seg_ch],
//		ap_uint<bw_th> th11[3][3][th_ch11],
//		ap_uint<bw_th> th[6][9][seg_ch],
//		ap_uint<seg_ch> vl[6][9],
//		ap_uint<3> phzvl[6][9],
//		ap_uint<seg_ch> me11a[3][3],
//		ap_uint<4> cpatr[6][9][seg_ch],
//		ap_uint<ph_hit_w> ph_hit[6][9],
//		ap_uint<th_hit_w> th_hit[6][9],
//	//	ap_uint<12> *r_out,
//		//till here for pcs
//		//Used for zns
//	    ap_uint<ph_raw_w>  ph_zone [4][5],
//		//Used for Extend Sector
//		 ap_uint<ph_raw_w>	ph_ext[4][5],
//		 //Used for phps
//		 ap_uint<6> ph_rank[4][ph_raw_w],
//		 //Used for  sort sector
//			// numbers of best ranks [zone][num]
//		 ap_uint<bpow+1>  ph_num [4][3],
//			// best ranks [zone][num]
//		 ap_uint<bwr>  ph_q [4][3],
//		 //match_ph_seg
//		 ap_uint<seg_ch> vi [4][3][4], // valid (for each segment in chamber, so we can identify which th to use later)
//		 ap_uint<2> 		hi [4][3][4], // bx index
//		 ap_uint<3> 		ci [4][3][4], // chamber
//		 ap_uint<4> 		si [4][3], // segment which has matching ph
//		 ap_uint<bw_fph> ph_match [4][3][4], // matching
//		 ap_uint<bw_th>	th_match   [4][3][4][2*2/*zone_seg*/], // matching th, 2 segments
//		 ap_uint<bw_th>	th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
//		 ap_uint<4> 		cpat_match [4][3][4], // matching patterns
//		 ap_uint<6> 	ph_qr [4][3],
//		 //used for deltas sector
//		 ap_uint<bw_fph> phi [4][3],
//		 ap_uint<bw_th>  theta [4][3],
//		 ap_uint<4> cpattern [4][3][4],
//		 // ph and th deltas from best stations
//		 // [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
//		 ap_uint<bw_fph>  	delta_ph [4][3][6],
//		 ap_uint<bw_th>  	delta_th [4][3][6],
//		 ap_uint<6>  			sign_ph[4][3],
//		 ap_uint<6>  			sign_th[4][3],
//		 // updated ranks [zone][pattern_num]
//		 ap_uint<bwr+1>  		rank [4][3],
//		 //[zone][pattern_num][station 0-3]
//		 ap_uint<seg_ch>  	vir [4][3][4], // valid
//		 ap_uint<2>  			hir [4][3][4], // bx index
//		 ap_uint<3>  			cir [4][3][4], // chamber
//		 ap_uint<4>  			sir [4][3], // segment
///////////////////////////////////////////////////////////////////////////////////////////////////


		 //used for best_tracks
		ap_uint<bw_fph>	 bt_phi [3],
		ap_uint<bw_th>	 bt_theta [3],
		// [best_track_num][station]
		ap_uint<4>	   	 bt_cpattern [3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  bt_delta_ph [3][6],
		ap_uint<bw_th> 	 bt_delta_th [3][6],
		ap_uint<6>    	 bt_sign_ph[3],
		ap_uint<6>	  	 bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1> 	 bt_rank [3],
		//[best_track_num][station 0-3]
		ap_uint<seg_ch>	 bt_vi [3][5], // valid
		ap_uint<2>	   	 bt_hi [3][5], // bx index
		ap_uint<4>   	 bt_ci [3][5], // chamber
		ap_uint<5>   	 bt_si [3], // segment

		//used for ptlut
	    ap_uint<30>  ptlut_addr [3], // ptlut addresses for best 3 muons
	    ap_uint<32>  ptlut_cs [3], // pre-decoded chip selects
	    ap_uint<3>   *ptlut_addr_val, // ptlut address valid flags
		ap_uint<8>   gmt_phi [3], // phi for gmt
	    ap_uint<9>   gmt_eta [3], // eta for gmt
	    ap_uint<4>   gmt_qlt [3], // quality for gmt
		ap_uint<3>   *gmt_crg,

		ap_uint<1>  endcap,
		ap_uint<3>  sector,
		ap_uint<1>  lat_test



		){
#endif
#else

 void sp(ap_uint<seg_ch> vpf[6][9],
		ap_uint<4>         q  [6][9][seg_ch],
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


/////////////////////////////////////USED if need to debug each module outputs//////////////////////////////////////////////////////////////
//		//used for only pcs
//		ap_uint<bw_fph> ph[6][9][seg_ch],
//		ap_uint<bw_th> th11[3][3][th_ch11],
//		ap_uint<bw_th> th[6][9][seg_ch],
//		ap_uint<seg_ch> vl[6][9],
//		ap_uint<3> phzvl[6][9],
//		ap_uint<seg_ch> me11a[3][3],
//		ap_uint<4> cpatr[6][9][seg_ch],
//		ap_uint<ph_hit_w> ph_hit[6][9],
//		ap_uint<th_hit_w> th_hit[6][9],
//	//	ap_uint<12> *r_out,
//		//till here for pcs
//		//Used for zns
//	    ap_uint<ph_raw_w>  ph_zone [4][5],
//		//Used for Extend Sector
//		 ap_uint<ph_raw_w>	ph_ext[4][5],
//		 //Used for phps
//		 ap_uint<6> ph_rank[4][ph_raw_w],
//		 //Used for  sort sector
//			// numbers of best ranks [zone][num]
//		 ap_uint<bpow+1>  ph_num [4][3],
//			// best ranks [zone][num]
//		 ap_uint<bwr>  ph_q [4][3],
//		 //match_ph_seg
//		 ap_uint<seg_ch> vi [4][3][4], // valid (for each segment in chamber, so we can identify which th to use later)
//		 ap_uint<2> 		hi [4][3][4], // bx index
//		 ap_uint<3> 		ci [4][3][4], // chamber
//		 ap_uint<4> 		si [4][3], // segment which has matching ph
//		 ap_uint<bw_fph> ph_match [4][3][4], // matching
//		 ap_uint<bw_th>	th_match   [4][3][4][2*2/*zone_seg*/], // matching th, 2 segments
//		 ap_uint<bw_th>	th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
//		 ap_uint<4> 		cpat_match [4][3][4], // matching patterns
//		 ap_uint<6> 	ph_qr [4][3],
//		 //used for deltas sector
//		 ap_uint<bw_fph> phi [4][3],
//		 ap_uint<bw_th>  theta [4][3],
//		 ap_uint<4> cpattern [4][3][4],
//		 // ph and th deltas from best stations
//		 // [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
//		 ap_uint<bw_fph>  	delta_ph [4][3][6],
//		 ap_uint<bw_th>  	delta_th [4][3][6],
//		 ap_uint<6>  			sign_ph[4][3],
//		 ap_uint<6>  			sign_th[4][3],
//		 // updated ranks [zone][pattern_num]
//		 ap_uint<bwr+1>  		rank [4][3],
//		 //[zone][pattern_num][station 0-3]
//		 ap_uint<seg_ch>  	vir [4][3][4], // valid
//		 ap_uint<2>  			hir [4][3][4], // bx index
//		 ap_uint<3>  			cir [4][3][4], // chamber
//		 ap_uint<4>  			sir [4][3], // segment
///////////////////////////////////////////////////////////////////////////////////////////////////


		 //used for best_tracks
		ap_uint<bw_fph>	 bt_phi [3],
		ap_uint<bw_th>	 bt_theta [3],
		// [best_track_num][station]
		ap_uint<4>	   	 bt_cpattern [3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph>  bt_delta_ph [3][6],
		ap_uint<bw_th> 	 bt_delta_th [3][6],
		ap_uint<6>    	 bt_sign_ph[3],
		ap_uint<6>	  	 bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr+1> 	 bt_rank [3],
		//[best_track_num][station 0-3]
		ap_uint<seg_ch>	 bt_vi [3][5], // valid
		ap_uint<2>	   	 bt_hi [3][5], // bx index
		ap_uint<4>   	 bt_ci [3][5], // chamber
		ap_uint<5>   	 bt_si [3], // segment

		//used for ptlut
	    ap_uint<30>  ptlut_addr [3], // ptlut addresses for best 3 muons
	    ap_uint<32>  ptlut_cs [3], // pre-decoded chip selects
	    ap_uint<3>   *ptlut_addr_val, // ptlut address valid flags
		ap_uint<8>   gmt_phi [3], // phi for gmt
	    ap_uint<9>   gmt_eta [3], // eta for gmt
	    ap_uint<4>   gmt_qlt [3], // quality for gmt
		ap_uint<3>   *gmt_crg,

		ap_uint<1>  endcap,
		ap_uint<3>  sector,
		ap_uint<1>  lat_test



		)


{

 // this is for generating registers at outputs

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

//This is for avoiding unnecessary input registering
#pragma HLS INTERFACE ap_stable port=q
#pragma HLS INTERFACE ap_stable port=hstr
#pragma HLS INTERFACE ap_stable port=cpat
#pragma HLS INTERFACE ap_stable port=wg
#pragma HLS INTERFACE ap_stable port=pcs_cs
#pragma HLS INTERFACE ap_stable port=we
#pragma HLS INTERFACE ap_stable port=r_in
#pragma HLS INTERFACE ap_stable port=endcap
#pragma HLS INTERFACE ap_stable port=lat_test
#pragma HLS INTERFACE ap_stable port=sector
#pragma HLS INTERFACE ap_stable port=sel

#endif

 // coordinates [station][chamber][segment]
	ap_uint<bw_fph>  ph_t   [6][9][seg_ch];
	ap_uint<bw_th>   th11_t [6][3][th_ch11];
	ap_uint<bw_th>   th_t   [6][9][seg_ch];
	ap_uint<seg_ch>  vl_t   [6][9];
	ap_uint<3>  	 phzvl_t[6][9];
	ap_uint<seg_ch>  me11a_t [3][3];
	ap_uint<4>  	 cpatr_t [6][9][seg_ch];

 // ph and th raw hits [station][chamber]
	 ap_uint<ph_hit_w>  ph_hit_t [6][9];
	 ap_uint<th_hit_w>  th_hit_t [6][9];
	 ap_uint<ph_raw_w>  ph_zone_t [4][5];
	 ap_uint<ph_raw_w>  ph_zone_t_s [20];
	 ap_uint<ph_raw_w>	ph_ext_t[4][5];
	 ap_uint<ph_raw_w>	ph_ext_t_s[20];
	 ap_uint<6>         ph_rank_t[4][ph_raw_w];
	 ap_uint<bpow+1>    ph_num_t [4][3];
	 ap_uint<bwr>       ph_q_t [4][3];

	 ap_uint<12> r_out_t;

	ap_uint<bw_fph> phd[max_drift][6][9][seg_ch];
	ap_uint<bw_th> th11d[max_drift][3][3][th_ch11];
	ap_uint<bw_th>	thd[max_drift][6][9][seg_ch];
	ap_uint<seg_ch>	vld[max_drift][6][9];
	ap_uint<seg_ch>	me11ad[max_drift][3][3];
	ap_uint<4>	cpatd[max_drift][6][9][seg_ch];
	ap_uint<4>	dummy[max_drift][6][9][seg_ch];

		// find_segment outputs, in terms of segments match in zones [zone][pattern_num][station 0-3]
 	ap_uint<seg_ch>  patt_ph_vi [4][3][4]; // valid
 	ap_uint<2>  	 patt_ph_hi [4][3][4]; // bx index
 	ap_uint<3>  	 patt_ph_ci [4][3][4]; // chamber
 	ap_uint<4>  	 patt_ph_si [4][3]; // segment
 	ap_uint<bw_fph>  ph_match_t [4][3][4]; // matching ph
 	ap_uint<bw_th> 	 th_match_t   [4][3][4][4]; // matching th, 2 segments
 	ap_uint<bw_th> 	 th_match_t1   [4][3][4][seg_ch]; // matching th, 2 segments
 	ap_uint<bw_th> 	 th_match11_t [3][3][th_ch11]; // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
 	ap_uint<4>  	 cpat_match_t [4][3][4]; // matching patter
    ap_uint<6> 	     ph_qr_t [4][3];

	ap_uint<bw_fph>	 bt_phi_t [3];
	ap_uint<bw_th>	 bt_theta_t [3];
	// [best_track_num][station]
	ap_uint<4>	   	 bt_cpattern_t [3][4];
	// ph and th deltas from best stations
	// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
	ap_uint<bw_fph>  bt_delta_ph_t [3][6];
	ap_uint<bw_th> 	 bt_delta_th_t [3][6];
	ap_uint<6>    	 bt_sign_ph_t[3];
	ap_uint<6>	  	 bt_sign_th_t[3];
	// ranks [best_track_num]
	ap_uint<bwr+1> 	 bt_rank_t [3];
	//[best_track_num][station 0-3]
	ap_uint<seg_ch>	 bt_vi_t [3][5]; // valid
	ap_uint<2>	   	 bt_hi_t [3][5]; // bx index
	ap_uint<4>   	 bt_ci_t [3][5]; // chamber
	ap_uint<5>   	 bt_si_t [3]; // segment

	ap_uint<bw_fph>  phi_t [4][3];
	ap_uint<bw_th>   theta_t [4][3];
	ap_uint<4> 	     cpattern_t [4][3][4];


	 // ph and th deltas from best stations
	 // [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
	ap_uint<bw_fph>  delta_ph_t [4][3][6];
	ap_uint<bw_th>   delta_th_t [4][3][6];
	ap_uint<6>  	 sign_ph_t[4][3];
	ap_uint<6>  	 sign_th_t[4][3];
	// updated ranks [zone][pattern_num]
	ap_uint<bwr+1>   rank_t [4][3];
	//[zone][pattern_num][station 0-3]
	ap_uint<seg_ch>  vir_t [4][3][4]; // valid
	ap_uint<2>  	 hir_t [4][3][4]; // bx index
	ap_uint<3>  	 cir_t [4][3][4]; // chamber
	ap_uint<4>  	 sir_t [4][3]; // segment



	ap_uint<3> drifttime=3;
	ap_uint<3> ph_foldn=0;
	ap_uint<bw_th> th_window=4;

	//static objects for each module to maintain persistence
	static sp_c pcs;
	static sp_c zns;
	static sp_c exts;
	static sp_c phps;
 	static sp_c srts;
 	static sp_c cdl;
 	static sp_c mphseg;
 	static sp_c ds;
 	static sp_c bt;
 	static sp_c pta;

//	static ap_uint<ph_raw_w>  ph_ext_reg [4][5];
//	static ap_uint<6> ph_rank_reg[4][ph_raw_w];
//	static ap_uint<bpow+1>  ph_num_reg [4][3];
//	static ap_uint<bwr>  ph_q_reg [4][3];

/************************START SP*******************************************************/


/************************prim_conv_sector*************************************/

	pcs.prim_conv_sector(
			vpf,q, wg, hstr, cpat,
			ph_t, th11_t, th_t,	vl_t, phzvl_t, me11a_t,	cpatr_t,
			ph_hit_t, th_hit_t, &r_out_t,
			sel, addr, r_in, we, endcap, lat_test, pcs_cs
			 );
/************************************************************/

#ifndef __SYNTHESIS__
	 if(this->pr){
		 for(int i=0;i<6;i++){
			 for(int j=0;j<9;j++){
				 for(int k=0;k<2;k++){
					 if(ph_t[i][j][k]!=0)
						 cout<<"ph["<<i<<"]["<<j<<"]["<<k<<"]= "<<ph_t[i][j][k]<<endl;
				 }
			 }
		 }

	 }
#endif

/********************START FLOATING REGION*************************************/

   	{
	#pragma HLS PROTOCOL floating

 			cdl.co_ord_delay(
 			 ph_t,  th11_t, th_t,  vl_t,
 			 me11a_t, cpatr_t, cppf_rxd, cppf_rx_valid,
 			 phd, th11d, thd, vld, me11ad, cpatd, dummy
 			 );


//////////////////////////zones/////////////////////////////////////////////
		zns.zones(phzvl_t,
				  ph_hit_t,
				  ph_zone_t
			);
///////////////////////////extender////////////////////////////////////////////

		exts.extend_sector(
				ph_zone_t,
				ph_ext_t,
				drifttime);


//////////////////////////ph_pattern_Sector/////////////////////////////////////////////

		phps.ph_pattern_sector(ph_ext_t,
				drifttime,
				ph_foldn,
				ph_rank_t);


//////////////////////////sort_sector/////////////////////////////////////////////

		srts.sort_sector(ph_rank_t,
						ph_num_t,
						ph_q_t);

   	}
/********************END FLOATING REGION*************************************/


#ifndef __SYNTHESIS__
 if(this->pr){
	 for(int i=0;i<4;i++){
		 for(int j=0;j<3;j++){
			 if(ph_num_t[i][j]!=0x7f)
				 cout<<"ph_num["<<i<<"]["<<j<<"]= "<<ph_num_t[i][j]<<endl;
			 if(ph_q_t[i][j]!=0)
			 				 cout<<"ph_q["<<i<<"]["<<j<<"]= "<<ph_q_t[i][j]<<endl;
			 }
	 }

 }
#endif



 /*************************match_ph_segments*****************************************************************/
 {


#pragma HLS PROTOCOL fixed

 	mphseg.match_ph_seg(
 		     ph_num_t, ph_q_t,
 		     phd, vld, th11d, thd, cpatd,
			 patt_ph_vi, patt_ph_hi, patt_ph_ci, patt_ph_si,
			 ph_match_t, th_match_t, th_match11_t, cpat_match_t, ph_qr_t
 			 );

 }

#ifndef __SYNTHESIS__
 if(this->pr){
	 for(int i=0;i<4;i++){
		 for(int j=0;j<3;j++){
			 for(int k=0;k<4;k++){
				 if(ph_match_t[i][j][k]!=0)
					 cout<<"ph_match["<<i<<"]["<<j<<"]["<<k<<"]= "<<ph_match_t[i][j][k]<<endl;
			 }
		 }
	 }

 }
#endif

//Assign th_match_t to th_match_t1 to match the array dimensions for deltas_sector
	for(int i=0;i<4;i++){
		#pragma HLS UNROLL
				for(int j=0;j<3;j++){
		#pragma HLS UNROLL
					for(int k=0;k<4;k++){
		#pragma HLS UNROLL
						for(int l=0; l<seg_ch;l++){
							th_match_t1[i][j][k][l]=th_match_t[i][j][k][l];
						}
					}
				}
			}

/********************************deltas_sector****************************************************/
	{
#pragma HLS PROTOCOL fixed

	ds.deltas_sector(
	   patt_ph_vi, patt_ph_hi, patt_ph_ci, patt_ph_si,
	   ph_match_t, th_match_t1, cpat_match_t, ph_qr_t, th_window,
	   phi_t, theta_t, cpattern_t, delta_ph_t, delta_th_t,
	   sign_ph_t, sign_th_t, rank_t,
	   vir_t, hir_t, cir_t, sir_t
	   );
	}
/********************************best_tracks****************************************************/



	{
#pragma HLS PROTOCOL fixed
	bt.best_tracks(
		phi_t, theta_t, cpattern_t,	delta_ph_t, delta_th_t,
		sign_ph_t, sign_th_t,rank_t,
		patt_ph_vi, patt_ph_hi, patt_ph_ci, patt_ph_si,
		bt_phi_t, bt_theta_t, bt_cpattern_t, bt_delta_ph_t,	bt_delta_th_t,
		bt_sign_ph_t, bt_sign_th_t,	bt_rank_t,
		bt_vi_t, bt_hi_t, bt_ci_t, bt_si_t
		);

	}
/**********************************ptut_address**************************************************/

	{
#pragma HLS PROTOCOL fixed
	    pta.ptlut_address(
	        bt_phi_t, bt_theta_t, bt_cpattern_t, bt_delta_ph_t, bt_delta_th_t,
	        bt_sign_ph_t, bt_sign_th_t, bt_rank_t,
			bt_vi_t, bt_hi_t, bt_ci_t, bt_si_t,
			0,//vl_single
			0,//ph_single
	        0,//th_single
	        ptlut_addr,  ptlut_cs, ptlut_addr_val, bt_rank,
			gmt_phi, gmt_eta, gmt_qlt, gmt_crg,
	        sector, endcap, we
	    	);
	}

/*******************************END SP***********************************************/


/*******************ASSIGN OUTPUTS*********************************************/



		for(int i=0;i<3;i++){
	#pragma HLS UNROLL
			bt_phi[i]=bt_phi_t[i];
			bt_theta[i]=bt_theta_t[i];
			bt_sign_ph[i]=bt_sign_ph_t[i];
			bt_sign_th[i]=bt_sign_th_t[i];
			bt_rank[i]=bt_rank_t[i];
			bt_si[i]=bt_si_t[i];
					}

		for(int i=0;i<3;i++){
			#pragma HLS UNROLL
				for(int j=0;j<4;j++){
			#pragma HLS UNROLL
					bt_cpattern[i][j]=bt_cpattern_t[i][j];
					}
				}

		for(int i=0;i<3;i++){
			#pragma HLS UNROLL
				for(int j=0;j<6;j++){
			#pragma HLS UNROLL
					bt_delta_ph[i][j]=bt_delta_ph_t[i][j];
					bt_delta_th[i][j]=bt_delta_th_t[i][j];
					}
				}

		for(int i=0;i<3;i++){
			#pragma HLS UNROLL
				for(int j=0;j<5;j++){
			#pragma HLS UNROLL
					bt_vi[i][j]=bt_vi_t[i][j];
					bt_hi[i][j]=bt_hi_t[i][j];
					bt_ci[i][j]=bt_ci_t[i][j];

					}
				}

/////////////////////////USED if need to debug module outputs////////////////////////
//	for(int i=0;i<6;i++){
//	#pragma HLS UNROLL
//			for(int j=0;j<9;j++){
//	#pragma HLS UNROLL
//				ph_hit[i][j]=ph_hit_t[i][j];
//				th_hit[i][j]=th_hit_t[i][j];
//				phzvl[i][j]=phzvl_t[i][j];
//				vl[i][j]=vl_t[i][j];
//				for(int k=0;k<seg_ch;k++){
//	#pragma HLS UNROLL
//					ph[i][j][k]=ph_t[i][j][k];
//					th[i][j][k]=th_t[i][j][k];
//					cpatr[i][j][k]=cpatr_t[i][j][k];
//				}
//			}
//		}
//		for(int i=0;i<3;i++){
//	#pragma HLS UNROLL
//			for(int j=0;j<3;j++){
//	#pragma HLS UNROLL
//				me11a[i][j]=me11a_t[i][j];
//				for(int k=0;k<th_ch11;k++){
//	#pragma HLS UNROLL
//					th11[i][j][k]=th11_t[i][j][k];
//				}
//			}
//		}
//
//	 for(int i=0;i<4;i++){
//#pragma HLS UNROLL
//	for(int j=0;j<5;j++){
//#pragma HLS UNROLL
//		ph_zone[i][j]=ph_zone_t[i][j];
//		ph_ext[i][j]=ph_ext_t[i][j];
//	}
// }
//		  for(int i=0;i<4;i++){
//#pragma HLS UNROLL
//				for(int j=0;j<ph_raw_w;j++){
//#pragma HLS UNROLL
//					ph_rank[i][j]=ph_rank_t[i][j];
//				}
//			  }
//			  for(int i=0;i<4;i++){
//#pragma HLS UNROLL
//				for(int j=0;j<3;j++){
//#pragma HLS UNROLL
//					ph_num[i][j]=ph_num_t[i][j];
//					ph_q[i][j]=ph_q_t[i][j];
//				}
//			  }
//		for(int i=0;i<4;i++){
//			#pragma HLS UNROLL
//					for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//						si[i][j]=patt_ph_si[i][j];
//						ph_qr[i][j]=ph_qr_t[i][j];
//						for(int k=0;k<4;k++){
//			#pragma HLS UNROLL
//							vi[i][j][k]=patt_ph_vi[i][j][k];
//							hi[i][j][k]=patt_ph_hi[i][j][k];
//							ci[i][j][k]=patt_ph_ci[i][j][k];
//							ph_match[i][j][k]=ph_match_t[i][j][k];
//							cpat_match[i][j][k]=cpat_match_t[i][j][k];
//						}
//					}
//				}
//		for(int i=0;i<2;i++){
//			#pragma HLS UNROLL
//					for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//						for(int k=0;k<4;k++){
//			#pragma HLS UNROLL
//						th_match11[i][j][k]=th_match11_t[i][j][k];
//						}
//					}
//				}
//		for(int i=0;i<4;i++){
//			#pragma HLS UNROLL
//					for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//						for(int k=0;k<4;k++){
//			#pragma HLS UNROLL
//							for(int l=0; l<2;l++){
//								th_match[i][j][k][l]=th_match_t1[i][j][k][l];
//							}
//						}
//					}
//				}
//
//
//
//
//		for(int i=0;i<4;i++){
//			#pragma HLS UNROLL
//				for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//				phi[i][j]=phi_t[i][j];
//				theta[i][j]=theta_t[i][j];
//				rank[i][j]=rank_t[i][j];
//				sir[i][j]=sir_t[i][j];
//				sign_ph[i][j]=sign_ph_t[i][j];
//				sign_th[i][j]=sign_th_t[i][j];
//					}
//				}
//		for(int i=0;i<4;i++){
//			#pragma HLS UNROLL
//					for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//						for(int k=0;k<6;k++){
//			#pragma HLS UNROLL
//					delta_ph[i][j][k]=delta_ph_t[i][j][k];
//					delta_th[i][j][k]=delta_th_t[i][j][k];
//						}
//					}
//				}
//		for(int i=0;i<4;i++){
//			#pragma HLS UNROLL
//					for(int j=0;j<3;j++){
//			#pragma HLS UNROLL
//						for(int k=0;k<4;k++){
//			#pragma HLS UNROLL
//					vir[i][j][k]=vir_t[i][j][k];
//					hir[i][j][k]=hir_t[i][j][k];
//					cir[i][j][k]=cir_t[i][j][k];
//					cpattern[i][j][k]=cpattern_t[i][j][k];
//						}
//					}
//				}




 	}


