#include <ap_int.h>
#include "spbits.h"
#include "ph_pattern.h"
#include "sp.h"

using namespace std;

void ph_pattern::ph_pattern_exec(
        ap_uint<full_pat_w_st1> st1,
        ap_uint<1> st2,
		int station,
		int cscid,
        ap_uint<full_pat_w_st3> st3,
        ap_uint<full_pat_w_st3> st4,
        ap_uint<3> drifttime,
        ap_uint<3> foldn,
        ap_uint<6> *qcode
        )

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=bx complete dim=1
     int mi=0;


     ap_uint<3>   lyhits=0;;
     ap_uint<6>   qcode_p [5];
     ap_uint<3>   straightness;
     ap_uint<6>   comp1 [2];
     ap_uint<6>   comp2;
     ap_uint<1>   more_than_one, more_than_zero;

     ap_uint<8>   a_st1_t1,a_st1_t2;
     ap_uint<15>  a_st4;
     ap_uint<14>  a_st3;
     ap_uint<6>   a_qcode;
     ap_uint<3>   a_foldn;



    for (mi = 0; mi < 5; mi = mi + 1){
     #pragma HLS UNROLL
    	a_st1_t1=0;a_st1_t2=0;
    	a_st3=0;
    	a_st4=0;

    	switch (mi){

    		case 0:
    			a_st1_t1=st1(30,23); a_st1_t2=st1(7,0);
    			a_st3=st3(14,0);
    			a_st4=st4(14,0);

    			lyhits[2] = a_st1_t1.or_reduce() | a_st1_t2.or_reduce();
    			lyhits[1] = st2;
    			lyhits[0] = ((a_st3).or_reduce()) | (a_st4.or_reduce());
    			straightness = 0;
    			break;

            case 1:
            	a_st1_t1=(ap_uint<4>(0),st1(22,19)); a_st1_t2=(ap_uint<4>(0),st1(11,8));
            	a_st3=st3(14,0);
            	a_st4=st4(14,0);

            	lyhits[2] = a_st1_t1.or_reduce() | a_st1_t2.or_reduce();
            	lyhits[1] = st2;
            	lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
            	straightness = 1;
            	break;

            case 2:
            	a_st1_t1=(ap_uint<6>(0),st1(18,17)); a_st1_t2=(ap_uint<6>(0),st1(13,12));
            	a_st3=(ap_uint<8>(0),st3(10,4));
            	a_st4=(ap_uint<8>(0),st4(10,4));

            	lyhits[2] = a_st1_t1.or_reduce() | a_st1_t2.or_reduce();
            	lyhits[1] = st2;
            	lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
            	straightness = 2;
            	break;

            case 3:
            	a_st3=(ap_uint<12>(0),st3(8,6));
            	a_st4=(ap_uint<12>(0),st4(8,6));

            	lyhits[2] = st1[16] | st1[14];
            	lyhits[1] = st2;
            	lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
            	straightness = 0x3;
            	break;

            case 4:
            	lyhits[2] = st1[15];
            	lyhits[1] = st2;
            	lyhits[0] = st3[7] | st4[7];
            	straightness = 0x4;
            	break;

            default:
                break;

    	}

        qcode_p[mi] = 0;

        more_than_one = (lyhits != 0x0 && lyhits != 0x1 && lyhits != 0x2 && lyhits != 0x4) ? 1 : 0;
        more_than_zero = (lyhits != 0x0) ? 1 : 0;
//if(station==2 && cscid==64 && mi==1){
//	cout<<"straightness= "<<straightness<<" lyhits= "<<lyhits<<endl;
//	cout<<"bx[1][0][2]= "<<bx[1][0][2]<<" bx[1][0][1]= "<<bx[1][0][1]<<endl;
//	cout<<"more_than_zero= "<<more_than_zero<<" more_than_one= "<<more_than_one<<endl;
//}
		if
		(
		    bx[mi][foldn][2] == 0 && // if drift time is up, find quality of this pattern
            bx[mi][foldn][1] == 1 &&
			more_than_one// remove single-layer and ME3-4 hit patterns
		){
			// this quality code scheme is giving almost-equal priority to more stations and better straightness.
			// station 1 has higher weight, station 2 lower, st. 3 and 4 lowest
			qcode_p[mi] = (straightness[2], lyhits[2], straightness[1], lyhits[1], straightness[0], lyhits[0]);
		}

	   // process bx shifter
        bx[mi][foldn][2] = bx[mi][foldn][1];
        bx[mi][foldn][1] = bx[mi][foldn][0];
        bx[mi][foldn][0] = more_than_zero; // put 1 in shifter when one layer is hit


}
     a_qcode = 0;

     // find max quality on each clock
	comp1[0] = qcode_p[0] > qcode_p[1] ? qcode_p[0] : qcode_p[1];
	comp1[1] = qcode_p[2] > qcode_p[3] ? qcode_p[2] : qcode_p[3];

	comp2 = comp1[0] > comp1[1] ? comp1[0] : comp1[1];

	a_qcode = comp2 > qcode_p[4] ? comp2 : qcode_p[4];

	*qcode=a_qcode;


}

