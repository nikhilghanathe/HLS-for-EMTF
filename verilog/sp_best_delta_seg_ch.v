// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.2
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module sp_best_delta_seg_ch (
        dth_0_V_read,
        dth_1_V_read,
        dth_2_V_read,
        dth_3_V_read,
        sth_V,
        dvl_V,
        ap_return_0,
        ap_return_1,
        ap_return_2,
        ap_return_3
);

parameter    ap_const_lv2_3 = 2'b11;
parameter    ap_const_lv2_1 = 2'b1;
parameter    ap_const_lv2_0 = 2'b00;
parameter    ap_const_lv7_7F = 7'b1111111;
parameter    ap_const_lv32_2 = 32'b10;
parameter    ap_const_lv32_3 = 32'b11;
parameter    ap_const_lv2_2 = 2'b10;
parameter    ap_const_lv32_1 = 32'b1;
parameter    ap_const_lv4_0 = 4'b0000;

input  [6:0] dth_0_V_read;
input  [6:0] dth_1_V_read;
input  [6:0] dth_2_V_read;
input  [6:0] dth_3_V_read;
input  [3:0] sth_V;
input  [3:0] dvl_V;
output  [6:0] ap_return_0;
output  [0:0] ap_return_1;
output  [0:0] ap_return_2;
output  [1:0] ap_return_3;

wire   [1:0] tmp_2757_fu_94_p1;
wire   [0:0] tmp_s_fu_88_p2;
wire   [0:0] tmp_401_fu_98_p2;
wire   [0:0] sel_tmp_fu_110_p2;
wire   [0:0] tmp_402_fu_104_p2;
wire   [0:0] sel_tmp1_fu_116_p2;
wire   [0:0] not_sel_tmp1_fu_122_p2;
wire   [0:0] tmp_403_fu_140_p2;
wire   [6:0] cmp1_V_load3_fu_132_p3;
wire   [1:0] p_Result_1213_1_fu_160_p4;
wire   [0:0] tmp_1139_1_fu_154_p2;
wire   [0:0] tmp_1142_1_fu_170_p2;
wire   [0:0] sel_tmp9_fu_198_p2;
wire   [0:0] tmp_1143_1_fu_176_p2;
wire   [0:0] sel_tmp10_fu_204_p2;
wire   [0:0] tmp_2758_fu_182_p3;
wire   [0:0] tmp_2759_fu_190_p3;
wire   [0:0] tmp_1153_1_fu_234_p2;
wire   [6:0] cmp1_V_load_s_fu_218_p3;
wire   [6:0] cmp1_V_load_fu_146_p3;
wire   [6:0] cmp1_V_load_1_fu_240_p3;
wire   [0:0] tmp_2760_fu_254_p1;
wire   [0:0] tmp_2761_fu_258_p3;
wire   [0:0] tmp_fu_248_p2;
wire   [1:0] num1_V_load_cast_fu_128_p1;
wire   [1:0] num1_V_load_1_fu_210_p3;
wire   [0:0] tmp_216_fu_266_p3;
wire   [0:0] tmp_213_fu_226_p3;
wire   [6:0] a_bth_V_fu_282_p3;
wire   [0:0] p_Result_s_fu_290_p3;
wire   [0:0] a_bvl_V_fu_298_p2;
wire   [1:0] a_bnm_V_fu_274_p3;

assign a_bnm_V_fu_274_p3 = ((tmp_fu_248_p2[0:0] === 1'b1) ? num1_V_load_cast_fu_128_p1 : num1_V_load_1_fu_210_p3);

assign a_bth_V_fu_282_p3 = ((tmp_fu_248_p2[0:0] === 1'b1) ? cmp1_V_load_fu_146_p3 : cmp1_V_load_1_fu_240_p3);

assign a_bvl_V_fu_298_p2 = ((dvl_V != ap_const_lv4_0) ? 1'b1 : 1'b0);

assign ap_return_0 = a_bth_V_fu_282_p3;

assign ap_return_1 = p_Result_s_fu_290_p3;

assign ap_return_2 = a_bvl_V_fu_298_p2;

assign ap_return_3 = a_bnm_V_fu_274_p3;

assign cmp1_V_load3_fu_132_p3 = ((sel_tmp1_fu_116_p2[0:0] === 1'b1) ? dth_0_V_read : dth_1_V_read);

assign cmp1_V_load_1_fu_240_p3 = ((tmp_1153_1_fu_234_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load_s_fu_218_p3);

assign cmp1_V_load_fu_146_p3 = ((tmp_403_fu_140_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load3_fu_132_p3);

assign cmp1_V_load_s_fu_218_p3 = ((sel_tmp10_fu_204_p2[0:0] === 1'b1) ? dth_2_V_read : dth_3_V_read);

assign not_sel_tmp1_fu_122_p2 = (sel_tmp1_fu_116_p2 ^ 1'b1);

assign num1_V_load_1_fu_210_p3 = ((sel_tmp10_fu_204_p2[0:0] === 1'b1) ? ap_const_lv2_2 : ap_const_lv2_3);

assign num1_V_load_cast_fu_128_p1 = not_sel_tmp1_fu_122_p2;

assign p_Result_1213_1_fu_160_p4 = {{dvl_V[ap_const_lv32_3 : ap_const_lv32_2]}};

assign p_Result_s_fu_290_p3 = ((tmp_fu_248_p2[0:0] === 1'b1) ? tmp_216_fu_266_p3 : tmp_213_fu_226_p3);

assign sel_tmp10_fu_204_p2 = (sel_tmp9_fu_198_p2 | tmp_1143_1_fu_176_p2);

assign sel_tmp1_fu_116_p2 = (sel_tmp_fu_110_p2 | tmp_402_fu_104_p2);

assign sel_tmp9_fu_198_p2 = (tmp_1139_1_fu_154_p2 & tmp_1142_1_fu_170_p2);

assign sel_tmp_fu_110_p2 = (tmp_s_fu_88_p2 & tmp_401_fu_98_p2);

assign tmp_1139_1_fu_154_p2 = ((dth_2_V_read < dth_3_V_read) ? 1'b1 : 1'b0);

assign tmp_1142_1_fu_170_p2 = ((p_Result_1213_1_fu_160_p4 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_1143_1_fu_176_p2 = ((p_Result_1213_1_fu_160_p4 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_1153_1_fu_234_p2 = ((p_Result_1213_1_fu_160_p4 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_213_fu_226_p3 = ((sel_tmp10_fu_204_p2[0:0] === 1'b1) ? tmp_2758_fu_182_p3 : tmp_2759_fu_190_p3);

assign tmp_216_fu_266_p3 = ((sel_tmp1_fu_116_p2[0:0] === 1'b1) ? tmp_2760_fu_254_p1 : tmp_2761_fu_258_p3);

assign tmp_2757_fu_94_p1 = dvl_V[1:0];

assign tmp_2758_fu_182_p3 = sth_V[ap_const_lv32_2];

assign tmp_2759_fu_190_p3 = sth_V[ap_const_lv32_3];

assign tmp_2760_fu_254_p1 = sth_V[0:0];

assign tmp_2761_fu_258_p3 = sth_V[ap_const_lv32_1];

assign tmp_401_fu_98_p2 = ((tmp_2757_fu_94_p1 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_402_fu_104_p2 = ((tmp_2757_fu_94_p1 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_403_fu_140_p2 = ((tmp_2757_fu_94_p1 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_fu_248_p2 = ((cmp1_V_load_fu_146_p3 < cmp1_V_load_1_fu_240_p3) ? 1'b1 : 1'b0);

assign tmp_s_fu_88_p2 = ((dth_0_V_read < dth_1_V_read) ? 1'b1 : 1'b0);

endmodule //sp_best_delta_seg_ch