#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/match_seg.h"

using namespace std;


void match_seg::find_segment_st1_7_2(
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

	)

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS LATENCY max=1

    // max phi difference between pattern and segment
    const int max_ph_diff = 496;//' : // width of pattern in ME1 + rounding error 15*32+16 //                          station == 2 ? 13'd16 : // just rounding error for ME2 (pattern must match ME2 hit phi if there was one)
                            //240; // width of pattern in ME3,4 + rounding error 7*32+16

    const int bw_phdiff = 9 ; // ph difference bit width

	const int tot_diff = max_drift*zone_cham*seg_ch;
	// sorter stages
	const int stage1 = (tot_diff /3) + 1; // 9 or 15
	const int stage2 = (stage1 == 9) ? 3 : 6;
	const int stage3 = stage2 / 3; // 1 or 2

    const int nodiff = 0x1ff ; // invalid difference



	int i,j,k,di;
	//registers
	ap_uint<bw_fph> ph_pat; // ph detected in pattern
	ap_uint<1>		ph_pat_v; // pattern valid
	ap_uint<bw_fph> ph_seg [max_drift][zone_cham][seg_ch];
	ap_uint<seg_ch> ph_seg_v [max_drift][zone_cham];
	ap_uint<bw_th>  th_seg [max_drift][zone_cham][/*zone_seg*/2];
	ap_uint<4>	 	cpat_seg [max_drift][zone_cham][seg_ch];
    ap_uint<bw_fph>  	ph_segr;
	ap_uint<bw_fph>   	ph_diff_tmp;
	ap_uint<bw_phdiff> 	ph_diff [tot_diff+3]; // create longer array here to provide padding for 3-input comparators
	ap_uint<2> 	 		rcomp;

	ap_uint<6> 	 		diffi0 [tot_diff+3]; // create longer array here to provide padding for 3-input comparators
	ap_uint<bw_phdiff> 	cmp1 [stage1];
	ap_uint<6> 	 		diffi1      [stage1];
	ap_uint<bw_phdiff> 	cmp2 [stage2];
	ap_uint<6> 	 		diffi2      [stage2];
	ap_uint<bw_phdiff> 	cmp3 [stage3];
	ap_uint<6> 	 		diffi3      [stage3];
	ap_uint<bw_phdiff> 	cmp4;
	ap_uint<6> 	 		diffi4;
	ap_uint<2> 	 		ri;
	ap_uint<3> 	 		rj;
	ap_uint<1>	 		rk;

	ap_uint<seg_ch>  a_vid; // match valid, each flag shows validity of th coord
	ap_uint<2> 		 a_hid; // history id
	ap_uint<3> 		 a_cid; // chamber id
	ap_uint<1> 		 a_sid; // segment id


		if(this->pr==1 && ki==0){
			cout<<"ph_pat_v= "<<ph_pat_v<<endl;
		}
		for(int i=0;i<max_drift;i++){
			for(int j=0;j<zone_cham;j++){
				for(int k=0;k<seg_ch;k++){
					if(this->pr==1 && ki==0){
						cout<<"ph_seg["<<i<<"]["<<j<<"]["<<k<<"]= "<<ph_seg[i][j][k]<<endl;
					}
				}
				for(int k=0;k</*zone_seg*/2;k++){
				}

			}
		}



		ph_pat = (ph_pat_p, ap_uint<5>(0)); // add missing 5 lower bits to pattern phi
		ph_pat_v = ph_pat_q_p != 0; // non-zero quality means valid pattern

		for(int i=0;i<max_drift;i++){
			for(int j=0;j<zone_cham;j++){
				ph_seg_v[i][j] = ph_seg_v_p[i][j];
				for(int k=0;k<seg_ch;k++){
					ph_seg[i][j][k] = ph_seg_p[i][j][k];
					cpat_seg[i][j][k] = cpat_seg_p[i][j][k];
				}
				for(int k=0;k</*zone_seg*/2;k++){
					th_seg[i][j][k] = th_seg_p[i][j][k];
				}

			}
		}
		// fill unused differences with max values
		ph_diff[tot_diff+2] = nodiff;
		ph_diff[tot_diff+1] = nodiff;
		ph_diff[tot_diff  ] = nodiff;
		diffi0 [tot_diff+2] = 0x3f; // invalid
		diffi0 [tot_diff+1] = 0x3f; // invalid
		diffi0 [tot_diff  ] = 0x3f; // invalid

		// calculate abs differences
		di = 0;
		for (i = 0; i < max_drift; i = i+1){ // history loop
			for (j = 0; j < zone_cham; j = j+1){ // chamber loop
				for (k = 0; k < seg_ch; k = k+1){ // segment loop
				    ph_segr = ph_seg[i][j][k];

					// get abs difference
					if (ph_seg_v[i][j][k] && ph_pat_v)
 					    ph_diff_tmp = (ph_pat > ph_segr) ? ph_pat - ph_segr : ph_segr - ph_pat;
					else
						ph_diff_tmp = nodiff; // if segment invalid put max value into diff

				    if (ph_diff_tmp > max_ph_diff)
 					    ph_diff[i*zone_cham*seg_ch + j*seg_ch + k] = nodiff; // difference is too high, cannot be the same pattern
				    else
				 	    ph_diff[i*zone_cham*seg_ch + j*seg_ch + k] = ph_diff_tmp(bw_phdiff-1,0);


					ri = i;
					rj = j;
					rk = k;
					// diffi variables carry track indexes
					diffi0[i*zone_cham*seg_ch + j*seg_ch + k] = (ri, rj, rk);
				}
			}
		} // for (i = 0; i < max_drift; i = i+1)

		// sort differences
		// first stage
		for (i = 0; i < stage1; i = i+1){
			// compare 3 values
			rcomp = comp3(ph_diff[i*3], ph_diff[i*3+1], ph_diff[i*3+2]);
			// fill outputs
			switch (rcomp){
			case 0:  cmp1[i] = ph_diff[i*3+0]; diffi1[i] = diffi0[i*3+0]; break;
			case 1:  cmp1[i] = ph_diff[i*3+1]; diffi1[i] = diffi0[i*3+1]; break;
			case 2:  cmp1[i] = ph_diff[i*3+2]; diffi1[i] = diffi0[i*3+2]; break;
			default: break;
			}
		}

		// second stage
		for (i = 0; i < (stage2 == 6 ? 5 : stage2); i = i+1){
			// compare 3 values
			rcomp = comp3(cmp1[i*3], cmp1[i*3+1], cmp1[i*3+2]);
			// fill outputs
			switch (rcomp){
			case 0:  cmp2[i] = cmp1[i*3+0]; diffi2[i] = diffi1[i*3+0]; break;
			case 1:  cmp2[i] = cmp1[i*3+1]; diffi2[i] = diffi1[i*3+1]; break;
			case 2:  cmp2[i] = cmp1[i*3+2]; diffi2[i] = diffi1[i*3+2]; break;
			default: break;
			}
		}

        // fill unused comparator output in case of 7-chamber unit
        if (stage2 == 6){
            cmp2[5] = nodiff;
            diffi2[5] = 0x3f;
        }

		// third stage
		for (i = 0; i < stage3; i = i+1){
			// compare 3 values
            rcomp = comp3(cmp2[i*3], cmp2[i*3+1], cmp2[i*3+2]);
            // fill outputs
            switch (rcomp){
            case 0:  cmp3[i] = cmp2[i*3+0]; diffi3[i] = diffi2[i*3+0]; break;
            case 1:  cmp3[i] = cmp2[i*3+1]; diffi3[i] = diffi2[i*3+1]; break;
            case 2:  cmp3[i] = cmp2[i*3+2]; diffi3[i] = diffi2[i*3+2]; break;
            default: break;
            }
		}

		// last stage depends on number of input segments
		if (stage3 > 1){
			// compare 2 values
			rcomp[0] = cmp3[0] >= cmp3[1];
			// fill outputs
			switch (rcomp[0]){
			case 0:  cmp4 = cmp3[0]; diffi4 = diffi3[0]; break;
			case 1:  cmp4 = cmp3[1]; diffi4 = diffi3[1]; break;
			default: break;
			}
		}
		else
		{
			cmp4 = cmp3[0];
			diffi4 = diffi3[0];
		}


		(a_hid, a_cid, a_sid) = diffi4;
		a_vid = ph_seg_v[a_hid][a_cid][a_sid];
		// if pattern invalid or all differences invalid remove valid flags
		if (!ph_pat_v || cmp4 == nodiff) a_vid = 0;

        *ph_match = ph_seg[a_hid][a_cid][a_sid]; // route best matching phi to output
        if(this->pr && ki==0){
         	cout<<"ph_match= "<<*ph_match<<endl;
         }
          // rework of th_match to remove unphysical thetas, per Jia Fu request 2016-10-18
        if (/*zone_seg*/2 == seg_ch){ // not ME1/1
        	for (i = 0; i < seg_ch; i = i+1){
            	th_match[i] = th_seg[a_hid][a_cid][i]; // route all th coords from matching chamber to output

        	}
        }
        else
        { // ME1/1
            for (i = 0; i < seg_ch; i = i+1){
               th_match[i] = th_seg[a_hid][a_cid][a_sid*seg_ch+i]; // route 2 th coords from matching chamber to output
            }
        }
		*cpat_match = cpat_seg[a_hid][a_cid][a_sid]; // route pattern to output

		*vid=a_vid;
		*hid=a_hid;
		*sid=a_sid;
		*cid=a_cid;

//		ph_pat = (ph_pat_p, ap_uint<5>(0)); // add missing 5 lower bits to pattern phi
//		ph_pat_v = ph_pat_q_p != 0; // non-zero quality means valid pattern
//
//		for(int i=0;i<max_drift;i++){
//			for(int j=0;j<zone_cham;j++){
//				ph_seg_v[i][j] = ph_seg_v_p[i][j];
//				for(int k=0;k<seg_ch;k++){
//					ph_seg[i][j][k] = ph_seg_p[i][j][k];
//					cpat_seg[i][j][k] = cpat_seg_p[i][j][k];
//				}
//				for(int k=0;k</*zone_seg*/2;k++){
//					th_seg[i][j][k] = th_seg_p[i][j][k];
//				}
//
//			}
//		}

}
