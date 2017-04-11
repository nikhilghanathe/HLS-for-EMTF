    #include <ap_int.h>
#include "spbits.h"
#include "best_track.h"
using namespace std;

void best_track::best_tracks_actual(ap_uint<bw_fph> phi[4][3],
		ap_uint<bw_th> theta[4][3],
		// [zone][pattern_num][station]
		ap_uint<4> cpattern[4][3][4],
		// ph and th deltas from best stations
		// [zone][pattern_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph> delta_ph[4][3][6], ap_uint<bw_th> delta_th[4][3][6],
		ap_uint<6> sign_ph[4][3], ap_uint<6> sign_th[4][3],
		// updated ranks [zone][pattern_num]
		ap_uint<bwr + 1> rank[4][3],
		//[zone][pattern_num][station 0-3]
		ap_uint<seg_ch> vi[4][3][4], // valid
		ap_uint<2> hi[4][3][4], // bx index
		ap_uint<3> ci[4][3][4], // chamber
		ap_uint<4> si[4][3], // segment

		// precise phi and theta of best tracks
		// [best_track_num]
		ap_uint<bw_fph> bt_phi[3], ap_uint<bw_th> bt_theta[3],
		// [best_track_num][station]
		ap_uint<4> bt_cpattern[3][4],
		// ph and th deltas from best stations
		// [best_track_num], last index: 0=12, 1=13, 2=14, 3=23, 4=24, 5=34
		ap_uint<bw_fph> bt_delta_ph[3][6], ap_uint<bw_th> bt_delta_th[3][6],
		ap_uint<6> bt_sign_ph[3], ap_uint<6> bt_sign_th[3],
		// ranks [best_track_num]
		ap_uint<bwr + 1> bt_rank[3],
		//[best_track_num][station 0-3]
		ap_uint<seg_ch> bt_vi[3][5], // valid
		ap_uint<2> bt_hi[3][5], // bx index
		ap_uint<4> bt_ci[3][5], // chamber
		ap_uint<5> bt_si[3] // segment

		) {
//#pragma HLS LOOP_MERGE force
//#pragma HLS EXPRESSION_BALANCE
//#pragma HLS LATENCY max=0
#pragma HLS INLINE off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=theta complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpattern complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=delta_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=sign_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=rank complete dim=0
#pragma HLS ARRAY_PARTITION variable=vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=si complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_theta complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_cpattern complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_delta_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_delta_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_sign_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_sign_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_rank complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=bt_si complete dim=0




	// segment ids reformatted to chamber ids in sector
	//[zone][pattern_num][station 0-4]
	ap_uint<seg_ch> cn_vi[4][3][5];

 // valid
	ap_uint<2> cn_hi[4][3][5]; // bx index
	ap_uint<4> cn_ci[4][3][5]; // chamber
	ap_uint<5> cn_si[4][3]; // segment

#pragma HLS ARRAY_PARTITION variable=cn_vi complete dim=0
#pragma HLS ARRAY_PARTITION variable=cn_hi complete dim=0
#pragma HLS ARRAY_PARTITION variable=cn_ci complete dim=0
#pragma HLS ARRAY_PARTITION variable=cn_si complete dim=0

	int z, n, s, bn, i, j;
	ap_uint<12> larger[12];
	ap_uint<7> ri, rj;
	ap_uint<12> exists, kill1;
	ap_uint<12> kill1_t[12][12];
	ap_uint<1> winner[12][3];

#pragma HLS ARRAY_RESHAPE variable=winner complete dim=0
	ap_uint<1> gt, eq;
	ap_uint<4> cham[4][3][5];
	ap_uint<6> sum[12];
	ap_uint<3> sh_segs[12][12];


	// [zone][pattern][station]		//	ap_uint<7> zm_addr [4][3][4];
			ap_uint<4> real_ch [4][3][4];
			ap_uint<3> real_st [4][3][4];
			//ap_uint<4> real_ch;
			//ap_uint<3> real_st;



	ap_uint<2> cand_bx[4][3];

	ap_uint<3> h1, h2;
	ap_uint<36> good_bx;


	for (i = 0; i < 12; i = i + 1) {
#pragma HLS UNROLL
		larger[i] = 0;
		winner[i][0] = 0;
		winner[i][1] = 0;
		winner[i][2] = 0;

}


		// zero outputs initially
		for (n = 0; n < 3; n = n+1){

			bt_rank [n] = 0;
			bt_phi[n] = 0;
			bt_theta[n] = 0;
			for (s = 0; s < 4; s = s+1){ // station loop
			    bt_cpattern[n][s] = 0;
			}

			for (s = 0; s < 6; s = s+1){ // delta loop
				bt_delta_ph [n][s] = 0;
				bt_sign_ph  [n][s] = 0;
				bt_delta_th [n][s] = 0;
				bt_sign_th  [n][s] = 0;
			}

			for (s = 0; s < 5; s = s+1){ // station loop
				bt_vi[n][s] = 0;
				bt_hi[n][s] = 0;
				bt_si[n][s] = 0;
				bt_ci[n][s] = 0;
			}
		}



	// zero segment numbers
	for (z = 0; z < 4; z = z + 1) {
//#pragma HLS LOOP_FLATTEN
 // zone loop
#pragma HLS UNROLL
		for (n = 0; n < 3; n = n + 1) { // pattern number
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
			for (s = 0; s < 5; s = s + 1) { // station
#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN
				cn_vi[z][n][s] = 0;
				cn_hi[z][n][s] = 0;
				cn_si[z][n][s] = 0;
				cn_ci[z][n][s] = 0;
			}
		}
	}




			// input segment numbers are in terms of chambers in zone
		// convert them back into chamber ids in sector
		for (z = 0; z < 4; z = z+1){ // zone loop
			for (n = 0; n < 3; n = n+1){ // pattern number
				for (s = 0; s < 4; s = s+1){// station
					// calculate real station and chamber numbers
					cham[z][n][s] = ci[z][n][s];
					if (s == 0){
						real_st[z][n][s] = (cham[z][n][s] < 3) ? 0 : 1;
						real_ch[z][n][s] = mod3(cham[z][n][s]); // will this synthesize OK?
						if (z == 2) real_ch[z][n][s] = real_ch[z][n][s] + 3;
						if (z == 3) real_ch[z][n][s] = real_ch[z][n][s] + 6;
					}
					else if (s == 1){
						real_st[z][n][s] = s + 1;
						real_ch[z][n][s] = cham[z][n][s];
						if (z > 1) real_ch[z][n][s] = real_ch[z][n][s] + 3;
					}
					else{
						real_st[z][n][s] = s + 1;
						real_ch[z][n][s] = cham[z][n][s];
						if (z > 0) real_ch[z][n][s] = real_ch[z][n][s] + 3;
					}

					cn_vi[z][n][real_st[z][n][s]] = vi[z][n][s];
					cn_hi[z][n][real_st[z][n][s]] = hi[z][n][s];
					cn_si[z][n][real_st[z][n][s]] = si[z][n][s];
					cn_ci[z][n][real_st[z][n][s]] = real_ch[z][n][s];
				}
			}
		}





		// simultaneously compare each rank with each
	for (i = 0; i < 12; i = i+1){
		larger[i] = 0;
		larger[i][i] = 1; // result of comparison with itself
		ri = rank[i%4][i/4]; // first index loops zone, second loops candidate. Zone loops faster, so we give equal priority to zones
		for (j = 0; j < 12; j = j+1){
			// ilgj bits show which rank is larger
			// the comparison scheme below avoids problems
			// when there are two or more tracks with the same rank
			rj = rank[j%4][j/4];

			gt = ri > rj;
			eq = ri == rj;
			if (((i < j) && (gt || eq)) || ((i > j) && gt)){
				larger[i][j] = 1;

			//cout<<"i= "<<i<<" j= "<<j<<" gt = "<<gt<<" eq= "<<eq<<" ((i < j) && (gt || eq))= "<<((i < j) && (gt || eq))<<" ((i > j) && gt)= "<<((i > j) && gt)<<endl;
		//	printf("i= %d j= %d   gt= %d, eq= %d  ((i < j) && (gt || eq))= %d  ((i > j) && gt)= %d ,   phi[0][0]=%d\n",i,j,gt,eq,((i < j) && (gt || eq)),((i > j) && gt), int(phi[0][0]));
			}
			if(i==0 ){
		//		cout<<"rank= "<<rank[j%4][j/4]<<endl;
		//		cout<<"ri= "<<ri<<" rj= "<<rj<<endl;
			}
		}
		// "larger" array shows the result of comparison for each rank

		// track exists if quality != 0
		exists[i] = (ri != 0);
	}



	good_bx = 0;


	kill1=0;
	ap_uint<7> index_i=0;
	ap_uint<6> index_j=0;
	for(int i=0;i<12;i++){
	#pragma HLS UNROLL
	   for(int j=0;j<12;j++){
		 kill1_t[i][j]=0;

		}
	}


	for(index_i=0,i=0;i<12;i++,index_i=index_i+1){
	#pragma HLS DEPENDENCE false


	#pragma HLS UNROLL
	index_j=0;



		for(int j=0;j<12;j++){

		if(j>i){
			sh_segs[i][j]=count_shsegs(cn_vi[index_i(1,0)][index_i(5,2)],
					cn_ci[index_i(1,0)][index_i(5,2)],
					cn_si[index_i(1,0)][index_i(5,2)],
					cn_hi[index_i(1,0)][index_i(5,2)],

					cn_vi[index_j(1,0)][index_j(5,2)],
					cn_ci[index_j(1,0)][index_j(5,2)],
					cn_si[index_j(1,0)][index_j(5,2)],
					cn_hi[index_j(1,0)][index_j(5,2)]);

			if(sh_segs[i][j]>0){
					if (larger[i][j]) kill1_t[i][j][j] = 1;
					else kill1_t[i][j][i] = 1;

			}
			}
					index_j++;

		}
		index_j=0;

	}
	for(int i=0;i<12;i++){
	#pragma HLS UNROLL
		for(int j=0;j<12;j++){
			kill1 =kill1 | kill1_t[i][j];
		}
	}
	//exists = (~kill1);


	// remove ghosts according to kill mask
	exists = exists & (~kill1);




	for (i = 0; i <12 ; i = i + 1) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
//#pragma HLS LOOP_MERGE force
#pragma HLS DEPENDENCE false
		if(exists[i]){
		larger[i] = larger[i] | (~exists); // if this track exists make it larger than all non-existing tracks
		}else{
			larger[i] = 0; // else make it smaller than anything

		}
		// count zeros in the comparison results. The best track will have none, the next will have one, the third will have two.
		sum[i]=zero_count(larger[i]);

		if (sum[i] < 3)//CULPRIT
			winner[i][sum[i]] =1;//(~sum[5] & ~sum[4] & ~sum[3] & ~sum[2] & (~sum[1] 	| (sum[1] & ~sum[0])));//1; // assign positional winner codes
	}


	// multiplex best tracks to outputs according to winner signals
	for (n = 0; n < 3; n = n + 1) { // output loop !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
		for (i = 0; i < 12; i = i + 1) { // winner bit loop//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
			if(winner[i][n]){
			//if (winner[n][i]) {

				bt_rank[n] = bt_rank[n] | rank[i % 4][i / 4];
				bt_phi[n] = bt_phi[n] | phi[i % 4][i / 4];
				bt_theta[n] = bt_theta[n] | theta[i % 4][i / 4];

				for (s = 0; s < 4; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					bt_cpattern[n][s] =bt_cpattern[n][s]
							| cpattern[i % 4][i / 4][s];
				}

				for (s = 0; s < 6; s = s + 1) { // delta loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					bt_delta_ph[n][s] = bt_delta_ph[n][s] | delta_ph[i % 4][i / 4][s];
					bt_sign_ph[n][s] = bt_sign_ph[n][s]   | sign_ph[i % 4][i / 4][s];
					bt_delta_th[n][s] = bt_delta_th[n][s] | delta_th[i % 4][i / 4][s];
					bt_sign_th[n][s] = bt_sign_th[n][s]   | sign_th[i % 4][i / 4][s];
				}

				for (s = 0; s < 5; s = s + 1) { // station loop
#pragma HLS UNROLL
#pragma HLS DEPENDENCE false
//#pragma HLS LOOP_FLATTEN
					bt_vi[n][s] = bt_vi[n][s] | cn_vi[i % 4][i / 4][s];
					bt_hi[n][s] = bt_hi[n][s] | cn_hi[i % 4][i / 4][s];
					bt_ci[n][s] = bt_ci[n][s] | cn_ci[i % 4][i / 4][s];
					bt_si[n][s] = bt_si[n][s] | cn_si[i % 4][i / 4][s];
				}
			}
		}


	}



}
