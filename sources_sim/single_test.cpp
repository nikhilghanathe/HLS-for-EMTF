#include <ap_int.h>
#include "spbits.h"
using namespace std;
void single(
    ap_uint<bw_fph>  ph   [5][9][seg_ch],
    ap_uint<bw_th>  th11 [2][3][th_ch11],
    ap_uint<bw_th>  th   [5][9][seg_ch],
    ap_uint<seg_ch>  vl   [5][9],
    ap_uint<1>  *vl_single,
    ap_uint<bw_fph> *ph_single,
    ap_uint<bw_th>  *th_single,
    ap_uint<1> en
);


int main (int argc, char** argv){



    ap_uint<bw_fph>  ph   [5][9][seg_ch];
    ap_uint<bw_th>  th11 [2][3][th_ch11];
    ap_uint<bw_th>  th   [5][9][seg_ch];
    ap_uint<seg_ch>  vl   [5][9];
    ap_uint<1>  vl_single;
    ap_uint<bw_fph> ph_single;
    ap_uint<bw_th>  th_single;
    ap_uint<1> en;
for(int i=0;i<5;i++){
	for(int j=0;j<9;j++){
		vl[i][j]=0;
		for(int k=0;k<seg_ch;k++){
			ph[i][j][k]=0;
			th[i][j][k]=0;

		}
	}
}
for(int i=0;i<2;i++){
	for(int j=0;j<3;j++){
		for(int k=0;k<th_ch11;k++){
			th11[i][j][k]=0;

		}
	}
}
    ph[0][0][0]=2;
    vl[0][0][0]=1;
    th[0][0][0]=3;
    th11[0][0][0]=4;
    en=1;
	single( ph ,
		   th11 ,
		   th   ,
		    vl   ,
		   &vl_single,
		  &ph_single,
		  &th_single,
		  en
		);
    ph[0][0][0]=0;
    vl[0][0][0]=0;
    th[0][0][0]=0;
    th11[0][0][0]=0;
	single( ph ,
		   th11 ,
		   th   ,
		    vl   ,
		   &vl_single,
		  &ph_single,
		  &th_single,
		  en
		);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;
single( ph ,
	   th11 ,
	   th   ,
	    vl   ,
	   &vl_single,
	  &ph_single,
	  &th_single,
	  en
	);

cout<<"vl_single = "<<vl_single<<endl;
cout<<"ph_single = "<<ph_single<<endl;
cout<<"th_single = "<<th_single<<endl;

}
