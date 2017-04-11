#include <ap_int.h>
#include "best_track.h"
using namespace std;
//ap_uint<4> zero_count(ap_uint<8> larger);
void best_track::zero_count_36bits(ap_uint<36> larger, ap_uint<6> *sum){
	ap_uint<6> temp;
#pragma HLS INLINE off
#pragma HLS LATENCY max=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
temp=0;
ap_uint<1> a,b,c,d, a1,b1,c1,d1;
ap_uint<1> y0,y1,y2 ,y0a,y1a,y2a;
a=larger[3]; b=larger[2]; c=larger[1]; d=larger[0];
a1=larger[7]; b1=larger[6]; c1=larger[5]; d1=larger[4];

ap_uint<8> temp1,temp2,temp3,temp4,temp5;
ap_uint<6> sum1,sum2,sum3,sum4,sum5;
temp1=larger(7,0);
temp2=larger(15,8);
temp3=larger(23,16);
temp4=larger(31,24);
temp5=(ap_uint<4>(0xF),larger(35,32));

sum1=zero_count(temp1);
sum2=zero_count(temp2);
sum3=zero_count(temp3);
sum4=zero_count(temp4);
sum5=zero_count(temp5);
temp=sum1+sum2+sum3+sum4+sum5;

*sum=temp;
}

