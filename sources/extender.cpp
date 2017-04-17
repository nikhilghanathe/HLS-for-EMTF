#include <ap_int.h>
#include "spbits.h"
#include "extender.h"



void extend::extender(   ap_uint<ph_raw_w> inp,
			  ap_uint<ph_raw_w>	*outp,
			ap_uint<3> drifttime)
			{
#pragma HLS INTERFACE ap_stable port=inp  //This directive optimizes unnecessary registers
#pragma HLS INTERFACE ap_none port=outp
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

		//build delay lines for each bit
		     volatile ap_uint<ph_raw_w> d[2];
	      ap_uint<ph_raw_w> t1, t2;


		     //volatile temp variable to preserve the operation and prevent HLS optimization
		      volatile  ap_uint<ph_raw_w>temp;


		      //load previous two bunch crossings
		      	 t1=bx1;
		      	 t2=bx2;

		     //use volatile variable to prevent HLS optimization
		      temp = inp | bx1 | bx2;


		      //Build delay line
		      	d[0]=t1;
		      	d[1]=t2;
		      	d[1]=d[0];
		      	d[0]=inp;

		      	//store current and previous bunch crossing values for use in next function call
				bx1=d[0];
				bx2=d[1];

				//assign output
				*outp=temp;






			}
