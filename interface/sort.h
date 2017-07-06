#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"

class sorter{
public:
	ap_uint<1> pr;
	ap_uint<bwr> rankr[cnrex];

	void sort(ap_uint<bwr> *winner0,
			ap_uint<bpow+1> *winindex0,
			int station,
			ap_uint<bwr> ret_win[cnr]);

	void sort1(ap_uint<bwr> ret_win[cnr],
			ap_uint<bwr> *winner0,
			ap_uint<bpow+1> *winindex0,
			ap_uint<bwr> ret_win_next[cnr]);

	void best3(ap_uint<bwr> rank_ex[cnrex],
			ap_uint<bwr> winner[3],
			int station,
			ap_uint<bpow+1> winid[3]);


};


ap_uint<bwr> min_elem(ap_uint<bwr> a,
			ap_uint<bwr> b,
			ap_uint<bwr> c,
			ap_uint<bwr> d,
			ap_uint<bpow+1> *index);

void sort(ap_uint<bwr> a[cnrex],
		ap_uint<bwr> *winner0,
		ap_uint<bpow+1> *winindex0,
		ap_uint<bwr> ret_a[cnr]);

void sort1(ap_uint<bwr> a[cnr],
		ap_uint<bwr> *winner0,
		ap_uint<bpow+1> *winindex0,
		ap_uint<bwr> ret_a[cnr]);

void best3(ap_uint<bwr> rank_ex[cnrex],
		ap_uint<bwr> winner[3],
		ap_uint<bpow+1> winid[3]);
