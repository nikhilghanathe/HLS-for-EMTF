#include "ap_int.h"
#include "spbits.h"
#include <stdio.h>
#include "primitive.h"


using namespace std;

void primitive11::prim_conv11(
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


/*
#pragma HLS INTERFACE register port=ph
#pragma HLS INTERFACE register port=th
#pragma HLS INTERFACE register port=vl
#pragma HLS INTERFACE register port=me11a
#pragma HLS INTERFACE register port=phzvl
#pragma HLS INTERFACE register port=clctpat_r
#pragma HLS INTERFACE register port=ph_hit
#pragma HLS INTERFACE register port=th_hit
#pragma HLS INTERFACE register port=r_out
*/


	int i,j;



//std::cout<<"stationa = "<<station<<"cscid = "<<cscid<<std::endl;

/*	for(int i=0;i<th_corr_mem_sz;i++)
				std::cout<<"th_Corr_mem_st["<<i<<"] = "<<th_corr_mem[i]<<"   "<<std::endl;*/


	ap_uint<12> temp;

	ap_uint<8> pc_id;
	ap_uint<seg_ch> me11a_w;

	// initial ph for this chamber scaled to 0.1333 deg/strip
	ap_uint<12> fph[seg_ch]={0};
#pragma HLS ARRAY_PARTITION variable=fph complete dim=1
    ap_uint<3>  aclct_pat_corr; // phi correction derived from clct pattern
    ap_uint<1>  clct_pat_sign; // phi correction sign

     ap_uint<bw_fph> eight_str[seg_ch]; // eighth-strip
#pragma HLS ARRAY_PARTITION variable=eight_str complete dim=1
     ap_uint<mult_bw> mult;
     ap_uint<bw_fph> ph_tmp;
     ap_uint<bw_wg>  wg;
     ap_uint<bw_th>  th_tmp;

      ap_uint<th_hit_w> a_th_hit=0;
     ap_uint<ph_hit_w> a_ph_hit=0;
     ap_uint<bw_fph> a_ph[seg_ch]={0};
     ap_uint<3> a_phzvl;
     ap_uint<11> factor[seg_ch]; // strip width factors for each segment
    const  ap_uint<1> one=1;
    const  ap_uint<2> zero_2=0;
    const  ap_uint<3> zero_3=0;
    const  ap_uint<1> zero_1=0;
//    ap_uint<4> th_corr;
   // ap_uint<1> ph_reverse;

   //ap_uint<16> ph_coverage;
     ap_uint<4> th_corr;
     const int ph_coverage=20;
     const int th_coverage=45;
     const int ph_zone_bnd1=41;
     const int ph_zone_bnd2=127;

     ap_uint<1>ph_reverse = (endcap == 0x1 && station <  3) ? 1: 0;

      ap_uint<bw_th> a_th[seg_ch*seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_th complete dim=0
/*
    if(station <= 1 && cscid >= 6)
    	ph_coverage=15;
    else if(station >= 2 && cscid <= 2)
    	ph_coverage=40;
    else
    	ph_coverage=20;
*/



// is this chamber mounted in reverse direction?

/*
    ap_uint<16>th_coverage;
	th_coverage= 0;
    		if(station <= 1){
    			if(cscid<=2)th_coverage=45;
    			if(cscid >= 6)  th_coverage=27;
    			else if(cscid >= 3)  th_coverage=39;

    		}

    		if(station == 2){
    			if(cscid<=2) th_coverage=43;
    			if(cscid >= 3)  th_coverage=56;
    		}
    		if(station == 3){
    		    if(cscid <= 2)  th_coverage=34;
    		    if(cscid >= 3)  th_coverage=52;
    		}
    		if(station == 4){
    			if(cscid <= 2)  th_coverage=28;
    		    if(cscid >= 3)  th_coverage=50;
    		}
*/



/*const int  ph_zone_bnd1 =(station <= 1 && cscid <= 2) ? 41 :(station == 2 && cscid <= 2) ? 41 : (station == 2 && cscid >  2) ? 87 :(station == 3 && cscid >  2) ? 49 :(station == 4 && cscid >  2) ? 49 : 127;

const int ph_zone_bnd2= (station == 3 && cscid >  2) ? 87 : 127;*/

/*    ph_reverse=0;
        	 if(endcap == 0 && station >= 3)
        		 	 ph_reverse=1;

        	 if(endcap == 0x1 && station <  3)
        		 ph_reverse=1;*/


    			ap_uint<2> a_vl;
    			ap_uint<3>  ph_init_ix; // parameter index for ph_init
    			ap_uint<6> th_orig;
    		// theta correction lut, for me1/1 only
  			// takes index = {wiregroup(2 MS bits), dblstrip}, returns theta correction for tilted wires

    			ap_uint<4> a_clctpat_r[seg_ch];




	 pc_id=  (cscid,station);

for(int i=0;i<seg_ch*seg_ch;i++){
#pragma HLS UNROLL
	a_th[i]=0;
}

	 a_ph_hit=0; a_th_hit=0; a_phzvl=0; a_vl=0;

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


		//	cout<<"me11a_1 of iteration "<<i<<"is "<<me11a_w[i]<<hex<<endl;

			// clct pattern convertion array from CMSSW
			//{0.0, 0.0, -0.60,  0.60, -0.64,  0.64, -0.23,  0.23, -0.21,  0.21, 0.0}
			// 0    0    -5      +5    -5      +5    -2      +2    -2      +2    0
			switch(clctpat[i])
			{
			case 0  :  aclct_pat_corr = 0x0; clct_pat_sign = 0; break;
			case 1  :  aclct_pat_corr = 0x0; clct_pat_sign = 0; break;
			case 2  :  aclct_pat_corr = 0x5; clct_pat_sign = 1; break;
			case 3  :  aclct_pat_corr = 0x5; clct_pat_sign = 0; break;
			case 4  :  aclct_pat_corr = 0x5; clct_pat_sign = 1; break;
			case 5  :  aclct_pat_corr = 0x5; clct_pat_sign = 0; break;
			case 6  :  aclct_pat_corr = 0x2; clct_pat_sign = 1; break;
			case 7  :  aclct_pat_corr = 0x2; clct_pat_sign = 0; break;
			case 8  :  aclct_pat_corr = 0x2; clct_pat_sign = 1; break;
			case 9  :  aclct_pat_corr = 0x2; clct_pat_sign = 0; break;
			case 10 :  aclct_pat_corr = 0x0; clct_pat_sign = 0; break;
			default :  aclct_pat_corr = 0x0; clct_pat_sign = 0; break;
			}


			// reverse clct pattern correction if chamber is reversed
			//			if (ph_reverse) clct_pat_sign = ~clct_pat_sign;

						// 10 deg chambers

			// full precision, uses only 2 bits of clct pattern correction
			// convert into 1/8 strips and remove ME1/1a offset (512=128*4)

				eight_str[i]  = (zero_2,hstrip[i],zero_2)- (me11a_w[i] ? 512:0);

			if (clct_pat_sign == 0)
				eight_str[i] = eight_str[i] + (aclct_pat_corr(2,1));
			else
				eight_str[i] = eight_str[i] - (aclct_pat_corr(2,1));


				//cout<<"eight_str before of iteration "<<i<<"is "<<eight_str[i]<<hex<<endl;




			if(quality[i])
			{
				a_vl[i] = 1;
				// ph conversion
				// for factors 1024 and 2048 the multiplier should be replaced with shifts by synthesizer
				mult = eight_str[i] * factor[i];
				ph_tmp = (mult >> 10);
				//cout<<"ph_tmp of iteration "<<i<<"is "<<ph_tmp<<hex<<endl;

					ph_init_ix = (me11a_w[i] ? 2:0); // index of ph_init parameter to apply (different for ME11a and b)



	    		  if (ph_reverse)
					{
				    	fph[i] = params[ph_init_ix] - ph_tmp;
				    //	cout<<"fph of iteration "<<i<<"is "<<fph[i]<<hex<<endl;
						// set ph raw hits
					a_ph_hit.set_bit(int(ph_coverage-(ph_tmp(bw_fph-1,5)) + (params[ph_init_ix+1](7,1))),1);
					}
				  else
					{
						fph[i] = params[ph_init_ix] + ph_tmp;
						// set ph raw hits
					a_ph_hit.set_bit(int((ph_tmp(bw_fph-1,5)) + (params[ph_init_ix+1](7,1))),1);


					}

	   		  wg = wiregroup[i];
			// th conversion
	   		// call appropriate LUT, it returns th[i] relative to wg0 of that chamber
	   		  th_orig = th_mem[wg];

	   		prim_conv11_label0:for (j = 0; j < seg_ch; j = j+1)
	   		{
#pragma HLS UNROLL
	   		  if (quality[j])
	   		  {
	   			  // calculate correction for each strip number

				// index is: {wiregroup(2 MS bits), dblstrip(5-bit for these chambers)}

	   			  ap_uint<7> index = (wg(5,4), eight_str[j](8,4));


				 th_corr = th_corr_mem[index];

				// apply correction to the corresponding output
				if (ph_reverse) th_tmp = (th_orig - th_corr) & 0x3F;
				else            th_tmp = (th_orig + th_corr) & 0x3F;


				// check that correction did not make invalid value outside chamber coverage
				// this will actually take care of both positive and negative illegal values
				if (th_tmp < th_coverage)
				{
					// apply initial th value for that chamber

				  a_th[i*seg_ch+j] = th_tmp + params[4];
				  // th hits
				  a_th_hit.set_bit(int(th_tmp + params[5]),1);

						// check which zones ph hits should be applied to
					if (a_th[i*seg_ch+j] <= (ph_zone_bnd1 + zone_overlap)) a_phzvl[0]= 1;
					if (a_th[i*seg_ch+j] >=  (ph_zone_bnd2 - zone_overlap)) a_phzvl[2]= 1;
					if (
						(a_th[i*seg_ch+j] >  (ph_zone_bnd1 - zone_overlap)) &&
						(a_th[i*seg_ch+j] <= (ph_zone_bnd2 + zone_overlap))
					) a_phzvl[1]=1;
				}
				else{
					a_th[(i*seg_ch)+j]=0;
					//a_th_hit=0;
					//a_phzvl=0;
				}
	   		  }
	   		  else{
	   			  a_th[(2*i)+j]=0;
	   		  }

	   		}
	   		clctpat_r[i] = clctpat[i]; // just propagate pattern downstream

			}// if (quality[i])
			else
			{
				fph[i] = 0; clctpat_r[i] = 0;
				//a_phzvl = 0;
				//a_ph_hit = 0;
				//a_th_hit = 0;
				//a_vl=0;
			}
	    		  			ph[i] = fph[i];

			}

for(int i=0;i<seg_ch*seg_ch;i++){
#pragma HLS UNROLL
	th[i]=a_th[i];
		}
*me11a = (me11a_w[1],me11a_w[0]);
*phzvl=a_phzvl;
*ph_hit= a_ph_hit;
*th_hit = a_th_hit;
*vl = a_vl;


/*
		if(sel==0)
			temp= params[addr];
		else if(sel==1)
			temp=th_mem[addr];
		else if(sel11==0)
			temp= params[addr];
		else if(sel11==1)
			temp=th_corr_mem[addr];
		else
			temp=pc_id;
*/


*r_out=temp;
}


