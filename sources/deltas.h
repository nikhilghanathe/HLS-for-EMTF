#include <ap_int.h>
#include "spbits.h"

#define nodiff ((1<<(bw_th))-1)
#define seg_1 th_ch11



class delta{

public:


	void best_delta_seg_ch(
				ap_uint<bw_th> dth [seg_ch*seg_ch], //change this when nseg value is changed
				ap_uint<seg_ch*seg_ch>  sth,//change this when nseg value is changed
				ap_uint<seg_ch*seg_ch>  dvl,//change this when nseg value is changed
				ap_uint<bw_th> *bth, // smallest delta
				ap_uint<1>   *bsg, // sign of bth
				ap_uint<1>  *bvl, // valid flag
				ap_uint<2> *bnm // winner number//change this when bnum value is changed

				);
	void best_delta_seg1(
				ap_uint<bw_th> dth [seg_1 * seg_ch],
				ap_uint<seg_1 * seg_ch>  sth,
				ap_uint<seg_1 * seg_ch>  dvl,
				ap_uint<bw_th> *bth, // smallest delta
				ap_uint<1>   *bsg, // sign of bth
				ap_uint<1>  *bvl, // valid flag
				ap_uint<3> *bnm // winner number
				);

	void deltas_m0(
			ap_uint<seg_ch> vi [4], // valid
				ap_uint<2> hi [4], // bx index
				ap_uint<3>  ci [4], // chamber
				ap_uint<4>  si, // segment
				ap_uint<bw_fph> ph_match [4], // matching ph
				// theta coordinates [station][segment]
				ap_uint<bw_th> th_match [4][seg_ch],
				// ME11 duplicated thetas [segment]
				ap_uint<bw_th> th_match11 [th_ch11],
				ap_uint<4> cpat_match [4], // matching pattern
				ap_uint<bwr>  ph_q, // pattern rank, carries straigtness and ph station information
				ap_uint<bw_th>  th_window, // max th diff

				// precise phi and theta
				ap_uint<bw_fph> *phi,
				ap_uint<bw_th>  *theta,
				// [station]
				ap_uint<4> 	cpattern [4],
				// ph and th deltas from best stations
				// indexes: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
				ap_uint<bw_fph> delta_ph [6],
				ap_uint<bw_th>  delta_th [6],
				ap_uint<6> *sign_ph,
				ap_uint<6> *sign_th,
				ap_uint<bwr+1> *rank, // output rank, to be used for sorting
				ap_uint<seg_ch> vir[4], // valid
				ap_uint<2> hir [4], // bx index
				ap_uint<3> cir [4], // chamber
				ap_uint<4> *sir // segment
				);

	void deltas_m1(
				ap_uint<seg_ch> vi [4], // valid
					ap_uint<2> hi [4], // bx index
					ap_uint<3>  ci [4], // chamber
					ap_uint<4>  si, // segment
					ap_uint<bw_fph> ph_match [4], // matching ph
					// theta coordinates [station][segment]
					ap_uint<bw_th> th_match [4][seg_ch],
					// ME11 duplicated thetas [segment]
					ap_uint<bw_th> th_match11 [th_ch11],
					ap_uint<4> cpat_match [4], // matching pattern
					ap_uint<bwr>  ph_q, // pattern rank, carries straigtness and ph station information
					ap_uint<bw_th>  th_window, // max th diff

					// precise phi and theta
					ap_uint<bw_fph> *phi,
					ap_uint<bw_th>  *theta,
					// [station]
					ap_uint<4> 	cpattern [4],
					// ph and th deltas from best stations
					// indexes: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
					ap_uint<bw_fph> delta_ph [6],
					ap_uint<bw_th>  delta_th [6],
					ap_uint<6> *sign_ph,
					ap_uint<6> *sign_th,
					ap_uint<bwr+1> *rank, // output rank, to be used for sorting
					ap_uint<seg_ch> vir[4], // valid
					ap_uint<2> hir [4], // bx index
					ap_uint<3> cir [4], // chamber
					ap_uint<4> *sir // segment
					);
};

