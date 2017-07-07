#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/primitive.h"
#include "../interface/sp.h"


void sp_c::prim_conv_sector(/*inputs*/
		ap_uint<seg_ch> vpf [6][9],
		ap_uint<4> q[6][9][seg_ch],
		ap_uint<bw_wg> wg[6][9][seg_ch],
		ap_uint<bw_hs> hstr[6][9][seg_ch],
		ap_uint<4> cpat[6][9][seg_ch],

		/*outputs*/
		 ap_uint<bw_fph> ph[6][9][seg_ch],

		 // special th outputs for ME11 because of duplication
		 // [station][chamber][segment with duplicates], station 2 = neighbor segment
		 ap_uint<bw_th> th11[3][3][th_ch11],
		 ap_uint<bw_th> th[6][9][seg_ch],
		 ap_uint<seg_ch> vl[6][9],
		 ap_uint<3> phzvl[6][9],
		// me11a flags only for ME11 (stations 1,0, chambers 2:0)
		// [station][chamber][segment], station 2 = neighbor segment
		 ap_uint<seg_ch> me11a[3][3],
		 ap_uint<4> cpatr[6][9][seg_ch],
		 ap_uint<ph_hit_w> ph_hit[6][9],
		 ap_uint<th_hit_w> th_hit[6][9],
		 ap_uint<12> *r_out,

		/*inputs*/
		ap_uint<2> sel,
		ap_uint<bw_addr> addr,
		ap_uint<13> r_in,
		ap_uint<1> we,
		ap_uint<1> endcap,
		ap_uint<1> lat_test,
		ap_uint<9> cs[6]

		)

		{

#pragma HLS PROTOCOL fixed
#pragma HLS LATENCY max=0
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



	int i, j;

	static primitive inst_prim_conv[2][9];
	static primitive inst_prim_conv_1[3][9];
	static primitive11 inst_prim_conv11_5;
	static primitive inst_prim_conv_neighbor[9];
	static primitive11 inst_prim_conv11[2][3];


#pragma HLS ARRAY_PARTITION variable=inst_prim_conv complete dim=0
#pragma HLS ARRAY_PARTITION variable=inst_prim_conv_1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=inst_prim_conv11 complete dim=0

	ap_uint<12> r_out_w[6][9];
	ap_uint<12> temp;
	// wires for we signals for each module
	ap_uint<9> we_w[6];
	ap_uint<seg_ch> dummy[6][9];
#pragma HLS ARRAY_PARTITION variable=we_w complete dim=0
#pragma HLS ARRAY_PARTITION variable=dummy complete dim=0
#pragma HLS ARRAY_PARTITION variable=r_out_w complete dim=0

	// mux LUT outputs to r_out
	int s, c;

	for (i = 0; i < 6; i = i + 1) {
#pragma HLS UNROLL
		we_w[i]= we ? cs[i] : ap_uint<9>(0);
	}
//	for (i = 0; i < 6; i = i + 1) {
//		std::cout<<"we_w["<<i<<"]= "<<we_w[i]<<std::endl;
//	}

	inst_prim_conv11[0][0].pr=0;
	inst_prim_conv11[1][1].pr=1;
	for (i = 0; i < 2; i++) {
#pragma HLS UNROLL
		//station11
		prim_conv_sector_label1: for (j = 0; j < 3; j++) {
#pragma HLS UNROLL

			 //defparam pc11.station = i;
			 //defparam pc11.cscid = j;

			inst_prim_conv11[i][j].top_prim_conv11(vpf[i][j],q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j],
					ph[i][j], th11[i][j], &vl[i][j], &phzvl[i][j], &me11a[i][j],
					cpatr[i][j], &ph_hit[i][j], sel,  addr,
					endcap, &r_out_w[i][j]);

		}
	}









	prim_conv_sector_label01: for (i = 0; i < 2; i = i + 1) {
#pragma HLS UNROLL
		prim_conv_sector_label11: for (j = 3; j < 9; j = j + 1) {
#pragma HLS UNROLL

			inst_prim_conv[i][j].top_prim_conv(vpf[i][j],q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j], ph[i][j], th[i][j], &vl[i][j],
					&phzvl[i][j], &dummy[i][j], cpatr[i][j], &ph_hit[i][j],
					 sel, addr, endcap, lat_test, &r_out_w[i][j]

					);
			// block: station12
			if(this->pr)std::cout<<"PrimSector phzvl["<<i<<"]["<<j<<"]= "<<phzvl[i][j]<<std::endl;
		}
	}


	inst_prim_conv_1[0][0].pr=0;
	prim_conv_sector_label2: for (i = 2; i < 5; i = i + 1) {
#pragma HLS UNROLL
		prim_conv_sector_label3: for (j = 0; j < 9; j = j + 1) {
#pragma HLS UNROLL

			inst_prim_conv_1[i-2][j].top_prim_conv(vpf[i][j],q[i][j], wg[i][j], hstr[i][j],
					cpat[i][j], i,//station
					j,//cscid
					r_in, we_w[i][j], ph[i][j], th[i][j], &vl[i][j],
					&phzvl[i][j], &dummy[i][j], cpatr[i][j], &ph_hit[i][j],
					sel, addr, endcap, lat_test, &r_out_w[i][j]);
			// block: station
			if(this->pr)std::cout<<"PrimSector phzvl["<<i<<"]["<<j<<"]= "<<phzvl[i][j]<<std::endl;

		}
	}



	// neighbor sector single ME11 chamber
   inst_prim_conv11_5.top_prim_conv11(vpf[5][0],q[5][0], wg[5][0], hstr[5][0],
   					cpat[5][0], i,//station
   					j,//cscid
   					r_in, we_w[5][0], ph[5][0], th[5][0], &vl[5][0],
   					&phzvl[5][0], &me11a[2][0], cpatr[5][0], &ph_hit[5][0],
   					sel, addr, endcap,  &r_out_w[0][0]);
   if(this->pr)std::cout<<"PrimSector phzvl["<<5<<"]["<<0<<"]= "<<phzvl[5][0]<<std::endl;


   // rest of neighbor chambers
   for(j=1;j<9;j++){
	  int  station= (j < 3 ? 0 : (j+1)/2);
	  int cscid=(j < 3 ? j + 12 : (j-1)%2 + 9);
   inst_prim_conv_neighbor[j].top_prim_conv(vpf[5][j],q[5][j], wg[5][j], hstr[5][j],
   					cpat[5][j], station, cscid,
   					r_in, we_w[5][j], ph[5][j], th[5][j], &vl[5][j],
   					&phzvl[5][j], &dummy[5][j], cpatr[5][j], &ph_hit[5][j],
   					sel, addr, endcap, lat_test, &r_out_w[5][j]);

   if(this->pr)std::cout<<"PrimSector phzvl["<<5<<"]["<<j<<"]= "<<phzvl[5][j]<<std::endl;
   }





}

