#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"

class zones_class{

public:
	ap_uint<1> pr;
	ap_uint<ph_raw_w> a_ph_zone[4][5];

	zones_class()
	{
		#pragma HLS ARRAY_PARTITION variable=a_ph_zone complete dim=0

		zones_class_label3:for(int i=0;i<4;i++)
			zones_class_label2:for(int j=0;j<5;j++)
				a_ph_zone[i][j]=0;

	}


	void zones_actual(  ap_uint<3> phzvl_in[6][9],
			 ap_uint<ph_hit_w> ph_hit_in[6][9],
		    	 ap_uint<ph_raw_w> ph_zone[4][5]);
};













