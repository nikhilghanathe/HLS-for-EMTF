#include "ap_int.h"
#include "spbits.h"
#include <stdio.h>
#include "primitive.h"


using namespace std;

void primitive11::prim_conv11(
			ap_uint<seg_ch> vpf,
			ap_uint<4> quality[seg_ch],
			ap_uint<bw_wg> wiregroup[seg_ch],
			ap_uint<bw_hs> hstrip[seg_ch],
			ap_uint<4> clctpat[seg_ch],
			const ap_uint<8> station,
			const ap_uint<8> cscid,
			 ap_uint<bw_fph> ph[seg_ch],
			 ap_uint<bw_th> th[seg_ch*seg_ch],
			 ap_uint<seg_ch> *vl,
			 ap_uint<3> *phzvl,
			 ap_uint<seg_ch> *me11a,
			 ap_uint<4> clctpat_r[seg_ch],
			 ap_uint<ph_hit_w> *ph_hit,
			 ap_uint<th_hit_w> *th_hit,
			ap_uint<2>  sel,
			ap_uint<bw_addr>  addr,
			ap_uint<1> endcap,
			ap_uint<12> *r_out
			)

{
//#pragma HLS LATENCY min=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=quality complete dim=0
#pragma HLS ARRAY_PARTITION variable=wiregroup complete dim=0
#pragma HLS ARRAY_PARTITION variable=hstrip complete dim=0
#pragma HLS ARRAY_PARTITION variable=clctpat complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=th complete dim=0
#pragma HLS ARRAY_PARTITION variable=clctpat_r complete dim=0
#pragma HLS ARRAY_PARTITION variable=params complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_corr_mem complete dim=0
#pragma HLS LATENCY max=0


const int ph_init_hard [5][16]= {{39,  57,  76, 39,  58,  76, 41,  60,  79, 39,  57,  76,21,21,23,21},
		{95, 114, 132, 95, 114, 133, 98, 116, 135, 95, 114, 132, 0, 0, 0, 0},
		{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
		{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
		{38,  76, 113, 38,  57,  76, 95, 113, 132,  1,  20,   0, 0, 0, 0, 0}};


int i,j;


ap_uint<12> temp;
ap_uint<8> pc_id;
ap_uint<seg_ch> me11a_w;

// initial ph for this chamber scaled to 0.1333 deg/strip
ap_uint<12> fph[seg_ch];
ap_uint<bw_fph-5-1> ph_hard = ph_init_hard[station][cscid];
ap_uint<bw_fph>  fph_to_reduce[2];
ap_uint<bw_fph>  ph_reduced[2];

ap_uint<3>  aclct_pat_corr[seg_ch]; // phi correction derived from clct pattern
ap_uint<1>  clct_pat_sign[seg_ch]; // phi correction sign

 ap_uint<bw_fph> eight_str[seg_ch]; // eighth-strip
#pragma HLS ARRAY_PARTITION variable=eight_str complete dim=1
 ap_uint<mult_bw> mult[seg_ch];
 ap_uint<bw_fph> ph_tmp[seg_ch];
 ap_uint<bw_wg>  wg[seg_ch];
 ap_uint<bw_th>  th_tmp[seg_ch][seg_ch],thf[seg_ch][seg_ch];
 ap_uint<7> th_tmp1[2];

 ap_uint<th_hit_w> a_th_hit[seg_ch][seg_ch];
 ap_uint<ph_hit_w> a_ph_hit[seg_ch];

 ap_uint<3> a_phzvl[seg_ch][seg_ch];
 ap_uint<11> factor[seg_ch]; // strip width factors for each segment
const  ap_uint<1> one=1;
const  ap_uint<2> zero_2=0;
const  ap_uint<3> zero_3=0;
const  ap_uint<1> zero_1=0;

 ap_uint<4> th_corr[seg_ch][seg_ch];
 const int ph_coverage=20;
 const int th_coverage=45;
 const int ph_zone_bnd1=41;
 const int ph_zone_bnd2=127;
 const int th_negative = 50;

 // is this chamber mounted in reverse direction?
 ap_uint<1>ph_reverse = (endcap == 0x0 && station >=  3) ? 1: (endcap == 1 && station <  3) ? 1 : 0;

// if(station==1 && cscid==0){
// 	for(int i=0;i<6;i++)
// 		cout<<"params["<<i<<"]= "<<params[i]<<endl;
// }
 //cout<<endl;
  ap_uint<bw_th> a_th[seg_ch*seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_th complete dim=0

			ap_uint<2> a_vl[seg_ch];
			ap_uint<3>  ph_init_ix[seg_ch]; // parameter index for ph_init
			ap_uint<6> th_orig[seg_ch];
		// theta correction lut, for me1/1 only
	// takes index = {wiregroup(2 MS bits), dblstrip}, returns theta correction for tilted wires

	 ap_uint<4> a_clctpat_r[seg_ch];
 pc_id=  (cscid,station);

 //Initialize outputs to 0
for(int i=0;i<seg_ch*seg_ch;i++){
#pragma HLS UNROLL
th[i]=0;
}
for(int i=0;i<seg_ch;i++){
#pragma HLS UNROLL
	a_vl[i]=0;
	a_ph_hit[i]=0;
	for(int j=0;j<seg_ch;j++){
		a_phzvl[i][j]=0;

	}
}





	prim_conv1_label0:for (i = 0; i < seg_ch; i = i+1)
	{
#pragma HLS UNROLL

		//factor[i]=(station <= 1 && cscid <= 2 && hstrip[i] > 127) ? 1707 :  // ME1/1a
			//	1301; // ME1/1b

		 if(hstrip[i] > 127){
			 me11a_w[i] =1;
			 factor[i]=1707;

		}
		 else
		 {
			 me11a_w[i]=0;
			 factor[i]=1301;
		 }

		// clct pattern convertion array from CMSSW
		//{0.0, 0.0, -0.60,  0.60, -0.64,  0.64, -0.23,  0.23, -0.21,  0.21, 0.0}
		// 0    0    -5      +5    -5      +5    -2      +2    -2      +2    0
		switch(clctpat[i])
		{
		case 0  :  aclct_pat_corr[i] = 0x0; clct_pat_sign[i] = 0; break;
		case 1  :  aclct_pat_corr[i] = 0x0; clct_pat_sign[i] = 0; break;
		case 2  :  aclct_pat_corr[i] = 0x5; clct_pat_sign[i] = 1; break;
		case 3  :  aclct_pat_corr[i] = 0x5; clct_pat_sign[i] = 0; break;
		case 4  :  aclct_pat_corr[i] = 0x5; clct_pat_sign[i] = 1; break;
		case 5  :  aclct_pat_corr[i] = 0x5; clct_pat_sign[i] = 0; break;
		case 6  :  aclct_pat_corr[i] = 0x2; clct_pat_sign[i] = 1; break;
		case 7  :  aclct_pat_corr[i] = 0x2; clct_pat_sign[i] = 0; break;
		case 8  :  aclct_pat_corr[i] = 0x2; clct_pat_sign[i] = 1; break;
		case 9  :  aclct_pat_corr[i] = 0x2; clct_pat_sign[i] = 0; break;
		case 10 :  aclct_pat_corr[i] = 0x0; clct_pat_sign[i] = 0; break;
		default :  aclct_pat_corr[i] = 0x0; clct_pat_sign[i] = 0; break;
		}


		// reverse clct pattern correction if chamber is reversed
		//			if (ph_reverse) clct_pat_sign = ~clct_pat_sign;

					// 10 deg chambers

		// full precision, uses only 2 bits of clct pattern correction
		// convert into 1/8 strips and remove ME1/1a offset (512=128*4)

			eight_str[i]  = (zero_2,hstrip[i],zero_2)- (me11a_w[i] ? 512:0);

		if (clct_pat_sign)
			eight_str[i] = eight_str[i] - (aclct_pat_corr[i](2,1));
		else
			eight_str[i] = eight_str[i] + (aclct_pat_corr[i](2,1));

	}




	for(i=0;i<seg_ch;i++){
#pragma HLS UNROLL
		if(vpf[i])
		{
			a_vl[i] = 1;
			// ph conversion
			// for factors 1024 and 2048 the multiplier should be replaced with shifts by synthesizer
			mult[i]= eight_str[i] * factor[i];
			ph_tmp[i] = (mult[i](mult_bw-1,10));
			ph_init_ix[i] = (me11a_w[i] ? 2:0); // index of ph_init parameter to apply (different for ME11a and b)

			if (ph_reverse)
			  fph[i] = params[ph_init_ix[i]] - ph_tmp[i];
			else
			  fph[i] = params[ph_init_ix[i]] + ph_tmp[i];


			fph_to_reduce[i] = fph[i] + 16; // +16 to put the rounded value into the middle of error range
			// divide full ph by 32, subtract chamber start
			ph_reduced[i] = fph_to_reduce[i](bw_fph-1,5) - ph_hard;
			a_ph_hit[i][ph_reduced[i]] = 1; // set hit in zone
			if(station==1 && cscid==0){
//				cout<<"eight_str["<<i<<"]= "<<eight_str[i]<<endl;
//				cout<<"factor["<<i<<"]= "<<factor[i]<<endl;
//				cout<<"mult["<<i<<"]= "<<mult[i]<<endl;
//				for(int i=0;i<6;i++)
//					cout<<"params["<<i<<"]= "<<params[i]<<endl;
//				cout<<"ph_tmp["<<i<<"]= "<<ph_tmp[i]<<endl;
//				cout<<"ph_init_ix["<<i<<"]= "<<ph_init_ix[i]<<endl;
//				cout<<"this->pr= "<<this->pr<<endl;
//				cout<<"ph_reduced["<<i<<"]= "<<ph_reduced[i]<<endl;
//				cout<<"fph_to_reduce["<<i<<"]= "<<fph_to_reduce[i]<<endl;
//				cout<<"fph["<<i<<"]= "<<fph[i]<<endl;
//				cout<<"ph_hard["<<i<<"]= "<<ph_hard[i]<<endl;
//				cout<<"a_ph_hit["<<i<<"]= "<<a_ph_hit[i]<<endl;

			}


		wg[i] = wiregroup[i];
		// th conversion
   		// call appropriate LUT, it returns th[i] relative to wg0 of that chamber
   		  th_orig[i] = th_mem[wg[i]];
   		if(station==1 && cscid==0){
   			 // cout<<"fph[0]= "<<fph[0]<<endl;
   		  }

   		prim_conv11_label0:for (j = 0; j < seg_ch; j = j+1)
   		{
#pragma HLS UNROLL
   		  if (vpf[j])
   		  {
   			  // calculate correction for each strip number

			// index is: {wiregroup(2 MS bits), dblstrip(5-bit for these chambers)}
   			  ap_uint<7> index[seg_ch] [seg_ch];
			 index[i][j]= (wg[i](5,4), eight_str[j](8,4));
			 th_corr[i][j] = th_corr_mem[index[i][j]];

			// apply correction to the corresponding output
			if (ph_reverse) th_tmp[i][j] = (th_orig[i] - th_corr[i][j]) ;
			else            th_tmp[i][j] = (th_orig[i] + th_corr[i][j]) ;


			if (th_tmp[i][j] > th_negative || wg[i] == 0)
				th_tmp[i][j] = 0; // limit at the bottom

			if (th_tmp[i][j] > th_coverage)
				th_tmp[i][j] = th_coverage; // limit at the top

			// apply initial th value for that chamber
			thf[i][j] = th_tmp[i][j] + params[4];
			if (thf[i][j] == 0) thf[i][j] = 1; // protect against invalid value
			th[j*seg_ch+i] = thf[i][j]; // indexes switched i<-->j per Jia Fu request 2016-10-18
			if(this->pr){
				cout<<"thf[0[0]="<<thf[0][0]<<endl;
				cout<<"th_tmp[0[0]="<<th_tmp[0][0]<<endl;
			}
			// check which zones ph hits should be applied to
			if (thf[i][j] <= (ph_zone_bnd1 + zone_overlap)) a_phzvl[i][j][0] = 1;
			if (thf[i][j] >  (ph_zone_bnd2 - zone_overlap)) a_phzvl[i][j][2] = 1;
			if (
				(thf[i][j] >  (ph_zone_bnd1 - zone_overlap)) &&
				(thf[i][j] <= (ph_zone_bnd2 + zone_overlap))
				) a_phzvl[i][j][1] = 1;


   		  }//if (quality[j])

   		}//for (j = 0; j < seg_ch; j = j+1)
   		clctpat_r[i] = clctpat[i]; // just propagate pattern downstream

		}// if (quality[i])
		else
		{
			fph[i] = 0; clctpat_r[i] = 0;
		}
    		  			ph[i] = fph[i];

		}//for (i = 0; i < seg_ch; i = i+1)




*me11a = (me11a_w[1],me11a_w[0]);
*phzvl=a_phzvl[0][0] | a_phzvl[0][1] | a_phzvl[1][0] | a_phzvl[1][1];
*ph_hit= a_ph_hit[1] | a_ph_hit[0];
*vl = a_vl[0] | a_vl[1];

*r_out=temp;
}
