#include <ap_int.h>
#include "spbits.h"
#define num_levels 4
#include "sort.h"

void sorter::best3(ap_uint<bwr> rank_ex[cnrex],
		ap_uint<bwr> winner[3],
		ap_uint<bpow+1> winid[3])

{

#pragma HLS ARRAY_PARTITION variable=winner complete dim=1
#pragma HLS ARRAY_PARTITION variable=rank_ex complete dim=1
#pragma HLS ARRAY_PARTITION variable=winid complete dim=1
#pragma HLS INTERFACE ap_ctrl_none port=return


	ap_uint<bwr> ret_a[cnrex],ret_a1[cnrex],ret_a2[cnrex];
		ap_uint<bwr> ret_win[cnr],ret_win1[cnr],ret_win2[cnr];
#pragma HLS ARRAY_PARTITION variable=ret_a complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_a2 complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_a1 complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_win complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_win1 complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_win2 complete dim=1

#pragma HLS ARRAY_PARTITION variable=a complete dim=0

//load contents into temp static array
for(int i=0;i<cnrex;i++){
#pragma HLS UNROLL
	a[i]=rank_ex[i];
}

volatile ap_uint<bwr> dummy1,dummy2;
ap_uint<bwr> temp;
static sorter inst;

	//3 calls to sorter to get best 3 tracks
		this->sort( &winner[0],&winid[0],ret_win);//INLINE off

		this->sort1( ret_win, &winner[1],&winid[1],ret_win1);//INLINE

		this->sort1( ret_win1,&temp,&winid[2], ret_win2);//INLINE


winner[2]=temp;
}

