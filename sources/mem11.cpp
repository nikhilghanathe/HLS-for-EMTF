#include <ap_int.h>
#include "spbits.h"
#include "primitive.h"

void primitive11::mem11(ap_uint<12> r_in,
		ap_uint<1> we,
		ap_uint<bw_addr> addr,
		ap_uint<2> sel,
		//ap_uint<12> *r_out,
		const int station,
		const int cscid,
		ap_uint<1> endcap
		)

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=params complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_corr_mem complete dim=0









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
   ph_reverse=0;
       	 if(endcap == 0 && station >= 3)
       		 	 ph_reverse=1;

       	 if(endcap == 0x1 && station <  3)
       		 ph_reverse=1;

*/

	/*th_coverage= 0;
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



ph_zone_bnd1 =(station <= 1 && cscid <= 2) ? 41 :(station == 2 && cscid <= 2) ? 41 : (station == 2 && cscid >  2) ? 87 :(station == 3 && cscid >  2) ? 49 :(station == 4 && cscid >  2) ? 49 : 127;

ph_zone_bnd2= (station == 3 && cscid >  2) ? 87 : 127;*/


	ap_uint<12> temp;
					if(sel==0 && we==1)
						params[addr]=r_in;

					// programmable parameters
					// [0] = ph_init_b
					// [1] = ph_displacement_b
					// [2] = ph_init_a
					// [3] = ph_displacement_a
					// [4] = th_init
					// [5] = th_displacement

					if(sel==1 && we==1)
						th_mem[addr]=r_in;

					if(sel==2 && we==1)
						th_corr_mem[addr]=r_in;


				/*	if(sel==0)
						temp= params[addr];
					else if(sel==1)
						temp=th_mem[addr];
					else if(sel11==0)
						temp= params[addr];
					else if(sel11==1)
						temp=th_corr_mem[addr];*/


			//*r_out=temp;
/*if(station==0 && cscid==0){
			for(int i=0;i<th_corr_mem_sz;i++)
				std::cout<<"th_mem["<<i<<"] = "<<th_mem[i]<<"   ";

			std::cout<<std::endl;
			std::cout<<"station  = "<<station<<" cscid = "<<cscid<<" we = "<<we<<std::endl;
			std::cout<<"r_in  = "<<r_in<<" sel = "<<sel<<" sel11 = "<<sel11<<" addr = "<<addr<<std::endl;
}*/

}



