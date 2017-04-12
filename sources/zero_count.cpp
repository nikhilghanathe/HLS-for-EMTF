#include <ap_int.h>
#include "best_track.h"


//optimized implementation to count number of zeroes in the 12-bit input
ap_uint<4> best_track::zero_count(ap_uint<12> larger){
	ap_uint<6> temp;
#pragma HLS INLINE
#pragma HLS LATENCY max=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
temp=0;
ap_uint<1> a,b,c,d, a1,b1,c1,d1, a2,b2,c2,d2;
ap_uint<1> y0,y1,y2 ,y0a,y1a,y2a, y0b,y1b,y2b;

//assign inputs
a=larger[3]; b=larger[2]; c=larger[1]; d=larger[0];
a1=larger[7]; b1=larger[6]; c1=larger[5]; d1=larger[4];
a2=larger[11]; b2=larger[10]; c2=larger[9]; d2=larger[8];


//bits 0-3
y0= ((c ^ d) & (~(a ^ b)))| ((~(c ^ d)) & (a ^ b));
y1= (~a & ~c & d) | (~a & ~b & c) | (~a & c & ~d) | (~b & c & ~d) | (a & ~c & ~d) | (a & ~b & ~c);
y2= ((~a) & (~b) & (~c) & (~d));

//bits 7-4
y0a= ((c1 ^ d1) & (~(a1 ^ b1)))| ((~(c1 ^ d1)) & (a1 ^ b1));
y1a= (~a1 & ~c1 & d1) | (~a1 & ~b1 & c1) | (~a1 & c1 & ~d1) | (~b1 & c1 & ~d1) | (a1 & ~c1 & ~d1) | (a1 & ~b1 & ~c1);
y2a= ((~a1) & (~b1) & (~c1) & (~d1));

//bits 11-8
y0b= ((c2 ^ d2) & (~(a2 ^ b2)))| ((~(c2 ^ d2)) & (a2 ^ b2));
y1b= (~a2 & ~c2 & d2) | (~a2 & ~b2 & c2) | (~a2 & c2 & ~d2) | (~b2 & c2 & ~d2) | (a2 & ~c2 & ~d2) | (a2 & ~b2 & ~c2);
y2b= ((~a2) & (~b2) & (~c2) & (~d2));

ap_uint<4> sum_t=(y2,y1,y0) + (y2a,y1a,y0a) + (y2b,y1b,y0b);

return sum_t;

}
