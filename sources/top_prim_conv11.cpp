#include "spbits.h"
#include <ap_int.h>
#include "primitive.h"
#include <fstream>
#include <iostream>

//wrapper func for prim_conv11
void primitive11::top_prim_conv11(
					ap_uint<4> quality[seg_ch],
					ap_uint<bw_wg> wiregroup[seg_ch],
					ap_uint<bw_hs> hstrip[seg_ch],
					ap_uint<4> clctpat[seg_ch],
					ap_uint<8> station,
					ap_uint<8> cscid,
					ap_uint<12> r_in,
					ap_uint<1> we,
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
					ap_uint<1> print_flag,
					ap_uint<12> *r_out)
{
#pragma HLS LATENCY min=0 max=0
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


	volatile ap_uint<3> a_phzvl;
	volatile ap_uint<ph_hit_w> a_ph_hit;
	volatile ap_uint<th_hit_w> a_th_hit;

if(we==1)
{
	//load LUTs
	this->mem11(r_in,
			 we,
			 addr,
			 sel,
			 // r_out,
			 station,
			 cscid,
			 endcap
			 );

}

else
{
		//primtive converter
		this->prim_conv11(
			 		quality,
			 		wiregroup,
			 		hstrip,
			 		clctpat,
			 		station,
			 		cscid,
			 		ph,
			 		th,
			 		vl,
			 		phzvl,
			 		me11a,
			 		clctpat_r,
			 	    ph_hit,
					th_hit,
			 		sel,
			 		addr,
			 	    endcap,
			 		r_out
			 		);

}


/*

#ifndef __SYNTHESIS__

    char* fes=  "_endcap_1_sec_2_"; // endcap and sector numbers for LUT file names
	char* fest= "_endcap_1_sect_2"; // endcap and sector numbers for LUT file names
	char* dpath= "C:/Vivado/Verification_PRATAP";
	char concat[1000]; unsigned int tmp;
	int errors=0;

	if(station==0 && cscid==0 && we==1){
	//	cout<<"th_mem["<<i<<"]= "<<th_mem[i]<<endl;

		cout<<"r_in ="<<r_in<<" addr= "<<addr<<"for st: "<<station<< " cscid: "<<cscid<<endl;
	}

if(print_flag==1 && station==0 && cscid==0){
errors=0;
	//verify th_corr_mem
	sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_%d_st_1_ch_%d.lut",dpath,fes,int(station+1),int(cscid+1));
	cout<<concat<<endl;
	FILE *fp;
	fp=fopen(concat,"r");

	for(int i=0;i<th_corr_mem_sz;i++){
		fscanf(fp,"%x", &tmp);
		if(feof(fp) && errors==0){
					cout<<" Success of th_corr_mem from st: "<<station<<" and cscid: "<<cscid<<endl;
							break;}
		if(tmp!=th_corr_mem[i]){
			cout<<"tmp= "<<tmp<<" th_corr_mem= "<<(th_corr_mem)[i]<<" with st: "<<int(station)<<" and cscid: "<<int(cscid)<<" failed at i= "<<int(i)<<endl;
			//break;
			errors++;
		}

		}

	fclose(fp);
	tmp=0;
	errors=0;

	//verify th_mem
    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_%d_st_1_ch_%d.lut",dpath,fes,int(station+1),int(cscid+1));
    cout<<concat<<endl;

		fp=fopen(concat,"r");

		for(int i=0;i<th_mem_sz;i++){
			fscanf(fp,"%x", &tmp);
			if(feof(fp) && errors==0){
							cout<<" Success of th_mem from st: "<<station<<" and cscid: "<<cscid<<endl;
										break;
							}
			if(tmp!=th_mem[i]){
				cout<<"tmp= "<<int(tmp)<<" th_mem= "<<int(th_mem[i])<<" with st: "<<int(station)<<" and cscid: "<<int(cscid)<<" failed at i= "<<int(i)<<"errors: "<<int(errors)<<endl;
				//break;
				errors++;
			}

		}
		fclose(fp);
cout<<endl; cout<<endl;
}
#endif
*/


/*
*phzvl=a_phzvl;
*ph_hit=a_ph_hit;
*th_hit=a_th_hit;
*/
}


