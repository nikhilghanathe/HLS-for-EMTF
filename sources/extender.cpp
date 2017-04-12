#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
#include "extender.h"



void extend::extender(   ap_uint<ph_raw_w> inp,
			  ap_uint<ph_raw_w>	*outp,
			ap_uint<3> drifttime)
			{
#pragma HLS INTERFACE ap_stable port=inp  //This directive optimizes unnecessary registers

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
		//build delay lines for each bit
		volatile ap_uint<ph_raw_w> d[2]; //volatile ensures registers

		 ap_uint<ph_raw_w> temp, t1, t2;

		 volatile  ap_uint<ph_raw_w>temp3;

		 //load previous bunch crossing values
		 	 	 t1=bx1;
		      	 t2=bx2;

		  //combine values from three bunch crossings
		      temp = inp | bx1 | bx2;

		  //build delay line
		      	d[0]=t1;
		      	d[1]=t2;
		      	d[1]=d[0];
		      	d[0]=inp;

		  //save values from the two most recent bunch crossings
		      	bx1=d[0];
		      	bx2=d[1];

		 //assign outputs
				*outp=temp;




			}
