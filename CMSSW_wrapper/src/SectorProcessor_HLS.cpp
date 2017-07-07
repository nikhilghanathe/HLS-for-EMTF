#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessor_HLS.h"
#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessor.hh"
#include "L1Trigger/L1TMuonEndCap/interface/SectorProcessorLUT.hh"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "L1Trigger/L1TMuonEndCap/interface/TrackTools.hh"


using CSCData = L1TMuon::TriggerPrimitive::CSCData;
using RPCData = L1TMuon::TriggerPrimitive::RPCData;



#define call_sp() 
 /*this->sp( \
		vpf,qi, wgi, hstri, cpati,\
		csi, seli, addri, r_ini, r_outo, wei,\
		cppf_rxd, cppf_rx_valid,\
   		bt_phi, bt_theta, bt_cpattern, bt_delta_ph,	bt_delta_th,\
   		bt_sign_ph,	bt_sign_th, bt_rank, \
   		bt_vi, bt_hi, bt_ci, bt_si,\
   		ptlut_addr, ptlut_cs, &ptlut_addr_val,\
		gmt_phi, gmt_eta, gmt_qlt, &gmt_crg,\
   		endcap, sector, lat_test\
   		)
*/
#define fill_param(addr,r_in,b,c) for(int s=0;s<6;s++)\
	  csi[s]=0;\
addri=addr; r_ini=r_in; csi[b][c]=1; call_sp();
			

#define  fill_LUT_th_corr(a,b,c)\
	addri=0; seli=2; wei=1;\
	for(int j=0;j<6;j++)\
		csi[j]=0;\
	csi[b][c]=1;\
	fp=fopen(concat,"r");\
	if(fp==NULL){std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!Could not open file"<<std::endl; std::cout<<"file path: "<<concat<<std::endl; exit(1);}\
	for( int p=0;p<th_mem_sz||(!feof(fp));p++){\
		fscanf(fp,"%x",&tmp);\
	if(feof(fp)) {break;}\
	addri=p; r_ini=tmp;\
	call_sp();}\
	fclose(fp)
		
#define  fill_LUT_th(a,b,c)\
	addri=0; seli=1; wei=1;\
	for(int j=0;j<6;j++)\
		csi[j]=0;\
	csi[b][c]=1;\
	fp=fopen(concat,"r");\
	if(fp==NULL){std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!Could not open file"<<std::endl; std::cout<<"file path: "<<concat<<std::endl; exit(1);}\
	for( int p=0;p<th_mem_sz||(!feof(fp));p++){\
		fscanf(fp,"%x",&tmp);\
	if(feof(fp)) { break;}\
	addri=p; r_ini=tmp;\
	call_sp();}\
	fclose(fp)
		
				
				
const SectorProcessorLUT& SectorProcessor_HLS::lut_HLS() const {
  return *lut_;
}
				
void SectorProcessor_HLS::configure( const SectorProcessorLUT* lut,
									int endcap, int sector, 
									int verbose, int we){
this->endcap_=endcap;
this->sector_=sector;
this->verbose_=verbose;
this->lut_=lut;

std::cout<<"configure sector inside sectorprocessor_HLS is "<<sector_<<" real sector= "<<sector<<std::endl;

	    for(int i=0;i<6;i++){
	    	for(int j=0;j<9;j++){
				vpf[i][j]=0;
	    		for(int k=0;k<seg_ch;k++){
	    			qi[i][j][k]=0;
	    			wgi[i][j][k]=0;
	    			hstri[i][j][k]=0;
	    			cpati[i][j][k]=0;
	    		}

	    	}
	    }
		
		
   int tmp;
   FILE *fp;
   char concat[1000];
   
	// ph_init storage is full-precision now
	// chamber index is 0..11 to include ME11a and b
	ap_uint<bw_fph>  	  ph_init0 [16];
	ap_uint<bw_fph>  	  ph_init1 [16];
	ap_uint<bw_fph>  	  ph_init2 [16];
	ap_uint<bw_fph>  	  ph_init3 [16];
	ap_uint<bw_fph>  	  ph_init4 [16];
	ap_uint<bw_fph> 	  ph_init [5][16]; // [station][chamber]

	// arrays below contains values for each chamber
	// chamber count is ME1=12*2 ME2,3,4=9*3, total 51
	ap_uint<bw_th>    th_init [61]; // chamber origins in th
	ap_uint<bw_ph>  	  ph_disp [61]; // chamber displacements in ph
	ap_uint<bw_th>    th_disp [61]; // chamber displacements in th
   	
	char fes[500]; // endcap and sector numbers for LUT file names
	char fest[500]; // endcap and sector numbers for LUT file names
	const char *dpath= "/afs/cern.ch/user/n/npratapg/public/CMSSW_9_0_0_pre2/src/L1Trigger/L1TMuonEndCap/data/emtf_luts_HLS";
	sprintf(fes,"_endcap_%d_sec_%d_",endcap,sector);
	sprintf(fest,"_endcap_%d_sect_%d",endcap,sector); 
     


   //FILL TH_CORR_MEM
/*******************fill the LUTs******************************************/


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



	sprintf(concat,"%s/vl_lut/th_init%s.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<61;i++){
		fscanf(fp,"%x",&tmp);
		th_init[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_disp%s.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<61;i++){
		fscanf(fp,"%x",&tmp);
		ph_disp[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);


	sprintf(concat,"%s/vl_lut/th_disp%s.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<61;i++){
		fscanf(fp,"%x",&tmp);
		th_disp[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_init_full%s_st_0.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<16;i++){
		fscanf(fp,"%x",&tmp);
		ph_init0[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_init_full%s_st_1.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<16;i++){
		fscanf(fp,"%x",&tmp);
		ph_init1[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_init_full%s_st_2.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<16;i++){
		fscanf(fp,"%x",&tmp);
		ph_init2[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_init_full%s_st_3.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<16;i++){
		fscanf(fp,"%x",&tmp);
		ph_init3[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	sprintf(concat,"%s/vl_lut/ph_init_full%s_st_4.lut",dpath,fest);
	fp=fopen(concat,"r");
	for(int i=0;i<16;i++){
		fscanf(fp,"%x",&tmp);
		ph_init4[i]=tmp;
		if(feof(fp))break;
	 }fclose(fp);

	for(int i=0;i<16;i++)
		ph_init[0][i] = ph_init0[i];
	for(int i=0;i<16;i++)
		ph_init[1][i] = ph_init1[i];
	for(int i=0;i<16;i++)
		ph_init[2][i] = ph_init2[i];
	for(int i=0;i<16;i++)
		ph_init[3][i] = ph_init3[i];
	for(int i=0;i<16;i++)
		ph_init[4][i] = ph_init4[i];


seli=0; wei=1;


  fill_param(0,ph_init0[0],0,0); //ME11b
  fill_param(1,ph_disp[0],0,0);//ME11b
  fill_param(2,ph_init0[0+9],0,0);//Me11a
  fill_param(3,ph_disp[0+9],0,0);//Me11a
  fill_param(4,th_init[0],0,0);
  fill_param(5,th_disp[0],0,0);


  fill_param(0,ph_init0[1],0,1); //ME11b
  fill_param(1,ph_disp[1],0,1);//ME11b
  fill_param(2,ph_init0[1+9],0,1);//Me11a
  fill_param(3,ph_disp[1+9],0,1);//Me11a
  fill_param(4,th_init[1],0,1);
  fill_param(5,th_disp[1],0,1);

  fill_param(0,ph_init0[2],0,2); //ME11b
  fill_param(1,ph_disp[2],0,2);//ME11b
  fill_param(2,ph_init0[2+9],0,2);//Me11a
  fill_param(3,ph_disp[2+9],0,2);//Me11a
  fill_param(4,th_init[2],0,2);
  fill_param(5,th_disp[2],0,2);

  fill_param(0,ph_init0[3],0,3);
  fill_param(1,th_init[3],0,3);
  fill_param(2,ph_disp[3],0,3);
  fill_param(3,th_disp[3],0,3);

  fill_param(0,ph_init0[4],0,4);
  fill_param(1,th_init[4],0,4);
  fill_param(2,ph_disp[4],0,4);
  fill_param(3,th_disp[4],0,4);

  fill_param(0,ph_init0[5],0,5);
  fill_param(1,th_init[5],0,5);
  fill_param(2,ph_disp[5],0,5);
  fill_param(3,th_disp[5],0,5);

  fill_param(0,ph_init0[6],0,6);
  fill_param(1,th_init[6],0,6);
  fill_param(2,ph_disp[6],0,6);
  fill_param(3,th_disp[6],0,6);

  fill_param(0,ph_init0[7],0,7);
  fill_param(1,th_init[7],0,7);
  fill_param(2,ph_disp[7],0,7);
  fill_param(3,th_disp[7],0,7);

  fill_param(0,ph_init0[8],0,8);
  fill_param(1,th_init[8],0,8);
  fill_param(2,ph_disp[8],0,8);
  fill_param(3,th_disp[8],0,8);


  fill_param(0,ph_init1[0],1,0); //ME11b
  fill_param(1,ph_disp[16],1,0);//ME11b
  fill_param(2,ph_init1[0+9],1,0);//Me11a
  fill_param(3,ph_disp[16+9],1,0);//Me11a
  fill_param(4,th_init[16],1,0);
  fill_param(5,th_disp[16],1,0);

  fill_param(0,ph_init1[0+1],1,1); //ME11b
  fill_param(1,ph_disp[16+1],1,1);//ME11b
  fill_param(2,ph_init1[0+9+1],1,1);//Me11a
  fill_param(3,ph_disp[16+9+1],1,1);//Me11a
  fill_param(4,th_init[16+1],1,1);
  fill_param(5,th_disp[16+1],1,1);

  fill_param(0,ph_init1[0+1+1],1,2); //ME11b
  fill_param(1,ph_disp[16+1+1],1,2);//ME11b
  fill_param(2,ph_init1[0+9+1+1],1,2);//Me11a
  fill_param(3,ph_disp[16+9+1+1],1,2);//Me11a
  fill_param(4,th_init[16+1+1],1,2);
  fill_param(5,th_disp[16+1+1],1,2);

  fill_param(0,ph_init1[1],1,3);
  fill_param(1,th_init[19],1,3);
  fill_param(2,ph_disp[19],1,3);
  fill_param(3,th_disp[19],1,3);

  fill_param(0,ph_init1[1+1],1,4);
  fill_param(1,th_init[19+1],1,4);
  fill_param(2,ph_disp[19+1],1,4);
  fill_param(3,th_disp[19+1],1,4);

  fill_param(0,ph_init1[1+1+1],1,5);
  fill_param(1,th_init[19+1+1],1,5);
  fill_param(2,ph_disp[19+1+1],1,5);
  fill_param(3,th_disp[19+1+1],1,5);

  fill_param(0,ph_init1[1+1+1+1],1,6);
  fill_param(1,th_init[19+1+1+1],1,6);
  fill_param(2,ph_disp[19+1+1+1],1,6);
  fill_param(3,th_disp[19+1+1+1],1,6);

  fill_param(0,ph_init1[1+1+1+1+1],1,7);
  fill_param(1,th_init[19+1+1+1+1],1,7);
  fill_param(2,ph_disp[19+1+1+1+1],1,7);
  fill_param(3,th_disp[19+1+1+1+1],1,7);

  fill_param(0,ph_init1[1+1+1+1+1+1],1,8);
  fill_param(1,th_init[19+1+1+1+1+1],1,8);
  fill_param(2,ph_disp[19+1+1+1+1+1],1,8);
  fill_param(3,th_disp[19+1+1+1+1+1],1,8);



  //neighbor sector ME1
  //ME11 single chamber
  fill_param(0,ph_init0[12],5,0); //ME11b
  fill_param(1,ph_disp[12],5,0);//ME11b
  fill_param(2,ph_init0[15],5,0);//Me11a
  fill_param(3,ph_disp[15],5,0);//Me11a
  fill_param(4,th_init[12],5,0);
  fill_param(5,th_disp[12],5,0);

  fill_param(0,ph_init0[1+12],5,1);
  fill_param(1,th_init[13],5,1);
  fill_param(2,ph_disp[13],5,1);
  fill_param(3,th_disp[13],5,1);

  fill_param(0,ph_init0[2+12],5,2);
  fill_param(1,th_init[14],5,2);
  fill_param(2,ph_disp[14],5,2);
  fill_param(3,th_disp[14],5,2);


  	  //ME234
  fill_param(0,ph_init2[0],2,0);
  fill_param(1,th_init[28],2,0);
  fill_param(2,ph_disp[28],2,0);
  fill_param(3,th_disp[28],2,0);

  fill_param(0,ph_init2[1],2,1);
  fill_param(1,th_init[29],2,1);
  fill_param(2,ph_disp[29],2,1);
  fill_param(3,th_disp[29],2,1);

  fill_param(0,ph_init2[2],2,2);
  fill_param(1,th_init[30],2,2);
  fill_param(2,ph_disp[30],2,2);
  fill_param(3,th_disp[30],2,2);

  fill_param(0,ph_init2[3],2,3);
  fill_param(1,th_init[31],2,3);
  fill_param(2,ph_disp[31],2,3);
  fill_param(3,th_disp[31],2,3);

  fill_param(0,ph_init2[4],2,4);
  fill_param(1,th_init[32],2,4);
  fill_param(2,ph_disp[32],2,4);
  fill_param(3,th_disp[32],2,4);

  fill_param(0,ph_init2[5],2,5);
  fill_param(1,th_init[33],2,5);
  fill_param(2,ph_disp[33],2,5);
  fill_param(3,th_disp[33],2,5);

  fill_param(0,ph_init2[6],2,6);
  fill_param(1,th_init[34],2,6);
  fill_param(2,ph_disp[34],2,6);
  fill_param(3,th_disp[34],2,6);

  fill_param(0,ph_init2[7],2,7);
  fill_param(1,th_init[35],2,7);
  fill_param(2,ph_disp[35],2,7);
  fill_param(3,th_disp[35],2,7);

  fill_param(0,ph_init2[8],2,8);
  fill_param(1,th_init[36],2,8);
  fill_param(2,ph_disp[36],2,8);
  fill_param(3,th_disp[36],2,8);


  //ME234 neighbors
  fill_param(0,ph_init2[0+9],5,(2*2-1+0));
  fill_param(1,th_init[37],5,(2*2-1+0));
  fill_param(2,ph_disp[37],5,(2*2-1+0));
  fill_param(3,th_disp[37],5,(2*2-1+0));

  fill_param(0,ph_init2[10],5,(2*2-1+1));
  fill_param(1,th_init[38],5,(2*2-1+1));
  fill_param(2,ph_disp[38],5,(2*2-1+1));
  fill_param(3,th_disp[38],5,(2*2-1+1));



  //ME234
  fill_param(0,ph_init3[0],3,0);
  fill_param(1,th_init[39],3,0);
  fill_param(2,ph_disp[39],3,0);
  fill_param(3,th_disp[39],3,0);

  fill_param(0,ph_init3[1],3,1);
  fill_param(1,th_init[40],3,1);
  fill_param(2,ph_disp[40],3,1);
  fill_param(3,th_disp[40],3,1);

  fill_param(0,ph_init3[2],3,2);
  fill_param(1,th_init[41],3,2);
  fill_param(2,ph_disp[41],3,2);
  fill_param(3,th_disp[41],3,2);

  fill_param(0,ph_init3[3],3,3);
  fill_param(1,th_init[42],3,3);
  fill_param(2,ph_disp[42],3,3);
  fill_param(3,th_disp[42],3,3);

  fill_param(0,ph_init3[4],3,4);
  fill_param(1,th_init[43],3,4);
  fill_param(2,ph_disp[43],3,4);
  fill_param(3,th_disp[43],3,4);

  fill_param(0,ph_init3[5],3,5);
  fill_param(1,th_init[44],3,5);
  fill_param(2,ph_disp[44],3,5);
  fill_param(3,th_disp[44],3,5);

  fill_param(0,ph_init3[6],3,6);
  fill_param(1,th_init[45],3,6);
  fill_param(2,ph_disp[45],3,6);
  fill_param(3,th_disp[45],3,6);

  fill_param(0,ph_init3[7],3,7);
  fill_param(1,th_init[46],3,7);
  fill_param(2,ph_disp[46],3,7);
  fill_param(3,th_disp[46],3,7);

  fill_param(0,ph_init3[8],3,8);
  fill_param(1,th_init[47],3,8);
  fill_param(2,ph_disp[47],3,8);
  fill_param(3,th_disp[47],3,8);



  //ME234 neighbors
  fill_param(0,ph_init3[9],5,(3*2-1+0));
  fill_param(1,th_init[48],5,(3*2-1+0));
  fill_param(2,ph_disp[48],5,(3*2-1+0));
  fill_param(3,th_disp[48],5,(3*2-1+0));

  fill_param(0,ph_init3[10],5,(3*2-1+1));
  fill_param(1,th_init[49],5,(3*2-1+1));
  fill_param(2,ph_disp[49],5,(3*2-1+1));
  fill_param(3,th_disp[49],5,(3*2-1+1));



  //ME234
  fill_param(0,ph_init4[0],4,0);
  fill_param(1,th_init[50],4,0);
  fill_param(2,ph_disp[50],4,0);
  fill_param(3,th_disp[50],4,0);

  fill_param(0,ph_init4[1],4,1);
  fill_param(1,th_init[51],4,1);
  fill_param(2,ph_disp[51],4,1);
  fill_param(3,th_disp[51],4,1);

  fill_param(0,ph_init4[2],4,2);
  fill_param(1,th_init[52],4,2);
  fill_param(2,ph_disp[52],4,2);
  fill_param(3,th_disp[52],4,2);

  fill_param(0,ph_init4[3],4,3);
  fill_param(1,th_init[53],4,3);
  fill_param(2,ph_disp[53],4,3);
  fill_param(3,th_disp[53],4,3);

  fill_param(0,ph_init4[4],4,4);
  fill_param(1,th_init[54],4,4);
  fill_param(2,ph_disp[54],4,4);
  fill_param(3,th_disp[54],4,4);

  fill_param(0,ph_init4[5],4,5);
  fill_param(1,th_init[55],4,5);
  fill_param(2,ph_disp[55],4,5);
  fill_param(3,th_disp[55],4,5);

  fill_param(0,ph_init4[6],4,6);
  fill_param(1,th_init[56],4,6);
  fill_param(2,ph_disp[56],4,6);
  fill_param(3,th_disp[56],4,6);

  fill_param(0,ph_init4[7],4,7);
  fill_param(1,th_init[57],4,7);
  fill_param(2,ph_disp[57],4,7);
  fill_param(3,th_disp[57],4,7);

  fill_param(0,ph_init4[8],4,8);
  fill_param(1,th_init[58],4,8);
  fill_param(2,ph_disp[58],4,8);
  fill_param(3,th_disp[58],4,8);


  //ME234  neighbors
  fill_param(0,ph_init4[9],5,(4*2-1+0));
  fill_param(1,th_init[59],5,(4*2-1+0));
  fill_param(2,ph_disp[59],5,(4*2-1+0));
  fill_param(3,th_disp[59],5,(4*2-1+0));

  fill_param(0,ph_init4[10],5,(4*2-1+1));
  fill_param(1,th_init[60],5,(4*2-1+1));
  fill_param(2,ph_disp[60],5,(4*2-1+1));
  fill_param(3,th_disp[60],5,(4*2-1+1));


		
		
		std::cout<<"lut_filled= "<<lut_filled<<std::endl;
 lut_filled=true;
 std::cout<<"lut_filled= "<<lut_filled<<std::endl;
		

   
}	



									
void SectorProcessor_HLS::process( const SectorProcessorLUT* lut, 
  				   int endcap, int sector, 
				   int verbose, int we,
				   const std::map<int, TriggerPrimitiveCollection>& selected_csc_map,
   				   EMTFHitCollection conv_hits,
				   EMTFTrackCollection best_tracks_HLS ){ 
	

wei=we;
lat_test=0;
std::cout<<"sector inside sectorprocessor_HLS is "<<sector_<<" real sector= "<<sector<<std::endl;

  	//Clear inputs
	for(int i=0;i<5;i++){
		for(int j=0;j<9;j++){
			pr_cnt[i][j]=0;
			for(int k=0;k<seg_ch;k++){
				qi[i][j][k]=0;
				wgi[i][j][k]=0;
				hstri[i][j][k]=0;
				cpati[i][j][k]=0;
			}

		}
	}

  
  int index=0;


  std::map<int, TriggerPrimitiveCollection>::const_iterator map_tp_it  = selected_csc_map.begin();
  std::map<int, TriggerPrimitiveCollection>::const_iterator map_tp_end = selected_csc_map.end();
  
  for (; map_tp_it != map_tp_end; ++map_tp_it) {
    // Unique chamber ID in FW, {0, 53} as defined in get_index_csc in src/PrimitiveSelection.cc
    int selected   = map_tp_it->first;
    // "Primitive Conversion" sector/station/chamber ID scheme used in FW
    int pc_sector  = sector_;
    int pc_station = selected / 9;  // {0, 5} = {ME1 sub 1, ME1 sub 2, ME2, ME3, ME4, neighbor}
    int pc_chamber = selected % 9;  // Equals CSC ID - 1 for all except neighbor chambers
    int pc_segment = 0;             // Counts hits in a single chamber

    TriggerPrimitiveCollection::const_iterator tp_it  = map_tp_it->second.begin();
    TriggerPrimitiveCollection::const_iterator tp_end = map_tp_it->second.end();
int i=0;
  	    
		
    for (; tp_it != tp_end; ++tp_it) {
		i++;
      EMTFHit conv_hit;
   //   convert_csc(pc_sector, pc_station, pc_chamber, pc_segment, *tp_it, conv_hit);
    
    
 
      
  const CSCDetId& tp_detId = tp_it->detId<CSCDetId>();
  const CSCData&  tp_data  = tp_it->getCSCData();

  int tp_endcap    = tp_detId.endcap();
  int tp_sector    = tp_detId.triggerSector();
  int tp_station   = tp_detId.station();
  int tp_ring      = tp_detId.ring();
  int tp_chamber   = tp_detId.chamber();
  
  int tp_bx        = tp_data.bx;
  int tp_csc_ID    = tp_data.cscID;
  int csc_nID;
  // station 1 --> subsector 1 or 2
  // station 2,3,4 --> subsector 0
  int tp_subsector = (tp_station != 1) ? 0 : ((tp_chamber % 6 > 2) ? 1 : 2);

  const bool is_neighbor = (pc_station == 5);

  csc_nID      = tp_csc_ID;  // modify csc_ID if coming from neighbor sector
  if (is_neighbor) {
    // station 1 has 3 neighbor chambers: 13,14,15 in rings 1,2,3
    // (where are chambers 10,11,12 in station 1? they were used to label ME1/1a, but not anymore)
    // station 2,3,4 have 2 neighbor chambers: 10,11 in rings 1,2
    csc_nID = (pc_chamber < 3) ? (pc_chamber + 12) : ( ((pc_chamber - 1) % 2) + 9);
    csc_nID += 1;

    if (tp_station == 1) {  // neighbor ME1
      assert(tp_subsector == 2);
    }
  }

/*   // Set properties
  conv_hit.SetCSCDetId     ( tp_detId );

  conv_hit.set_endcap      ( (tp_endcap == 2) ? -1 : tp_endcap );
  conv_hit.set_station     ( tp_station );
  conv_hit.set_ring        ( tp_ring );
  //conv_hit.set_roll        ( tp_roll );
  conv_hit.set_chamber     ( tp_chamber );
  conv_hit.set_sector      ( tp_sector );
  conv_hit.set_subsector   ( tp_subsector );
  conv_hit.set_csc_ID      ( tp_csc_ID );
  conv_hit.set_csc_nID     ( csc_nID );
  conv_hit.set_track_num   ( tp_data.trknmb );
  conv_hit.set_sync_err    ( tp_data.syncErr );

  conv_hit.set_bx          ( tp_bx + bxShiftCSC_ );
  conv_hit.set_subsystem   ( TriggerPrimitive::kCSC );
  conv_hit.set_is_CSC      ( true );
  conv_hit.set_is_RPC      ( false );

  conv_hit.set_pc_sector   ( pc_sector );
  conv_hit.set_pc_station  ( pc_station );
  conv_hit.set_pc_chamber  ( pc_chamber );
  conv_hit.set_pc_segment  ( pc_segment );

  conv_hit.set_valid       ( tp_data.valid );
  conv_hit.set_strip       ( tp_data.strip );
  //conv_hit.set_strip_low   ( tp_data.strip_low );
  //conv_hit.set_strip_hi    ( tp_data.strip_hi );
  conv_hit.set_wire        ( tp_data.keywire );
  conv_hit.set_quality     ( tp_data.quality );
  conv_hit.set_pattern     ( tp_data.pattern );
  conv_hit.set_bend        ( tp_data.bend );

  conv_hit.set_neighbor    ( is_neighbor );
  conv_hit.set_sector_idx  ( (endcap_ == 1) ? sector_ - 1 : sector_ + 5 ); */

  //convert_csc_details(conv_hit);
  
  
	

 		std::cout<<"station= "<<pc_station<<" pc_chamber= "<<pc_chamber<<" pr_cnt[tp_station][cscid]= "<<pr_cnt[tp_station][pc_chamber]<<"index= "<<index<<std::endl;
		std::cout<<" in SectorProcessor_HLS.cpp  tp_data.quality= "<<tp_data.quality<<" wiregroup= "<<tp_data.keywire<<std::endl;
		
		index++;
		vpf[pc_station][pc_chamber][pr_cnt[pc_station][pc_chamber]]=tp_data.valid;
		qi[pc_station][pc_chamber][pr_cnt[pc_station][pc_chamber]]=tp_data.quality;
		wgi[pc_station][pc_chamber][pr_cnt[pc_station][pc_chamber]]=tp_data.keywire;
		hstri[pc_station][pc_chamber][pr_cnt[pc_station][pc_chamber]]=tp_data.strip;
		cpati[pc_station][pc_chamber][pr_cnt[pc_station][pc_chamber]]=tp_data.pattern;
  
		pr_cnt[tp_station][csc_nID]++;
   
  

   // Add coordinates from fullsim
/*   {
    const GlobalPoint& gp = tp_geom_->getGlobalPoint(muon_primitive);
    double glob_phi   = emtf::rad_to_deg(gp.phi().value());
    double glob_theta = emtf::rad_to_deg(gp.theta());
    double glob_eta   = gp.eta();

    conv_hit.set_phi_sim   ( glob_phi );
    conv_hit.set_theta_sim ( glob_theta );
    conv_hit.set_eta_sim   ( glob_eta );
  } */
 
  }
 }
 
 
     
 
 	call_sp();
	 
  
/*   // Output

  conv_hit.set_phi_fp     ( fph );        // Full-precision integer phi
  conv_hit.set_theta_fp   ( th );         // Full-precision integer theta
  conv_hit.set_phzvl      ( phzvl );      // Local zone word: (1*low) + (2*mid) + (4*low) - used in FW debugging
  conv_hit.set_ph_hit     ( ph_hit );     // Intermediate quantity in phi calculation - used in FW debugging
  conv_hit.set_zone_hit   ( zone_hit );   // Phi value for building patterns (0.53333 deg precision)
  conv_hit.set_zone_code  ( zone_code );  // Full zone word: 1*(zone 0) + 2*(zone 1) + 4*(zone 2) + 8*(zone 3)

  conv_hit.set_fs_segment   ( fs_segment );    // Segment number used in primitive matching
  conv_hit.set_fs_zone_code ( fs_zone_code );  // Zone word used in primitive matching

  conv_hit.set_bt_station   ( bt_station );
  conv_hit.set_bt_segment   ( bt_segment );

  conv_hit.set_phi_loc  ( emtf::calc_phi_loc_deg(fph) );
  conv_hit.set_phi_glob ( emtf::calc_phi_glob_deg(conv_hit.Phi_loc(), conv_hit.Sector()) );
  conv_hit.set_theta    ( emtf::calc_theta_deg_from_int(th) );
  conv_hit.set_eta      ( emtf::calc_eta_from_theta_deg(conv_hit.Theta(), conv_hit.Endcap()) );
	
  (tp_chamber % 6 > 2) ? 1 : 2);
      conv_hits.push_back(conv_hit);
 */
  
}






