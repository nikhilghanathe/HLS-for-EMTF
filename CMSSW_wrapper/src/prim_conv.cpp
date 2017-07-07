#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include <stdio.h>
#include "../interface/primitive.h"

using namespace std;


void primitive::prim_conv(
		ap_uint<seg_ch> vpf,
		ap_uint<4> quality[seg_ch],
		ap_uint<bw_wg> wiregroup[seg_ch],
		ap_uint<bw_hs> hstrip[seg_ch],
		ap_uint<4> clctpat[seg_ch],
		const ap_uint<8> station,
		const ap_uint<8> cscid,
		ap_uint<bw_fph> ph[seg_ch],
		ap_uint<bw_th> th[seg_ch],
		ap_uint<seg_ch> *vl,
		ap_uint<3> *phzvl,
		ap_uint<seg_ch> *me11a,
		ap_uint<4> clctpat_r[seg_ch],
	    ap_uint<ph_hit_w> *ph_hit,
		ap_uint<2>  sel,
		ap_uint<bw_addr>  addr,
		ap_uint<1> endcap,
		ap_uint<1> lat_test,
		ap_uint<12> *r_out
		)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

	const int ph_init_hard [5][16]= {{39,  57,  76, 39,  58,  76, 41,  60,  79, 39,  57,  76,21,21,23,21},
			{95, 114, 132, 95, 114, 133, 98, 116, 135, 95, 114, 132, 0, 0, 0, 0},
			{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
			{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
			{38,  76, 113, 38,  57,  76, 95, 113, 132,  1,  20,   0, 0, 0, 0, 0}};

	int i;
	ap_uint<12> 	temp;

	ap_uint<11> 	factor;
	ap_uint<8>  	pc_id;
	ap_uint<seg_ch> me11a_w;

	// initial ph for this chamber scaled to 0.1333 deg/strip
	ap_uint<bw_fph> 	fph[seg_ch];
	ap_uint<bw_fph-5-1> ph_hard = ph_init_hard[station][cscid];
	ap_uint<bw_fph>  	fph_to_reduce[2];
	ap_uint<bw_fph>  	ph_reduced[2];
    ap_uint<3>  		clct_pat_corr; // phi correction derived from clct pattern
    ap_uint<1>  		clct_pat_sign; // phi correction sign
    // eighth-strip
    ap_uint<bw_fph> 	eight_str[seg_ch];
    ap_uint<mult_bw> 	mult;
    ap_uint<bw_fph> 	ph_tmp;
    ap_uint<bw_wg>  	wg;
    ap_uint<bw_th>  	th_tmp;

    ap_uint<th_hit_w> 	a_th_hit;
    ap_uint<ph_hit_w> 	a_ph_hit;
    ap_uint<bw_fph> 	ph_hit_local;
    ap_uint<3> 			a_phzvl;
    const static ap_uint<1> one=1;
    const static ap_uint<2> zero_2=0;
    const static ap_uint<3> zero_3=0;
    const static ap_uint<1> zero_1=0;
    ap_uint<16> 		ph_coverage;


     //calc parameters based on station and cscid
    const int  ph_zone_bnd1 =(station <= 1 && cscid <= 2) ? 41 :(station == 2 && cscid <= 2) ? 41 : (station == 2 && cscid >  2) ? 87 :(station == 3 && cscid >  2) ? 49 :(station == 4 && cscid >  2) ? 49 : 127;
    const int ph_zone_bnd2= ((station == 3 && cscid >  2) ? 87 : 127);

    if(station <= 1 && cscid >= 6)
    	ph_coverage=15;
    else if(station >= 2 && cscid <= 2)
    	ph_coverage=40;
    else
    	ph_coverage=20;

    // is this chamber mounted in reverse direction?
     ap_uint<1>ph_reverse = (endcap == 0x0 && station >=  3) ? 1: (endcap == 1 && station <  3) ? 1 : 0;


	ap_uint<2> a_vl;
	ap_uint<4> a_clctpat_r[seg_ch];
	ap_uint<7> a_th[seg_ch];

	ap_uint<4> a_cscid=cscid;
	ap_uint<4> a_station=station;


	 pc_id=  (cscid,station);


//	 if(station==2 && cscid==4){
//		 if(vpf[0] || vpf[1])
//			 cout<<"vpf valid"<<endl;
//	 }


	 for(int i=0;i<seg_ch;i++){
	 #pragma HLS UNROLL
	 	th[i]=0; fph[i]=0; clctpat_r[i]=0;
	 }
	 a_vl=0; a_phzvl=0; a_ph_hit=0; a_th_hit=0;


	 // strip width factor relative to ME234/2
	 		// 1024 == 1
	 factor = (station <= 1 && ((cscid >= 6 && cscid <= 8) || (cscid == 14))) ? 947 : // ME1/3
	 				 1024; // all other chambers



	for (i = 0; i < seg_ch; i = i+1){

		// clct pattern convertion array from CMSSW
		//{0.0, 0.0, -0.60,  0.60, -0.64,  0.64, -0.23,  0.23, -0.21,  0.21, 0.0}
		// 0    0    -5      +5    -5      +5    -2      +2    -2      +2    0
		switch(clctpat[i])
		{
		case 0  :  clct_pat_corr = 0x0; clct_pat_sign = 0; break;
		case 1  :  clct_pat_corr = 0x0; clct_pat_sign = 0; break;
		case 2  :  clct_pat_corr = 0x5; clct_pat_sign = 1; break;
		case 3  :  clct_pat_corr = 0x5; clct_pat_sign = 0; break;
		case 4  :  clct_pat_corr = 0x5; clct_pat_sign = 1; break;
		case 5  :  clct_pat_corr = 0x5; clct_pat_sign = 0; break;
		case 6  :  clct_pat_corr = 0x2; clct_pat_sign = 1; break;
		case 7  :  clct_pat_corr = 0x2; clct_pat_sign = 0; break;
		case 8  :  clct_pat_corr = 0x2; clct_pat_sign = 1; break;
		case 9  :  clct_pat_corr = 0x2; clct_pat_sign = 0; break;
		case 10 :  clct_pat_corr = 0x0; clct_pat_sign = 0; break;
		default :  clct_pat_corr = 0x0; clct_pat_sign = 0; break;
		}


		// reverse clct pattern correction if chamber is reversed
		//			if (ph_reverse) clct_pat_sign = ~clct_pat_sign;

		// 10 deg chambers
		ap_uint<10> con;
		ap_uint<11> con1;

		if ((station <= 1) ||  (station >= 2 && ((cscid >= 3 && cscid <= 8) || cscid  == 10)))
		{
			// full precision, uses only 2 bits of clct pattern correction
			eight_str[i]  = (zero_2,hstrip[i],zero_2);

			if (clct_pat_sign == 0) eight_str[i] = eight_str[i] + (clct_pat_corr >> 1);
			else eight_str[i] = eight_str[i] - (clct_pat_corr >> 1);
		}
		else{
			// 20 deg chambersse
			// multiply by 2, uses all 3 bits of pattern correction
			con1  = (hstrip[i],zero_3);
			eight_str[i]  = (zero_1,con1);
			if (clct_pat_sign == 0) eight_str[i] = eight_str[i] + clct_pat_corr;
			else eight_str[i] = eight_str[i] - clct_pat_corr;
		}



		if(vpf[i])
		{
			a_vl[i] = 1;
			// ph conversion
			// for factors 1024 and 2048 the multiplier should be replaced with shifts by synthesizer
			mult = eight_str[i] * factor;
			ph_tmp = mult(mult_bw-1,10);
			if (ph_reverse) fph[i] = params[0] - ph_tmp;
			else            fph[i] = params[0] + ph_tmp;


			fph_to_reduce[i] = fph[i] + 16; // +16 to put the rounded value into the middle of error range
			// divide full ph by 32, subtract chamber start
			ph_reduced[i] = fph_to_reduce[i](bw_fph-1,5) - ph_hard;
			a_ph_hit[ph_reduced[i]] = 1; // set hit in zone

			wg = wiregroup[i];
			// th conversion
			th_tmp = th_mem[wg];
			th[i] = th_tmp + params[1];
			if (th[i] == 0) th[i] = 1; // protect against invalid value


			// check which zones ph hits should be applied to
			if (th[i] <= (ph_zone_bnd1 + zone_overlap)){
				a_phzvl[0] = 1;
			}
			if (th[i] >  (ph_zone_bnd2 - zone_overlap)) a_phzvl[2] = 1;
			if (
				(th[i] >  (ph_zone_bnd1 - zone_overlap)) &&
				(th[i] <= (ph_zone_bnd2 + zone_overlap))
				) a_phzvl[1] = 1;

			clctpat_r[i] = clctpat[i]; // just propagate pattern downstream
		}
		else
		if (lat_test == 1 && cscid == 0 && i == 0)
		{
			 // in latency test mode, generate fake stub in chamber 0
			 a_vl[i] = 1;
			 fph[i] = 2048;
			 a_ph_hit[22] = 1;
			 th[i] = 30; // ~17 deg
			 a_phzvl[0] = 1;

		}

       ph[i] = fph[i];

		}


//Assign outputs
ph[0]=fph[0];ph[1]=fph[1];
*me11a = 0;
*phzvl=a_phzvl;
*ph_hit= a_ph_hit;
*vl = a_vl;


		if(sel==0)
			temp= params[addr];
		else if(sel==1)
			temp=th_mem[addr];
		else
			temp=pc_id;


*r_out=temp;
}

