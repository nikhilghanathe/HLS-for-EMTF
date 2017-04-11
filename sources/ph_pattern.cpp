#include <ap_int.h>
#include "spbits.h"
#include "ph_pattern.h"


void ph_pattern::ph_pattern_exec(
        ap_uint<full_pat_w_st1> st1,
        ap_uint<1> st2,
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
#pragma HLS ARRAY_PARTITION variable=bx complete dim=0
     int mi=0;
 //    ap_uint<3> bx[red_pat_w_st1];

     ap_uint<3> lyhits=0;
     ap_uint<6> qcode_p [9];
#pragma HLS ARRAY_PARTITION variable=qcode_p complete dim=0
     ap_uint<3> straightness;
     ap_uint<6> comp1 [4];
#pragma HLS ARRAY_PARTITION variable=comp1 complete dim=0
     ap_uint<6> comp2 [2];
     ap_uint<6> comp3;

     ap_uint<8> a_st1;
     ap_uint<4> a_st4;
     ap_uint<8> a_st3;
     ap_uint<6> a_qcode;
     ap_uint<3> a_foldn;

     a_foldn=foldn;
label0:
{


     ph_for:for (mi = 0; mi < red_pat_w_st1; mi = mi + 1){
     #pragma HLS UNROLL
            a_st1=0;
            a_st3=0;
            a_st4=0;

            label2:switch (mi){

            case 0:
                    a_st1=st1(7,0);
                    a_st3=st3(14,7);
                    a_st4=st4(14,7);

                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = ((a_st3).or_reduce()) | (a_st4.or_reduce());
                    straightness = 0;
                    break;

            case 1:
                    a_st1=st1(30,23);
                    a_st3=st3(7,0);
                    a_st4=st4(7,0);

                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0;
                    break;

            case 2:
                    a_st1=st1(11,8);
                    a_st3=st3(14,7);
                    a_st4=st4(14,7);

                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x1;
                    break;

            case 3:
                    a_st1=st1(22,19);
                    a_st3=st3(7,0);
                    a_st4=st4(7,0);
                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x1;
                    break;

            case 4:
                    a_st1=st1(13,12);
                    a_st3=st3(10,7);
                    a_st4=st4(10,7);
                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x2;
                    break;

            case 5:
                    a_st1=st1(18,17);
                    a_st3=st3(7,5);
                    a_st4=st4(7,5);
                    lyhits[2] = a_st1.or_reduce();
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x2;
                    break;

            case 6:
                    a_st3=st3(8,7);
                    a_st4=st4(8,7);
                    lyhits[2] = st1[14];
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x3;
                    break;

            case 7:
                    a_st3=st3(7,6);
                    a_st4=st4(7,6);
                    lyhits[2] = st1[16];
                    lyhits[1] = st2;
                    lyhits[0] = (a_st3.or_reduce()) | (a_st4.or_reduce());
                    straightness = 0x3;
                    break;

            case 8:
                    lyhits[2] = st1[15];
                    lyhits[1] = st2;
                    lyhits[0] = st3[7] | st4[7];
                    straightness = 0x4;
                    break;

            default:
                break;

        }
            qcode_p[mi] = 0;



            bx[mi] = (lyhits == 0x0 ? 0x0 :\
                              ((int(bx[mi]) == 0x7) ? 0x7 :\
                              int(bx[mi]) + 0x1)); // bx starts counting at any hit in the pattern, even single

/*
            if(lyhits==0){
            	bx[mi]=0;
            }
            else if(bx[mi]==0x7){
            	bx[mi]=7;
            }
            else{
            	bx[mi]=bx[mi]+1;
            }

*/


            if
            (
             bx[mi] == drifttime && // if drift time is up, find quality of this pattern
                // remove single-layer and ME3-4 hit patterns
             lyhits != 0x1 &&
             lyhits != 0x2 &&
             lyhits != 0x4 &&
             lyhits != 0x0
            ){
                // this quality code scheme is giving almost-equal priority to more stations and better straightness.
                // station 1 has higher weight, station 2 lower, st. 3 and 4 lowest
               qcode_p[mi] = (straightness[2], lyhits[2], straightness[1], lyhits[1], straightness[0], lyhits[0]);
            }
            /*else
            {
            	qcode_p[mi]=0;
            }*/




        		 	//	    std::cout<<"bx["<<mi<<"]= "<<bx[mi]<<std::endl;
/*            if(station==2 && cscid==64){
                    cout<<"st1= "<<st1<<" st2= "<<st2<<" st3= "<<st3<<" st4= "<<st4<<" drifttime= "<<drifttime<<hex<<endl;
               	 cout<<"qcode_p["<<mi<<"]= "<<qcode_p[mi]<< "   bx[5]= "<<bx[5]<< "  lyhits= "<<lyhits<<hex<<endl;
                          }*/

           }

}
     a_qcode = 0;
            // find max quality on each clock
            comp1[0] = qcode_p[0] > qcode_p[1] ? qcode_p[0] : qcode_p[1];
            comp1[1] = qcode_p[2] > qcode_p[3] ? qcode_p[2] : qcode_p[3];
            comp1[2] = qcode_p[4] > qcode_p[5] ? qcode_p[4] : qcode_p[5];
            comp1[3] = qcode_p[6] > qcode_p[7] ? qcode_p[6] : qcode_p[7];

            comp2[0] = comp1[0] > comp1[1] ? comp1[0] : comp1[1];
            comp2[1] = comp1[2] > comp1[3] ? comp1[2] : comp1[3];

            comp3 = comp2[0] > comp2[1] ? comp2[0] : comp2[1];

            a_qcode = comp3 > qcode_p[8] ? comp3 : qcode_p[8];
            *qcode=a_qcode;

}

