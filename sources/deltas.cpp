#ifndef CMSSW_MACRO
 #include <ap_int.h>
#else
#include "../include/ap_int.h"
#endif

#include "../interface/spbits.h"
#include "../interface/deltas.h"
using namespace std;


void delta::deltas(
		int st, int csc,
		ap_uint<seg_ch> 	vi [4], // valid
			ap_uint<2> 		hi [4], // bx index
			ap_uint<3>  	ci [4], // chamber
			ap_uint<4>  	si, // segment
			ap_uint<bw_fph> ph_match [4], // matching ph
			// theta coordinates [station][segment]
			ap_uint<bw_th> 	th_match [4][seg_ch],
			ap_uint<4> 		cpat_match [4], // matching pattern
			ap_uint<bwr>  	ph_q, // pattern rank, carries straigtness and ph station information
			ap_uint<bw_th>  th_window, // max th diff

			// precise phi and theta
			ap_uint<bw_fph> *phi,
			ap_uint<bw_th>  *theta,
			// [station]
			ap_uint<4> 		cpattern [4],
			// ph and th deltas from best stations
			// indexes: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
			ap_uint<bw_fph> delta_ph [6],
			ap_uint<bw_th>  delta_th [6],
			ap_uint<6> 		*sign_ph,
			ap_uint<6> 		*sign_th,
			ap_uint<bwr+1> 	*rank, // output rank, to be used for sorting
			ap_uint<seg_ch> vir[4], // valid
			ap_uint<2> 		hir [4], // bx index
			ap_uint<3> 		cir [4], // chamber
			ap_uint<4> 		*sir // segment
			){
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return



	const int seg1 = 0 ? th_ch11 : seg_ch; // number of segments station 1
	const int bw_nm1 = 0 ? 3 : 2;
	const int bw_nm2 = 2;
	const ap_uint<1> C_1=0x1;

	if(this->pr){
	cout<<"ph_q= "<<ph_q<<endl;
	}

	ap_uint<4>  vstat; // valid stations based on th coordinates
	ap_uint<bw_th> thA, thB, dth;

	ap_uint<1> 			   dvl;
	ap_uint<bw_th> dth12 [seg1*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth12 complete dim=0
	ap_uint<bw_th> dth13 [seg1*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth13 complete dim=0
	ap_uint<bw_th> dth14 [seg1*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth14 complete dim=0
	ap_uint<bw_th> dth23 [seg_ch*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth23 complete dim=0
	ap_uint<bw_th> dth24 [seg_ch*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth24 complete dim=0
	ap_uint<bw_th> dth34 [seg_ch*seg_ch];
#pragma HLS ARRAY_PARTITION variable=dth34 complete dim=0

	ap_uint<seg1*seg_ch>  dvl12 ;
	ap_uint<seg1*seg_ch>	dvl13 ;
	ap_uint<seg1*seg_ch>	dvl14 ;
	ap_uint<seg_ch*seg_ch>	dvl23 ;
	ap_uint<seg_ch*seg_ch>	dvl24 ;
	ap_uint<seg_ch*seg_ch>	dvl34 ;

	ap_uint<bw_th> bth12 ;
	ap_uint<bw_th> bth13 ;
	ap_uint<bw_th> bth14 ;
	ap_uint<bw_th> bth23 ;
	ap_uint<bw_th> bth24 ;
	ap_uint<bw_th> bth34 ;

	ap_uint<seg1*seg_ch>  sth12;
	ap_uint<seg1*seg_ch>  sth13;
	ap_uint<seg1*seg_ch>  sth14;
	ap_uint<seg_ch*seg_ch>  sth23;
	ap_uint<seg_ch*seg_ch>  sth24;
	ap_uint<seg_ch*seg_ch>  sth34;

	ap_uint<bw_nm1>  bnm12;
	ap_uint<bw_nm1>  bnm13;
	ap_uint<bw_nm1>  bnm14;
	ap_uint<bw_nm2>  bnm23;
	ap_uint<bw_nm2>  bnm24;
	ap_uint<bw_nm2>  bnm34;

	ap_uint<bw_fph>    phA, phB, dph, sph;

	ap_uint<bw_fph>	dph12, dph13, dph14, dph23, dph24, dph34;
	ap_uint<1> 		sph12, sph13, sph14, sph23, sph24, sph34;
	ap_uint<1> 		bsg12, bsg13, bsg14, bsg23, bsg24, bsg34;
	ap_uint<1> 		bvl12, bvl13, bvl14, bvl23, bvl24, bvl34;
	ap_uint<bwr+1> a_rank;
	int j, k;
	ap_uint<4> i1, i2;

	static delta bd12,bd13,bd14,bd23,bd24,bd34;

	ap_uint<1>		sth;
	ap_uint<4>		vmask1, vmask2, vmask3;
	ap_uint<6> 		a_sign_ph;
	ap_uint<6> 		a_sign_th;
	ap_uint<bw_fph> a_phi;
	ap_uint<bw_th>  a_theta;


	if(this->pr){
		for(int i=0;i<4;i++){
			cout<<"ph_match["<<i<<"]= "<<ph_match[i]<<endl;
		}
	}

	if(this->pr){
		for(int i=0;i<4;i++){
			for(int j=0;j<seg_ch;j++){
				cout<<"th_match["<<i<<"]["<<j<<"]="<<th_match[i][j]<<endl;
			}
		}
	}

	for (i1 = 0; i1 < 3; i1 = i1+1){ // station 1 loop
		for (i2 = i1+1; i2 < 4; i2 = i2+1){ // station 2 loop
			// calculate theta deltas
			for (j = 0; j < ((i1==0) ? seg1 : seg_ch); j = j+1){ // segment st A loop
				for (k = 0; k < seg_ch; k = k+1){ // segment st B loop
					thA = th_match[i1][j];
					thB = th_match[i2][k];
					if(this->pr){
						if(i1==0 && i2==3){
							cout<<"thA th_match[i1]["<<j<<"]="<<th_match[i1][j]<<endl;
							cout<<"thB th_match[i1]["<<k<<"]="<<th_match[i2][k]<<endl;
						}
					}
					dth = (thA > thB) ? thA - thB : thB - thA;
					sth = (thA > thB); // sign

					// if any of the thetas are invalid, set difference to max
					if (thA == 0 || thB == 0) dth = 0x7f;

					// if one of the segments not valid, delta not valid
					dvl = vi[i1][j%seg_ch] & vi[i2][k]; // difference valid flag
					switch((i1(1,0), i2(1,0))){
					case 1:	 dth12[j*seg_ch + k] = dth; dvl12[j*seg_ch + k] = dvl; sth12[j*seg_ch + k] = sth; break;
					case 2:  dth13[j*seg_ch + k] = dth; dvl13[j*seg_ch + k] = dvl; sth13[j*seg_ch + k] = sth; break;
					case 3:  dth14[j*seg_ch + k] = dth; dvl14[j*seg_ch + k] = dvl; sth14[j*seg_ch + k] = sth; break;
					case 6:  dth23[j*seg_ch + k] = dth; dvl23[j*seg_ch + k] = dvl; sth23[j*seg_ch + k] = sth; break;
					case 7:	 dth24[j*seg_ch + k] = dth; dvl24[j*seg_ch + k] = dvl; sth24[j*seg_ch + k] = sth; break;
					case 11: dth34[j*seg_ch + k] = dth; dvl34[j*seg_ch + k] = dvl; sth34[j*seg_ch + k] = sth; break;
					default: break;
					}
				}
			} // for (j = 0; j < ((i1==0) ? seg1 : seg_ch); j = j+1)

			// calculate phi deltas
			phA = ph_match[i1];
			phB = ph_match[i2];
			dph = (phA > phB) ? phA - phB : phB - phA;
			sph = (phA <= phB); // sign reversed according to Matt's oral request, 2016-04-27

			switch ((i1(1,0), i2(1,0))){
			case 1:  dph12 = dph; sph12 = sph; break;
			case 2:  dph13 = dph; sph13 = sph; break;
			case 3:  dph14 = dph; sph14 = sph; break;
			case 6:  dph23 = dph; sph23 = sph; break;
			case 7:  dph24 = dph; sph24 = sph; break;
			case 11: dph34 = dph; sph34 = sph; break;
			default: break;
			}


		}
	} // for (i = 0; i < 3; i = i+1)



	bd12.best_delta_seg_ch(
			dth12,
			sth12,
			dvl12,
			&bth12, // smallest delta
			&bsg12, // sign of bth
			&bvl12, // valid flag
			&bnm12 // winner number
	);

	bd13.best_delta_seg_ch(
			dth13,
			sth13,
			dvl13,
			&bth13, // smallest delta
			&bsg13, // sign of bth
			&bvl13, // valid flag
			&bnm13 // winner number
	);

	bd14.best_delta_seg_ch(
			dth14,
			sth14,
			dvl14,
			&bth14, // smallest delta
			&bsg14, // sign of bth
			&bvl14, // valid flag
			&bnm14 // winner number
	);


	bd23.best_delta_seg_ch(
			dth23,
			sth23,
			dvl23,
			&bth23, // smallest delta
			&bsg23, // sign of bth
			&bvl23, // valid flag
			&bnm23 // winner number
	);

	bd24.best_delta_seg_ch(
			dth24,
			sth24,
			dvl24,
			&bth24, // smallest delta
			&bsg24, // sign of bth
			&bvl24, // valid flag
			&bnm24 // winner number
	);

	bd34.best_delta_seg_ch(
			dth34,
			sth34,
			dvl34,
			&bth34, // smallest delta
			&bsg34, // sign of bth
			&bvl34, // valid flag
			&bnm34 // winner number
	);

	ap_uint<1>	dvalid = dvl12 != 0 || dvl13 != 0 || dvl14 != 0 || dvl23 != 0 || dvl24 != 0 || dvl34 != 0;

	if(this->pr){
		cout<<"dth14= "<<dth14[0]<<" "<<dth14[1]<<" "<<dth14[2]<<" "<<dth14[3] <<" sth14= "<<sth14<<" dvl14= "<<dvl14<<endl;
		//cout<<" bsg12= "<<bsg12<<" bsg13= "<<bsg13<<" bsg14= "<<bsg14<<" bsg23= "<<bsg23<<" bsg24= "<<bsg24<<" bsg34= "<<bsg34<<endl;
		cout<<" bvl12= "<<bvl12<<" bvl13= "<<bvl13<<" bvl14= "<<bvl14<<" bvl23= "<<bvl23<<" bvl24= "<<bvl24<<" bvl34= "<<bvl34<<endl;
	}



	// find valid segments
	vmask1 = 0x0;
	vmask2 = 0x0;
	vmask3 = 0x0;

	// vmask contains valid station mask = {ME4,ME3,ME2,ME1}
	if ((bth12 <= th_window) && bvl12) vmask1 = vmask1 | 0x3;
	if ((bth13 <= th_window) && bvl13) vmask1 = vmask1 | 0x5;
	if ((bth14 <= th_window) && bvl14) vmask1 = vmask1 | 0x9;
	if ((bth23 <= th_window) && bvl23) vmask2 = vmask2 | 0x6;
	if ((bth24 <= th_window) && bvl24) vmask2 = vmask2 | 0xA;
	if ((bth34 <= th_window) && bvl34) vmask3 = vmask3 | 0xC;

	if(this->pr){
		cout<<" bth12= "<<bth12<<" bth13= "<<bth13<<" bth14= "<<bth14<<" bth23= "<<bth23<<" bth24= "<<bth24<<" bth34= "<<bth34<<endl;
	}

	// merge station masks only if they share bits
	// could try here to find two tracks with identical ph
	// for example vmask1 = 1001 and vmask2 = 0110
	// not done so far, just select one with better station combination
	vstat = vmask1;
	if ((vstat & vmask2) != 0x0 || vstat == 0x0) vstat = vstat | vmask2;
	if ((vstat & vmask3) != 0x0 || vstat == 0x0) vstat = vstat | vmask3;

	// all deltas go to outputs
	delta_ph[0] = dph12; delta_th[0] = bth12; a_sign_ph[0] = sph12; a_sign_th[0] = bsg12;
	delta_ph[1] = dph13; delta_th[1] = bth13; a_sign_ph[1] = sph13; a_sign_th[1] = bsg13;
	delta_ph[2] = dph14; delta_th[2] = bth14; a_sign_ph[2] = sph14; a_sign_th[2] = bsg14;
	delta_ph[3] = dph23; delta_th[3] = bth23; a_sign_ph[3] = sph23; a_sign_th[3] = bsg23;
	delta_ph[4] = dph24; delta_th[4] = bth24; a_sign_ph[4] = sph24; a_sign_th[4] = bsg24;
	delta_ph[5] = dph34; delta_th[5] = bth34; a_sign_ph[5] = sph34; a_sign_th[5] = bsg34;

	// segment ids
	for(int i=0;i<4;i++){
#pragma HLS UNROLL
		vir[i] = vi[i];
		hir[i] = hi[i];
		cir[i] = ci[i];
	}
	*sir = si;

	// remove some valid flags if th did not line up
	for (j = 0; j < 4; j = j+1){
#pragma HLS UNROLL
		if (vstat[j] == 0x0){ vir[j] = 0;}
	}

	// assign precise phi and theta
	a_phi = 0x0;
	a_theta = 0x0;
	if(vstat[1] == 0x1) // ME2 present
	{
		// phi is simple, we have it
		a_phi = ph_match[1];

		// for theta, select delta to best station, use winner number as index
		if      (bvl12) a_theta = th_match[1][bnm12[0]];
		else if (bvl23) a_theta = th_match[1][bnm23[1]];
		else if (bvl24) a_theta = th_match[1][bnm24[1]];
	}
	else if (vstat[2] == 0x1) // ME3 present
	{
		a_phi = ph_match[2];
		if      (bvl13) a_theta = th_match[2][bnm13[0]];
		else if (bvl34) a_theta = th_match[2][bnm34[1]];
	}
	else if (vstat[3] == 0x1) // ME4 present
	{
		a_phi = ph_match[3];
		if      (bvl14) a_theta = th_match[3][bnm14[0]];
	}


	if(this->pr){
		cout<<"vstat= "<<vstat<<endl;
	}

	// if less than 2 segments, kill rank
	if (vstat == 0x1 || vstat == 0x2 || vstat == 0x4 || vstat == 0x8 || vstat == 0x0){
		a_rank = 0;
	}
	else
	{
		// update rank taking into account available stations after th deltas
		// keep straightness as it was
		a_rank = (ph_q, ap_uint<1>(0)); // output rank is one bit longer than input, to accommodate ME4 separately
		a_rank[0] = vstat[3]; // ME4
		a_rank[1] = vstat[2]; // ME3
		a_rank[3] = vstat[1]; // ME2
		a_rank[5] = vstat[0]; // ME1
	}
	// if less than 2 segments, kill rank
	if (vstat == 0x1 || vstat == 0x2 || vstat == 0x4 || vstat == 0x8 || vstat == 0x0)
		a_rank = 0;

	for(int i=0;i<4;i++){
#pragma HLS UNROLL
		cpattern[i] = cpat_match[i]; // take all CLCT patterns
	}



*rank=a_rank;
*sign_ph=a_sign_ph;
*sign_th=a_sign_th;
*phi=a_phi;
*theta=a_theta;

if(this->pr){
	cout<<"rank= "<<a_rank<<endl;
	cout<<"sign _ph= "<<a_sign_ph<<endl;
	cout<<"sign_th= "<<a_sign_th<<endl;
	cout<<"phi= "<<a_phi<<endl;
	cout<<"theta= "<<a_theta<<endl;
}


}
