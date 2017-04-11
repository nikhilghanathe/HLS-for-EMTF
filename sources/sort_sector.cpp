#include <ap_int.h>
#include "spbits.h"
#include "sort.h"
#include "sp.h"
#include <ap_utils.h>
#define num_levels 4


/*
void best3(ap_uint<bwr> rank_ex[cnrex],
		ap_uint<bwr> winner[3],
		ap_uint<bpow+1> winid[3]);
*/

void sp_c::sort_sector(ap_uint<bwr> ph_rank[4][ph_raw_w],
				 ap_uint<bpow+1> ph_num[4][3],
				 ap_uint<bwr> ph_q[4][3]
		)
{
	//ap_wait();
//
#pragma HLS PROTOCOL fixed
#pragma HLS LATENCY min=1 max=1
#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=ph_q complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_num complete dim=0
#pragma HLS ARRAY_PARTITION variable=ph_rank complete dim=0

sorter inst[4];
{
//#pragma HLS LATENCY min=1 max=1
#pragma HLS PROTOCOL fixed

//Select best3 from each of the four zones
	sort_sector_label4:for(int i=0;i<4;i++){
#pragma HLS UNROLL
		inst[i].best3(ph_rank[i],
				ph_q[i],
				ph_num[i]
				);
	}

/*	{
#pragma HLS PROTOCOL fixed
#pragma HLS LATENCY min=0 max=0
	ap_wait_n(0);
	}*/
	//ap_wait_n(2);
}
//ap_wait();

}
