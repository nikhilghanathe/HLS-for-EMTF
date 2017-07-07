#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/match_seg.h"




ap_uint<2> match_seg::comp3(ap_uint<5> a,ap_uint<5> b,ap_uint<5> c)
{
 ap_uint<3> r=0;
 ap_uint<2> a_comp3;

	if(a <= b)
		r[2] =1;
	else
		r[2]=0;

	if (b <= c)
		r[1] =1;
	else
		r[1]=0;

	if(c <= a)
		r[0] = 1;
	else
		r[0]=0;

	switch(r){
		case 0x0 : a_comp3 = 0x3;// invalid
				  break;
		case 0x1 : a_comp3 = 0x2; // c
		  	  	  break;
		case 0x2 : a_comp3 = 0x1; // b
		  	  	  break;
		case 0x3 : a_comp3 = 0x1; // b
		  	  	  break;
		case 0x4 : a_comp3 = 0x0; // a
		  	  	  break;
		case 0x5 : a_comp3 = 0x2; // c
		  	  	  break;
		case 0x6 : a_comp3 = 0x0; // a
		  	  	  break;
		case 0x7 : a_comp3 = 0x0; // a
		  	  	  break;
		default: break;

			}

	return a_comp3;
}






















































