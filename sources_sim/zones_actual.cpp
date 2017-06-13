#include <ap_int.h>
#include "spbits.h"
#include "zones.h"





/*
void zones()
{
std::cout<<"ph_raw_w: "<<ph_raw_w<<std::endl;
ap_uint<4> phzvl[5][9];
            phzvl[0][0]=0x8;
std::cout<<"phzvl: "<<phzvl[0][0]<<std::hex<<std::endl;
if(phzvl[0][0] & 0x1)
	std::cout<<" HI"<<std::endl;
else
	std::cout<<"BYE "<<std::endl;

ap_uint<4> ret=0x1;
phzvl[0][0](2,0)=phzvl[0][0](2,0) | ret;
std::cout<<"phzvl after : "<<phzvl[0][0]<<std::hex<<std::endl;


}
*/

using namespace std;





void zones_class::zones_actual(
		 ap_uint<3> phzvl[6][9],
		 ap_uint<ph_hit_w> ph_hit[6][9],
			 ap_uint<ph_raw_w> ph_zone[4][5])
{
#pragma HLS ARRAY_PARTITION variable=phzvl complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_hit complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_zone complete dim=0
#pragma HLS ARRAY_PARTITION variable=a_ph_zone complete dim=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
	// the hardcoded numbers in the code below come from ph_init_full* files generated by CMSSW
			// they are divided by 32 since pattern detectors are using 7-bit phi.
			// Offset is subtracted from them to account for possible chamber movement
			// CMSSW software has these numbers in ph_init_hard array, so it can generate ph_offsets

	const int ph_init_hard [5][16]= {{39,  57,  76, 39,  58,  76, 41,  60,  79, 39,  57,  76,21,21,23,21},
			{95, 114, 132, 95, 114, 133, 98, 116, 135, 95, 114, 132, 0, 0, 0, 0},
			{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
			{38,  76, 113, 39,  58,  76, 95, 114, 132,  1,  21,   0, 0, 0, 0, 0},
			{38,  76, 113, 38,  57,  76, 95, 113, 132,  1,  20,   0, 0, 0, 0, 0}};



			// ph zone 0 stations 1234
	ap_uint<3> a_phzvl[6][9];
	ap_uint<ph_hit_w> a_ph_hit[6][9];
#pragma HLS ARRAY_PARTITION variable=a_phzvl complete dim=0
#pragma HLS ARRAY_PARTITION variable=a_ph_hit complete dim=0

	for(int i=0;i<4;i++){
#pragma HLS UNROLL
    	for(int j=0;j<5;j++){
#pragma HLS UNROLL
    		a_ph_zone[i][j]=0;
    	}
    }



		// ph zone 0 stations 1234
		a_ph_zone[0][1] = 0;
		if (phzvl[5][0][0]) a_ph_zone[0][1](ph_init_hard[0][12]+ph_hit_w10-1, ph_init_hard[0][12]) =a_ph_zone[0][1](ph_init_hard[0][12]+ph_hit_w10-1, ph_init_hard[0][12]) |  ph_hit[5][0]; // neighbor sector
		if (phzvl[0][0][0]) a_ph_zone[0][1](ph_init_hard[0][0] +ph_hit_w10-1, ph_init_hard[0][0]) = a_ph_zone[0][1](ph_init_hard[0][0]+ph_hit_w10-1, ph_init_hard[0][0]) | ph_hit[0][0];
		if (phzvl[0][1][0]) a_ph_zone[0][1](ph_init_hard[0][1] +ph_hit_w10-1, ph_init_hard[0][1]) = a_ph_zone[0][1](ph_init_hard[0][1]+ph_hit_w10-1, ph_init_hard[0][1]) | ph_hit[0][1];
		if (phzvl[0][2][0]) a_ph_zone[0][1](ph_init_hard[0][2] +ph_hit_w10-1, ph_init_hard[0][2]) = a_ph_zone[0][1](ph_init_hard[0][2]+ph_hit_w10-1, ph_init_hard[0][2]) | ph_hit[0][2];
		if (phzvl[1][0][0]) a_ph_zone[0][1](ph_init_hard[1][0] +ph_hit_w10-1, ph_init_hard[1][0]) = a_ph_zone[0][1](ph_init_hard[1][0]+ph_hit_w10-1, ph_init_hard[1][0]) | ph_hit[1][0];
		if (phzvl[1][1][0]) a_ph_zone[0][1](ph_init_hard[1][1] +ph_hit_w10-1, ph_init_hard[1][1]) = a_ph_zone[0][1](ph_init_hard[1][1]+ph_hit_w10-1, ph_init_hard[1][1]) | ph_hit[1][1];
		if (phzvl[1][2][0]) a_ph_zone[0][1](ph_init_hard[1][2] +ph_hit_w10-1, ph_init_hard[1][2]) = a_ph_zone[0][1](ph_init_hard[1][2]+ph_hit_w10-1, ph_init_hard[1][2]) | ph_hit[1][2];

		a_ph_zone[0][2] = 0;
		if (phzvl[5][3][0]) a_ph_zone[0][2](ph_init_hard[2][9]+ph_hit_w20-1, ph_init_hard[2][9]) = a_ph_zone[0][2](ph_init_hard[2][9]+ph_hit_w20-1, ph_init_hard[2][9]) | ph_hit[5][3]; // neighbor sector
		if (phzvl[2][0][0]) a_ph_zone[0][2](ph_init_hard[2][0]+ph_hit_w20-1, ph_init_hard[2][0]) = a_ph_zone[0][2](ph_init_hard[2][0]+ph_hit_w20-1, ph_init_hard[2][0]) |  ph_hit[2][0];
		if (phzvl[2][1][0]) a_ph_zone[0][2](ph_init_hard[2][1]+ph_hit_w20-1, ph_init_hard[2][1]) = a_ph_zone[0][2](ph_init_hard[2][1]+ph_hit_w20-1, ph_init_hard[2][1]) |  ph_hit[2][1];
		if (phzvl[2][2][0]) a_ph_zone[0][2](ph_init_hard[2][2]+ph_hit_w20-1, ph_init_hard[2][2]) = a_ph_zone[0][2](ph_init_hard[2][2]+ph_hit_w20-1, ph_init_hard[2][2]) |  ph_hit[2][2];

		a_ph_zone[0][3] = 0;
		if (phzvl[5][5][0]) a_ph_zone[0][3](ph_init_hard[3][9]+ph_hit_w20-1, ph_init_hard[3][9]) =a_ph_zone[0][3](ph_init_hard[3][9]+ph_hit_w20-1, ph_init_hard[3][9]) | ph_hit[5][5]; // neighbor sector
		if (phzvl[3][0][0]) a_ph_zone[0][3](ph_init_hard[3][0]+ph_hit_w20-1, ph_init_hard[3][0]) =a_ph_zone[0][3](ph_init_hard[3][0]+ph_hit_w20-1, ph_init_hard[3][0]) | ph_hit[3][0];
		if (phzvl[3][1][0]) a_ph_zone[0][3](ph_init_hard[3][1]+ph_hit_w20-1, ph_init_hard[3][1]) =a_ph_zone[0][3](ph_init_hard[3][1]+ph_hit_w20-1, ph_init_hard[3][1]) |  ph_hit[3][1];
		if (phzvl[3][2][0]) a_ph_zone[0][3](ph_init_hard[3][2]+ph_hit_w20-1, ph_init_hard[3][2]) =a_ph_zone[0][3](ph_init_hard[3][2]+ph_hit_w20-1, ph_init_hard[3][2]) |  ph_hit[3][2];

		a_ph_zone[0][4] = 0;
		if (phzvl[5][7][0]) a_ph_zone[0][4](ph_init_hard[4][9]+ph_hit_w20-1, ph_init_hard[4][9]) = a_ph_zone[0][4](ph_init_hard[4][9]+ph_hit_w20-1, ph_init_hard[4][9]) | ph_hit[5][7]; // neighbor sector
		if (phzvl[4][0][0]) a_ph_zone[0][4](ph_init_hard[4][0]+ph_hit_w20-1, ph_init_hard[4][0]) = a_ph_zone[0][4](ph_init_hard[4][0]+ph_hit_w20-1, ph_init_hard[4][0]) | ph_hit[4][0];
		if (phzvl[4][1][0]) a_ph_zone[0][4](ph_init_hard[4][1]+ph_hit_w20-1, ph_init_hard[4][1]) = a_ph_zone[0][4](ph_init_hard[4][1]+ph_hit_w20-1, ph_init_hard[4][1]) | ph_hit[4][1];
		if (phzvl[4][2][0]) a_ph_zone[0][4](ph_init_hard[4][2]+ph_hit_w20-1, ph_init_hard[4][2]) = a_ph_zone[0][4](ph_init_hard[4][2]+ph_hit_w20-1, ph_init_hard[4][2]) | ph_hit[4][2];

		// ph zone 1 stations 1234
		a_ph_zone[1][1] = 0;
		if (phzvl[5][0][1]) a_ph_zone[1][1](ph_init_hard[0][12]+ph_hit_w10-1, ph_init_hard[0][12]) = a_ph_zone[1][1](ph_init_hard[0][12]+ph_hit_w10-1, ph_init_hard[0][12]) | ph_hit[5][0];
		if (phzvl[0][0][1]) a_ph_zone[1][1](ph_init_hard[0][0] +ph_hit_w10-1, ph_init_hard[0][0]) = a_ph_zone[1][1](ph_init_hard[0][0]+ph_hit_w10-1, ph_init_hard[0][0]) | ph_hit[0][0];
		if (phzvl[0][1][1]) a_ph_zone[1][1](ph_init_hard[0][1] +ph_hit_w10-1, ph_init_hard[0][1]) = a_ph_zone[1][1](ph_init_hard[0][1]+ph_hit_w10-1, ph_init_hard[0][1]) | ph_hit[0][1];
		if (phzvl[0][2][1]) a_ph_zone[1][1](ph_init_hard[0][2] +ph_hit_w10-1, ph_init_hard[0][2]) = a_ph_zone[1][1](ph_init_hard[0][2]+ph_hit_w10-1, ph_init_hard[0][2]) | ph_hit[0][2];
		if (phzvl[1][0][1]) a_ph_zone[1][1](ph_init_hard[1][0] +ph_hit_w10-1, ph_init_hard[1][0]) = a_ph_zone[1][1](ph_init_hard[1][0]+ph_hit_w10-1, ph_init_hard[1][0]) | ph_hit[1][0];
		if (phzvl[1][1][1]) a_ph_zone[1][1](ph_init_hard[1][1] +ph_hit_w10-1, ph_init_hard[1][1]) = a_ph_zone[1][1](ph_init_hard[1][1]+ph_hit_w10-1, ph_init_hard[1][1]) | ph_hit[1][1];
		if (phzvl[1][2][1]) a_ph_zone[1][1](ph_init_hard[1][2] +ph_hit_w10-1, ph_init_hard[1][2]) = a_ph_zone[1][1](ph_init_hard[1][2]+ph_hit_w10-1, ph_init_hard[1][2]) | ph_hit[1][2];

		a_ph_zone[1][2] = 0;
		if (phzvl[5][3][1]) a_ph_zone[1][2](ph_init_hard[2][9]+ph_hit_w20-1, ph_init_hard[2][9]) = a_ph_zone[1][2](ph_init_hard[2][9]+ph_hit_w20-1, ph_init_hard[2][9]) | ph_hit[5][3];
		if (phzvl[2][0][1]) a_ph_zone[1][2](ph_init_hard[2][0]+ph_hit_w20-1, ph_init_hard[2][0]) = a_ph_zone[1][2](ph_init_hard[2][0]+ph_hit_w20-1, ph_init_hard[2][0]) | ph_hit[2][0];
		if (phzvl[2][1][1]) a_ph_zone[1][2](ph_init_hard[2][1]+ph_hit_w20-1, ph_init_hard[2][1]) = a_ph_zone[1][2](ph_init_hard[2][1]+ph_hit_w20-1, ph_init_hard[2][1]) | ph_hit[2][1];
		if (phzvl[2][2][1]) a_ph_zone[1][2](ph_init_hard[2][2]+ph_hit_w20-1, ph_init_hard[2][2]) = a_ph_zone[1][2](ph_init_hard[2][2]+ph_hit_w20-1, ph_init_hard[2][2]) | ph_hit[2][2];


		a_ph_zone[1][3] = 0;
		if (phzvl[5][6][0]) a_ph_zone[1][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) = a_ph_zone[1][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) | ph_hit[5][6];
		if (phzvl[3][3][0]) a_ph_zone[1][3](ph_init_hard[3][3] +ph_hit_w10-1, ph_init_hard[3][3]) = a_ph_zone[1][3](ph_init_hard[3][3]+ph_hit_w10-1, ph_init_hard[3][3]) | ph_hit[3][3];
		if (phzvl[3][4][0]) a_ph_zone[1][3](ph_init_hard[3][4] +ph_hit_w10-1, ph_init_hard[3][4]) = a_ph_zone[1][3](ph_init_hard[3][4]+ph_hit_w10-1, ph_init_hard[3][4]) | ph_hit[3][4];
		if (phzvl[3][5][0]) a_ph_zone[1][3](ph_init_hard[3][5] +ph_hit_w10-1, ph_init_hard[3][5]) = a_ph_zone[1][3](ph_init_hard[3][5]+ph_hit_w10-1, ph_init_hard[3][5]) | ph_hit[3][5];
		if (phzvl[3][6][0]) a_ph_zone[1][3](ph_init_hard[3][6] +ph_hit_w10-1, ph_init_hard[3][6]) = a_ph_zone[1][3](ph_init_hard[3][6]+ph_hit_w10-1, ph_init_hard[3][6]) | ph_hit[3][6];
		if (phzvl[3][7][0]) a_ph_zone[1][3](ph_init_hard[3][7] +ph_hit_w10-1, ph_init_hard[3][7]) = a_ph_zone[1][3](ph_init_hard[3][7]+ph_hit_w10-1, ph_init_hard[3][7]) | ph_hit[3][7];
		if (phzvl[3][8][0]) a_ph_zone[1][3](ph_init_hard[3][8] +ph_hit_w10-1, ph_init_hard[3][8]) = a_ph_zone[1][3](ph_init_hard[3][8]+ph_hit_w10-1, ph_init_hard[3][8]) | ph_hit[3][8];

		a_ph_zone[1][4] = 0;
		if (phzvl[5][8][0]) a_ph_zone[1][4](ph_init_hard[4][10]+ph_hit_w10-1, ph_init_hard[4][10]) = a_ph_zone[1][4](ph_init_hard[4][10]+ph_hit_w10-1, ph_init_hard[4][10]) | ph_hit[5][8];
		if (phzvl[4][3][0]) a_ph_zone[1][4](ph_init_hard[4][3] +ph_hit_w10-1, ph_init_hard[4][3]) = a_ph_zone[1][4](ph_init_hard[4][3]+ph_hit_w10-1, ph_init_hard[4][3]) | ph_hit[4][3];
		if (phzvl[4][4][0]) a_ph_zone[1][4](ph_init_hard[4][4] +ph_hit_w10-1, ph_init_hard[4][4]) = a_ph_zone[1][4](ph_init_hard[4][4]+ph_hit_w10-1, ph_init_hard[4][4]) | ph_hit[4][4];
		if (phzvl[4][5][0]) a_ph_zone[1][4](ph_init_hard[4][5] +ph_hit_w10-1, ph_init_hard[4][5]) = a_ph_zone[1][4](ph_init_hard[4][5]+ph_hit_w10-1, ph_init_hard[4][5]) | ph_hit[4][5];
		if (phzvl[4][6][0]) a_ph_zone[1][4](ph_init_hard[4][6] +ph_hit_w10-1, ph_init_hard[4][6]) = a_ph_zone[1][4](ph_init_hard[4][6]+ph_hit_w10-1, ph_init_hard[4][6]) | ph_hit[4][6];
		if (phzvl[4][7][0]) a_ph_zone[1][4](ph_init_hard[4][7] +ph_hit_w10-1, ph_init_hard[4][7]) = a_ph_zone[1][4](ph_init_hard[4][7]+ph_hit_w10-1, ph_init_hard[4][7]) | ph_hit[4][7];
		if (phzvl[4][8][0]) a_ph_zone[1][4](ph_init_hard[4][8] +ph_hit_w10-1, ph_init_hard[4][8]) = a_ph_zone[1][4](ph_init_hard[4][8]+ph_hit_w10-1, ph_init_hard[4][8]) | ph_hit[4][8];

		// ph zone 2 stations 1234
		a_ph_zone[2][1] = 0;
		if (phzvl[5][1][0]) a_ph_zone[2][1](ph_init_hard[0][13]+ph_hit_w10-1, ph_init_hard[0][13]) = a_ph_zone[2][1](ph_init_hard[0][13]+ph_hit_w10-1, ph_init_hard[0][13]) | ph_hit[5][1];
		if (phzvl[0][3][0]) a_ph_zone[2][1](ph_init_hard[0][3] +ph_hit_w10-1, ph_init_hard[0][3]) = a_ph_zone[2][1](ph_init_hard[0][3]+ph_hit_w10-1, ph_init_hard[0][3]) | ph_hit[0][3];
		if (phzvl[0][4][0]) a_ph_zone[2][1](ph_init_hard[0][4] +ph_hit_w10-1, ph_init_hard[0][4]) = a_ph_zone[2][1](ph_init_hard[0][4]+ph_hit_w10-1, ph_init_hard[0][4]) | ph_hit[0][4];
		if (phzvl[0][5][0]) a_ph_zone[2][1](ph_init_hard[0][5] +ph_hit_w10-1, ph_init_hard[0][5]) = a_ph_zone[2][1](ph_init_hard[0][5]+ph_hit_w10-1, ph_init_hard[0][5]) | ph_hit[0][5];
		if (phzvl[1][3][0]) a_ph_zone[2][1](ph_init_hard[1][3] +ph_hit_w10-1, ph_init_hard[1][3]) = a_ph_zone[2][1](ph_init_hard[1][3]+ph_hit_w10-1, ph_init_hard[1][3]) | ph_hit[1][3];
		if (phzvl[1][4][0]) a_ph_zone[2][1](ph_init_hard[1][4] +ph_hit_w10-1, ph_init_hard[1][4]) = a_ph_zone[2][1](ph_init_hard[1][4]+ph_hit_w10-1, ph_init_hard[1][4]) | ph_hit[1][4];
		if (phzvl[1][5][0]) a_ph_zone[2][1](ph_init_hard[1][5] +ph_hit_w10-1, ph_init_hard[1][5]) = a_ph_zone[2][1](ph_init_hard[1][5]+ph_hit_w10-1, ph_init_hard[1][5]) | ph_hit[1][5];

		a_ph_zone[2][2] = 0;
		if (phzvl[5][4][0]) a_ph_zone[2][2](ph_init_hard[2][10]+ph_hit_w10-1, ph_init_hard[2][10]) = a_ph_zone[2][2](ph_init_hard[2][10]+ph_hit_w10-1, ph_init_hard[2][10]) | ph_hit[5][4];
		if (phzvl[2][3][0]) a_ph_zone[2][2](ph_init_hard[2][3] +ph_hit_w10-1, ph_init_hard[2][3]) = a_ph_zone[2][2](ph_init_hard[2][3]+ph_hit_w10-1, ph_init_hard[2][3]) | ph_hit[2][3];
		if (phzvl[2][4][0]) a_ph_zone[2][2](ph_init_hard[2][4] +ph_hit_w10-1, ph_init_hard[2][4]) = a_ph_zone[2][2](ph_init_hard[2][4]+ph_hit_w10-1, ph_init_hard[2][4]) | ph_hit[2][4];
		if (phzvl[2][5][0]) a_ph_zone[2][2](ph_init_hard[2][5] +ph_hit_w10-1, ph_init_hard[2][5]) = a_ph_zone[2][2](ph_init_hard[2][5]+ph_hit_w10-1, ph_init_hard[2][5]) | ph_hit[2][5];
		if (phzvl[2][6][0]) a_ph_zone[2][2](ph_init_hard[2][6] +ph_hit_w10-1, ph_init_hard[2][6]) = a_ph_zone[2][2](ph_init_hard[2][6]+ph_hit_w10-1, ph_init_hard[2][6]) | ph_hit[2][6];
		if (phzvl[2][7][0]) a_ph_zone[2][2](ph_init_hard[2][7] +ph_hit_w10-1, ph_init_hard[2][7]) = a_ph_zone[2][2](ph_init_hard[2][7]+ph_hit_w10-1, ph_init_hard[2][7]) | ph_hit[2][7];
		if (phzvl[2][8][0]) a_ph_zone[2][2](ph_init_hard[2][8] +ph_hit_w10-1, ph_init_hard[2][8]) = a_ph_zone[2][2](ph_init_hard[2][8]+ph_hit_w10-1, ph_init_hard[2][8]) | ph_hit[2][8];
	//	cout<<"a_ph_zone[2][2]= "<<a_ph_zone[2][2]<<endl;

		a_ph_zone[2][3] = 0;
		if (phzvl[5][6][1]) a_ph_zone[2][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) = a_ph_zone[2][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) | ph_hit[5][6];
		if (phzvl[3][3][1]) a_ph_zone[2][3](ph_init_hard[3][3] +ph_hit_w10-1, ph_init_hard[3][3]) = a_ph_zone[2][3](ph_init_hard[3][3]+ph_hit_w10-1, ph_init_hard[3][3]) | ph_hit[3][3];
		if (phzvl[3][4][1]) a_ph_zone[2][3](ph_init_hard[3][4] +ph_hit_w10-1, ph_init_hard[3][4]) = a_ph_zone[2][3](ph_init_hard[3][4]+ph_hit_w10-1, ph_init_hard[3][4]) | ph_hit[3][4];
		if (phzvl[3][5][1]) a_ph_zone[2][3](ph_init_hard[3][5] +ph_hit_w10-1, ph_init_hard[3][5]) = a_ph_zone[2][3](ph_init_hard[3][5]+ph_hit_w10-1, ph_init_hard[3][5]) | ph_hit[3][5];
		if (phzvl[3][6][1]) a_ph_zone[2][3](ph_init_hard[3][6] +ph_hit_w10-1, ph_init_hard[3][6]) = a_ph_zone[2][3](ph_init_hard[3][6]+ph_hit_w10-1, ph_init_hard[3][6]) | ph_hit[3][6];
		if (phzvl[3][7][1]) a_ph_zone[2][3](ph_init_hard[3][7] +ph_hit_w10-1, ph_init_hard[3][7]) = a_ph_zone[2][3](ph_init_hard[3][7]+ph_hit_w10-1, ph_init_hard[3][7]) | ph_hit[3][7];
		if (phzvl[3][8][1]) a_ph_zone[2][3](ph_init_hard[3][8] +ph_hit_w10-1, ph_init_hard[3][8]) = a_ph_zone[2][3](ph_init_hard[3][8]+ph_hit_w10-1, ph_init_hard[3][8]) | ph_hit[3][8];

		a_ph_zone[2][4] = 0;
		//cout<<"1 a_ph_zone[2][4]= "<<a_ph_zone[2][4]<<endl;
		if (phzvl[5][8][1]) a_ph_zone[2][4](ph_init_hard[4][10]+ph_hit_w10-1, ph_init_hard[4][10]) = a_ph_zone[2][4](ph_init_hard[4][10]+ph_hit_w10-1, ph_init_hard[4][10]) | ph_hit[5][8];
		if (phzvl[4][3][1]) a_ph_zone[2][4](ph_init_hard[4][3] +ph_hit_w10-1, ph_init_hard[4][3]) = a_ph_zone[2][4](ph_init_hard[4][3]+ph_hit_w10-1, ph_init_hard[4][3]) | ph_hit[4][3];
		if (phzvl[4][4][1]) a_ph_zone[2][4](ph_init_hard[4][4] +ph_hit_w10-1, ph_init_hard[4][4]) = a_ph_zone[2][4](ph_init_hard[4][4]+ph_hit_w10-1, ph_init_hard[4][4]) | ph_hit[4][4];
		if (phzvl[4][5][1]) a_ph_zone[2][4](ph_init_hard[4][5] +ph_hit_w10-1, ph_init_hard[4][5]) = a_ph_zone[2][4](ph_init_hard[4][5]+ph_hit_w10-1, ph_init_hard[4][5]) | ph_hit[4][5];
		if (phzvl[4][6][1]) a_ph_zone[2][4](ph_init_hard[4][6] +ph_hit_w10-1, ph_init_hard[4][6]) = a_ph_zone[2][4](ph_init_hard[4][6]+ph_hit_w10-1, ph_init_hard[4][6]) | ph_hit[4][6];
		if (phzvl[4][7][1]) a_ph_zone[2][4](ph_init_hard[4][7] +ph_hit_w10-1, ph_init_hard[4][7]) = a_ph_zone[2][4](ph_init_hard[4][7]+ph_hit_w10-1, ph_init_hard[4][7]) | ph_hit[4][7];
		if (phzvl[4][8][1]) a_ph_zone[2][4](ph_init_hard[4][8] +ph_hit_w10-1, ph_init_hard[4][8]) = a_ph_zone[2][4](ph_init_hard[4][8]+ph_hit_w10-1, ph_init_hard[4][8]) | ph_hit[4][8];
		//cout<<"a_ph_zone[2][4]= "<<a_ph_zone[2][4]<<endl;
		// ph zone 3 stations 1234
		a_ph_zone[3][1] = 0;
		a_ph_zone[3][1](ph_init_hard[0][14]+ph_hit_w10-1, ph_init_hard[0][14]) = a_ph_zone[3][1](ph_init_hard[0][14]+ph_hit_w10-1, ph_init_hard[0][14]) | ph_hit[5][2];
		a_ph_zone[3][1](ph_init_hard[0][6] +ph_hit_w10-1, ph_init_hard[0][6]) = a_ph_zone[3][1](ph_init_hard[0][6]+ph_hit_w10-1, ph_init_hard[0][6]) | ph_hit[0][6];
		a_ph_zone[3][1](ph_init_hard[0][7] +ph_hit_w10-1, ph_init_hard[0][7]) = a_ph_zone[3][1](ph_init_hard[0][7]+ph_hit_w10-1, ph_init_hard[0][7]) | ph_hit[0][7];
		a_ph_zone[3][1](ph_init_hard[0][8] +ph_hit_w10-1, ph_init_hard[0][8]) = a_ph_zone[3][1](ph_init_hard[0][8]+ph_hit_w10-1, ph_init_hard[0][8]) | ph_hit[0][8];
		a_ph_zone[3][1](ph_init_hard[1][6] +ph_hit_w10-1, ph_init_hard[1][6]) = a_ph_zone[3][1](ph_init_hard[1][6]+ph_hit_w10-1, ph_init_hard[1][6]) | ph_hit[1][6];
		a_ph_zone[3][1](ph_init_hard[1][7] +ph_hit_w10-1, ph_init_hard[1][7]) = a_ph_zone[3][1](ph_init_hard[1][7]+ph_hit_w10-1, ph_init_hard[1][7]) | ph_hit[1][7];
		a_ph_zone[3][1](ph_init_hard[1][8] +ph_hit_w10-1, ph_init_hard[1][8]) = a_ph_zone[3][1](ph_init_hard[1][8]+ph_hit_w10-1, ph_init_hard[1][8]) | ph_hit[1][8];


		a_ph_zone[3][2] = 0;
		if (phzvl[5][4][1]) a_ph_zone[3][2](ph_init_hard[2][10]+ph_hit_w10-1, ph_init_hard[2][10]) = a_ph_zone[3][2](ph_init_hard[2][10]+ph_hit_w10-1, ph_init_hard[2][0]) | ph_hit[5][4];
		if (phzvl[2][3][1]) a_ph_zone[3][2](ph_init_hard[2][3] +ph_hit_w10-1, ph_init_hard[2][3]) = a_ph_zone[3][2](ph_init_hard[2][3]+ph_hit_w10-1, ph_init_hard[2][3]) | ph_hit[2][3];
		if (phzvl[2][4][1]) a_ph_zone[3][2](ph_init_hard[2][4] +ph_hit_w10-1, ph_init_hard[2][4]) = a_ph_zone[3][2](ph_init_hard[2][4]+ph_hit_w10-1, ph_init_hard[2][4]) | ph_hit[2][4];
		if (phzvl[2][5][1]) a_ph_zone[3][2](ph_init_hard[2][5] +ph_hit_w10-1, ph_init_hard[2][5]) = a_ph_zone[3][2](ph_init_hard[2][5]+ph_hit_w10-1, ph_init_hard[2][5]) | ph_hit[2][5];
		if (phzvl[2][6][1]) a_ph_zone[3][2](ph_init_hard[2][6] +ph_hit_w10-1, ph_init_hard[2][6]) = a_ph_zone[3][2](ph_init_hard[2][6]+ph_hit_w10-1, ph_init_hard[2][6]) | ph_hit[2][6];
		if (phzvl[2][7][1]) a_ph_zone[3][2](ph_init_hard[2][7] +ph_hit_w10-1, ph_init_hard[2][7]) = a_ph_zone[3][2](ph_init_hard[2][7]+ph_hit_w10-1, ph_init_hard[2][7]) | ph_hit[2][7];
		if (phzvl[2][8][1]) a_ph_zone[3][2](ph_init_hard[2][8] +ph_hit_w10-1, ph_init_hard[2][8]) = a_ph_zone[3][2](ph_init_hard[2][8]+ph_hit_w10-1, ph_init_hard[2][8]) | ph_hit[2][8];

		a_ph_zone[3][3] = 0;
		if (phzvl[5][6][2]) a_ph_zone[3][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) = a_ph_zone[3][3](ph_init_hard[3][10]+ph_hit_w10-1, ph_init_hard[3][10]) | ph_hit[5][6];
		if (phzvl[3][3][2]) a_ph_zone[3][3](ph_init_hard[3][3] +ph_hit_w10-1, ph_init_hard[3][3]) = a_ph_zone[3][3](ph_init_hard[3][3]+ph_hit_w10-1, ph_init_hard[3][3]) | ph_hit[3][3];
		if (phzvl[3][4][2]) a_ph_zone[3][3](ph_init_hard[3][4] +ph_hit_w10-1, ph_init_hard[3][4]) = a_ph_zone[3][3](ph_init_hard[3][4]+ph_hit_w10-1, ph_init_hard[3][4]) | ph_hit[3][4];
		if (phzvl[3][5][2]) a_ph_zone[3][3](ph_init_hard[3][5] +ph_hit_w10-1, ph_init_hard[3][5]) = a_ph_zone[3][3](ph_init_hard[3][5]+ph_hit_w10-1, ph_init_hard[3][5]) | ph_hit[3][5];
		if (phzvl[3][6][2]) a_ph_zone[3][3](ph_init_hard[3][6] +ph_hit_w10-1, ph_init_hard[3][6]) = a_ph_zone[3][3](ph_init_hard[3][6]+ph_hit_w10-1, ph_init_hard[3][6]) | ph_hit[3][6];
		if (phzvl[3][7][2]) a_ph_zone[3][3](ph_init_hard[3][7] +ph_hit_w10-1, ph_init_hard[3][7]) = a_ph_zone[3][3](ph_init_hard[3][7]+ph_hit_w10-1, ph_init_hard[3][7]) | ph_hit[3][7];
		if (phzvl[3][8][2]) a_ph_zone[3][3](ph_init_hard[3][8] +ph_hit_w10-1, ph_init_hard[3][8]) = a_ph_zone[3][3](ph_init_hard[3][8]+ph_hit_w10-1, ph_init_hard[3][8]) | ph_hit[3][8];

		a_ph_zone[3][4] = 0; // no st 4 in this zone



	     /*********assign output******/

	        zones_label0:for(int i=0;i<4;i++){
#pragma HLS UNROLL
	        	zones_label1:for(int j=0;j<5;j++){
#pragma HLS UNROLL
	        		ph_zone[i][j]=a_ph_zone[i][j];
	        	}
	        }
}


