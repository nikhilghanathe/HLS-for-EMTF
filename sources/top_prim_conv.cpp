#include "spbits.h"
#include <ap_int.h>
#include "primitive.h"
#include <fstream>
#include <iostream>

using namespace std;

void primitive::top_prim_conv(
			ap_uint<4> quality[seg_ch],
					ap_uint<bw_wg> wiregroup[seg_ch],
					ap_uint<bw_hs> hstrip[seg_ch],
					ap_uint<4> clctpat[seg_ch],
					ap_uint<8> station,
					ap_uint<8> cscid,
					ap_uint<12> r_in,
					ap_uint<1> we,
					ap_uint<bw_fph> ph[seg_ch],
					ap_uint<bw_th> th[seg_ch],
					ap_uint<seg_ch> *vl,
					ap_uint<3> *phzvl,
					ap_uint<seg_ch> *me11a,
					ap_uint<4> clctpat_r[seg_ch],
					ap_uint<ph_hit_w> *ph_hit,
					ap_uint<th_hit_w> *th_hit,
					ap_uint<2>  sel,
					ap_uint<bw_addr>  addr,
					ap_uint<1> endcap,
					ap_uint<1> lat_test,
					ap_uint<1> print_flag,
					ap_uint<12> *r_out)

{
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



	ap_uint<3> a_phzvl;
		ap_uint<ph_hit_w> a_ph_hit;
		ap_uint<th_hit_w> a_th_hit;
	//primitive inst;
if(we==1)
{
	this->mem( 	r_in,
			 we,
			 addr,
			 sel,
			 station,
			 cscid
			 );

}

else
{

		this->prim_conv1(
			 		quality,
			 		wiregroup,
			 		hstrip,
			 		clctpat,
			 		station,
			 		cscid,
			 		ph,
			 		th,
			 		vl,
			 		&a_phzvl,
			 		me11a,
			 		clctpat_r,
					&a_ph_hit,
					&a_th_hit,
			 		sel,
			 		addr,
			 		endcap,
			 		lat_test,
			 		r_out
			 		);

}


#ifndef __SYNTHESIS__

    char* fes=  "_endcap_1_sec_2_"; // endcap and sector numbers for LUT file names
	char* fest= "_endcap_1_sect_2"; // endcap and sector numbers for LUT file names
	char* dpath= "C:/Vivado/Verification_PRATAP";
	char concat[1000]; unsigned int tmp;
	int errors;

/*	if(station==2 && cscid==0 && we==1 && sel==1){
	//	cout<<"th_mem["<<i<<"]= "<<th_mem[i]<<endl;

		cout<<"r_in ="<<r_in<<" addr= "<<addr<<"for st: "<<station<< " cscid: "<<cscid<<endl;
	}*/

if(print_flag==1/* && station==2 && cscid==0*/){
errors=0;
	FILE *fp;


	//verify th_mem
	if(station<=1)
		sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_%d_st_1_ch_%d.lut",dpath,fes,int(station+1),int(cscid+1));
	else
		 sprintf(concat,"%s/vl_lut/vl_th_lut%sst_%d_ch_%d.lut",dpath,fes,int(station),int(cscid+1));

  cout<<concat<< " with st: "<<station<<" cscid: "<<cscid<<endl;

		fp=fopen(concat,"r");

		for(int i=0;i<th_mem_sz;i++){
			fscanf(fp,"%x", &tmp);
			if(feof(fp) && errors==0){
						cout<<" Success of th_mem from st: "<<station<<" and cscid: "<<cscid<<endl;
								break;
					}
			if(tmp!=th_mem[i]){
				cout<<"tmp= "<<int(tmp)<<" th_mem= "<<int(th_mem[i])<<" with st: "<<station<<" and cscid: "<<cscid<<" failed at i= "<<int(i)<<endl;
				//break;
				errors++;
			}


		}
		fclose(fp);
cout<<endl; cout<<endl;
}
#endif
*phzvl=a_phzvl;
*ph_hit=a_ph_hit;
*th_hit=a_th_hit;
}



