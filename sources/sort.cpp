#include <ap_int.h>
#include "spbits.h"
//#include "sort.h"
#define num_levels 4
#include "sort.h"
using namespace std;

ap_uint<bwr> min_elem(ap_uint<bwr> a,
		ap_uint<bwr> b,
		ap_uint<bwr> c,
		ap_uint<bwr> d,
		ap_uint<bpow+1> *index);

void sorter::sort(ap_uint<bwr> *winner0,
		ap_uint<bpow+1> *winindex0,
		ap_uint<bwr> ret_win[cnr])
{
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
#pragma HLS ARRAY_PARTITION variable=ret_win complete dim=0


#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1





	ap_uint<bwr> win_l0[cnr];
#pragma HLS ARRAY_PARTITION variable=win_l0 complete dim=1
	ap_uint<bwr> win_l1[cnr/4];
#pragma HLS ARRAY_PARTITION variable=win_l1 complete dim=1
	ap_uint<bwr> win_l2[cnr/16];
#pragma HLS ARRAY_PARTITION variable=win_l2 complete dim=1

	ap_uint<bwr> win0, win1, win2;
	ap_uint<bpow+1> winid0, winid1, winid2;



	ap_uint<bpow+1> a_winid;ap_uint<bpow+1> a_winid_1; ap_uint<bpow+1> a_winid_2;

	int i,j;
	ap_uint<bpow+1> ranki[cnr];
#pragma HLS ARRAY_PARTITION variable=ranki complete dim=1
	ap_uint<bpow+1> ranki_l1[cnr/4];
#pragma HLS ARRAY_PARTITION variable=ranki_l1 complete dim=1
	ap_uint<bpow+1> ranki_l2[cnr/16];
#pragma HLS ARRAY_PARTITION variable=ranki_l2 complete dim=1



	/*for(int i=0;i<cnrex;i++)
		cout<<"a["<<i<<"]= "<<a[i]<<endl;
*/

/*
	sort_label1:for(int i=0;i<cnrex/2;i++){
#pragma HLS UNROLL
		ranki[i]=i;
		win_l0[i]=a[2*i] | a[(2*i)+1];
	}
*/



	best3_label6:for(int i = 0; i < cnrex/2; i = i+1){
#pragma HLS UNROLL
win_l0[i] = a[i*2] | a[(2*i)+1];
ranki[i]=i;
	}
	/*	best3_label7:for (int i = cnrex/2; i < cnr; i = i+1)
		{
#pragma HLS UNROLL
win_l0[i] = 0;
		}*/

	win_l0[61]=0;
	win_l0[62]=0;
	win_l0[63]=0;
	ranki[61]=61;
	ranki[62]=62;
	ranki[63]=63;

/*
	for(int i=0;i<3;i++)
				std::cout<<winner<<"["<<i<<"]= "<<winner[i]<<std::endl;
*/

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
		/*win_l1[15]=win_l0[60];
		ranki_l1[15]=60;*/

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

/*			cout<<"elements are : "<<win_l1[4*(j)]<<" "<<win_l1[(4*j)+1]<<" "<<win_l1[(4*j)+2]<<" "<<win_l1[(4*j)+3]<<endl;
			cout<<"indices are : "<<ranki_l1[4*(j)]<<" "<<ranki_l1[(4*j)+1]<<" "<<ranki_l1[(4*j)+2]<<" "<<ranki_l1[(4*j)+3]<<endl;
			cout<<"win_l1["<<j<<"]= "<<win_l2[j]<<endl;
			cout<<"ranki_l2["<<j<<"]= "<<ranki_l2[j]<<endl;
			cout<<j<<": a_wind= "<<a_winid_1<<endl;*/



	}

/*****************FINAL LEVEL******************************/
	win0=min_elem(win_l2[0],win_l2[1],win_l2[2],win_l2[3],&a_winid_2);
	//if(win0==0)
		*winner0= win0; //? win0 : ap_uint<bwr>(0x7E);
	winid0=ranki_l2[a_winid_2];
	if(win0==a[2*winid0])
		*winindex0= winid0 ? ap_uint<bpow+1>((2* winid0)) : ap_uint<bpow+1>(0x7F);
	else
		*winindex0= winid0 ? ap_uint<bpow+1>((2*winid0)+1) : ap_uint<bpow+1>(0x7F);


	//*winindex0=winid0;



/***********Return the array which excludes MAX element to next stage**********/
	win_l0[winid0]=0;


	sort_label2:for(int h=0;h<cnr;h++){
#pragma HLS UNROLL
		ret_win[h]=win_l0[h];
	}


}

