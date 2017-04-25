// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.2
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module sp_co_ord_delay_actual (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        phi_0_0_0_V_read,
        phi_0_0_1_V_read,
        phi_0_1_0_V_read,
        phi_0_1_1_V_read,
        phi_0_2_0_V_read,
        phi_0_2_1_V_read,
        phi_0_3_0_V_read,
        phi_0_3_1_V_read,
        phi_0_4_0_V_read,
        phi_0_4_1_V_read,
        phi_0_5_0_V_read,
        phi_0_5_1_V_read,
        phi_0_6_0_V_read,
        phi_0_6_1_V_read,
        phi_0_7_0_V_read,
        phi_0_7_1_V_read,
        phi_0_8_0_V_read,
        phi_0_8_1_V_read,
        phi_1_0_0_V_read,
        phi_1_0_1_V_read,
        phi_1_1_0_V_read,
        phi_1_1_1_V_read,
        phi_1_2_0_V_read,
        phi_1_2_1_V_read,
        phi_1_3_0_V_read,
        phi_1_3_1_V_read,
        phi_1_4_0_V_read,
        phi_1_4_1_V_read,
        phi_1_5_0_V_read,
        phi_1_5_1_V_read,
        phi_1_6_0_V_read,
        phi_1_6_1_V_read,
        phi_1_7_0_V_read,
        phi_1_7_1_V_read,
        phi_1_8_0_V_read,
        phi_1_8_1_V_read,
        phi_2_0_0_V_read,
        phi_2_0_1_V_read,
        phi_2_1_0_V_read,
        phi_2_1_1_V_read,
        phi_2_2_0_V_read,
        phi_2_2_1_V_read,
        phi_2_3_0_V_read,
        phi_2_3_1_V_read,
        phi_2_4_0_V_read,
        phi_2_4_1_V_read,
        phi_2_5_0_V_read,
        phi_2_5_1_V_read,
        phi_2_6_0_V_read,
        phi_2_6_1_V_read,
        phi_2_7_0_V_read,
        phi_2_7_1_V_read,
        phi_2_8_0_V_read,
        phi_2_8_1_V_read,
        phi_3_0_0_V_read,
        phi_3_0_1_V_read,
        phi_3_1_0_V_read,
        phi_3_1_1_V_read,
        phi_3_2_0_V_read,
        phi_3_2_1_V_read,
        phi_3_3_0_V_read,
        phi_3_3_1_V_read,
        phi_3_4_0_V_read,
        phi_3_4_1_V_read,
        phi_3_5_0_V_read,
        phi_3_5_1_V_read,
        phi_3_6_0_V_read,
        phi_3_6_1_V_read,
        phi_3_7_0_V_read,
        phi_3_7_1_V_read,
        phi_3_8_0_V_read,
        phi_3_8_1_V_read,
        phi_4_0_0_V_read,
        phi_4_0_1_V_read,
        phi_4_1_0_V_read,
        phi_4_1_1_V_read,
        phi_4_2_0_V_read,
        phi_4_2_1_V_read,
        phi_4_3_0_V_read,
        phi_4_3_1_V_read,
        phi_4_4_0_V_read,
        phi_4_4_1_V_read,
        phi_4_5_0_V_read,
        phi_4_5_1_V_read,
        phi_4_6_0_V_read,
        phi_4_6_1_V_read,
        phi_4_7_0_V_read,
        phi_4_7_1_V_read,
        phi_4_8_0_V_read,
        phi_4_8_1_V_read,
        cpati_0_0_0_V_read,
        cpati_0_0_1_V_read,
        cpati_0_1_0_V_read,
        cpati_0_1_1_V_read,
        cpati_0_2_0_V_read,
        cpati_0_2_1_V_read,
        cpati_0_3_0_V_read,
        cpati_0_3_1_V_read,
        cpati_0_4_0_V_read,
        cpati_0_4_1_V_read,
        cpati_0_5_0_V_read,
        cpati_0_5_1_V_read,
        cpati_0_6_0_V_read,
        cpati_0_6_1_V_read,
        cpati_0_7_0_V_read,
        cpati_0_7_1_V_read,
        cpati_0_8_0_V_read,
        cpati_0_8_1_V_read,
        cpati_1_0_0_V_read,
        cpati_1_0_1_V_read,
        cpati_1_1_0_V_read,
        cpati_1_1_1_V_read,
        cpati_1_2_0_V_read,
        cpati_1_2_1_V_read,
        cpati_1_3_0_V_read,
        cpati_1_3_1_V_read,
        cpati_1_4_0_V_read,
        cpati_1_4_1_V_read,
        cpati_1_5_0_V_read,
        cpati_1_5_1_V_read,
        cpati_1_6_0_V_read,
        cpati_1_6_1_V_read,
        cpati_1_7_0_V_read,
        cpati_1_7_1_V_read,
        cpati_1_8_0_V_read,
        cpati_1_8_1_V_read,
        cpati_2_0_0_V_read,
        cpati_2_0_1_V_read,
        cpati_2_1_0_V_read,
        cpati_2_1_1_V_read,
        cpati_2_2_0_V_read,
        cpati_2_2_1_V_read,
        cpati_2_3_0_V_read,
        cpati_2_3_1_V_read,
        cpati_2_4_0_V_read,
        cpati_2_4_1_V_read,
        cpati_2_5_0_V_read,
        cpati_2_5_1_V_read,
        cpati_2_6_0_V_read,
        cpati_2_6_1_V_read,
        cpati_2_7_0_V_read,
        cpati_2_7_1_V_read,
        cpati_2_8_0_V_read,
        cpati_2_8_1_V_read,
        cpati_3_0_0_V_read,
        cpati_3_0_1_V_read,
        cpati_3_1_0_V_read,
        cpati_3_1_1_V_read,
        cpati_3_2_0_V_read,
        cpati_3_2_1_V_read,
        cpati_3_3_0_V_read,
        cpati_3_3_1_V_read,
        cpati_3_4_0_V_read,
        cpati_3_4_1_V_read,
        cpati_3_5_0_V_read,
        cpati_3_5_1_V_read,
        cpati_3_6_0_V_read,
        cpati_3_6_1_V_read,
        cpati_3_7_0_V_read,
        cpati_3_7_1_V_read,
        cpati_3_8_0_V_read,
        cpati_3_8_1_V_read,
        cpati_4_0_0_V_read,
        cpati_4_0_1_V_read,
        cpati_4_1_0_V_read,
        cpati_4_1_1_V_read,
        cpati_4_2_0_V_read,
        cpati_4_2_1_V_read,
        cpati_4_3_0_V_read,
        cpati_4_3_1_V_read,
        cpati_4_4_0_V_read,
        cpati_4_4_1_V_read,
        cpati_4_5_0_V_read,
        cpati_4_5_1_V_read,
        cpati_4_6_0_V_read,
        cpati_4_6_1_V_read,
        cpati_4_7_0_V_read,
        cpati_4_7_1_V_read,
        cpati_4_8_0_V_read,
        cpati_4_8_1_V_read,
        ap_return_0,
        ap_return_1,
        ap_return_2,
        ap_return_3,
        ap_return_4,
        ap_return_5,
        ap_return_6,
        ap_return_7,
        ap_return_8,
        ap_return_9,
        ap_return_10,
        ap_return_11,
        ap_return_12,
        ap_return_13,
        ap_return_14,
        ap_return_15,
        ap_return_16,
        ap_return_17,
        ap_return_18,
        ap_return_19,
        ap_return_20,
        ap_return_21,
        ap_return_22,
        ap_return_23,
        ap_return_24,
        ap_return_25,
        ap_return_26,
        ap_return_27,
        ap_return_28,
        ap_return_29,
        ap_return_30,
        ap_return_31,
        ap_return_32,
        ap_return_33,
        ap_return_34,
        ap_return_35,
        ap_return_36,
        ap_return_37
);

parameter    ap_ST_pp0_stg0_fsm_0 = 1'b1;
parameter    ap_const_lv32_0 = 32'b00000000000000000000000000000000;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [11:0] phi_0_0_0_V_read;
input  [11:0] phi_0_0_1_V_read;
input  [11:0] phi_0_1_0_V_read;
input  [11:0] phi_0_1_1_V_read;
input  [11:0] phi_0_2_0_V_read;
input  [11:0] phi_0_2_1_V_read;
input  [11:0] phi_0_3_0_V_read;
input  [11:0] phi_0_3_1_V_read;
input  [11:0] phi_0_4_0_V_read;
input  [11:0] phi_0_4_1_V_read;
input  [11:0] phi_0_5_0_V_read;
input  [11:0] phi_0_5_1_V_read;
input  [11:0] phi_0_6_0_V_read;
input  [11:0] phi_0_6_1_V_read;
input  [11:0] phi_0_7_0_V_read;
input  [11:0] phi_0_7_1_V_read;
input  [11:0] phi_0_8_0_V_read;
input  [11:0] phi_0_8_1_V_read;
input  [11:0] phi_1_0_0_V_read;
input  [11:0] phi_1_0_1_V_read;
input  [11:0] phi_1_1_0_V_read;
input  [11:0] phi_1_1_1_V_read;
input  [11:0] phi_1_2_0_V_read;
input  [11:0] phi_1_2_1_V_read;
input  [11:0] phi_1_3_0_V_read;
input  [11:0] phi_1_3_1_V_read;
input  [11:0] phi_1_4_0_V_read;
input  [11:0] phi_1_4_1_V_read;
input  [11:0] phi_1_5_0_V_read;
input  [11:0] phi_1_5_1_V_read;
input  [11:0] phi_1_6_0_V_read;
input  [11:0] phi_1_6_1_V_read;
input  [11:0] phi_1_7_0_V_read;
input  [11:0] phi_1_7_1_V_read;
input  [11:0] phi_1_8_0_V_read;
input  [11:0] phi_1_8_1_V_read;
input  [11:0] phi_2_0_0_V_read;
input  [11:0] phi_2_0_1_V_read;
input  [11:0] phi_2_1_0_V_read;
input  [11:0] phi_2_1_1_V_read;
input  [11:0] phi_2_2_0_V_read;
input  [11:0] phi_2_2_1_V_read;
input  [11:0] phi_2_3_0_V_read;
input  [11:0] phi_2_3_1_V_read;
input  [11:0] phi_2_4_0_V_read;
input  [11:0] phi_2_4_1_V_read;
input  [11:0] phi_2_5_0_V_read;
input  [11:0] phi_2_5_1_V_read;
input  [11:0] phi_2_6_0_V_read;
input  [11:0] phi_2_6_1_V_read;
input  [11:0] phi_2_7_0_V_read;
input  [11:0] phi_2_7_1_V_read;
input  [11:0] phi_2_8_0_V_read;
input  [11:0] phi_2_8_1_V_read;
input  [11:0] phi_3_0_0_V_read;
input  [11:0] phi_3_0_1_V_read;
input  [11:0] phi_3_1_0_V_read;
input  [11:0] phi_3_1_1_V_read;
input  [11:0] phi_3_2_0_V_read;
input  [11:0] phi_3_2_1_V_read;
input  [11:0] phi_3_3_0_V_read;
input  [11:0] phi_3_3_1_V_read;
input  [11:0] phi_3_4_0_V_read;
input  [11:0] phi_3_4_1_V_read;
input  [11:0] phi_3_5_0_V_read;
input  [11:0] phi_3_5_1_V_read;
input  [11:0] phi_3_6_0_V_read;
input  [11:0] phi_3_6_1_V_read;
input  [11:0] phi_3_7_0_V_read;
input  [11:0] phi_3_7_1_V_read;
input  [11:0] phi_3_8_0_V_read;
input  [11:0] phi_3_8_1_V_read;
input  [11:0] phi_4_0_0_V_read;
input  [11:0] phi_4_0_1_V_read;
input  [11:0] phi_4_1_0_V_read;
input  [11:0] phi_4_1_1_V_read;
input  [11:0] phi_4_2_0_V_read;
input  [11:0] phi_4_2_1_V_read;
input  [11:0] phi_4_3_0_V_read;
input  [11:0] phi_4_3_1_V_read;
input  [11:0] phi_4_4_0_V_read;
input  [11:0] phi_4_4_1_V_read;
input  [11:0] phi_4_5_0_V_read;
input  [11:0] phi_4_5_1_V_read;
input  [11:0] phi_4_6_0_V_read;
input  [11:0] phi_4_6_1_V_read;
input  [11:0] phi_4_7_0_V_read;
input  [11:0] phi_4_7_1_V_read;
input  [11:0] phi_4_8_0_V_read;
input  [11:0] phi_4_8_1_V_read;
input  [3:0] cpati_0_0_0_V_read;
input  [3:0] cpati_0_0_1_V_read;
input  [3:0] cpati_0_1_0_V_read;
input  [3:0] cpati_0_1_1_V_read;
input  [3:0] cpati_0_2_0_V_read;
input  [3:0] cpati_0_2_1_V_read;
input  [3:0] cpati_0_3_0_V_read;
input  [3:0] cpati_0_3_1_V_read;
input  [3:0] cpati_0_4_0_V_read;
input  [3:0] cpati_0_4_1_V_read;
input  [3:0] cpati_0_5_0_V_read;
input  [3:0] cpati_0_5_1_V_read;
input  [3:0] cpati_0_6_0_V_read;
input  [3:0] cpati_0_6_1_V_read;
input  [3:0] cpati_0_7_0_V_read;
input  [3:0] cpati_0_7_1_V_read;
input  [3:0] cpati_0_8_0_V_read;
input  [3:0] cpati_0_8_1_V_read;
input  [3:0] cpati_1_0_0_V_read;
input  [3:0] cpati_1_0_1_V_read;
input  [3:0] cpati_1_1_0_V_read;
input  [3:0] cpati_1_1_1_V_read;
input  [3:0] cpati_1_2_0_V_read;
input  [3:0] cpati_1_2_1_V_read;
input  [3:0] cpati_1_3_0_V_read;
input  [3:0] cpati_1_3_1_V_read;
input  [3:0] cpati_1_4_0_V_read;
input  [3:0] cpati_1_4_1_V_read;
input  [3:0] cpati_1_5_0_V_read;
input  [3:0] cpati_1_5_1_V_read;
input  [3:0] cpati_1_6_0_V_read;
input  [3:0] cpati_1_6_1_V_read;
input  [3:0] cpati_1_7_0_V_read;
input  [3:0] cpati_1_7_1_V_read;
input  [3:0] cpati_1_8_0_V_read;
input  [3:0] cpati_1_8_1_V_read;
input  [3:0] cpati_2_0_0_V_read;
input  [3:0] cpati_2_0_1_V_read;
input  [3:0] cpati_2_1_0_V_read;
input  [3:0] cpati_2_1_1_V_read;
input  [3:0] cpati_2_2_0_V_read;
input  [3:0] cpati_2_2_1_V_read;
input  [3:0] cpati_2_3_0_V_read;
input  [3:0] cpati_2_3_1_V_read;
input  [3:0] cpati_2_4_0_V_read;
input  [3:0] cpati_2_4_1_V_read;
input  [3:0] cpati_2_5_0_V_read;
input  [3:0] cpati_2_5_1_V_read;
input  [3:0] cpati_2_6_0_V_read;
input  [3:0] cpati_2_6_1_V_read;
input  [3:0] cpati_2_7_0_V_read;
input  [3:0] cpati_2_7_1_V_read;
input  [3:0] cpati_2_8_0_V_read;
input  [3:0] cpati_2_8_1_V_read;
input  [3:0] cpati_3_0_0_V_read;
input  [3:0] cpati_3_0_1_V_read;
input  [3:0] cpati_3_1_0_V_read;
input  [3:0] cpati_3_1_1_V_read;
input  [3:0] cpati_3_2_0_V_read;
input  [3:0] cpati_3_2_1_V_read;
input  [3:0] cpati_3_3_0_V_read;
input  [3:0] cpati_3_3_1_V_read;
input  [3:0] cpati_3_4_0_V_read;
input  [3:0] cpati_3_4_1_V_read;
input  [3:0] cpati_3_5_0_V_read;
input  [3:0] cpati_3_5_1_V_read;
input  [3:0] cpati_3_6_0_V_read;
input  [3:0] cpati_3_6_1_V_read;
input  [3:0] cpati_3_7_0_V_read;
input  [3:0] cpati_3_7_1_V_read;
input  [3:0] cpati_3_8_0_V_read;
input  [3:0] cpati_3_8_1_V_read;
input  [3:0] cpati_4_0_0_V_read;
input  [3:0] cpati_4_0_1_V_read;
input  [3:0] cpati_4_1_0_V_read;
input  [3:0] cpati_4_1_1_V_read;
input  [3:0] cpati_4_2_0_V_read;
input  [3:0] cpati_4_2_1_V_read;
input  [3:0] cpati_4_3_0_V_read;
input  [3:0] cpati_4_3_1_V_read;
input  [3:0] cpati_4_4_0_V_read;
input  [3:0] cpati_4_4_1_V_read;
input  [3:0] cpati_4_5_0_V_read;
input  [3:0] cpati_4_5_1_V_read;
input  [3:0] cpati_4_6_0_V_read;
input  [3:0] cpati_4_6_1_V_read;
input  [3:0] cpati_4_7_0_V_read;
input  [3:0] cpati_4_7_1_V_read;
input  [3:0] cpati_4_8_0_V_read;
input  [3:0] cpati_4_8_1_V_read;
output  [11:0] ap_return_0;
output  [11:0] ap_return_1;
output  [11:0] ap_return_2;
output  [11:0] ap_return_3;
output  [11:0] ap_return_4;
output  [11:0] ap_return_5;
output  [11:0] ap_return_6;
output  [11:0] ap_return_7;
output  [11:0] ap_return_8;
output  [6:0] ap_return_9;
output  [6:0] ap_return_10;
output  [6:0] ap_return_11;
output  [6:0] ap_return_12;
output  [6:0] ap_return_13;
output  [6:0] ap_return_14;
output  [6:0] ap_return_15;
output  [6:0] ap_return_16;
output  [6:0] ap_return_17;
output  [6:0] ap_return_18;
output  [6:0] ap_return_19;
output  [6:0] ap_return_20;
output  [6:0] ap_return_21;
output  [6:0] ap_return_22;
output  [6:0] ap_return_23;
output  [6:0] ap_return_24;
output  [6:0] ap_return_25;
output  [6:0] ap_return_26;
output  [6:0] ap_return_27;
output  [6:0] ap_return_28;
output  [3:0] ap_return_29;
output  [3:0] ap_return_30;
output  [3:0] ap_return_31;
output  [3:0] ap_return_32;
output  [3:0] ap_return_33;
output  [3:0] ap_return_34;
output  [3:0] ap_return_35;
output  [3:0] ap_return_36;
output  [3:0] ap_return_37;

reg ap_done;
reg ap_idle;
reg ap_ready;

(* fsm_encoding = "none" *) reg   [0:0] ap_CS_fsm;
reg    ap_sig_cseq_ST_pp0_stg0_fsm_0;
reg    ap_sig_18;
wire    ap_reg_ppiten_pp0_it0;
reg    ap_reg_ppiten_pp0_it1;
reg    ap_reg_ppiten_pp0_it2;
reg    ap_reg_ppiten_pp0_it3;
reg   [11:0] inst_t_phi_1_V_0_0_1_1;
reg   [11:0] inst_t_phi_1_V_0_0_4_1;
reg   [11:0] inst_t_phi_1_V_0_0_7_1;
reg   [11:0] inst_t_phi_1_V_0_2_4_1;
reg   [11:0] inst_t_phi_1_V_0_3_4_1;
reg   [11:0] inst_t_phi_1_V_0_4_4_1;
reg   [11:0] inst_t_phi_1_V_1_0_1_1;
reg   [11:0] inst_t_phi_1_V_1_0_4_1;
reg   [11:0] inst_t_phi_1_V_1_0_7_1;
reg   [11:0] inst_t_phi_1_V_1_2_1_1;
reg   [11:0] inst_t_phi_1_V_1_2_4_1;
reg   [11:0] inst_t_phi_1_V_1_3_1_1;
reg   [11:0] inst_t_phi_1_V_1_3_4_1;
reg   [11:0] inst_t_phi_1_V_1_4_1_1;
reg   [11:0] inst_t_phi_1_V_1_4_4_1;
reg   [11:0] inst_t_phi_1_V_2_0_1_1;
reg   [11:0] inst_t_phi_1_V_2_0_4_1;
reg   [11:0] inst_t_phi_1_V_2_0_7_1;
reg   [11:0] inst_t_phi_1_V_2_2_1_1;
reg   [11:0] inst_t_phi_1_V_2_2_4_1;
reg   [11:0] inst_t_phi_1_V_2_3_1_1;
reg   [11:0] inst_t_phi_1_V_2_3_4_1;
reg   [11:0] inst_t_phi_1_V_2_4_1_1;
reg   [11:0] inst_t_phi_1_V_2_4_4_1;
reg   [11:0] a_phi_1_0_0_1_1_V_1_fu_1482;
reg   [11:0] a_phi_1_0_0_4_1_V_1_fu_1506;
reg   [11:0] a_phi_1_0_0_7_1_V_1_fu_1530;
reg   [11:0] a_phi_1_0_2_4_1_V_1_fu_1650;
reg   [11:0] a_phi_1_0_3_4_1_V_1_fu_1722;
reg   [11:0] a_phi_1_0_4_4_1_V_1_fu_1794;
reg   [11:0] a_phi_1_1_2_1_1_V_1_fu_1986;
reg   [11:0] a_phi_1_1_3_1_1_V_1_fu_2058;
reg   [11:0] a_phi_1_1_4_1_1_V_1_fu_2130;
wire   [0:0] a_th11i_1_0_0_1_0_V_fu_2566;
wire   [0:0] a_th11i_1_0_0_1_1_V_fu_2570;
wire   [0:0] a_th11i_1_0_0_1_2_V_fu_2574;
wire   [0:0] a_th11i_1_0_0_1_3_V_fu_2578;
wire   [0:0] a_thi_1_0_0_4_0_V_fu_2870;
wire   [0:0] a_thi_1_0_0_4_1_V_fu_2874;
wire   [0:0] a_thi_1_0_0_7_0_V_fu_2894;
wire   [0:0] a_thi_1_0_0_7_1_V_fu_2898;
wire   [0:0] a_thi_1_0_2_4_0_V_fu_3014;
wire   [0:0] a_thi_1_0_2_4_1_V_fu_3018;
wire   [0:0] a_thi_1_0_3_4_0_V_fu_3086;
wire   [0:0] a_thi_1_0_3_4_1_V_fu_3090;
wire   [0:0] a_thi_1_0_4_4_0_V_fu_3158;
wire   [0:0] a_thi_1_0_4_4_1_V_fu_3162;
wire   [0:0] a_thi_1_1_2_1_0_V_fu_3350;
wire   [0:0] a_thi_1_1_2_1_1_V_fu_3354;
wire   [0:0] a_thi_1_1_3_1_0_V_fu_3422;
wire   [0:0] a_thi_1_1_3_1_1_V_fu_3426;
wire   [0:0] a_thi_1_1_4_1_0_V_fu_3494;
wire   [0:0] a_thi_1_1_4_1_1_V_fu_3498;
wire   [0:0] a_cpati_1_0_0_1_1_V_fu_4542;
wire   [0:0] a_cpati_1_0_0_4_1_V_fu_4566;
wire   [0:0] a_cpati_1_0_0_7_1_V_fu_4590;
wire   [0:0] a_cpati_1_0_2_4_1_V_fu_4710;
wire   [0:0] a_cpati_1_0_3_4_1_V_fu_4782;
wire   [0:0] a_cpati_1_0_4_4_1_V_fu_4854;
wire   [0:0] a_cpati_1_1_2_1_1_V_fu_5046;
wire   [0:0] a_cpati_1_1_3_1_1_V_fu_5118;
wire   [0:0] a_cpati_1_1_4_1_1_V_fu_5190;
wire   [6:0] th11o_2_0_1_0_V_write_assi_fu_22500_p1;
wire   [6:0] th11o_2_0_1_1_V_write_assi_fu_22507_p1;
wire   [6:0] th11o_2_0_1_2_V_write_assi_fu_22514_p1;
wire   [6:0] th11o_2_0_1_3_V_write_assi_fu_22521_p1;
wire   [6:0] tho_1_2_1_0_V_write_assign_fu_23144_p1;
wire   [6:0] tho_1_2_1_1_V_write_assign_fu_23151_p1;
wire   [6:0] tho_1_3_1_0_V_write_assign_fu_23206_p1;
wire   [6:0] tho_1_3_1_1_V_write_assign_fu_23213_p1;
wire   [6:0] tho_1_4_1_0_V_write_assign_fu_23268_p1;
wire   [6:0] tho_1_4_1_1_V_write_assign_fu_23275_p1;
wire   [6:0] tho_2_0_4_0_V_write_assign_fu_22744_p1;
wire   [6:0] tho_2_0_4_1_V_write_assign_fu_22751_p1;
wire   [6:0] tho_2_0_7_0_V_write_assign_fu_22770_p1;
wire   [6:0] tho_2_0_7_1_V_write_assign_fu_22777_p1;
wire   [6:0] tho_2_2_4_0_V_write_assign_fu_22868_p1;
wire   [6:0] tho_2_2_4_1_V_write_assign_fu_22875_p1;
wire   [6:0] tho_2_3_4_0_V_write_assign_fu_22930_p1;
wire   [6:0] tho_2_3_4_1_V_write_assign_fu_22937_p1;
wire   [6:0] tho_2_4_4_0_V_write_assign_fu_22992_p1;
wire   [6:0] tho_2_4_4_1_V_write_assign_fu_22999_p1;
wire   [3:0] cpato_1_2_1_1_V_write_assi_fu_24464_p1;
wire   [3:0] cpato_1_3_1_1_V_write_assi_fu_24522_p1;
wire   [3:0] cpato_1_4_1_1_V_write_assi_fu_24580_p1;
wire   [3:0] cpato_2_0_1_1_V_write_assi_fu_24062_p1;
wire   [3:0] cpato_2_0_4_1_V_write_assi_fu_24084_p1;
wire   [3:0] cpato_2_0_7_1_V_write_assi_fu_24106_p1;
wire   [3:0] cpato_2_2_4_1_V_write_assi_fu_24200_p1;
wire   [3:0] cpato_2_3_4_1_V_write_assi_fu_24258_p1;
wire   [3:0] cpato_2_4_4_1_V_write_assi_fu_24316_p1;
reg   [0:0] ap_NS_fsm;
reg    ap_sig_pprstidle_pp0;

// power-on initialization
initial begin
#0 ap_CS_fsm = 1'b1;
#0 ap_reg_ppiten_pp0_it1 = 1'b0;
#0 ap_reg_ppiten_pp0_it2 = 1'b0;
#0 ap_reg_ppiten_pp0_it3 = 1'b0;
#0 inst_t_phi_1_V_0_0_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_0_0_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_0_0_7_1 = 12'b000000000000;
#0 inst_t_phi_1_V_0_2_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_0_3_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_0_4_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_0_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_0_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_0_7_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_2_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_2_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_3_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_3_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_4_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_1_4_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_0_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_0_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_0_7_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_2_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_2_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_3_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_3_4_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_4_1_1 = 12'b000000000000;
#0 inst_t_phi_1_V_2_4_4_1 = 12'b000000000000;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_pp0_stg0_fsm_0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_reg_ppiten_pp0_it1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & ~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0)))) begin
            ap_reg_ppiten_pp0_it1 <= ap_start;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_reg_ppiten_pp0_it2 <= 1'b0;
    end else begin
        if (~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0))) begin
            ap_reg_ppiten_pp0_it2 <= ap_reg_ppiten_pp0_it1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_reg_ppiten_pp0_it3 <= 1'b0;
    end else begin
        if (~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0))) begin
            ap_reg_ppiten_pp0_it3 <= ap_reg_ppiten_pp0_it2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it0) & ~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0)))) begin
        a_phi_1_0_0_1_1_V_1_fu_1482 <= inst_t_phi_1_V_0_0_1_1;
        a_phi_1_0_0_4_1_V_1_fu_1506 <= inst_t_phi_1_V_0_0_4_1;
        a_phi_1_0_0_7_1_V_1_fu_1530 <= inst_t_phi_1_V_0_0_7_1;
        a_phi_1_0_2_4_1_V_1_fu_1650 <= inst_t_phi_1_V_0_2_4_1;
        a_phi_1_0_3_4_1_V_1_fu_1722 <= inst_t_phi_1_V_0_3_4_1;
        a_phi_1_0_4_4_1_V_1_fu_1794 <= inst_t_phi_1_V_0_4_4_1;
        a_phi_1_1_2_1_1_V_1_fu_1986 <= inst_t_phi_1_V_1_2_1_1;
        a_phi_1_1_3_1_1_V_1_fu_2058 <= inst_t_phi_1_V_1_3_1_1;
        a_phi_1_1_4_1_1_V_1_fu_2130 <= inst_t_phi_1_V_1_4_1_1;
        inst_t_phi_1_V_0_0_1_1 <= inst_t_phi_1_V_1_0_1_1;
        inst_t_phi_1_V_0_0_4_1 <= inst_t_phi_1_V_1_0_4_1;
        inst_t_phi_1_V_0_0_7_1 <= inst_t_phi_1_V_1_0_7_1;
        inst_t_phi_1_V_0_2_4_1 <= inst_t_phi_1_V_1_2_4_1;
        inst_t_phi_1_V_0_3_4_1 <= inst_t_phi_1_V_1_3_4_1;
        inst_t_phi_1_V_0_4_4_1 <= inst_t_phi_1_V_1_4_4_1;
        inst_t_phi_1_V_1_0_1_1 <= inst_t_phi_1_V_2_0_1_1;
        inst_t_phi_1_V_1_0_4_1 <= inst_t_phi_1_V_2_0_4_1;
        inst_t_phi_1_V_1_0_7_1 <= inst_t_phi_1_V_2_0_7_1;
        inst_t_phi_1_V_1_2_1_1 <= inst_t_phi_1_V_2_2_1_1;
        inst_t_phi_1_V_1_2_4_1 <= inst_t_phi_1_V_2_2_4_1;
        inst_t_phi_1_V_1_3_1_1 <= inst_t_phi_1_V_2_3_1_1;
        inst_t_phi_1_V_1_3_4_1 <= inst_t_phi_1_V_2_3_4_1;
        inst_t_phi_1_V_1_4_1_1 <= inst_t_phi_1_V_2_4_1_1;
        inst_t_phi_1_V_1_4_4_1 <= inst_t_phi_1_V_2_4_4_1;
        inst_t_phi_1_V_2_0_1_1 <= phi_0_1_1_V_read;
        inst_t_phi_1_V_2_0_4_1 <= phi_0_4_1_V_read;
        inst_t_phi_1_V_2_0_7_1 <= phi_0_7_1_V_read;
        inst_t_phi_1_V_2_2_1_1 <= phi_2_1_1_V_read;
        inst_t_phi_1_V_2_2_4_1 <= phi_2_4_1_V_read;
        inst_t_phi_1_V_2_3_1_1 <= phi_3_1_1_V_read;
        inst_t_phi_1_V_2_3_4_1 <= phi_3_4_1_V_read;
        inst_t_phi_1_V_2_4_1_1 <= phi_4_1_1_V_read;
        inst_t_phi_1_V_2_4_4_1 <= phi_4_4_1_V_read;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_start) & (1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it0)) | ((1'b1 == ap_reg_ppiten_pp0_it3) & ~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0))))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_start) & (1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b0 == ap_reg_ppiten_pp0_it0) & (1'b0 == ap_reg_ppiten_pp0_it1) & (1'b0 == ap_reg_ppiten_pp0_it2) & (1'b0 == ap_reg_ppiten_pp0_it3))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it0) & ~((1'b1 == ap_reg_ppiten_pp0_it0) & (ap_start == 1'b0)))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (ap_sig_18) begin
        ap_sig_cseq_ST_pp0_stg0_fsm_0 = 1'b1;
    end else begin
        ap_sig_cseq_ST_pp0_stg0_fsm_0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_start) & (1'b0 == ap_reg_ppiten_pp0_it0) & (1'b0 == ap_reg_ppiten_pp0_it1) & (1'b0 == ap_reg_ppiten_pp0_it2))) begin
        ap_sig_pprstidle_pp0 = 1'b1;
    end else begin
        ap_sig_pprstidle_pp0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_pp0_stg0_fsm_0 : begin
            ap_NS_fsm = ap_ST_pp0_stg0_fsm_0;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign a_cpati_1_0_0_1_1_V_fu_4542 = 1'b0;

assign a_cpati_1_0_0_4_1_V_fu_4566 = 1'b0;

assign a_cpati_1_0_0_7_1_V_fu_4590 = 1'b0;

assign a_cpati_1_0_2_4_1_V_fu_4710 = 1'b0;

assign a_cpati_1_0_3_4_1_V_fu_4782 = 1'b0;

assign a_cpati_1_0_4_4_1_V_fu_4854 = 1'b0;

assign a_cpati_1_1_2_1_1_V_fu_5046 = 1'b0;

assign a_cpati_1_1_3_1_1_V_fu_5118 = 1'b0;

assign a_cpati_1_1_4_1_1_V_fu_5190 = 1'b0;

assign a_th11i_1_0_0_1_0_V_fu_2566 = 1'b0;

assign a_th11i_1_0_0_1_1_V_fu_2570 = 1'b0;

assign a_th11i_1_0_0_1_2_V_fu_2574 = 1'b0;

assign a_th11i_1_0_0_1_3_V_fu_2578 = 1'b0;

assign a_thi_1_0_0_4_0_V_fu_2870 = 1'b0;

assign a_thi_1_0_0_4_1_V_fu_2874 = 1'b0;

assign a_thi_1_0_0_7_0_V_fu_2894 = 1'b0;

assign a_thi_1_0_0_7_1_V_fu_2898 = 1'b0;

assign a_thi_1_0_2_4_0_V_fu_3014 = 1'b0;

assign a_thi_1_0_2_4_1_V_fu_3018 = 1'b0;

assign a_thi_1_0_3_4_0_V_fu_3086 = 1'b0;

assign a_thi_1_0_3_4_1_V_fu_3090 = 1'b0;

assign a_thi_1_0_4_4_0_V_fu_3158 = 1'b0;

assign a_thi_1_0_4_4_1_V_fu_3162 = 1'b0;

assign a_thi_1_1_2_1_0_V_fu_3350 = 1'b0;

assign a_thi_1_1_2_1_1_V_fu_3354 = 1'b0;

assign a_thi_1_1_3_1_0_V_fu_3422 = 1'b0;

assign a_thi_1_1_3_1_1_V_fu_3426 = 1'b0;

assign a_thi_1_1_4_1_0_V_fu_3494 = 1'b0;

assign a_thi_1_1_4_1_1_V_fu_3498 = 1'b0;

assign ap_reg_ppiten_pp0_it0 = ap_start;

assign ap_return_0 = a_phi_1_1_2_1_1_V_1_fu_1986;

assign ap_return_1 = a_phi_1_1_3_1_1_V_1_fu_2058;

assign ap_return_10 = th11o_2_0_1_1_V_write_assi_fu_22507_p1;

assign ap_return_11 = th11o_2_0_1_2_V_write_assi_fu_22514_p1;

assign ap_return_12 = th11o_2_0_1_3_V_write_assi_fu_22521_p1;

assign ap_return_13 = tho_1_2_1_0_V_write_assign_fu_23144_p1;

assign ap_return_14 = tho_1_2_1_1_V_write_assign_fu_23151_p1;

assign ap_return_15 = tho_1_3_1_0_V_write_assign_fu_23206_p1;

assign ap_return_16 = tho_1_3_1_1_V_write_assign_fu_23213_p1;

assign ap_return_17 = tho_1_4_1_0_V_write_assign_fu_23268_p1;

assign ap_return_18 = tho_1_4_1_1_V_write_assign_fu_23275_p1;

assign ap_return_19 = tho_2_0_4_0_V_write_assign_fu_22744_p1;

assign ap_return_2 = a_phi_1_1_4_1_1_V_1_fu_2130;

assign ap_return_20 = tho_2_0_4_1_V_write_assign_fu_22751_p1;

assign ap_return_21 = tho_2_0_7_0_V_write_assign_fu_22770_p1;

assign ap_return_22 = tho_2_0_7_1_V_write_assign_fu_22777_p1;

assign ap_return_23 = tho_2_2_4_0_V_write_assign_fu_22868_p1;

assign ap_return_24 = tho_2_2_4_1_V_write_assign_fu_22875_p1;

assign ap_return_25 = tho_2_3_4_0_V_write_assign_fu_22930_p1;

assign ap_return_26 = tho_2_3_4_1_V_write_assign_fu_22937_p1;

assign ap_return_27 = tho_2_4_4_0_V_write_assign_fu_22992_p1;

assign ap_return_28 = tho_2_4_4_1_V_write_assign_fu_22999_p1;

assign ap_return_29 = cpato_1_2_1_1_V_write_assi_fu_24464_p1;

assign ap_return_3 = a_phi_1_0_0_1_1_V_1_fu_1482;

assign ap_return_30 = cpato_1_3_1_1_V_write_assi_fu_24522_p1;

assign ap_return_31 = cpato_1_4_1_1_V_write_assi_fu_24580_p1;

assign ap_return_32 = cpato_2_0_1_1_V_write_assi_fu_24062_p1;

assign ap_return_33 = cpato_2_0_4_1_V_write_assi_fu_24084_p1;

assign ap_return_34 = cpato_2_0_7_1_V_write_assi_fu_24106_p1;

assign ap_return_35 = cpato_2_2_4_1_V_write_assi_fu_24200_p1;

assign ap_return_36 = cpato_2_3_4_1_V_write_assi_fu_24258_p1;

assign ap_return_37 = cpato_2_4_4_1_V_write_assi_fu_24316_p1;

assign ap_return_4 = a_phi_1_0_0_4_1_V_1_fu_1506;

assign ap_return_5 = a_phi_1_0_0_7_1_V_1_fu_1530;

assign ap_return_6 = a_phi_1_0_2_4_1_V_1_fu_1650;

assign ap_return_7 = a_phi_1_0_3_4_1_V_1_fu_1722;

assign ap_return_8 = a_phi_1_0_4_4_1_V_1_fu_1794;

assign ap_return_9 = th11o_2_0_1_0_V_write_assi_fu_22500_p1;

always @ (*) begin
    ap_sig_18 = (ap_CS_fsm[ap_const_lv32_0] == 1'b1);
end

assign cpato_1_2_1_1_V_write_assi_fu_24464_p1 = a_cpati_1_1_2_1_1_V_fu_5046;

assign cpato_1_3_1_1_V_write_assi_fu_24522_p1 = a_cpati_1_1_3_1_1_V_fu_5118;

assign cpato_1_4_1_1_V_write_assi_fu_24580_p1 = a_cpati_1_1_4_1_1_V_fu_5190;

assign cpato_2_0_1_1_V_write_assi_fu_24062_p1 = a_cpati_1_0_0_1_1_V_fu_4542;

assign cpato_2_0_4_1_V_write_assi_fu_24084_p1 = a_cpati_1_0_0_4_1_V_fu_4566;

assign cpato_2_0_7_1_V_write_assi_fu_24106_p1 = a_cpati_1_0_0_7_1_V_fu_4590;

assign cpato_2_2_4_1_V_write_assi_fu_24200_p1 = a_cpati_1_0_2_4_1_V_fu_4710;

assign cpato_2_3_4_1_V_write_assi_fu_24258_p1 = a_cpati_1_0_3_4_1_V_fu_4782;

assign cpato_2_4_4_1_V_write_assi_fu_24316_p1 = a_cpati_1_0_4_4_1_V_fu_4854;

assign th11o_2_0_1_0_V_write_assi_fu_22500_p1 = a_th11i_1_0_0_1_0_V_fu_2566;

assign th11o_2_0_1_1_V_write_assi_fu_22507_p1 = a_th11i_1_0_0_1_1_V_fu_2570;

assign th11o_2_0_1_2_V_write_assi_fu_22514_p1 = a_th11i_1_0_0_1_2_V_fu_2574;

assign th11o_2_0_1_3_V_write_assi_fu_22521_p1 = a_th11i_1_0_0_1_3_V_fu_2578;

assign tho_1_2_1_0_V_write_assign_fu_23144_p1 = a_thi_1_1_2_1_0_V_fu_3350;

assign tho_1_2_1_1_V_write_assign_fu_23151_p1 = a_thi_1_1_2_1_1_V_fu_3354;

assign tho_1_3_1_0_V_write_assign_fu_23206_p1 = a_thi_1_1_3_1_0_V_fu_3422;

assign tho_1_3_1_1_V_write_assign_fu_23213_p1 = a_thi_1_1_3_1_1_V_fu_3426;

assign tho_1_4_1_0_V_write_assign_fu_23268_p1 = a_thi_1_1_4_1_0_V_fu_3494;

assign tho_1_4_1_1_V_write_assign_fu_23275_p1 = a_thi_1_1_4_1_1_V_fu_3498;

assign tho_2_0_4_0_V_write_assign_fu_22744_p1 = a_thi_1_0_0_4_0_V_fu_2870;

assign tho_2_0_4_1_V_write_assign_fu_22751_p1 = a_thi_1_0_0_4_1_V_fu_2874;

assign tho_2_0_7_0_V_write_assign_fu_22770_p1 = a_thi_1_0_0_7_0_V_fu_2894;

assign tho_2_0_7_1_V_write_assign_fu_22777_p1 = a_thi_1_0_0_7_1_V_fu_2898;

assign tho_2_2_4_0_V_write_assign_fu_22868_p1 = a_thi_1_0_2_4_0_V_fu_3014;

assign tho_2_2_4_1_V_write_assign_fu_22875_p1 = a_thi_1_0_2_4_1_V_fu_3018;

assign tho_2_3_4_0_V_write_assign_fu_22930_p1 = a_thi_1_0_3_4_0_V_fu_3086;

assign tho_2_3_4_1_V_write_assign_fu_22937_p1 = a_thi_1_0_3_4_1_V_fu_3090;

assign tho_2_4_4_0_V_write_assign_fu_22992_p1 = a_thi_1_0_4_4_0_V_fu_3158;

assign tho_2_4_4_1_V_write_assign_fu_22999_p1 = a_thi_1_0_4_4_1_V_fu_3162;

endmodule //sp_co_ord_delay_actual
