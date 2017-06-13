#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
#define DEL 8
using namespace std;

class single_class{
public:
/*    ap_uint<DEL>  t_vl_d;
    ap_uint<bw_fph> t_ph_d [DEL];
    ap_uint<bw_th>   t_th_d [DEL];
    ap_uint<1> t_vl_s;
    ap_uint<bw_fph>  t_ph_s;
    ap_uint<bw_th>   t_th_s;*/

    void single_actual(
        ap_uint<bw_fph>  ph   [5][9][seg_ch],
        ap_uint<bw_th>  th11 [2][3][th_ch11],
        ap_uint<bw_th>  th   [5][9][seg_ch],
        ap_uint<seg_ch>  vl   [5][9],
        ap_uint<1>  *vl_single,
		ap_uint<DEL>   *dummy,
        ap_uint<bw_fph> *ph_single,
        ap_uint<bw_th>  *th_single,
        ap_uint<1> en);
};

void single(
    ap_uint<bw_fph>  ph   [5][9][seg_ch],
    ap_uint<bw_th>  th11 [2][3][th_ch11],
    ap_uint<bw_th>  th   [5][9][seg_ch],
    ap_uint<seg_ch>  vl   [5][9],
    ap_uint<1>  *vl_single,
    ap_uint<bw_fph> *ph_single,
    ap_uint<bw_th>  *th_single,
    ap_uint<1> en
){
//#pragma HLS LATENCY max=1
#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
	ap_uint<DEL>   dummy;
	static single_class inst;
	inst.single_actual( ph ,
		   th11 ,
		   th   ,
		    vl   ,
		   vl_single,
		   &dummy,
		  ph_single,
		  th_single,
		  en
		);

}

void single_class::single_actual(
    ap_uint<bw_fph>  ph   [5][9][seg_ch],
    ap_uint<bw_th>  th11 [2][3][th_ch11],
    ap_uint<bw_th>  th   [5][9][seg_ch],
    ap_uint<seg_ch>  vl   [5][9],
    ap_uint<1>  *vl_single,
	ap_uint<DEL>  *dummy,
    ap_uint<bw_fph> *ph_single,
    ap_uint<bw_th>  *th_single,
    ap_uint<1> en
)
{
#pragma HLS INTERFACE ap_stable port=ph
#pragma HLS INTERFACE ap_stable port=th11
#pragma HLS INTERFACE ap_stable port=th
#pragma HLS INTERFACE ap_stable port=vl
#pragma HLS INTERFACE ap_stable port=en

#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
    int i, j;
 static ap_uint<DEL>  t_vl_d;
 static ap_uint<bw_fph> t_ph_d [DEL];
 static ap_uint<bw_th>   t_th_d [DEL];
 static ap_uint<1> t_vl_s;
 static ap_uint<bw_fph>  t_ph_s;
 static ap_uint<bw_th>   t_th_s;

     ap_uint<1> vl_s;
    ap_uint<1> vl_s_t;

     ap_uint<DEL>  vl_d;
     volatile ap_uint<DEL>  dummy_t                                   ;
    ap_uint<DEL>  vl_d_t;

     ap_uint<bw_fph> ph_d [DEL];
    ap_uint<bw_fph> ph_d_t [DEL];

     ap_uint<bw_th>   th_d [DEL];
    ap_uint<bw_fph> th_d_t [DEL];

     ap_uint<bw_fph>  ph_s;
    ap_uint<bw_fph>  ph_s_t;

    ap_uint<bw_th>   th_s;
    ap_uint<bw_th>   th_s_t;

    ap_uint<1>  a_vl_single;
    ap_uint<bw_fph> a_ph_single;
    ap_uint<bw_th>  a_th_single;


//Previous value in temp values
vl_d=t_vl_d;
for(int i=0;i<DEL;i++){
#pragma HLS UNROLL
	ph_d[i]=t_ph_d[i];
	th_d[i]=t_th_d[i];
}
vl_s=t_vl_s;
ph_s=t_ph_s;
th_s=t_th_s;
dummy_t=t_vl_d;
/*cout<<"th_s0= "<<th_s<<endl;
cout<<"ph_s0= "<<ph_s<<endl;
cout<<"vl_s0= "<<vl_s<<endl;*/

        a_vl_single = t_vl_d[DEL-1];
        a_ph_single = t_ph_d[DEL-1];
        a_th_single = t_th_d[DEL-1];
        *dummy=dummy_t;
        // delay lines for outputs
        //vl_d[0]=vl_s;


        for(int i=DEL-2;i>=0;i--){
        #pragma HLS UNROLL
        ph_d[i+1] = ph_d[i];
        th_d[i+1] = th_d[i];
        }
        vl_d=(vl_d(DEL-2,0),vl_s);
             ph_d[0]=ph_s;
             th_d[0]=th_s;

for(int i=0;i<DEL;i++){
	cout<<"ph_d["<<i<<"]= "<<ph_d[i]<<endl;
}

        vl_s = 0;
        ph_s = 0;
        th_s = 0;
        if (en == 1){
            for (i = 0; i < 5; i = i+1){ // station loop
#pragma HLS UNROLL
                for (j = 0; j < 9; j = j+1){ // chamber loop
#pragma HLS UNROLL
                    vl_s = vl_s | vl[i][j][0];
                    if (vl[i][j][0] == 1){
                        ph_s = ph[i][j][0];
                        if (i < 2 && j < 3)
                            th_s = th11[i][j][0]; // ME1/1
                        else
                            th_s = th[i][j][0]; // all other chambers
                    }
                }
            }
        }

cout<<"th_s= "<<th_s<<endl;
cout<<"ph_s= "<<ph_s<<endl;
cout<<"vl_s= "<<vl_s<<endl;
/*        vl_s=vl_s_t;
        ph_s=ph_s_t;
        th_s=th_s_t;*/

        t_vl_d=vl_d;
        t_th_s=th_s;
        t_ph_s=ph_s;
        t_vl_s=vl_s;
for(int i=0;i<DEL;i++){
#pragma HLS UNROLL
	t_ph_d[i]=ph_d[i];
	t_th_d[i]=th_d[i];

}

*vl_single = a_vl_single;

*ph_single = a_ph_single;
*th_single = a_th_single;
}
