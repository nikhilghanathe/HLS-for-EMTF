#include <ap_int.h>
#include "spbits.h"



#define zone_cham  6 // 6 chambers in this zone and station
#define zone_seg  th_ch11 // segments per chamber in this zone and station

/*
#define max_ph_diff  (station == 1 ? 15 :7) // max phi difference between pattern and segment
#define bw_phdiff (station == 1 ? 5 : 4) // ph difference bit width
#define tot_diff = max_drift*zone_cham*seg_ch
#define nodiff  (station == 1 ? 31 :15) // invalid difference
*/

class match_seg{



public:
	ap_uint<1> pr;

	void find_segment_st1(
				 ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
					 ap_uint<6> ph_pat_q_p, // pattern valid

				 /* ph from segments [bx_history][chamber][segment],segments are coming from
				  chambers in the interesting zone only for example, in zone 0 ME1 segments
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
				 ap_uint<4> *cpat_match // pattern from matching segmen
				);

	void find_segment_stn1(
					 ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
					 ap_uint<6> ph_pat_q_p, // pattern valid

					 /* ph from segments [bx_history][chamber][segment],segments are coming from
					  chambers in the interesting zone only for example, in zone 0 ME1 segments
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
					 ap_uint<4> *cpat_match // pattern from matching segmen
				);


	void find_segment_1_62(
					 ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
					 ap_uint<6> ph_pat_q_p, // pattern valid

					 /* ph from segments [bx_history][chamber][segment],segments are coming from
					  chambers in the interesting zone only for example, in zone 0 ME1 segments
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
					 ap_uint<4> *cpat_match // pattern from matching segmen
				);

	void find_segment_n1_62(
					 ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
					 ap_uint<6> ph_pat_q_p, // pattern valid

					 /* ph from segments [bx_history][chamber][segment],segments are coming from
					  chambers in the interesting zone only for example, in zone 0 ME1 segments
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
					 ap_uint<4> *cpat_match // pattern from matching segmen
				);


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
				ap_uint<1> 		si [4][3][4], // segment which has matching ph
				ap_uint<bw_fph> ph_match [4][3][4], // matching phi
				// suspected matching th coordinates, all taken from chambers where ph comes from
				// [zone][pattern_num][station 0-3][segment]
				ap_uint<bw_th>	th_match   [4][3][4][zone_seg], // matching th, 2 segments
				ap_uint<bw_th>	th_match11 [2][3][th_ch11], // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
				ap_uint<4> 		cpat_match [4][3][4], // matching patterns
			    // best ranks [zone][rank number]
				ap_uint<6> 	ph_qr [4][3]);

	ap_uint<2> comp3(ap_uint<5> a,ap_uint<5> b,ap_uint<5> c);



};

