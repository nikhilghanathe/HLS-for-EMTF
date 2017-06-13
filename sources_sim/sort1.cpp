#include <ap_int.h>
#include "spbits.h"
#define num_levels 4
#include "sort.h"
using namespace std;

ap_uint<bwr> min_elem(ap_uint<bwr> a,
		ap_uint<bwr> b,
		ap_uint<bwr> c,
		ap_uint<bwr> d,
		ap_uint<bpow+1> *index);

void sorter::sort1(ap_uint<bwr> ret_win[cnr],
		ap_uint<bwr> *winner0,
		ap_uint<bpow+1> *winindex0,
		ap_uint<bwr> ret_win_next[cnr])

{

	for(int i=0;i<cnr;i++){
//		cout<<"ret_win["<<i<<"]= "<<ret_win[i]<<endl;
	}
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=a complete dim=1
#pragma HLS ARRAY_PARTITION variable=ret_win complete dim=0
#pragma HLS ARRAY_PARTITION variable=ret_win_next complete dim=0
#pragma HLS INLINE





	ap_uint<bwr> win_l0[cnr];
#pragma HLS ARRAY_PARTITION variable=win_l0 complete dim=1
	ap_uint<bwr> win_l1[cnr/4];
#pragma HLS ARRAY_PARTITION variable=win_l1 complete dim=1
	ap_uint<bwr> win_l2[cnr/16];
#pragma HLS ARRAY_PARTITION variable=win_l2 complete dim=1

	ap_uint<bwr> win0, win1, win2, win0_t1,win0_t2;
	ap_uint<bpow+1> winid0, winid1, winid2;



	ap_uint<bpow+1> a_winid;ap_uint<bpow+1> a_winid_1; ap_uint<bpow+1> a_winid_2;
	ap_uint<bpow+1> a_winid_t1; ap_uint<bpow+1> a_winid_t2;

	int i,j;
	ap_uint<bpow+1> ranki[cnr];
#pragma HLS ARRAY_PARTITION variable=ranki complete dim=1
	ap_uint<bpow+1> ranki_l1[cnr/4];
#pragma HLS ARRAY_PARTITION variable=ranki_l1 complete dim=1
	ap_uint<bpow+1> ranki_l2[cnr/16];
#pragma HLS ARRAY_PARTITION variable=ranki_l2 complete dim=1





	sort_label1:for(int i=0;i<cnr;i++){
#pragma HLS UNROLL
		ranki[i]=i;
		win_l0[i]=ret_win[i];
		if(win_l0[i]!=0)
			cout<<"win_l0["<<dec<<i<<"]= "<<hex<<win_l0[i]<<endl;

	}

/*****************FIRST LEVEL******************************/
int ncomp=cnr;
	ncomp=ncomp/4;
		sort_label4:for (j = 0; j < ncomp; j = j+1){
#pragma HLS UNROLL
 // comparator loop
			win_l1[j]=min_elem(win_l0[4*(j)],
								win_l0[(4*j)+1],
								win_l0[(4*j)+2],
								win_l0[(4*j)+3],
								&a_winid);
			ranki_l1[j]=ranki[a_winid+(4*j)];


		}

		ncomp=ncomp/4;


/*****************SECOND LEVEL******************************/

	sort_label5:for (j = 0; j < ncomp; j = j+1){
#pragma HLS UNROLL
 // comparator loop
						win_l2[j]=min_elem(win_l1[4*(j)],
											win_l1[(4*j)+1],
											win_l1[(4*j)+2],
											win_l1[(4*j)+3],
											&a_winid_1);
			ranki_l2[j]=ranki_l1[a_winid_1+(4*j)];

	}

/*****************FINAL LEVEL******************************/
	win0_t1=min_elem(win_l2[0],win_l2[1],win_l2[2],win_l2[3],&a_winid_t1);
	win0_t2=min_elem(win_l2[4],win_l2[5],win_l2[6],win_l2[7],&a_winid_t2);

		 if(win0_t1 > win0_t2){
			 win0= win0_t1; a_winid_2=ranki_l2[a_winid_t1];
		 }
		 else{
			 win0= win0_t2; a_winid_2=ranki_l2[4+a_winid_t2];
		 }

	winid0=a_winid_2;
	*winner0= win0 ;//? win0 : 0x7E;
	if(win0==a[2*winid0])
		*winindex0= win0 ? ap_uint<bpow+1>((2* winid0)) : ap_uint<bpow+1>(0x7F);
	else
		*winindex0= win0 ? ap_uint<bpow+1>((2*winid0)+1) : ap_uint<bpow+1>(0x7F);




/***********Return the array which excludes MAX element to next stage**********/
	win_l0[winid0]=0;
	sort_label2:for(int h=0;h<cnr;h++)
		ret_win_next[h]=win_l0[h];

//cout<<"win0= "<<win0<<endl;
/*	for(int h=0;h<cnrex;h++){
#pragma HLS UNROLL
		ret_a[h]=a[h];
	}*/


}


