#include <ap_int.h>
#include "spbits.h"
#include "sp.h"
using namespace std;


class co_ord{
public:

	/*** FIRST BUNCH CROSSING *****/
	 ap_uint<bw_fph> t_phi_1[6/*Delay*/][6][9][seg_ch];

	 ap_uint<bw_th> t_th11i_1[6/*Delay*/][3][3][th_ch11];

	 ap_uint<bw_th> t_thi_1[6/*Delay*/][6][9][seg_ch];

	 ap_uint<seg_ch> t_vli_1[6/*Delay*/][6][9];

	 ap_uint<seg_ch> t_me11ai_1[6/*Delay*/][3][3];

	 ap_uint<4> t_cpati_1[6/*Delay*/][6][9][seg_ch];

	 ap_uint<4> t_dummy_1[6/*Delay*/][6][9][seg_ch];






	void co_ord_delay_actual(ap_uint<bw_fph> phi[6][9][seg_ch],
					ap_uint<bw_th> th11i[3][3][th_ch11],
					ap_uint<bw_th> thi[6][9][seg_ch],
					ap_uint<seg_ch> vli[6][9],
					ap_uint<seg_ch> me11ai[3][3],
					ap_uint<4> cpati[6][9][seg_ch],
				    // CPPF data          [subsect][frame][stub*4]
					ap_uint<64> cppf_rxd [7][3], // cppf rx data, 3 frames x 64 bit, for 7 links
					ap_uint<7> cppf_rx_valid, // cppf rx data valid flags

					/*outputs*/
					ap_uint<bw_fph> pho[max_drift][6][9][seg_ch],
					ap_uint<bw_th> th11o[max_drift][3][3][th_ch11],
					ap_uint<bw_th>	tho[max_drift][6][9][seg_ch],
					ap_uint<seg_ch>	vlo[max_drift][6][9],
					ap_uint<seg_ch>	me11ao[max_drift][3][3],
					ap_uint<4>	cpato[max_drift][6][9][seg_ch],
					ap_uint<4>	dummy[max_drift][6][9][seg_ch]);


};


void sp_c::co_ord_delay	(ap_uint<bw_fph> phi[6][9][seg_ch],
		ap_uint<bw_th> th11i[3][3][th_ch11],
		ap_uint<bw_th> thi[6][9][seg_ch],
		ap_uint<seg_ch> vli[6][9],
		ap_uint<seg_ch> me11ai[3][3],
		ap_uint<4> cpati[6][9][seg_ch],
		ap_uint<64> cppf_rxd [7][3], // cppf rx data, 3 frames x 64 bit, for 7 links
		ap_uint<7> cppf_rx_valid, // cppf rx data valid flags

		/*outputs*/
		ap_uint<bw_fph> pho[max_drift][6][9][seg_ch],
		ap_uint<bw_th> th11o[max_drift][3][3][th_ch11],
		ap_uint<bw_th>	tho[max_drift][6][9][seg_ch],
		ap_uint<seg_ch>	vlo[max_drift][6][9],
		ap_uint<seg_ch>	me11ao[max_drift][3][3],
		ap_uint<4>	cpato[max_drift][6][9][seg_ch],
		ap_uint<4>	dummy[max_drift][6][9][seg_ch])

{
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=dummy complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpato complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11ao complete dim=0
#pragma HLS ARRAY_PARTITION variable=vlo complete dim=0
#pragma HLS ARRAY_PARTITION variable=tho complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11o complete dim=0
#pragma HLS ARRAY_PARTITION variable=pho complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpati complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11ai complete dim=0
#pragma HLS ARRAY_PARTITION variable=vli complete dim=0
#pragma HLS ARRAY_PARTITION variable=thi complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11i complete dim=0
#pragma HLS ARRAY_PARTITION variable=phi complete dim=0
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return

static co_ord inst;

	inst.co_ord_delay_actual(phi,
		  th11i,
		  thi,
		  vli,
		  me11ai,
		  cpati,
		  cppf_rxd,
		  cppf_rx_valid,

		  pho,
		  th11o,
		  tho,
		  vlo,
		  me11ao,
		  cpato,
		  dummy);




}
void co_ord::co_ord_delay_actual(ap_uint<bw_fph> phi[6][9][seg_ch],
				ap_uint<bw_th> th11i[3][3][th_ch11],
				ap_uint<bw_th> thi[6][9][seg_ch],
				ap_uint<seg_ch> vli[6][9],
				ap_uint<seg_ch> me11ai[3][3],
				ap_uint<4> cpati[6][9][seg_ch],
				ap_uint<64> cppf_rxd [7][3], // cppf rx data, 3 frames x 64 bit, for 7 links
				ap_uint<7> cppf_rx_valid, // cppf rx data valid flags

				/*outputs*/
				ap_uint<bw_fph> pho[max_drift][6][9][seg_ch],
				ap_uint<bw_th> th11o[max_drift][3][3][th_ch11],
				ap_uint<bw_th>	tho[max_drift][6][9][seg_ch],
				ap_uint<seg_ch>	vlo[max_drift][6][9],
				ap_uint<seg_ch>	me11ao[max_drift][3][3],
				ap_uint<4>	cpato[max_drift][6][9][seg_ch],
				ap_uint<4>	dummy[max_drift][6][9][seg_ch])


{
#pragma HLS PROTOCOL floating
#pragma HLS DEPENDENCE false
#pragma HLS ARRAY_PARTITION variable=cpato complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11ao complete dim=0
#pragma HLS ARRAY_PARTITION variable=vlo complete dim=0
#pragma HLS ARRAY_PARTITION variable=tho complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11o complete dim=0
#pragma HLS ARRAY_PARTITION variable=pho complete dim=0
#pragma HLS ARRAY_PARTITION variable=cpati complete dim=0
#pragma HLS ARRAY_PARTITION variable=me11ai complete dim=0
#pragma HLS ARRAY_PARTITION variable=vli complete dim=0
#pragma HLS ARRAY_PARTITION variable=thi complete dim=0
#pragma HLS ARRAY_PARTITION variable=th11i complete dim=0
#pragma HLS ARRAY_PARTITION variable=phi complete dim=0
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
//#pragma HLS DEPENDENCE false
	/*** FIRST BUNCH CROSSING *****/
	volatile ap_uint<bw_fph> a_phi_1[6/*Delay*/][6][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_phi_1 complete dim=0
	volatile ap_uint<bw_th> a_th11i_1[6/*Delay*/][3][3][th_ch11];
#pragma HLS ARRAY_PARTITION variable=a_th11i_1 complete dim=0
	volatile ap_uint<bw_th> a_thi_1[6/*Delay*/][6][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_thi_1 complete dim=0
	volatile ap_uint<seg_ch> a_vli_1[6/*Delay*/][6][9];
#pragma HLS ARRAY_PARTITION variable=a_vli_1 complete dim=0
	volatile ap_uint<seg_ch> a_me11ai_1[6/*Delay*/][3][3];
#pragma HLS ARRAY_PARTITION variable=a_me11ai_1 complete dim=0
	volatile ap_uint<4> a_cpati_1[6/*Delay*/][6][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_cpati_1 complete dim=0
	volatile ap_uint<4> a_dummy[6/*Delay*/][6][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_dummy complete dim=0


#pragma HLS ARRAY_PARTITION variable=t_phi_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_th11i_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_thi_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_vli_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_me11ai_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_cpati_1 complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_dummy_1 complete dim=0

	 ap_uint<bw_fph> t_phi[6/*Delay*/][6][9][seg_ch];
	 ap_uint<bw_th> t_th11i[6/*Delay*/][3][3][th_ch11];
	 ap_uint<bw_th> t_thi[6/*Delay*/][6][9][seg_ch];
	 ap_uint<seg_ch> t_vli[6/*Delay*/][6][9];
	 ap_uint<seg_ch> t_me11ai[6/*Delay*/][3][3];
	 ap_uint<4> t_cpati[6/*Delay*/][6][9][seg_ch];
	 ap_uint<4> t_dummy[6/*Delay*/][6][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=t_phi complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_th11i complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_thi complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_vli complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_me11ai complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_cpati complete dim=0

#pragma HLS ARRAY_PARTITION variable=t_dummy complete dim=0


/*
	** SECOND BUNCH CROSSING ****
	ap_uint<bw_fph> a_phi_2[5][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_phi_2 complete dim=0
	ap_uint<bw_th> a_th11i_2[2][3][th_ch11];
	ap_uint<bw_th> a_thi_2[5][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_thi_2 complete dim=0
	ap_uint<seg_ch> a_vli_2[5][9];
#pragma HLS ARRAY_PARTITION variable=a_vli_2 complete dim=0
	ap_uint<seg_ch> a_me11ai_2[2][3];
#pragma HLS ARRAY_PARTITION variable=a_me11ai_2 complete dim=0
	ap_uint<4> a_cpati_2[5][9][seg_ch];
#pragma HLS ARRAY_PARTITION variable=a_cpati_2 complete dim=0

*/


//	 std::cout<<"cdl ph[2][4][0]= "<<phi[2][4][0]<<std::endl;
//	 std::cout<<"cdl ph[4][4][0]= "<<phi[4][4][0]<<std::endl;



co_ord_delay_label21://while(en==1)

#pragma HLS PIPELINE II=1

//1
/***********************pho=phi*****************************************/
	for(int p=0;p<5;p++){
			#pragma HLS unroll
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				t_phi[p][i][j][k]=t_phi_1[p][i][j][k];

					}
				}
			}
}

	//Input
		for(int i=0; i<6;i++){
	#pragma HLS UNROLL
			for(int j=0;j<9;j++){
				for(int k=0;k<seg_ch;k++){
					t_phi[5][i][j][k]=phi[i][j][k];
			//		cout<<"phi_c["<<dec<<i<<"]["<<j<<"]["<<k<<"]= "<<hex<<phi[i][j][k]<<endl;
						}
			}
		}

//Shift reg
	for(int p=0;p<5;p++){
		#pragma HLS unroll
		/*a_phi_1[p-1]=a_phi_1[p];*/
		for(int i=0; i<6;i++){
	#pragma HLS UNROLL
			for(int j=0;j<9;j++){
				for(int k=0;k<seg_ch;k++){
					a_phi_1[p][i][j][k]=t_phi[p][i][j][k];
					t_phi_1[p][i][j][k]=t_phi[p+1][i][j][k];
						}
					}
				}
		}
	for(int i=0;i<max_drift;i++){
		#pragma HLS UNROLL
				for(int j=0;j<6;j++){
		#pragma HLS UNROLL
					for(int k=0;k<9;k++){
		#pragma HLS UNROLL
						for(int l=0; l<seg_ch;l++){

						//	std::cout<<"t_phi["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]= "<<t_phi[i][j][k][l]<<std::endl;
						}
					}
				}
			}
/*
	for(int p=0;p<5;p++){
			#pragma HLS unroll
	for(int i=0; i<5;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				t_phi_1[p][i][j][k]=a_phi_1[p+1][i][j][k];

					}
				}
			}
}
*/



	/*****pho[2]=a_phi_1[0]*******/
	co_ord_delay_label10:for(int i=0; i<6;i++){
	#pragma HLS UNROLL
			for(int j=0;j<9;j++){
				for(int k=0;k<seg_ch;k++){
					pho[2][i][j][k]=t_phi[0][i][j][k];

						}
					}
				}
	/*****pho[1]=a_phi_1[1]*******/
	co_ord_delay_label11:for(int i=0; i<6;i++){
	#pragma HLS UNROLL
			for(int j=0;j<9;j++){
				for(int k=0;k<seg_ch;k++){
					pho[1][i][j][k]=t_phi[1][i][j][k];

						}
					}
				}
	/*****pho[0]=a_phi_1[2]*******/
	co_ord_delay_label12:for(int i=0; i<6;i++){
	#pragma HLS UNROLL
			for(int j=0;j<9;j++){
				for(int k=0;k<seg_ch;k++){
					pho[0][i][j][k]=t_phi[2][i][j][k];

						}
					}
				}
	/*****************************************************************/


//	 std::cout<<"cdl pho[2][2][4][0]= "<<pho[2][2][4][0]<<std::endl;
//	 std::cout<<"cdl pho[2][4][4][0]= "<<pho[2][4][4][0]<<std::endl;





//2
/*******************a_th11i_1[4]=th11i;*******************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<3;i++){
#pragma HLS UNROLL
	for(int j=0;j<3;j++){
		for(int k=0;k<th_ch11;k++){
			t_th11i[p][i][j][k]=t_th11i_1[p][i][j][k];

				}
			}
		}
}

//Input
/********************a_th11i_1[4]=th11i;********************/
	for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
			for(int k=0;k<th_ch11;k++){
				t_th11i[5][i][j][k]=th11i[i][j][k];
					}
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	/*a_phi_1[p-1]=a_phi_1[p];*/
	for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
			for(int k=0;k<th_ch11;k++){
				a_th11i_1[p][i][j][k]=t_th11i[p][i][j][k];
				t_th11i_1[p][i][j][k]=t_th11i[p+1][i][j][k];
					}
				}
			}
	}

/*for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<2;i++){
#pragma HLS UNROLL
	for(int j=0;j<3;j++){
		for(int k=0;k<th_ch11;k++){
			t_th11i_1[p][i][j][k]=a_th11i_1[p+1][i][j][k];

				}
			}
		}
}*/



/****th11o[2]=a_th11i_1[0]******/
co_ord_delay_label115:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
			for(int k=0;k<th_ch11;k++){
				th11o[2][i][j][k]=a_th11i_1[0][i][j][k];

					}
				}
			}
/****th11o[1]=a_th11i_1[1]******/
co_ord_delay_label16:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
			for(int k=0;k<th_ch11;k++){
				th11o[1][i][j][k]=a_th11i_1[1][i][j][k];

					}
				}
			}
/****pho[0]=a_phi_1[2]******/
co_ord_delay_label17:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
			for(int k=0;k<th_ch11;k++){
				th11o[0][i][j][k]=a_th11i_1[2][i][j][k];

					}
				}
			}
/***************************************************************/






//3
/*******************a_thi_1[4]=thi;*******************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<6;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_thi[p][i][j][k]=t_thi_1[p][i][j][k];

				}
			}
		}
}

//Input
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				t_thi[5][i][j][k]=thi[i][j][k];
					}
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				a_thi_1[p][i][j][k]=t_thi[p][i][j][k];
				t_thi_1[p][i][j][k]=t_thi[p+1][i][j][k];
					}
				}
			}
	}

/*
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<5;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_thi_1[p][i][j][k]=a_thi_1[p+1][i][j][k];

				}
			}
		}
}

*/

/****tho[2]=a_thi_1[0]******/
co_ord_delay_label20:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				tho[2][i][j][k]=a_thi_1[0][i][j][k];

					}
				}
			}
/****tho[1]=a_thi_1[1]******/
co_ord_delay_label110:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				tho[1][i][j][k]=a_thi_1[1][i][j][k];

					}
				}
			}
/****tho[0]=a_thi_1[2]******/
co_ord_delay_label120:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				tho[0][i][j][k]=a_thi_1[2][i][j][k];

					}
				}
			}
/***************************************************************/







/*******************a_vli_1[4]=vli;*******************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<6;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){

			t_vli[p][i][j]=t_vli_1[p][i][j];

			}
		}
}

//Input
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
				t_vli[5][i][j]=vli[i][j];
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	/*a_phi_1[p-1]=a_phi_1[p];*/
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
				a_vli_1[p][i][j]=t_vli[p][i][j];
				t_vli_1[p][i][j]=t_vli[p+1][i][j];
				}
			}
	}

/*
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<5;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
			t_vli_1[p][i][j]=a_vli_1[p+1][i][j];
			}
		}
}
*/



/****vlo[2]=a_vli_1[0]******/
co_ord_delay_label100:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){

			vlo[2][i][j]=a_vli_1[0][i][j];


				}
			}
/****vlo[1]=a_vli_1[1]******/
co_ord_delay_label1120:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){

			vlo[1][i][j]=a_vli_1[1][i][j];


				}
			}
/****vlo[0]=a_vli_1[2]******/
co_ord_delay_label1203:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){

			vlo[0][i][j]=a_vli_1[2][i][j];


				}
			}
/***************************************************************/







/*******************a_me11ai_1[5]=me11ai;****************************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<3;i++){
#pragma HLS UNROLL
	for(int j=0;j<3;j++){
			t_me11ai[p][i][j]=t_me11ai_1[p][i][j];
			}
		}
}

//Input
	for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
				t_me11ai[5][i][j]=me11ai[i][j];
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	/*a_phi_1[p-1]=a_phi_1[p];*/
	for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){
				a_me11ai_1[p][i][j]=t_me11ai[p][i][j];
				t_me11ai_1[p][i][j]=t_me11ai[p+1][i][j];
				}
			}
	}

/*
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<2;i++){
#pragma HLS UNROLL
	for(int j=0;j<3;j++){
			t_me11ai_1[p][i][j]=a_me11ai_1[p+1][i][j];
			}
		}
}
*/



/****me11ao[2]=a_me11ai_1[0]******/
co_ord_delay_label1011:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){

			me11ao[2][i][j]=a_me11ai_1[0][i][j];


				}
			}
/****me11ao[1]=a_me11ai_1[1]******/
co_ord_delay_label111:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){

			me11ao[1][i][j]=a_me11ai_1[1][i][j];


				}
			}
/****me11ao[0]=a_me11ai_1[2]******/
co_ord_delay_label121:for(int i=0; i<3;i++){
#pragma HLS UNROLL
		for(int j=0;j<3;j++){

			me11ao[0][i][j]=a_me11ai_1[2][i][j];


				}
			}
/***************************************************************/




/*******************a_cpati_1[5]=cpati;*******************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<6;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_cpati[p][i][j][k]=t_cpati_1[p][i][j][k];

				}
			}
		}
}

//Input
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				t_cpati[5][i][j][k]=cpati[i][j][k];
					}
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	/*a_phi_1[p-1]=a_phi_1[p];*/
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				a_cpati_1[p][i][j][k]=t_cpati[p][i][j][k];
				t_cpati_1[p][i][j][k]=t_cpati[p+1][i][j][k];
					}
				}
			}
	}

/*
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<5;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_cpati_1[p][i][j][k]=a_cpati_1[p+1][i][j][k];

				}
			}
		}
}
*/



/****cpato[2]=a_cpati_1[0]******/
co_ord_delay_label102:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				cpato[2][i][j][k]=a_cpati_1[0][i][j][k];

					}
				}
			}
/****cpato[1]=a_cpati_1[1]******/
co_ord_delay_label112:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				cpato[1][i][j][k]=a_cpati_1[1][i][j][k];

					}
				}
			}
/****cpato[0]=a_cpati_1[2]******/
co_ord_delay_label122:for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				cpato[0][i][j][k]=a_cpati_1[2][i][j][k];

					}
				}
			}






////Dummy line for shift reg
/******************DUMMY LINE******************/
for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<6;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_dummy[p][i][j][k]=t_dummy_1[p][i][j][k];

				}
			}
		}
}

//Input
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				a_dummy[5][i][j][k]=cpati[i][j][k];
					}
		}
	}

//Shift reg
for(int p=0;p<5;p++){
	#pragma HLS unroll
	//a_phi_1[p-1]=a_phi_1[p];
	for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				a_dummy[p][i][j][k]=t_dummy[p][i][j][k];

					}
				}
			}
	}

for(int p=0;p<5;p++){
		#pragma HLS unroll
for(int i=0; i<6;i++){
#pragma HLS UNROLL
	for(int j=0;j<9;j++){
		for(int k=0;k<seg_ch;k++){
			t_dummy_1[p][i][j][k]=a_dummy[p+1][i][j][k];

				}
			}
		}
}


/****cpato[2]=a_cpati_1[0]******/
for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				dummy[2][i][j][k]=a_dummy[0][i][j][k];

					}
				}
			}
/****cpato[1]=a_cpati_1[1]******/
for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				dummy[1][i][j][k]=a_dummy[1][i][j][k];

					}
				}
			}
/****cpato[0]=a_cpati_1[2]******/
for(int i=0; i<6;i++){
#pragma HLS UNROLL
		for(int j=0;j<9;j++){
			for(int k=0;k<seg_ch;k++){
				dummy[0][i][j][k]=a_dummy[2][i][j][k];

					}
				}
			}

/*****************************************************************/


}








