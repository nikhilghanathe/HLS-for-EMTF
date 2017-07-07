#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"

#define zone_cham  7 // 6 chambers in this zone and station
#define zone_seg  th_ch11 // segments per chamber in this zone and station


class match_seg{
public:
	ap_uint<1> pr;

	//registers
//	ap_uint<bw_fph> ph_pat; // ph detected in pattern
//	ap_uint<1>		ph_pat_v; // pattern valid
//	ap_uint<bw_fph> ph_seg [max_drift][zone_cham][seg_ch];
//	ap_uint<seg_ch> ph_seg_v [max_drift][zone_cham];
//	ap_uint<bw_th>  th_seg [max_drift][zone_cham][zone_seg];
//	ap_uint<4>	 	cpat_seg [max_drift][zone_cham][seg_ch];


	void find_segment_st1_7_2(
		int ki,
		ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
		ap_uint<6>   	ph_pat_q_p, // pattern valid
		// ph from segments [bx_history][chamber][segment]
		// segments are coming from chambers in the interesting zone only
		// for example, in zone 0 ME1 segments should come from chambers
		// subsector1: 1,2,3, subsector2: 1,2,3
		ap_uint<bw_fph> ph_seg_p [max_drift][zone_cham][seg_ch],
		// valid flags for segments
		ap_uint<seg_ch> ph_seg_v_p [max_drift][zone_cham],
		ap_uint<bw_th>  th_seg_p [max_drift][zone_cham][/*zone_seg*/2], // theta
		ap_uint<4>      cpat_seg_p [max_drift][zone_cham][seg_ch], // patterns

		// indexes of best match
		ap_uint<seg_ch> *vid, // match valid, each flag shows validity of th coord
		ap_uint<2> 		*hid, // history id
		ap_uint<3> 		*cid, // chamber id
		ap_uint<1> 		*sid, // segment id
		ap_uint<bw_fph> *ph_match, // ph from matching segment
		// all th's from matching chamber, we don't know which one will fit best
		// rework per Jia Fu request 2016-10-18
		ap_uint<bw_th>  th_match [seg_ch],
		ap_uint<4> 		*cpat_match // pattern from matching segment

		);

	void find_segment_st1_7_4(
		ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
		ap_uint<6>   	ph_pat_q_p, // pattern valid
		// ph from segments [bx_history][chamber][segment]
		// segments are coming from chambers in the interesting zone only
		// for example, in zone 0 ME1 segments should come from chambers
		// subsector1: 1,2,3, subsector2: 1,2,3
		ap_uint<bw_fph> ph_seg_p [max_drift][zone_cham][seg_ch],
		// valid flags for segments
		ap_uint<seg_ch> ph_seg_v_p [max_drift][zone_cham],
		ap_uint<bw_th>  th_seg_p [max_drift][zone_cham][zone_seg], // theta
		ap_uint<4>    	cpat_seg_p [max_drift][zone_cham][seg_ch], // patterns

		// indexes of best match
		ap_uint<seg_ch> *vid, // match valid, each flag shows validity of th coord
		ap_uint<2> 		*hid, // history id
		ap_uint<3> 		*cid, // chamber id
		ap_uint<1> 		*sid, // segment id
		ap_uint<bw_fph> *ph_match, // ph from matching segment
		// all th's from matching chamber, we don't know which one will fit best
		// rework per Jia Fu request 2016-10-18
		ap_uint<bw_th>  th_match [seg_ch],
		ap_uint<4> 		*cpat_match // pattern from matching segment

		);

	void find_segment_stn1_7_2(
			int ki,
		ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
		ap_uint<6>   	ph_pat_q_p, // pattern valid
		// ph from segments [bx_history][chamber][segment]
		// segments are coming from chambers in the interesting zone only
		// for example, in zone 0 ME1 segments should come from chambers
		// subsector1: 1,2,3, subsector2: 1,2,3
		ap_uint<bw_fph> ph_seg_p [max_drift][zone_cham][seg_ch],
		// valid flags for segments
		ap_uint<seg_ch> ph_seg_v_p [max_drift][zone_cham],
		ap_uint<bw_th>  th_seg_p [max_drift][zone_cham][/*zone_seg*/2], // theta
		ap_uint<4>    	cpat_seg_p [max_drift][zone_cham][seg_ch], // patterns

		// indexes of best match
		ap_uint<seg_ch> *vid, // match valid, each flag shows validity of th coord
		ap_uint<2> 		*hid, // history id
		ap_uint<3> 		*cid, // chamber id
		ap_uint<1> 		*sid, // segment id
		ap_uint<bw_fph> *ph_match, // ph from matching segment
		// all th's from matching chamber, we don't know which one will fit best
		// rework per Jia Fu request 2016-10-18
		ap_uint<bw_th>  th_match [seg_ch],
		ap_uint<4> 		*cpat_match // pattern from matching segment

		);


	void find_segment_stn1_4_2(
		ap_uint<bpow+1> ph_pat_p, // ph detected in pattern
		ap_uint<6>   	ph_pat_q_p, // pattern valid
		// ph from segments [bx_history][chamber][segment]
		// segments are coming from chambers in the interesting zone only
		// for example, in zone 0 ME1 segments should come from chambers
		// subsector1: 1,2,3, subsector2: 1,2,3
		ap_uint<bw_fph> ph_seg_p [max_drift][/*zone_cham*/4][seg_ch],
		// valid flags for segments
		ap_uint<seg_ch> ph_seg_v_p [max_drift][/*zone_cham*/4],
		ap_uint<bw_th>  th_seg_p [max_drift][/*zone_cham*/4][/*zone_seg*/2], // theta
		ap_uint<4>    	cpat_seg_p [max_drift][/*zone_cham*/4][seg_ch], // patterns

		// indexes of best match
		ap_uint<seg_ch> *vid, // match valid, each flag shows validity of th coord
		ap_uint<2> 		*hid, // history id
		ap_uint<3> 		*cid, // chamber id
		ap_uint<1> 		*sid, // segment id
		ap_uint<bw_fph> *ph_match, // ph from matching segment
		// all th's from matching chamber, we don't know which one will fit best
		// rework per Jia Fu request 2016-10-18
		ap_uint<bw_th>  th_match [seg_ch],
		ap_uint<4> 		*cpat_match // pattern from matching segment
		);




	ap_uint<2> comp3(ap_uint<5> a,ap_uint<5> b,ap_uint<5> c);



};

