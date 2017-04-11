#include<ap_int.h>
#include "spbits.h"
#include "primitive.h"
#include "sp.h"
#include <ap_utils.h>

void sp_c::prim_conv_sector(/*inputs*/
		ap_uint<4> q[5][9][seg_ch],
		ap_uint<bw_wg> wg[5][9][seg_ch],
		ap_uint<bw_hs> hstr[5][9][seg_ch],
		ap_uint<4> cpat[5][9][seg_ch],

		/*outputs*/
		 ap_uint<bw_fph> ph[5][9][seg_ch],
		 ap_uint<bw_th> th11[2][3][th_ch11],
		 ap_uint<bw_th> th[5][9][seg_ch],
		 ap_uint<seg_ch> vl[5][9],
		 ap_uint<3> phzvl[5][9],
		 ap_uint<seg_ch> me11a[2][3],
		 ap_uint<4> cpatr[5][9][seg_ch],
		 ap_uint<ph_hit_w> ph_hit[5][9],
		 ap_uint<th_hit_w> th_hit[5][9],
		 ap_uint<12> *r_out,

		/*inputs*/
		ap_uint<2> sel,
		ap_uint<bw_addr> addr,
		ap_uint<12> r_in,
		ap_uint<1> we,
		ap_uint<1> endcap,
		ap_uint<1> lat_test,
		ap_uint<1> print_flag,
		ap_uint<9> cs[5]

		)

		{
//#pragma HLS LATENCY min=0 max=0
//	ap_wait();
#pragma HLS PROTOCOL fixed

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=cpat complete dim=0
#pragma HLS ARRAY_PARTITION variable=hstr complete dim=0
#pragma HLS ARRAY_PARTITION variable=wg complete dim=0
#pragma HLS ARRAY_PARTITION variable=q dim=0
#pragma HLS ARRAY_PARTITION variable=cs complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_hit complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_hit complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpatr complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11a complete dim=0
#pragma HLS ARRAY_PARTITION variable=phzvl complete dim=0
#pragma HLS ARRAY_PARTITION variable=vl complete dim=0
#pragma HLS ARRAY_PARTITION variable=th complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11 complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph complete dim=0


/*
#pragma HLS INTERFACE register port=ph
#pragma HLS INTERFACE register port=th
#pragma HLS INTERFACE register port=vl
#pragma HLS INTERFACE register port=me11a
#pragma HLS INTERFACE register port=phzvl
#pragma HLS INTERFACE register port=cpatr
#pragma HLS INTERFACE register port=ph_hit
#pragma HLS INTERFACE register port=th_hit
#pragma HLS INTERFACE register port=r_out
*/


	int i, j;

	static primitive inst_prim_conv[2][9];
	static primitive inst_prim_conv_1[3][9];
	static primitive11 inst_prim_conv11[2][3];

#pragma HLS ARRAY_PARTITION variable=inst_prim_conv complete dim=0
#pragma HLS ARRAY_PARTITION variable=inst_prim_conv_1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=inst_prim_conv11 complete dim=0

	ap_uint<12> r_out_w[5][9];
	ap_uint<12> temp;
	// wires for we signals for each module
	ap_uint<9> we_w[5];
	ap_uint<seg_ch> dummy[5][9];
#pragma HLS ARRAY_PARTITION variable=we_w complete dim=0
#pragma HLS ARRAY_PARTITION variable=dummy complete dim=0
#pragma HLS ARRAY_PARTITION variable=r_out_w complete dim=0

	// mux LUT outputs to r_out
	int s, c;

	//temp = 0x0;
/*	for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL

		for (c = 0; c < 9; c = c + 1) // chamber loop
				{
#pragma HLS UNROLL
			if (cs[s][c])
				temp = temp | r_out_w[s][c];
			*r_out = temp;
		}
	}*/



	for (i = 0; i < 5; i = i + 1) {
#pragma HLS UNROLL
		we_w[i]= we ? cs[i] : ap_uint<9>(0);
	}




	/*for (i = 0; i < 5; i = i + 1) {
		for(int j=0;j<9;j++)
		std::cout<<"r_out_w["<<i<<"]["<<j<<"] = "<<r_out_w[i][j]<<std::endl;
	}
*/








	prim_conv_sector_label0: for (i = 0; i < 2/*2*/; i++) {
#pragma HLS UNROLL
		//station11
		prim_conv_sector_label1: for (j = 0; j < 3/*3*/; j++) {
#pragma HLS UNROLL
			//!!!!!!!!!attention!!!!!!!!
			 //* defparam pc11.station = i;
			 //defparam pc11.cscid = j;
			 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			inst_prim_conv11[i][j].top_prim_conv11(q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j],
					ph[i][j], th11[i][j], &vl[i][j], &phzvl[i][j], &me11a[i][j],
					cpatr[i][j], &ph_hit[i][j], &th_hit[i][j], sel,  addr,
					endcap, print_flag,&r_out_w[i][j]);

		}
	}














	prim_conv_sector_label01: for (i = 0; i < 2; i = i + 1) {
#pragma HLS UNROLL
		prim_conv_sector_label11: for (j = 3; j < 9; j = j + 1) {
#pragma HLS UNROLL

			inst_prim_conv[i][j].top_prim_conv(q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j], ph[i][j], th[i][j], &vl[i][j],
					&phzvl[i][j], &dummy[i][j], cpatr[i][j], &ph_hit[i][j],
					&th_hit[i][j], sel, addr, endcap, lat_test,print_flag, &r_out_w[i][j]

					);
			// block: station12

		}
	}



	prim_conv_sector_label2: for (i = 2; i < 5; i = i + 1) {
#pragma HLS UNROLL
		prim_conv_sector_label3: for (j = 0; j < 9; j = j + 1) {
#pragma HLS UNROLL

			inst_prim_conv_1[i-2][j].top_prim_conv(q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j], ph[i][j], th[i][j], &vl[i][j],
					&phzvl[i][j], &dummy[i][j], cpatr[i][j], &ph_hit[i][j],
					&th_hit[i][j], sel, addr, endcap, lat_test,print_flag, &r_out_w[i][j]);
			// block: station

		}
	}

















}

