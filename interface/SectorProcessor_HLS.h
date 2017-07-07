#ifndef L1TMuonEndCap_SectorProcessor_HLS_h
#define L1TMuonEndCap_SectorProcessor_HLS_h


#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessor.hh"

#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessorLUT.hh"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.hh"
#include "L1Trigger/L1TMuonEndCap/interface/Common.hh"


#include "L1Trigger/L1TMuonEndCap/include/ap_int.h"
#include "L1Trigger/L1TMuonEndCap/interface/sp.h"
#include "L1Trigger/L1TMuonEndCap/interface/spbits.h"
//#include "L1Trigger/L1TMuonEndCap/interface_HLS/primitive.h"
/*
#include "L1Trigger/L1TMuonEndCap/interface_HLS/zones.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/extender.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/ph_pattern.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/sort.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/match_seg.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/deltas.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/best_tracks.h"
#include "L1Trigger/L1TMuonEndCap/interface_HLS/ptlut_address.h"
*/



class SectorProcessor_HLS{
	public:
	
		void configure(const SectorProcessorLUT* lut, 
					   int endcap, int sector, 
					   int verbose, int we);
		
		void process( const SectorProcessorLUT* lut, 
						int endcap, int sector, 
						int verbose, int we,
						const std::map<int, TriggerPrimitiveCollection>& selected_csc_map,
						EMTFHitCollection conv_hits,
						EMTFTrackCollection best_tracks_HLS );
						
	const SectorProcessorLUT& lut_HLS() const; 
 
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
		);
						
							
		//Lut fill flag
			bool lut_filled;
			SectorProcessor_HLS(){
				lut_filled= false;
			}	
			
	private:
		const SectorProcessorLUT* lut_;
		int verbose_, endcap_, sector_;	
		
		ap_uint<seg_ch> vpf [6][9]; 
		ap_uint<4>       qi    [6][9][seg_ch];
	    ap_uint<bw_wg>   wgi   [6][9][seg_ch];
	    ap_uint<bw_hs>   hstri [6][9][seg_ch];
	    ap_uint<4>  	 cpati [6][9][seg_ch];
		
		ap_uint<9>  	  csi [6];
	    ap_uint<2>  	  seli;
	    ap_uint<bw_addr>  addri;

	    ap_uint<13>  r_ini; // ap_uint<> data for memory or ap_uint<>ister
	    ap_uint<13>  r_outo; // output data from memory or ap_uint<>ister
	    ap_uint<1> 	 wei; // write enable for memory or ap_uint<>ister
		
		ap_uint<64> cppf_rxd [7][3]; // cppf rx data, 3 frames x 64 bit, for 7 links
		ap_uint<7> cppf_rx_valid; // cppf rx data valid flags


		ap_uint<bw_fph>  	bt_phi [3];
		ap_uint<bw_th>  	bt_theta [3];
		ap_uint<4>  			bt_cpattern [3][4];
		// ph and th deltas from best stations
		// [best_track_num], last index: [0] - best pair of stations, [1] - second best pair
		ap_uint<bw_fph>  	bt_delta_ph [3][6];
		ap_uint<bw_th>  	bt_delta_th [3][6];
		ap_uint<6>  			bt_sign_ph[3];
		ap_uint<6>  			bt_sign_th[3];
		// ranks [best_track_num]
		ap_uint<bwr+1>  		bt_rank [3];
		// segment IDs
		// [best_track_num][station 0-3]
		ap_uint<seg_ch>  	bt_vi [3][5]; // valid
		ap_uint<2>  			bt_hi [3][5]; // bx index
		ap_uint<4>  			bt_ci [3][5]; // chamber
		ap_uint<5>  			bt_si [3]; // segment
	    ap_uint<1> lat_test=0; // latency test mode
	    ap_uint<1> en_single;
	    ap_uint<30>  ptlut_addr [3]; // ptlut addresses for best 3 muons
	   	ap_uint<32>  ptlut_cs [3]; // pre-decoded chip selects
	   	ap_uint<3>  ptlut_addr_val; // ptlut address valid flags

		ap_uint<8>  gmt_phi [3]; // phi for gmt
	    ap_uint<9>  gmt_eta [3]; // eta for gmt
	    ap_uint<3>  bt_rank_r;
		ap_uint<4> gmt_qlt [3]; // quality for gmt
		ap_uint<3> gmt_crg;
		
		int pr_cnt[6][9];
				
		
			
};



#endif