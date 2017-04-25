// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.2
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module sp_ptlut_address (
        ap_clk,
        ap_rst,
        bt_phi_i_0_V_read,
        bt_phi_i_1_V_read,
        bt_phi_i_2_V_read,
        bt_theta_i_0_V_read,
        bt_theta_i_1_V_read,
        bt_theta_i_2_V_read,
        bt_cpattern_0_0_V_read,
        bt_cpattern_0_1_V_read,
        bt_cpattern_0_2_V_read,
        bt_cpattern_0_3_V_read,
        bt_cpattern_1_0_V_read,
        bt_cpattern_1_1_V_read,
        bt_cpattern_1_2_V_read,
        bt_cpattern_1_3_V_read,
        bt_cpattern_2_0_V_read,
        bt_cpattern_2_1_V_read,
        bt_cpattern_2_2_V_read,
        bt_cpattern_2_3_V_read,
        bt_delta_ph_0_0_V_read,
        bt_delta_ph_0_1_V_read,
        bt_delta_ph_0_2_V_read,
        bt_delta_ph_0_3_V_read,
        bt_delta_ph_0_4_V_read,
        bt_delta_ph_0_5_V_read,
        bt_delta_ph_1_0_V_read,
        bt_delta_ph_1_1_V_read,
        bt_delta_ph_1_2_V_read,
        bt_delta_ph_1_3_V_read,
        bt_delta_ph_1_4_V_read,
        bt_delta_ph_1_5_V_read,
        bt_delta_ph_2_0_V_read,
        bt_delta_ph_2_1_V_read,
        bt_delta_ph_2_2_V_read,
        bt_delta_ph_2_3_V_read,
        bt_delta_ph_2_4_V_read,
        bt_delta_ph_2_5_V_read,
        bt_delta_th_0_0_V_read,
        bt_delta_th_0_1_V_read,
        bt_delta_th_0_2_V_read,
        bt_delta_th_0_3_V_read,
        bt_delta_th_0_4_V_read,
        bt_delta_th_0_5_V_read,
        bt_delta_th_1_0_V_read,
        bt_delta_th_1_1_V_read,
        bt_delta_th_1_2_V_read,
        bt_delta_th_1_3_V_read,
        bt_delta_th_1_4_V_read,
        bt_delta_th_1_5_V_read,
        bt_delta_th_2_0_V_read,
        bt_delta_th_2_1_V_read,
        bt_delta_th_2_2_V_read,
        bt_delta_th_2_3_V_read,
        bt_delta_th_2_4_V_read,
        bt_delta_th_2_5_V_read,
        bt_sign_ph_0_V_read,
        bt_sign_ph_1_V_read,
        bt_sign_ph_2_V_read,
        bt_sign_th_0_V_read,
        bt_sign_th_1_V_read,
        bt_sign_th_2_V_read,
        bt_rank_i_0_V_read,
        bt_rank_i_1_V_read,
        bt_rank_i_2_V_read,
        bt_vi_0_0_V_read,
        bt_vi_1_0_V_read,
        bt_vi_2_0_V_read,
        bt_ci_0_0_V_read,
        bt_ci_0_1_V_read,
        bt_ci_0_2_V_read,
        bt_ci_0_3_V_read,
        bt_ci_0_4_V_read,
        bt_ci_1_0_V_read,
        bt_ci_1_1_V_read,
        bt_ci_1_2_V_read,
        bt_ci_1_3_V_read,
        bt_ci_1_4_V_read,
        bt_ci_2_0_V_read,
        bt_ci_2_1_V_read,
        bt_ci_2_2_V_read,
        bt_ci_2_3_V_read,
        bt_ci_2_4_V_read,
        sector_V,
        endcap_V,
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
        ap_return_16
);


input   ap_clk;
input   ap_rst;
input  [11:0] bt_phi_i_0_V_read;
input  [11:0] bt_phi_i_1_V_read;
input  [11:0] bt_phi_i_2_V_read;
input  [6:0] bt_theta_i_0_V_read;
input  [6:0] bt_theta_i_1_V_read;
input  [6:0] bt_theta_i_2_V_read;
input  [3:0] bt_cpattern_0_0_V_read;
input  [3:0] bt_cpattern_0_1_V_read;
input  [3:0] bt_cpattern_0_2_V_read;
input  [3:0] bt_cpattern_0_3_V_read;
input  [3:0] bt_cpattern_1_0_V_read;
input  [3:0] bt_cpattern_1_1_V_read;
input  [3:0] bt_cpattern_1_2_V_read;
input  [3:0] bt_cpattern_1_3_V_read;
input  [3:0] bt_cpattern_2_0_V_read;
input  [3:0] bt_cpattern_2_1_V_read;
input  [3:0] bt_cpattern_2_2_V_read;
input  [3:0] bt_cpattern_2_3_V_read;
input  [11:0] bt_delta_ph_0_0_V_read;
input  [11:0] bt_delta_ph_0_1_V_read;
input  [11:0] bt_delta_ph_0_2_V_read;
input  [11:0] bt_delta_ph_0_3_V_read;
input  [11:0] bt_delta_ph_0_4_V_read;
input  [11:0] bt_delta_ph_0_5_V_read;
input  [11:0] bt_delta_ph_1_0_V_read;
input  [11:0] bt_delta_ph_1_1_V_read;
input  [11:0] bt_delta_ph_1_2_V_read;
input  [11:0] bt_delta_ph_1_3_V_read;
input  [11:0] bt_delta_ph_1_4_V_read;
input  [11:0] bt_delta_ph_1_5_V_read;
input  [11:0] bt_delta_ph_2_0_V_read;
input  [11:0] bt_delta_ph_2_1_V_read;
input  [11:0] bt_delta_ph_2_2_V_read;
input  [11:0] bt_delta_ph_2_3_V_read;
input  [11:0] bt_delta_ph_2_4_V_read;
input  [11:0] bt_delta_ph_2_5_V_read;
input  [6:0] bt_delta_th_0_0_V_read;
input  [6:0] bt_delta_th_0_1_V_read;
input  [6:0] bt_delta_th_0_2_V_read;
input  [6:0] bt_delta_th_0_3_V_read;
input  [6:0] bt_delta_th_0_4_V_read;
input  [6:0] bt_delta_th_0_5_V_read;
input  [6:0] bt_delta_th_1_0_V_read;
input  [6:0] bt_delta_th_1_1_V_read;
input  [6:0] bt_delta_th_1_2_V_read;
input  [6:0] bt_delta_th_1_3_V_read;
input  [6:0] bt_delta_th_1_4_V_read;
input  [6:0] bt_delta_th_1_5_V_read;
input  [6:0] bt_delta_th_2_0_V_read;
input  [6:0] bt_delta_th_2_1_V_read;
input  [6:0] bt_delta_th_2_2_V_read;
input  [6:0] bt_delta_th_2_3_V_read;
input  [6:0] bt_delta_th_2_4_V_read;
input  [6:0] bt_delta_th_2_5_V_read;
input  [5:0] bt_sign_ph_0_V_read;
input  [5:0] bt_sign_ph_1_V_read;
input  [5:0] bt_sign_ph_2_V_read;
input  [5:0] bt_sign_th_0_V_read;
input  [5:0] bt_sign_th_1_V_read;
input  [5:0] bt_sign_th_2_V_read;
input  [6:0] bt_rank_i_0_V_read;
input  [6:0] bt_rank_i_1_V_read;
input  [6:0] bt_rank_i_2_V_read;
input  [1:0] bt_vi_0_0_V_read;
input  [1:0] bt_vi_1_0_V_read;
input  [1:0] bt_vi_2_0_V_read;
input  [3:0] bt_ci_0_0_V_read;
input  [3:0] bt_ci_0_1_V_read;
input  [3:0] bt_ci_0_2_V_read;
input  [3:0] bt_ci_0_3_V_read;
input  [3:0] bt_ci_0_4_V_read;
input  [3:0] bt_ci_1_0_V_read;
input  [3:0] bt_ci_1_1_V_read;
input  [3:0] bt_ci_1_2_V_read;
input  [3:0] bt_ci_1_3_V_read;
input  [3:0] bt_ci_1_4_V_read;
input  [3:0] bt_ci_2_0_V_read;
input  [3:0] bt_ci_2_1_V_read;
input  [3:0] bt_ci_2_2_V_read;
input  [3:0] bt_ci_2_3_V_read;
input  [3:0] bt_ci_2_4_V_read;
input  [2:0] sector_V;
input  [0:0] endcap_V;
output  [2:0] ap_return_0;
output  [2:0] ap_return_1;
output  [31:0] ap_return_2;
output  [31:0] ap_return_3;
output  [31:0] ap_return_4;
output  [7:0] ap_return_5;
output  [7:0] ap_return_6;
output  [7:0] ap_return_7;
output  [3:0] ap_return_8;
output  [3:0] ap_return_9;
output  [3:0] ap_return_10;
output  [29:0] ap_return_11;
output  [29:0] ap_return_12;
output  [29:0] ap_return_13;
output  [8:0] ap_return_14;
output  [8:0] ap_return_15;
output  [8:0] ap_return_16;

wire   [2:0] grp_sp_ptlut_address_actual_fu_694_ap_return_0;
wire   [2:0] grp_sp_ptlut_address_actual_fu_694_ap_return_1;
wire   [29:0] grp_sp_ptlut_address_actual_fu_694_ap_return_2;
wire   [29:0] grp_sp_ptlut_address_actual_fu_694_ap_return_3;
wire   [29:0] grp_sp_ptlut_address_actual_fu_694_ap_return_4;
wire   [31:0] grp_sp_ptlut_address_actual_fu_694_ap_return_5;
wire   [31:0] grp_sp_ptlut_address_actual_fu_694_ap_return_6;
wire   [31:0] grp_sp_ptlut_address_actual_fu_694_ap_return_7;
wire   [7:0] grp_sp_ptlut_address_actual_fu_694_ap_return_8;
wire   [7:0] grp_sp_ptlut_address_actual_fu_694_ap_return_9;
wire   [7:0] grp_sp_ptlut_address_actual_fu_694_ap_return_10;
wire   [8:0] grp_sp_ptlut_address_actual_fu_694_ap_return_11;
wire   [8:0] grp_sp_ptlut_address_actual_fu_694_ap_return_12;
wire   [8:0] grp_sp_ptlut_address_actual_fu_694_ap_return_13;
wire   [3:0] grp_sp_ptlut_address_actual_fu_694_ap_return_14;
wire   [3:0] grp_sp_ptlut_address_actual_fu_694_ap_return_15;
wire   [3:0] grp_sp_ptlut_address_actual_fu_694_ap_return_16;

sp_ptlut_address_actual grp_sp_ptlut_address_actual_fu_694(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .bt_phi_i_0_V_read(bt_phi_i_0_V_read),
    .bt_phi_i_1_V_read(bt_phi_i_1_V_read),
    .bt_phi_i_2_V_read(bt_phi_i_2_V_read),
    .bt_theta_i_0_V_read(bt_theta_i_0_V_read),
    .bt_theta_i_1_V_read(bt_theta_i_1_V_read),
    .bt_theta_i_2_V_read(bt_theta_i_2_V_read),
    .bt_cpattern_0_0_V_read(bt_cpattern_0_0_V_read),
    .bt_cpattern_0_1_V_read(bt_cpattern_0_1_V_read),
    .bt_cpattern_0_2_V_read(bt_cpattern_0_2_V_read),
    .bt_cpattern_0_3_V_read(bt_cpattern_0_3_V_read),
    .bt_cpattern_1_0_V_read(bt_cpattern_1_0_V_read),
    .bt_cpattern_1_1_V_read(bt_cpattern_1_1_V_read),
    .bt_cpattern_1_2_V_read(bt_cpattern_1_2_V_read),
    .bt_cpattern_1_3_V_read(bt_cpattern_1_3_V_read),
    .bt_cpattern_2_0_V_read(bt_cpattern_2_0_V_read),
    .bt_cpattern_2_1_V_read(bt_cpattern_2_1_V_read),
    .bt_cpattern_2_2_V_read(bt_cpattern_2_2_V_read),
    .bt_cpattern_2_3_V_read(bt_cpattern_2_3_V_read),
    .bt_delta_ph_0_0_V_read(bt_delta_ph_0_0_V_read),
    .bt_delta_ph_0_1_V_read(bt_delta_ph_0_1_V_read),
    .bt_delta_ph_0_2_V_read(bt_delta_ph_0_2_V_read),
    .bt_delta_ph_0_3_V_read(bt_delta_ph_0_3_V_read),
    .bt_delta_ph_0_4_V_read(bt_delta_ph_0_4_V_read),
    .bt_delta_ph_0_5_V_read(bt_delta_ph_0_5_V_read),
    .bt_delta_ph_1_0_V_read(bt_delta_ph_1_0_V_read),
    .bt_delta_ph_1_1_V_read(bt_delta_ph_1_1_V_read),
    .bt_delta_ph_1_2_V_read(bt_delta_ph_1_2_V_read),
    .bt_delta_ph_1_3_V_read(bt_delta_ph_1_3_V_read),
    .bt_delta_ph_1_4_V_read(bt_delta_ph_1_4_V_read),
    .bt_delta_ph_1_5_V_read(bt_delta_ph_1_5_V_read),
    .bt_delta_ph_2_0_V_read(bt_delta_ph_2_0_V_read),
    .bt_delta_ph_2_1_V_read(bt_delta_ph_2_1_V_read),
    .bt_delta_ph_2_2_V_read(bt_delta_ph_2_2_V_read),
    .bt_delta_ph_2_3_V_read(bt_delta_ph_2_3_V_read),
    .bt_delta_ph_2_4_V_read(bt_delta_ph_2_4_V_read),
    .bt_delta_ph_2_5_V_read(bt_delta_ph_2_5_V_read),
    .bt_delta_th_0_0_V_read(bt_delta_th_0_0_V_read),
    .bt_delta_th_0_1_V_read(bt_delta_th_0_1_V_read),
    .bt_delta_th_0_2_V_read(bt_delta_th_0_2_V_read),
    .bt_delta_th_0_3_V_read(bt_delta_th_0_3_V_read),
    .bt_delta_th_0_4_V_read(bt_delta_th_0_4_V_read),
    .bt_delta_th_0_5_V_read(bt_delta_th_0_5_V_read),
    .bt_delta_th_1_0_V_read(bt_delta_th_1_0_V_read),
    .bt_delta_th_1_1_V_read(bt_delta_th_1_1_V_read),
    .bt_delta_th_1_2_V_read(bt_delta_th_1_2_V_read),
    .bt_delta_th_1_3_V_read(bt_delta_th_1_3_V_read),
    .bt_delta_th_1_4_V_read(bt_delta_th_1_4_V_read),
    .bt_delta_th_1_5_V_read(bt_delta_th_1_5_V_read),
    .bt_delta_th_2_0_V_read(bt_delta_th_2_0_V_read),
    .bt_delta_th_2_1_V_read(bt_delta_th_2_1_V_read),
    .bt_delta_th_2_2_V_read(bt_delta_th_2_2_V_read),
    .bt_delta_th_2_3_V_read(bt_delta_th_2_3_V_read),
    .bt_delta_th_2_4_V_read(bt_delta_th_2_4_V_read),
    .bt_delta_th_2_5_V_read(bt_delta_th_2_5_V_read),
    .bt_sign_ph_0_V_read(bt_sign_ph_0_V_read),
    .bt_sign_ph_1_V_read(bt_sign_ph_1_V_read),
    .bt_sign_ph_2_V_read(bt_sign_ph_2_V_read),
    .bt_sign_th_0_V_read(bt_sign_th_0_V_read),
    .bt_sign_th_1_V_read(bt_sign_th_1_V_read),
    .bt_sign_th_2_V_read(bt_sign_th_2_V_read),
    .bt_rank_i_0_V_read(bt_rank_i_0_V_read),
    .bt_rank_i_1_V_read(bt_rank_i_1_V_read),
    .bt_rank_i_2_V_read(bt_rank_i_2_V_read),
    .bt_vi_0_0_V_read(bt_vi_0_0_V_read),
    .bt_vi_1_0_V_read(bt_vi_1_0_V_read),
    .bt_vi_2_0_V_read(bt_vi_2_0_V_read),
    .bt_ci_0_0_V_read(bt_ci_0_0_V_read),
    .bt_ci_0_1_V_read(bt_ci_0_1_V_read),
    .bt_ci_0_2_V_read(bt_ci_0_2_V_read),
    .bt_ci_0_3_V_read(bt_ci_0_3_V_read),
    .bt_ci_0_4_V_read(bt_ci_0_4_V_read),
    .bt_ci_1_0_V_read(bt_ci_1_0_V_read),
    .bt_ci_1_1_V_read(bt_ci_1_1_V_read),
    .bt_ci_1_2_V_read(bt_ci_1_2_V_read),
    .bt_ci_1_3_V_read(bt_ci_1_3_V_read),
    .bt_ci_1_4_V_read(bt_ci_1_4_V_read),
    .bt_ci_2_0_V_read(bt_ci_2_0_V_read),
    .bt_ci_2_1_V_read(bt_ci_2_1_V_read),
    .bt_ci_2_2_V_read(bt_ci_2_2_V_read),
    .bt_ci_2_3_V_read(bt_ci_2_3_V_read),
    .bt_ci_2_4_V_read(bt_ci_2_4_V_read),
    .sector_V(sector_V),
    .endcap_V(endcap_V),
    .ap_return_0(grp_sp_ptlut_address_actual_fu_694_ap_return_0),
    .ap_return_1(grp_sp_ptlut_address_actual_fu_694_ap_return_1),
    .ap_return_2(grp_sp_ptlut_address_actual_fu_694_ap_return_2),
    .ap_return_3(grp_sp_ptlut_address_actual_fu_694_ap_return_3),
    .ap_return_4(grp_sp_ptlut_address_actual_fu_694_ap_return_4),
    .ap_return_5(grp_sp_ptlut_address_actual_fu_694_ap_return_5),
    .ap_return_6(grp_sp_ptlut_address_actual_fu_694_ap_return_6),
    .ap_return_7(grp_sp_ptlut_address_actual_fu_694_ap_return_7),
    .ap_return_8(grp_sp_ptlut_address_actual_fu_694_ap_return_8),
    .ap_return_9(grp_sp_ptlut_address_actual_fu_694_ap_return_9),
    .ap_return_10(grp_sp_ptlut_address_actual_fu_694_ap_return_10),
    .ap_return_11(grp_sp_ptlut_address_actual_fu_694_ap_return_11),
    .ap_return_12(grp_sp_ptlut_address_actual_fu_694_ap_return_12),
    .ap_return_13(grp_sp_ptlut_address_actual_fu_694_ap_return_13),
    .ap_return_14(grp_sp_ptlut_address_actual_fu_694_ap_return_14),
    .ap_return_15(grp_sp_ptlut_address_actual_fu_694_ap_return_15),
    .ap_return_16(grp_sp_ptlut_address_actual_fu_694_ap_return_16)
);

assign ap_return_0 = grp_sp_ptlut_address_actual_fu_694_ap_return_0;

assign ap_return_1 = grp_sp_ptlut_address_actual_fu_694_ap_return_1;

assign ap_return_10 = grp_sp_ptlut_address_actual_fu_694_ap_return_16;

assign ap_return_11 = grp_sp_ptlut_address_actual_fu_694_ap_return_2;

assign ap_return_12 = grp_sp_ptlut_address_actual_fu_694_ap_return_3;

assign ap_return_13 = grp_sp_ptlut_address_actual_fu_694_ap_return_4;

assign ap_return_14 = grp_sp_ptlut_address_actual_fu_694_ap_return_11;

assign ap_return_15 = grp_sp_ptlut_address_actual_fu_694_ap_return_12;

assign ap_return_16 = grp_sp_ptlut_address_actual_fu_694_ap_return_13;

assign ap_return_2 = grp_sp_ptlut_address_actual_fu_694_ap_return_5;

assign ap_return_3 = grp_sp_ptlut_address_actual_fu_694_ap_return_6;

assign ap_return_4 = grp_sp_ptlut_address_actual_fu_694_ap_return_7;

assign ap_return_5 = grp_sp_ptlut_address_actual_fu_694_ap_return_8;

assign ap_return_6 = grp_sp_ptlut_address_actual_fu_694_ap_return_9;

assign ap_return_7 = grp_sp_ptlut_address_actual_fu_694_ap_return_10;

assign ap_return_8 = grp_sp_ptlut_address_actual_fu_694_ap_return_14;

assign ap_return_9 = grp_sp_ptlut_address_actual_fu_694_ap_return_15;

endmodule //sp_ptlut_address
