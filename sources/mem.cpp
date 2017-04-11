#include <ap_int.h>
#include "spbits.h"
#include "primitive.h"


void primitive::mem(ap_uint<12> r_in,
		ap_uint<1> we,
		ap_uint<bw_addr> addr,
		ap_uint<2> sel,
		const int station,
		const int cscid

		)

{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=params complete dim=0
#pragma HLS ARRAY_PARTITION variable=th_mem complete dim=0




					if(sel==0 && we==1)
						params[addr]=r_in;

					// programmable parameters
					// [0] = ph_init_b
					// [1] = ph_displacement_b
					// [2] = ph_init_a
					// [3] = ph_displacement_a
					// [4] = th_init
					// [5] = th_displacement

					if(sel==1 && we==1)
						th_mem[addr]=r_in;




				/*	for(int i=0;i<th_mem_sz;i++)
						std::cout<<"th_mem["<<i<<"] = "<<th_mem[i]<<"   ";

					std::cout<<std::endl;
					std::cout<<"station  = "<<station<<" cscid = "<<cscid<<" we = "<<we<<std::endl;
					std::cout<<"r_in  = "<<r_in<<" sel = "<<sel<<" addr = "<<addr<<std::endl;
*/


}




