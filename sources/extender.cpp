#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
#include "extender.h"


/*void shifter( ap_uint<ph_raw_w> inp,
		  ap_uint<ph_raw_w>	*shift_out_1,
		  ap_uint<ph_raw_w>	*shift_out_2,
		  ap_uint<ph_raw_w>	*shift_out_3)
{
	volatile ap_uint<ph_raw_w> d[2];


//#pragma HLS LATENCY min=2 max=2
#pragma HLS INTERFACE ap_none port=inp
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	*shift_out_1=inp;
	    	d[0]=inp;

	    	d[1]=d[0];



	    *shift_out_2=d[0];
	    *shift_out_3=d[1];




}*/


void extend::extender(   ap_uint<ph_raw_w> inp,
			  ap_uint<ph_raw_w>	*outp,
			ap_uint<3> drifttime)
			{
#pragma HLS INTERFACE ap_stable port=inp  //This directive optimizes unnecessary registers

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
		//build delay lines for each bit
		     volatile ap_uint<ph_raw_w> d[2], d2;
		    //  static ap_uint<ph_raw_w>	 temp1, temp2;
		      ap_uint<ph_raw_w> temp, t1, t2;
		     ap_uint<ph_raw_w>	bx1, bx2;
		      volatile  ap_uint<ph_raw_w>temp3;
		      	 t1=temp1;
		      	 t2=temp2;
		      temp = inp | temp1 | temp2;
		      	d[0]=t1;
		      	d[1]=t2;
		      	d[1]=d[0];
		      	d[0]=inp;
				temp1=d[0];
				temp2=d[1];
				*outp=temp;
/*

	   	   	    d[0]=inp;
			    d[1]=d[0];
				temp1=d[0];
				temp2=d[1];

*/

		      *outp = inp | temp1 | temp2;




			}
