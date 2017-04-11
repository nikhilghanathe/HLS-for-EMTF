#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;


double timerval () {
    struct timeval st;
    gettimeofday(&st, NULL);
    return (st.tv_sec+st.tv_usec*1e-6);
}




#define max_ev 1000

/*
#define fes  "_endcap_1_sec_2_" // endcap and sector numbers for LUT file names
#define fest "_endcap_1_sect_2" // endcap and sector numbers for LUT file names
#define dpath "C:\Vivado\Verification_PRATAP\"
*/

#define call_sp()  uut.sp( (qi),\
   		(wgi),\
   		(hstri),\
   		(cpati),\
   		(csi),\
   		(pps_csi),\
   		(seli),\
   		(sel11i),\
   		(addri),\
   		(r_ini),\
   		(r_outo),\
   		(wei),\
   		(bt_phi),\
   		(bt_theta),\
   		(bt_cpattern),\
   		(bt_delta_ph),\
   		(bt_delta_th),\
   		(bt_sign_ph),\
   		(bt_sign_th),\
   		(bt_rank),\
   		(bt_vi),\
   		(bt_hi),\
   		(bt_ci),\
   		(bt_si),\
   		ptlut_addr,\
   		ptlut_cs,\
   		ptlut_addr_val,\
   		(gmt_phi),\
   		(gmt_eta),\
   		(endcap),\
   		(sector),\
   		(lat_test),\
   		print_flag\
   		);

#define  fill_LUT_th_corr(a,b,c) \
	    i=0;  addri=0; seli=2; sel11i=1;\
	   for(int j=0;j<5;j++)\
	   	csi[j]=0;\
	   csi[b][c]=1;\
	   fp=fopen(concat,"r");\
	   for( int p=0;p<th_corr_mem_sz;p++){\
	   	fscanf(fp,"%x",&tmp);\
	    addri=p;\
	   	r_ini=tmp;\
	   	uut.sp( (qi),\
	   		(wgi),\
	   		(hstri),\
	   		(cpati),\
	   		(csi),\
	   		(pps_csi),\
	   		(seli),\
	   		(sel11i),\
	   		(addri),\
	   		(r_ini),\
	   		(r_outo),\
	   		(wei),\
	   		(bt_phi),\
	   		(bt_theta),\
	   		(bt_cpattern),\
	   		(bt_delta_ph),\
	   		(bt_delta_th),\
	   		(bt_sign_ph),\
	   		(bt_sign_th),\
	   		(bt_rank),\
	   		(bt_vi),\
	   		(bt_hi),\
	   		(bt_ci),\
	   		(bt_si),\
	   		ptlut_addr,\
	   		ptlut_cs,\
	   		ptlut_addr_val,\
	   		(gmt_phi),\
	   		(gmt_eta),\
	   		(endcap),\
	   		(sector),\
	   		(lat_test),\
	   		print_flag\
	   		);\
	   	if(feof(fp)) { cout<<"!!!!!!!!!!!!!!!!!!!!!!!!  EOF reached"<<endl;\
	   	break;\
	   	}\
	   }fclose(fp)\


//if(csi[0][3])cout<<"test...r_in ="<<r_ini<<" addr= "<<addri<<endl;
//cout<<"p: "<<p<<" addr: "<<addri<<" r_in: "<<r_ini<<endl;
#define  fill_LUT_th(a,b,c) \
	    i=0;  addri=0; seli=1; sel11i=2;\
	   for(int j=0;j<5;j++)\
	   	csi[j]=0;\
	   csi[b][c]=1;\
	   fp=fopen(concat,"r");\
	   for( int p=0;p<th_mem_sz||(!feof(fp));p++){\
	   	fscanf(fp,"%x",&tmp);\
	   	if(feof(fp)) { cout<<"!!!!!!!!!!!!!!!!!!!!!!!!  EOF reached"<<endl;\
	   		   				   		   	break;}\
	    addri=p;\
	   	r_ini=tmp;\
	   	uut.sp( (qi),\
	   		(wgi),\
	   		(hstri),\
	   		(cpati),\
	   		(csi),\
	   		(pps_csi),\
	   		(seli),\
	   		(sel11i),\
	   		(addri),\
	   		(r_ini),\
	   		(r_outo),\
	   		(wei),\
	   		(bt_phi),\
	   		(bt_theta),\
	   		(bt_cpattern),\
	   		(bt_delta_ph),\
	   		(bt_delta_th),\
	   		(bt_sign_ph),\
	   		(bt_sign_th),\
	   		(bt_rank),\
	   		(bt_vi),\
	   		(bt_hi),\
	   		(bt_ci),\
	   		(bt_si),\
	   		ptlut_addr,\
	   		ptlut_cs,\
	   		ptlut_addr_val,\
	   		(gmt_phi),\
	   		(gmt_eta),\
	   		(endcap),\
	   		(sector),\
	   		(lat_test),\
	   		print_flag\
	   		);\
	   	   }\
	   fclose(fp)





int main (int argc, char** argv)
{

	char* fes=  "_endcap_1_sec_2_"; // endcap and sector numbers for LUT file names
	char* fest= "_endcap_1_sect_2"; // endcap and sector numbers for LUT file names
	//char* dpath= "C:/Vivado/Verification_PRATAP";
	char* dpath= "/home/ghanathe/Verification_PRATAP";


	// io
	    ap_uint<4>         qi    [5][9][seg_ch];
	    ap_uint<bw_wg>   wgi   [5][9][seg_ch];
	    ap_uint<bw_hs>   hstri [5][9][seg_ch];
	    ap_uint<4>  		 cpati [5][9][seg_ch];

	    for(int i=0;i<5;i++){
	    	for(int j=0;j<9;j++){
	    		for(int k=0;k<seg_ch;k++){
	    			qi[i][j][k]=0;
	    			wgi[i][j][k]=0;
	    			hstri[i][j][k]=0;
	    			cpati[i][j][k]=0;
	    		}

	    	}
	    }

	    // precise parameters
	    /*
		 * ap_uint<> [bw_phi-1:0] phi [3];
	    ap_uint<> [bw_eta-1:0] eta [3];
	    ap_uint<> [12:0] 	  pt [3];
	    ap_uint<> [3] 		  sign;
	    ap_uint<> [4] 		  modeMem [3];
	    ap_uint<> [5] 		  etaPT [3];
	    ap_uint<> [3] 		  FR;
		 */

	    ap_uint<9>  		  csi [5];
	    ap_uint<5>  		  pps_csi [3];
	    ap_uint<2>  		  seli;
	    ap_uint<2> 			  sel11i;
	    ap_uint<bw_addr>  addri;

	    ap_uint<12>  		  r_ini; // ap_uint<> data for memory or ap_uint<>ister
	    ap_uint<12>  	  r_outo; // output data from memory or ap_uint<>ister
	    ap_uint<1> 			  wei; // write enable for memory or ap_uint<>ister

	// ph quality codes output [zone][key_strip]
	    ap_uint<6>  		ph_ranko [4][ph_raw_w];
	    ap_uint<bw_fph>  	ph   [5][9][seg_ch];
	    ap_uint<bw_th>  	th11 [2][3][th_ch11];
	    ap_uint<bw_th>  	th   [5][9][seg_ch];
	    ap_uint<seg_ch>  vl   [5][9];
	    ap_uint<3>  		phzvl[5][9];
		ap_uint<seg_ch>  me11a [2][3];
		ap_uint<ph_raw_w>  ph_zone [4][5];

		ap_uint<seg_ch>  	patt_vi [4][3][4]; // valid
		ap_uint<2>  			patt_hi [4][3][4]; // bx index
		ap_uint<3>  			patt_ci [4][3][4]; // chamber
		ap_uint<4>  			patt_si [4][3]; // segment


	 //   ap_uint<> 			  clki; // write clock

	    // ph_init storage is full-precision now
		// chamber index is 0..11 to include ME11a and b
	    ap_uint<bw_fph>  	  ph_init0 [12];
	    ap_uint<bw_fph>  	  ph_init1 [12];
	    ap_uint<bw_fph>  	  ph_init2 [12];
	    ap_uint<bw_fph>  	  ph_init3 [12];
	    ap_uint<bw_fph>  	  ph_init4 [12];
	    ap_uint<bw_fph> 	  ph_init [5][12]; // [station][chamber]

	    for(int i=0;i<12;i++)
	    	ph_init[0][i] = ph_init0[i];
	    for(int i=0;i<12;i++)
	    	ph_init[1][i] = ph_init1[i];
	    for(int i=0;i<12;i++)
	    	ph_init[2][i] = ph_init2[i];
	    for(int i=0;i<12;i++)
	    	ph_init[3][i] = ph_init3[i];
	    for(int i=0;i<12;i++)
	    	ph_init[4][i] = ph_init4[i];

		// arrays below contains values for each chamber
		// chamber count is ME1=12*2 ME2,3,4=9*3, total 51
	    ap_uint<bw_th>    th_init [51]; // chamber origins in th
	    ap_uint<bw_ph>  	  ph_disp [51]; // chamber displacements in ph
	    ap_uint<bw_th>    th_disp [51]; // chamber displacements in th

	    // event storage
	    ap_uint<4>  		  quality   [max_ev][5][9][seg_ch];
	    ap_uint<7>  		  wiregroup [max_ev][5][9][seg_ch];
	    ap_uint<bw_hs>    hstrip [max_ev][5][9][seg_ch];
	    ap_uint<4>  		  clctpat [max_ev][5][9][seg_ch];

	    int 	      iadr = 0, s = 0, i = 0, pi, j = 0, sn;
	    //ap_uint<16>  		  v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
	    int  		  v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;
	    ap_uint<1> print_flag=0;
/*	    ap_uint<3>  		  pr_cnt [6][9];
	    ap_uint<10>  		  _event;
		ap_uint<10>  		  _bx_jitter;
	    ap_uint<2>  		  _endcap;
	    ap_uint<3>  		  _sector;
	    ap_uint<2>  		  _subsector;
	    ap_uint<3>  		  _station;
	    ap_uint<4>  		  _cscid;
	    ap_uint<4>  		  _bend;
	    ap_uint<8>  		  _halfstrip;
	    ap_uint<1> 			  _valid;
	    ap_uint<4>  		  _quality;
	    ap_uint<4>  		  _pattern;
	    ap_uint<7>  		  _wiregroup;*/

	    int  		  pr_cnt [6][9];
	    int  		  _event;
	    int  		  _bx_jitter;
	    int 		  _endcap;
	    int  		  _sector;
	    int  		  _subsector;
	    int  		  _station;
	    int  		  _cscid;
	    int  		  _bend;
	    int  		  _halfstrip;
	    int 			  _valid;
	    int  		  _quality;
	    int  		  _pattern;
	    int  		  _wiregroup;
	    int 	      ist, icid, ipr, /*code,*/ iev, im, iz, ir;
	    //ap_uint<800>  	  line;
	    char  	  line[1000];
	    char* code;
	    FILE 	      *in, *best_tracks, *vllut_in, *sim_out;
	    int 	      stat;
	    ap_uint<10>  		  ev = 0;
	    ap_uint<5>  		  good_ev = 0;
	    int 	      good_ev_cnt = 0;
	    int 	      found_tr = 0;
	    int 	      found_cand = 0;
	    int 	      st;
	    int 	      st_cnt; // station count
		int 		  iseg;
		int 		  zi, si, ip;
		int k;

	    double 			  begin_time, end_time, elapsed_time;
	    ap_uint<12>  		  tphi, a, b, d;
		ap_uint<1> 			  pts;
		// numbers of best ranks [zone][num]
		ap_uint<bpow+1>  ph_num [4][3];
		// best ranks [zone][num]
		ap_uint<bwr>  ph_q [4][3];
		ap_uint<bw_fph> 	ph_match [4][3][4]; // matching ph
		ap_uint<bw_th> 	th_match   [4][3][4][seg_ch]; // matching th, 2 segments
		ap_uint<bw_th> 	th_match11 [2][3][th_ch11]; // matching th for ME11 (station 0 only), 4 segments (due to th duplication)
		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph>  	bt_phi [3];
		ap_uint<bw_th>  	bt_theta [3];
		ap_uint<4>  			bt_cpattern [3][4];
		// ph and th deltas from best stations
		// [best_track_num], last index: [0] - best pair of stations, [1] - second best pair
		ap_uint<bw_fph>  	bt_delta_ph [3][6];
		ap_uint<bw_th>  	bt_delta_th [3][6];
		ap_uint<6>  			bt_sign_ph[3];
		ap_uint<6>  			bt_sign_th[3];
		// ranks [best_track_num]
		ap_uint<bwr+1>  		bt_rank [3];
		// segment IDs
		// [best_track_num][station 0-3]
		ap_uint<seg_ch>  	bt_vi [3][5]; // valid
		ap_uint<2>  			bt_hi [3][5]; // bx index
		ap_uint<4>  			bt_ci [3][5]; // chamber
		ap_uint<5>  			bt_si [3]; // segment
	    ap_uint<1> lat_test=0; // latency test mode
	    ap_uint<1> en_single;
	    ap_uint<30>  ptlut_addr [3]; // ptlut addresses for best 3 muons
	   	ap_uint<32>  ptlut_cs [3]; // pre-decoded chip selects
	   	ap_uint<3>  ptlut_addr_val; // ptlut address valid flags

		ap_uint<8>  gmt_phi [3]; // phi for gmt
	    ap_uint<9>  gmt_eta [3]; // eta for gmt
	    ap_uint<3>  bt_rank_r;


	    // IMPORTANT: modify 5 parameters below to match endcap/sector and file path
	    ap_uint<1> endcap = 0; // 0=ME+ 1=ME-
	    ap_uint<3>  sector = 0x2; // sector #-1

		int 	   ibx,ich,isg, ii, kp;


int _hex=15;
cout<<"hex value is "<<_hex<<std::hex<<endl;

		sim_out=fopen("C:/Vivado/Verification_PRATAP/HLS_sim.out","w");
		if(sim_out==NULL)cout <<sim_out<<endl;
		char concat[1000];

		sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_1_st_1_ch_1.lut",dpath,fes);
		printf("%s",concat );
		vllut_in = fopen(concat, "r");
	    if (vllut_in == NULL){
             fprintf( sim_out,"%s","cannot open lut file\n");
             cout<<"inhere"<<endl;
             fclose(sim_out);
            return 0;
	    }



	    /*****************************INSTANTIATE sp(CORE)***********************/
	   long long unsigned int tmp;
	    FILE *fp;
	    static sp_c uut;




/*******************fill the LUTs******************************************/
	    wei=1;


print_flag=0;
	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_1_st_1_ch_1.lut",dpath,fes);
	    fill_LUT_th_corr(concat,0,0);

	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_1_st_1_ch_2.lut",dpath,fes);
	   	    fill_LUT_th_corr(concat,0,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_1_st_1_ch_3.lut",dpath,fes);
	   	    fill_LUT_th_corr(concat,0,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_2_st_1_ch_1.lut",dpath,fes);
	   	    fill_LUT_th_corr(concat,1,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_2_st_1_ch_2.lut",dpath,fes);
	   	    fill_LUT_th_corr(concat,1,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_corr_lut%ssub_2_st_1_ch_3.lut",dpath,fes);
	   	    fill_LUT_th_corr(concat,1,2);


	   	  //  cout<<"check 1 !!!!!!!!!!!!!"<<endl;

	   /*
	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_1.lut",dpath,fes);
	   	    i=0;  addri=0; seli=1; sel11i=2;
	   	    cout<<"concat is  "<<concat<<endl;
	   	   for(int j=0;j<5;j++)
	   	   	csi[j]=0;
	   	   csi[0][0]=1;
	   	   fp=fopen(concat,"r");
	   	   cout<<"here!!!!!!!!!!"<<endl;
	   	   for(long int p=0;p<th_corr_mem_sz;p++){
	   		   cout<<"here!!!!!!!!!!"<<endl;
	   		   fscanf(fp,"%d",&tmp);
	   		   cout<<"here!!!!!!!!!!"<<endl;
	   	   	cout<<tmp<<endl;
	   	   	addri=p;
	   	   	r_ini=tmp;

	   	   	uut.sp( (qi),
	   	   		(wgi),
	   	   		(hstri),
	   	   		(cpati),
	   	   		(csi),
	   	   		(pps_csi),
	   	   		(seli),\
	   	   		(sel11i),
	   	   		(addri),
	   	   		(r_ini),
	   	   		(r_outo),
	   	   		(wei),
	   	   		(bt_phi),
	   	   		(bt_theta),
	   	   		(bt_cpattern),
	   	   		(bt_delta_ph),
	   	   		(bt_delta_th),
	   	   		(bt_sign_ph),
	   	   		(bt_sign_th),
	   	   		(bt_rank),
	   	   		(bt_vi),
	   	   		(bt_hi),
	   	   		(bt_ci),
	   	   		(bt_si),
	   	   		ptlut_addr,
	   	   		ptlut_cs,
	   	   		ptlut_addr_val,
	   	   		(gmt_phi),
	   	   		(gmt_eta),
	   	   		(endcap),
	   	   		(sector),
	   	   		(lat_test)
	   	   		);
	   	   		cout<<"rout is "<<r_outo<<endl;
	   	   	if(feof(fp)) { cout<<"!!!!!!!!!!!!!!!!!!!!!!!!  EOF reached"<<endl;
	   	   	break;
	   	   	}

	   	   }fclose(fp);

	   */






	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_1.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_2.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_3.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_4.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,3);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_5.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,4);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_6.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,5);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_7.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,6);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_8.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,7);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_1_st_1_ch_9.lut",dpath,fes);
	   	    fill_LUT_th(concat,0,8);




	   	    //th_mem
	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_1.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_2.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_3.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_4.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,3);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_5.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,4);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_6.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,5);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_7.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,6);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_8.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,7);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%ssub_2_st_1_ch_9.lut",dpath,fes);
	   	    fill_LUT_th(concat,1,8);







	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_1.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_2.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_3.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_4.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,3);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_5.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,4);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_6.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,5);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_7.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,6);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_8.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,7);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_2_ch_9.lut",dpath,fes);
	   	   	fill_LUT_th(concat,2,8);







	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_1.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_2.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_3.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_4.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,3);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_5.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,4);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_6.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,5);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_7.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,6);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_8.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,7);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_3_ch_9.lut",dpath,fes);
	   	   	fill_LUT_th(concat,3,8);






	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_1.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,0);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_2.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,1);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_3.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,2);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_4.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,3);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_5.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,4);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_6.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,5);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_7.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,6);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_8.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,7);

	   	    sprintf(concat,"%s/vl_lut/vl_th_lut%sst_4_ch_9.lut",dpath,fes);
	   	   	fill_LUT_th(concat,4,8);

/*
print_flag=1;
wei=0; seli=2; sel11i=2;
call_sp();
*/


	   	   	sprintf(concat,"%s/vl_lut/th_init%s.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<51;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		th_init[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_disp%s.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<51;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_disp[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);


	   		sprintf(concat,"%s/vl_lut/th_disp%s.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<51;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		th_disp[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_init_full%s_st_0.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<12;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_init0[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_init_full%s_st_1.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<12;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_init1[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_init_full%s_st_2.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<12;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_init2[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_init_full%s_st_3.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<12;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_init3[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   		sprintf(concat,"%s/vl_lut/ph_init_full%s_st_4.lut",dpath,fest);
	   	   	fp=fopen(concat,"r");
	   	   	for(int i=0;i<12;i++){
	   	   		fscanf(fp,"%x",&tmp);
	   	   		ph_init4[i]=tmp;
	   	   		if(feof(fp))break;
	   	     }fclose(fp);

	   	    for(int i=0;i<12;i++)
	   	    	ph_init[0][i] = ph_init0[i];
	   	    for(int i=0;i<12;i++)
	   	    	ph_init[1][i] = ph_init1[i];
	   	    for(int i=0;i<12;i++)
	   	    	ph_init[2][i] = ph_init2[i];
	   	    for(int i=0;i<12;i++)
	   	    	ph_init[3][i] = ph_init3[i];
	   	    for(int i=0;i<12;i++)
	   	    	ph_init[4][i] = ph_init4[i];


	   	   	//wei=0;seli=0;sel11i=2;
	   	  /* 		   //for(int p=0;p<th_corr_mem_sz;p++){

	   	   		   	   	addri=p;
	   	   		   	   	r_ini=tmp;

	   	   		   	   	uut.sp( (qi),
	   	   		   	   		(wgi),
	   	   		   	   		(hstri),
	   	   		   	   		(cpati),
	   	   		   	   		(csi),
	   	   		   	   		(pps_csi),
	   	   		   	   		(seli),\
	   	   		   	   		(sel11i),
	   	   		   	   		(addri),
	   	   		   	   		(r_ini),
	   	   		   	   		(r_outo),
	   	   		   	   		(wei),
	   	   		   	   		(bt_phi),
	   	   		   	   		(bt_theta),
	   	   		   	   		(bt_cpattern),
	   	   		   	   		(bt_delta_ph),
	   	   		   	   		(bt_delta_th),
	   	   		   	   		(bt_sign_ph),
	   	   		   	   		(bt_sign_th),
	   	   		   	   		(bt_rank),
	   	   		   	   		(bt_vi),
	   	   		   	   		(bt_hi),
	   	   		   	   		(bt_ci),
	   	   		   	   		(bt_si),
	   	   		   	   		ptlut_addr,
	   	   		   	   		ptlut_cs,
	   	   		   	   		ptlut_addr_val,
	   	   		   	   		(gmt_phi),
	   	   		   	   		(gmt_eta),
	   	   		   	   		(endcap),
	   	   		   	   		(sector),
	   	   		   	   		(lat_test),
	   	   		   	   		print_flag
	   	   		   	   		);
	   	   		   	   	//	cout<<"rout is "<<r_outo<<endl;
	   	   		   	   //}*/



	   	 for (iev = 0; iev < max_ev; iev=iev+1){
	   		 for (ist = 0; ist < 5; ist=ist+1) {
	   	   		for (icid = 0; icid < 9; icid=icid+1){
	   	   			for (ipr = 0; ipr < seg_ch; ipr=ipr+1){
	   	   				quality  [iev][ist][icid][ipr] = 0x0;
	   	   				wiregroup[iev][ist][icid][ipr] = 0x0;
	   	   				hstrip [iev][ist][icid][ipr] = 0x0;
	   	   				clctpat [iev][ist][icid][ipr] = 0x0;
	   	   			}
	   	   		}
	   		 }
	   	 }


	   	// cout<<"check 2 !!!!!!!!!!!!!"<<endl;

	   	 // read events
	   	 sprintf(concat,"%s/nidhi.txt",dpath);
	   	 in = fopen(concat, "r");
	   	 if (in == 0){
	            fprintf( sim_out,"%s","cannot open input file\n");
	   	 	return 0;
	   	 }
	   	// cout<<"check 3 !!!!!!!!!!!!!"<<endl;

	   	 _event = 0;

	    	while (!feof(in) && _event < max_ev){
	   		// read line
	   		code = fgets(line,1000, in);
	   //                $fwrite (sim_out, "%h\n", line);
	   		//printf("line %s  code %s\n",line, code);
	   		//cout<<"check 4 !!!!!!!!!!!!!"<<endl;
	   		// read values
	   		v0 = 0; v1 = 0; v2 = 0; v3 = 0; v4 = 0; v5 = 0; v6 = 0; v7 = 0; v8 = 0; v9 = 0; v10 = 0; v11 = 0;
	   		sn = sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d",
	   					 &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11);
	   		//cout<<"check 5 !!!!!!!!!!!!!"<<endl;

	   		/*printf( "code %s read %d items %d %d %d %d %d %d %d %d %d %d %d %d\n", code, sn,
	   				    v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
	   		fprintf(sim_out, "code %s read %d items %d %d %d %d %d %d %d %d %d %d %d %d\n", code, sn,
	   		    v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);*/



	   		switch(sn){
	   		case 1:
	   					// end of event
	   					// clean primitive counters
	   					for (i = 0; i < 5; i=i+1)
	   						for (j = 0; j < 9; j=j+1)
	   							pr_cnt[i][j] = 0;
	   					j = 0;
	   					_event = _event + 1;
	   					//call_sp();
	   //					$fwrite(sim_out, "End of event %d\n", _event);
	   					break;
	   		case 12:
	   					// primitive
	   				    fprintf (sim_out, "entering primitive *****************************************\n");
	   					_bx_jitter = v0;
	   					_endcap = v1;
	   //	  				_sector = v2;
	   					_sector = 1; // hardcode sector for now
	   					_subsector = v3;
	   					_station = v4;
	   					if (_station == 1 && _subsector == 1) _station = 0;
	   					_valid = v5;
	   					_quality = v6;
	   					_pattern = v7;
	   					_wiregroup = v8;
	   					_cscid = v9-1;
	   					_bend = v10;
	   					_halfstrip = v11;
	   //							$fwrite(sim_out, "primitive: subsec: %d  stat: %d  val: %d  hs: %d  wg: %d  q: %d\n",
	   //									_subsector, _station, _valid, _halfstrip, _wiregroup, _quality);

	   							// copy data to the corresponding input

	   					if (_station > 4) fprintf(sim_out, "bad station: %d, event: %d\n", _station, _event);
	   					else if (_sector != 1) fprintf(sim_out, "bad sector: %d\n", _sector);
	   						 else if (_cscid > 8) fprintf(sim_out, "bad cscid: %d, station: %d, event: %d\n", _cscid, _station, _event);
	   					//	else if (_wiregroup < 0 || _wiregroup >= chp[_station][_cscid].n_wiregroups)
	   					// cout << "bad wiregroup: " << _wiregroup << " station: " << _station << " cscid: " << _cscid << endl;
	   					//	else if (_halfstrip < 0 || _halfstrip >= chp[_station][_cscid].n_strips*2)
	   					// cout << "bad halfstrip: " << _halfstrip << " station: " << _station << " cscid: " << _cscid << endl;
	   							  else if (pr_cnt[_station][_cscid] >= seg_ch)
	   							  {
	   							  	  fprintf(sim_out, "bad segment index. event: %d, index: %d, station: %d, cscid: %d\n",
	   										 _event, pr_cnt[_station][_cscid], _station, _cscid);
	   							  }
	   								   else
	   								   {
	   									  _bx_jitter = 0; // remove jitter
	   									  quality  [_event + _bx_jitter][_station][_cscid][pr_cnt[_station][_cscid]] = _quality;
	   									  wiregroup[_event + _bx_jitter][_station][_cscid][pr_cnt[_station][_cscid]] = _wiregroup;
	   									  hstrip   [_event + _bx_jitter][_station][_cscid][pr_cnt[_station][_cscid]] = _halfstrip;
	   									  clctpat  [_event + _bx_jitter][_station][_cscid][pr_cnt[_station][_cscid]] = _pattern;

	   										   fprintf(sim_out, "ev: %d st: %d ch: %d prim: %d	q: %d w: %d s: %d\n",
	   											  _event, _station, _cscid, pr_cnt[_station][_cscid],
	   											 int( quality	[_event][_station][_cscid][pr_cnt[_station][_cscid]]),
	   											  int(wiregroup [_event][_station][_cscid][pr_cnt[_station][_cscid]]),
	   											  int(hstrip  [_event][_station][_cscid][pr_cnt[_station][_cscid]]));

	   												   // increase primitive counter
	   									  pr_cnt[_station][_cscid] = pr_cnt[_station][_cscid] + 1;


	   									  if (_station < 2 && _cscid < 3 && _halfstrip > 127)
	   										fprintf(sim_out, "ev: %d  ME1/1a strip: %d\n", int(_event), int(_halfstrip));
	   								   }
	   					break;

	   		default:
	   			break;
	   		}
	    	}

	   	seli = 0; sel11i=2;
	   	addri = 0;
	   	r_ini = 0;
	   	wei = 0;
	   	//clki = 0;
	   	en_single = 1;

	   	elapsed_time = 0;
	   	sprintf(concat,"%s/best_tracks.out",dpath);
	   	best_tracks = fopen(concat, "w");

	   /*	for (i = 0; i < 10; i = i+1){
	   		for (j = 0; j < 2; j = j+1){
	   			`clk_drive(clki, j);
	   			`__top_module__
	   	    end
	       end*/

	   	call_sp();

	   	for (i = 0; i < 200 + max_ev-1; i = i+1){
	   		wei = 0;
	   		for (k = 0; k < 5; k = k+1){

	   			csi[k] = 0;
	   			for (j = 0; j < 9; j = j+1){
	   				for (si = 0; si < seg_ch; si = si+1){
	   					qi[k][j][si] = 0;
	   					wgi[k][j][si] = 0;
	   					hstri[k][j][si] = 0;
	   					cpati[k][j][si] = 0;
	   				}
	   			}
	   		}




	   		// write ph_init and th_init parameters into ME1/1 only
	   		if (i < 36){
	   			csi[i/18][(i/6)%3] = 1;//[station][chamber]
	   			seli = 0; sel11i=2;
	   			wei = 1;
	   			addri = i%6;
	   			switch(addri){
	   			case 0: r_ini = ph_init[i/18][(i/6)%3]; // ph_init_b
	   				call_sp();
	   				break;
	   			case 1: r_ini = ph_disp[(i/18)*12 + (i/6)%3]; // ph_disp_b
	   				call_sp();
	   				break;
	   			case 2: r_ini = ph_init[i/18][(i/6)%3 + 9]; // ph_init_a
	   				call_sp();
	   				break;
	   			case 3: r_ini = ph_disp[(i/18)*12 + (i/6)%3 + 9]; // ph_disp_a
	   				call_sp();
	   				break;
	   			case 4: r_ini = th_init[(i/18)*12 + (i/6)%3]; // th_init
	   			call_sp();
	   				break;
	   			case 5: r_ini = th_disp[(i/18)*12 + (i/6)%3]; // th_disp
	   				call_sp();
	   				break;
	   			default: break;
	   			}
	   		}

	   		// all other ME1 chambers
	   		if (i >= 36 && i < 36+48){
	   			ii = i - 36;
	   			csi[ii/24][(ii/4)%6+3] = 1;//[station][chamber]
	   			seli = 0; sel11i=2;
	   			wei = 1;
	   			addri = ii % 4;
	   			switch(addri){
	   			case 0: r_ini = ph_init[ii/24][(ii/4)%6+3]; // ph_init
	   			call_sp();
	   				break;
	   			case 1: r_ini = th_init[(ii/24)*12 + (ii/4)%6+3]; // th_init
	   			call_sp();
	   				break;
	   			case 2: r_ini = ph_disp[(ii/24)*12 + (ii/4)%6+3]; // ph_disp
	   			call_sp();
	   				break;
	   			case 3: r_ini = th_disp[(ii/24)*12 + (ii/4)%6+3]; // th_disp
	   			call_sp();
	   				break;
	   			default: break;
	   			}
	   		}

	   		// ME2,3,4 chambers
	   		if (i >= 36+48 && i < 36+48+108){

	   			ii = i - (36+48);
	   			csi[ii/36+2][(ii/4)%9] = 1; //[station][chamber]
	   			seli = 0; sel11i=2;
	   			wei = 1;
	   			addri = ii % 4;
	   			switch(addri){
	   			case 0: r_ini = ph_init[ii/36+2][(ii/4)%9]; // ph_init
	   			call_sp();
	   				break;
	   			case 1: r_ini = th_init[(ii/36)*9 + (ii/4)%9 + 24]; // th_init
	   			call_sp();
	   				break;
	   			case 2: r_ini = ph_disp[(ii/36)*9 + (ii/4)%9 + 24]; // ph_disp
	   			call_sp();
	   				break;
	   			case 3: r_ini = th_disp[(ii/36)*9 + (ii/4)%9 + 24]; // th_disp
	   			call_sp();
	   				break;
	   			default:
	   				break;
	   			}
	   		}

	   /****************************************/
	   //read params registers not included*****/
	   /****************************************/


	   		if (i > 200){
	   			good_ev = 0;
	   			st_cnt = 0;
	   			for (ist = 0; ist < 5; ist=ist+1){
	   				for (icid = 0; icid < 9; icid=icid+1){
	   					for (si = 0; si < seg_ch; si = si+1){
	   						qi  [ist][icid][si] = quality  [ev][ist][icid][si];
	   						wgi [ist][icid][si] = wiregroup[ev][ist][icid][si];
	   						hstri[ist][icid][si] = hstrip  [ev][ist][icid][si];
	   						cpati[ist][icid][si] = clctpat [ev][ist][icid][si];
	   						//							$fwrite(sim_out, "ev: %d st: %d ch: %d prim: %d   q: %h w: %h s: %h\n",
	   						//								ev, ist, icid, ipr, qi [ist][icid], wgi [ist][icid], hstri [ist][icid]);

	   						// check if there is chamber data, update good event station mask
	   						if (qi  [ist][icid][si] > 0) good_ev[ist] = 1;
	   					}
	   				} // for (icid = 0; icid < 9; icid=icid+1)
	   				// count stations in this event
	   				if (good_ev[ist]) st_cnt = st_cnt + 1;
	   			}
	   			ev = ev + 1;
	   			// count event as good if more than 2 stations, other than 3-4
	   			if (good_ev != 0 && good_ev != 1 && good_ev != 2 && good_ev != 4 && good_ev != 8 && good_ev != 16 && good_ev != 24){
	   				good_ev_cnt = good_ev_cnt+1;
	   				//print_flag=1;
	   			}

	   				//print_flag=0;

	   			if (good_ev == 24) st_cnt = 7; // 3-4 tracks marked as having 7 stations

	   			//begin_time = timerval();


	   			///////////////////////////PRINT THE OUTPUTS/////////////////////////

	   			call_sp(); //////////////SEND INPUTS
	   			//print_flag=0;




	               iev = i-200;
	               fprintf(sim_out, "event: %d\n", iev);

	               //$fwrite(sim_out, "ph: %d %d %d %d %d\n",
	               //        uut.ph[0][3][0], uut.ph[1][3][0], uut.ph[2][3][0], uut.ph[3][3][0], uut.ph[4][3][0]);

	               for (ip = 0; ip < 5; ip = ip+1){
	                   for (j = 0; j < 9; j = j+1){

	                       for (k = 0; k < 2; k = k+1){
	                           if (uut.ph[ip][j][k] != 0){
	                               if (ip <= 1 && j < 3){ // ME11
	                                   fprintf(sim_out, "upper part st: %u ch: %d ph: %d  th: %d %d  qi:%d\n", ip, j,   int(uut.ph[ip][j][k]),   int(uut.th11[ip][j][k*2]),
	                                   		  int(uut.th11[ip][j][k*2+1]),int(qi[ip][j][k]));
	                               }
	                              else
	                                   fprintf(sim_out, "st: %d ch: %d ph: %d  th: %d, qi:%d\n", ip, j,   int(uut.ph[ip][j][k]),   int(uut.th[ip][j][k]), int(qi[ip][j][k]));
	                           }
	                       }
	                   }
	               }

	   		}


	   	}
	   	cout <<"here"<<sizeof(int)<<endl;
	   	//cout<<"events = "<<int(good_ev_cnt)<<endl;
	   	fprintf(sim_out, "elapsed_time: %lf\n", elapsed_time);
	   	fclose (best_tracks);
	   	fclose (sim_out);



return 0;
}
