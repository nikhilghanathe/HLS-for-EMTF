#include <ap_int.h>
#include "spbits.h"



class primitive11 {
public:
	ap_uint<12> params[6];
	ap_uint<6> th_mem[th_mem_sz];
	ap_uint<4> th_corr_mem[th_corr_mem_sz];

	void prim_conv11(
					ap_uint<4> quality[seg_ch],
					ap_uint<bw_wg> wiregroup[seg_ch],
					ap_uint<bw_hs> hstrip[seg_ch],
					ap_uint<4> clctpat[seg_ch],
					ap_uint<8> station,
					ap_uint<8> cscid,
					 ap_uint<bw_fph> ph[seg_ch],
					 ap_uint<bw_th> th[seg_ch*seg_ch],
					 ap_uint<seg_ch> *vl,
					 ap_uint<3> *phzvl,
					 ap_uint<seg_ch> *me11a,
					 ap_uint<4> clctpat_r[seg_ch],
					 ap_uint<ph_hit_w> *ph_hit,
					 ap_uint<th_hit_w> *th_hit,
					ap_uint<2>  sel,
					ap_uint<bw_addr>  addr,
					ap_uint<1> endcap,
					ap_uint<12> *r_out
					);
		void mem11(ap_uint<12> r_in,
				ap_uint<1> we,
				ap_uint<bw_addr> addr,
				ap_uint<2> sel,
				//ap_uint<12> *r_out,
				const int station,
				const int cscid,
				ap_uint<1> endcap
				);


		void top_prim_conv11(
						ap_uint<4> quality[seg_ch],
						ap_uint<bw_wg> wiregroup[seg_ch],
						ap_uint<bw_hs> hstrip[seg_ch],
						ap_uint<4> clctpat[seg_ch],
						ap_uint<8> station,
						ap_uint<8> cscid,
						ap_uint<12> r_in,
						ap_uint<1> we,
						 ap_uint<bw_fph> ph[seg_ch],
						 ap_uint<bw_th> th[seg_ch*seg_ch],
						 ap_uint<seg_ch> *vl,
						 ap_uint<3> *phzvl,
						 ap_uint<seg_ch> *me11a,
						 ap_uint<4> clctpat_r[seg_ch],
						 ap_uint<ph_hit_w> *ph_hit,
						 ap_uint<th_hit_w> *th_hit,
						ap_uint<2>  sel,
						ap_uint<bw_addr>  addr,
						ap_uint<1> endcap,
						ap_uint<1> print_flag,
						ap_uint<12> *r_out);

		primitive11()
		{
	#pragma HLS ARRAY_PARTITION variable=params complete dim=0
	#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0
	#pragma HLS ARRAY_PARTITION variable=th_corr_mem complete dim=0

		}
};
class primitive{

public:

	ap_uint<12> params[6];
	ap_uint<12> th_mem[th_mem_sz];


	void prim_conv1(
			ap_uint<4> quality[seg_ch],
			ap_uint<bw_wg> wiregroup[seg_ch],
			ap_uint<bw_hs> hstrip[seg_ch],
			ap_uint<4> clctpat[seg_ch],
			ap_uint<8> station,
			ap_uint<8> cscid,
			ap_uint<bw_fph> ph[seg_ch],
			ap_uint<bw_th> th[seg_ch],
			ap_uint<seg_ch> *vl,
			ap_uint<3> *phzvl,
			ap_uint<seg_ch> *me11a,
			ap_uint<4> clctpat_r[seg_ch],
		    ap_uint<ph_hit_w> *ph_hit,
		    ap_uint<th_hit_w> *th_hit,
			ap_uint<2>  sel,
			ap_uint<bw_addr>  addr,
			ap_uint<1> endcap,
			ap_uint<1> lat_test,
			ap_uint<12> *r_out
			);

	void mem(ap_uint<12> r_in,
			ap_uint<1> we,
			ap_uint<bw_addr> addr,
			ap_uint<2> sel,
			const int station,
			const int cscid
			);

	void top_prim_conv(
			ap_uint<4> quality[seg_ch],
					ap_uint<bw_wg> wiregroup[seg_ch],
					ap_uint<bw_hs> hstrip[seg_ch],
					ap_uint<4> clctpat[seg_ch],
					ap_uint<8> station,
					ap_uint<8> cscid,
					ap_uint<12> r_in,
					ap_uint<1> we,
					ap_uint<bw_fph> ph[seg_ch],
					ap_uint<bw_th> th[seg_ch],
					ap_uint<seg_ch> *vl,
					ap_uint<3> *phzvl,
					ap_uint<seg_ch> *me11a,
					ap_uint<4> clctpat_r[seg_ch],
					ap_uint<ph_hit_w> *ph_hit,
					ap_uint<th_hit_w> *th_hit,
					ap_uint<2>  sel,
					ap_uint<bw_addr>  addr,
					ap_uint<1> endcap,
					ap_uint<1> lat_test,
					ap_uint<1> print_flag,
					ap_uint<12> *r_out);




	primitive()
	{
#pragma HLS ARRAY_PARTITION variable=params complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0


	}


};
