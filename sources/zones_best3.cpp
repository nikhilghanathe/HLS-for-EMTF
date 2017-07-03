#include <ap_int.h>
#include "spbits.h"
#define num_levels 4
#include "sort.h"
using namespace std;
void sorter::best3(ap_uint<bwr> rank_ex[cnrex],
		ap_uint<bwr> winner[3],
		int station,
		ap_uint<bpow+1> winid[3])

{
#pragma HLS LATENCY max=3
#pragma HLS INTERFACE ap_ctrl_none port=return

	ap_uint<bwr> ret_a[cnrex],ret_a1[cnrex],ret_a2[cnrex];
	ap_uint<bwr> ret_win[cnr],ret_win1[cnr],ret_win2[cnr];



for(int i=0;i<cnrex;i++){
#pragma HLS UNROLL
	rankr[i]=rank_ex[i];
}

 sorter inst;
		this->sort( &winner[0],&winid[0], station,ret_win);//INLINE OFF

		this->sort1( ret_win, &winner[1],&winid[1],ret_win1);//INLINE

		this->sort1( ret_win1,&winner[2],&winid[2], ret_win2);//INLINE


}

