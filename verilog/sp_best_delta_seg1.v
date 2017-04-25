// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.2
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module sp_best_delta_seg1 (
        dth_0_V_read,
        dth_1_V_read,
        dth_2_V_read,
        dth_3_V_read,
        dth_4_V_read,
        dth_5_V_read,
        dth_6_V_read,
        dth_7_V_read,
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
parameter    ap_const_lv32_4 = 32'b100;
parameter    ap_const_lv32_5 = 32'b101;
parameter    ap_const_lv3_4 = 3'b100;
parameter    ap_const_lv3_5 = 3'b101;
parameter    ap_const_lv32_6 = 32'b110;
parameter    ap_const_lv32_7 = 32'b111;
parameter    ap_const_lv3_6 = 3'b110;
parameter    ap_const_lv3_7 = 3'b111;
parameter    ap_const_lv32_1 = 32'b1;
parameter    ap_const_lv8_0 = 8'b00000000;

input  [6:0] dth_0_V_read;
input  [6:0] dth_1_V_read;
input  [6:0] dth_2_V_read;
input  [6:0] dth_3_V_read;
input  [6:0] dth_4_V_read;
input  [6:0] dth_5_V_read;
input  [6:0] dth_6_V_read;
input  [6:0] dth_7_V_read;
input  [7:0] sth_V;
input  [7:0] dvl_V;
output  [6:0] ap_return_0;
output  [0:0] ap_return_1;
output  [0:0] ap_return_2;
output  [2:0] ap_return_3;

wire   [1:0] tmp_2762_fu_142_p1;
wire   [0:0] tmp_404_fu_136_p2;
wire   [0:0] tmp_fu_146_p2;
wire   [0:0] sel_tmp_fu_158_p2;
wire   [0:0] tmp_405_fu_152_p2;
wire   [0:0] sel_tmp1_fu_164_p2;
wire   [0:0] not_sel_tmp1_fu_170_p2;
wire   [0:0] tmp_406_fu_188_p2;
wire   [6:0] cmp1_V_load_s_fu_180_p3;
wire   [1:0] p_Result_1231_1_fu_208_p4;
wire   [0:0] tmp_1156_1_fu_202_p2;
wire   [0:0] tmp_1_fu_218_p2;
wire   [0:0] sel_tmp9_fu_230_p2;
wire   [0:0] tmp_1157_1_fu_224_p2;
wire   [0:0] sel_tmp10_fu_236_p2;
wire   [0:0] tmp_1175_1_fu_258_p2;
wire   [6:0] cmp1_V_load_13_s_fu_250_p3;
wire   [1:0] p_Result_1231_2_fu_278_p4;
wire   [0:0] tmp_1156_2_fu_272_p2;
wire   [0:0] tmp_2_fu_288_p2;
wire   [0:0] sel_tmp18_fu_300_p2;
wire   [0:0] tmp_1157_2_fu_294_p2;
wire   [0:0] sel_tmp19_fu_306_p2;
wire   [0:0] tmp_1175_2_fu_328_p2;
wire   [6:0] cmp1_V_load_2_fu_320_p3;
wire   [1:0] p_Result_1231_3_fu_348_p4;
wire   [0:0] tmp_1156_3_fu_342_p2;
wire   [0:0] tmp_3_fu_358_p2;
wire   [0:0] sel_tmp27_fu_386_p2;
wire   [0:0] tmp_1157_3_fu_364_p2;
wire   [0:0] sel_tmp28_fu_392_p2;
wire   [0:0] tmp_2763_fu_370_p3;
wire   [0:0] tmp_2764_fu_378_p3;
wire   [0:0] tmp_1175_3_fu_422_p2;
wire   [6:0] cmp1_V_load_13_2_fu_406_p3;
wire   [6:0] cmp1_V_load_fu_194_p3;
wire   [6:0] cmp1_V_load_3_fu_264_p3;
wire   [0:0] tmp_2765_fu_442_p1;
wire   [0:0] tmp_2766_fu_446_p3;
wire   [0:0] tmp_2767_fu_462_p3;
wire   [0:0] tmp_2768_fu_470_p3;
wire   [0:0] tmp_407_fu_436_p2;
wire   [1:0] num1_V_load_cast_fu_176_p1;
wire   [1:0] num1_V_load_2_fu_242_p3;
wire   [1:0] a_bnm_V_fu_486_p3;
wire   [6:0] cmp1_V_load_1_fu_334_p3;
wire   [6:0] cmp1_V_load_13_1_fu_428_p3;
wire   [0:0] tmp_2769_fu_512_p3;
wire   [0:0] tmp_2770_fu_520_p3;
wire   [0:0] tmp_1161_1_fu_506_p2;
wire   [2:0] num1_V_load_1_fu_312_p3;
wire   [2:0] num1_V_load_2_1_cast_cast_fu_398_p3;
wire   [0:0] tmp_226_fu_528_p3;
wire   [0:0] tmp_217_fu_414_p3;
wire   [6:0] a_bth_V_fu_498_p3;
wire   [6:0] a_bth_V_1_fu_544_p3;
wire   [0:0] tmp_220_fu_454_p3;
wire   [0:0] tmp_223_fu_478_p3;
wire   [0:0] tmp_s_fu_560_p2;
wire   [0:0] tmp_228_fu_566_p3;
wire   [0:0] tmp_227_fu_552_p3;
wire   [2:0] a_bnm_V_cast_fu_494_p1;
wire   [2:0] a_bnm_V_1_fu_536_p3;
wire   [6:0] a_bth_V_2_fu_574_p3;
wire   [0:0] a_bsg_V_fu_582_p3;
wire   [0:0] a_bvl_V_fu_598_p2;
wire   [2:0] a_bnm_V_2_fu_590_p3;

assign a_bnm_V_1_fu_536_p3 = ((tmp_1161_1_fu_506_p2[0:0] === 1'b1) ? num1_V_load_1_fu_312_p3 : num1_V_load_2_1_cast_cast_fu_398_p3);

assign a_bnm_V_2_fu_590_p3 = ((tmp_s_fu_560_p2[0:0] === 1'b1) ? a_bnm_V_cast_fu_494_p1 : a_bnm_V_1_fu_536_p3);

assign a_bnm_V_cast_fu_494_p1 = a_bnm_V_fu_486_p3;

assign a_bnm_V_fu_486_p3 = ((tmp_407_fu_436_p2[0:0] === 1'b1) ? num1_V_load_cast_fu_176_p1 : num1_V_load_2_fu_242_p3);

assign a_bsg_V_fu_582_p3 = ((tmp_s_fu_560_p2[0:0] === 1'b1) ? tmp_228_fu_566_p3 : tmp_227_fu_552_p3);

assign a_bth_V_1_fu_544_p3 = ((tmp_1161_1_fu_506_p2[0:0] === 1'b1) ? cmp1_V_load_1_fu_334_p3 : cmp1_V_load_13_1_fu_428_p3);

assign a_bth_V_2_fu_574_p3 = ((tmp_s_fu_560_p2[0:0] === 1'b1) ? a_bth_V_fu_498_p3 : a_bth_V_1_fu_544_p3);

assign a_bth_V_fu_498_p3 = ((tmp_407_fu_436_p2[0:0] === 1'b1) ? cmp1_V_load_fu_194_p3 : cmp1_V_load_3_fu_264_p3);

assign a_bvl_V_fu_598_p2 = ((dvl_V != ap_const_lv8_0) ? 1'b1 : 1'b0);

assign ap_return_0 = a_bth_V_2_fu_574_p3;

assign ap_return_1 = a_bsg_V_fu_582_p3;

assign ap_return_2 = a_bvl_V_fu_598_p2;

assign ap_return_3 = a_bnm_V_2_fu_590_p3;

assign cmp1_V_load_13_1_fu_428_p3 = ((tmp_1175_3_fu_422_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load_13_2_fu_406_p3);

assign cmp1_V_load_13_2_fu_406_p3 = ((sel_tmp28_fu_392_p2[0:0] === 1'b1) ? dth_6_V_read : dth_7_V_read);

assign cmp1_V_load_13_s_fu_250_p3 = ((sel_tmp10_fu_236_p2[0:0] === 1'b1) ? dth_2_V_read : dth_3_V_read);

assign cmp1_V_load_1_fu_334_p3 = ((tmp_1175_2_fu_328_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load_2_fu_320_p3);

assign cmp1_V_load_2_fu_320_p3 = ((sel_tmp19_fu_306_p2[0:0] === 1'b1) ? dth_4_V_read : dth_5_V_read);

assign cmp1_V_load_3_fu_264_p3 = ((tmp_1175_1_fu_258_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load_13_s_fu_250_p3);

assign cmp1_V_load_fu_194_p3 = ((tmp_406_fu_188_p2[0:0] === 1'b1) ? ap_const_lv7_7F : cmp1_V_load_s_fu_180_p3);

assign cmp1_V_load_s_fu_180_p3 = ((sel_tmp1_fu_164_p2[0:0] === 1'b1) ? dth_0_V_read : dth_1_V_read);

assign not_sel_tmp1_fu_170_p2 = (sel_tmp1_fu_164_p2 ^ 1'b1);

assign num1_V_load_1_fu_312_p3 = ((sel_tmp19_fu_306_p2[0:0] === 1'b1) ? ap_const_lv3_4 : ap_const_lv3_5);

assign num1_V_load_2_1_cast_cast_fu_398_p3 = ((sel_tmp28_fu_392_p2[0:0] === 1'b1) ? ap_const_lv3_6 : ap_const_lv3_7);

assign num1_V_load_2_fu_242_p3 = ((sel_tmp10_fu_236_p2[0:0] === 1'b1) ? ap_const_lv2_2 : ap_const_lv2_3);

assign num1_V_load_cast_fu_176_p1 = not_sel_tmp1_fu_170_p2;

assign p_Result_1231_1_fu_208_p4 = {{dvl_V[ap_const_lv32_3 : ap_const_lv32_2]}};

assign p_Result_1231_2_fu_278_p4 = {{dvl_V[ap_const_lv32_5 : ap_const_lv32_4]}};

assign p_Result_1231_3_fu_348_p4 = {{dvl_V[ap_const_lv32_7 : ap_const_lv32_6]}};

assign sel_tmp10_fu_236_p2 = (sel_tmp9_fu_230_p2 | tmp_1157_1_fu_224_p2);

assign sel_tmp18_fu_300_p2 = (tmp_1156_2_fu_272_p2 & tmp_2_fu_288_p2);

assign sel_tmp19_fu_306_p2 = (sel_tmp18_fu_300_p2 | tmp_1157_2_fu_294_p2);

assign sel_tmp1_fu_164_p2 = (sel_tmp_fu_158_p2 | tmp_405_fu_152_p2);

assign sel_tmp27_fu_386_p2 = (tmp_1156_3_fu_342_p2 & tmp_3_fu_358_p2);

assign sel_tmp28_fu_392_p2 = (sel_tmp27_fu_386_p2 | tmp_1157_3_fu_364_p2);

assign sel_tmp9_fu_230_p2 = (tmp_1156_1_fu_202_p2 & tmp_1_fu_218_p2);

assign sel_tmp_fu_158_p2 = (tmp_404_fu_136_p2 & tmp_fu_146_p2);

assign tmp_1156_1_fu_202_p2 = ((dth_2_V_read < dth_3_V_read) ? 1'b1 : 1'b0);

assign tmp_1156_2_fu_272_p2 = ((dth_4_V_read < dth_5_V_read) ? 1'b1 : 1'b0);

assign tmp_1156_3_fu_342_p2 = ((dth_6_V_read < dth_7_V_read) ? 1'b1 : 1'b0);

assign tmp_1157_1_fu_224_p2 = ((p_Result_1231_1_fu_208_p4 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_1157_2_fu_294_p2 = ((p_Result_1231_2_fu_278_p4 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_1157_3_fu_364_p2 = ((p_Result_1231_3_fu_348_p4 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_1161_1_fu_506_p2 = ((cmp1_V_load_1_fu_334_p3 < cmp1_V_load_13_1_fu_428_p3) ? 1'b1 : 1'b0);

assign tmp_1175_1_fu_258_p2 = ((p_Result_1231_1_fu_208_p4 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_1175_2_fu_328_p2 = ((p_Result_1231_2_fu_278_p4 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_1175_3_fu_422_p2 = ((p_Result_1231_3_fu_348_p4 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_1_fu_218_p2 = ((p_Result_1231_1_fu_208_p4 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_217_fu_414_p3 = ((sel_tmp28_fu_392_p2[0:0] === 1'b1) ? tmp_2763_fu_370_p3 : tmp_2764_fu_378_p3);

assign tmp_220_fu_454_p3 = ((sel_tmp1_fu_164_p2[0:0] === 1'b1) ? tmp_2765_fu_442_p1 : tmp_2766_fu_446_p3);

assign tmp_223_fu_478_p3 = ((sel_tmp10_fu_236_p2[0:0] === 1'b1) ? tmp_2767_fu_462_p3 : tmp_2768_fu_470_p3);

assign tmp_226_fu_528_p3 = ((sel_tmp19_fu_306_p2[0:0] === 1'b1) ? tmp_2769_fu_512_p3 : tmp_2770_fu_520_p3);

assign tmp_227_fu_552_p3 = ((tmp_1161_1_fu_506_p2[0:0] === 1'b1) ? tmp_226_fu_528_p3 : tmp_217_fu_414_p3);

assign tmp_228_fu_566_p3 = ((tmp_407_fu_436_p2[0:0] === 1'b1) ? tmp_220_fu_454_p3 : tmp_223_fu_478_p3);

assign tmp_2762_fu_142_p1 = dvl_V[1:0];

assign tmp_2763_fu_370_p3 = sth_V[ap_const_lv32_6];

assign tmp_2764_fu_378_p3 = sth_V[ap_const_lv32_7];

assign tmp_2765_fu_442_p1 = sth_V[0:0];

assign tmp_2766_fu_446_p3 = sth_V[ap_const_lv32_1];

assign tmp_2767_fu_462_p3 = sth_V[ap_const_lv32_2];

assign tmp_2768_fu_470_p3 = sth_V[ap_const_lv32_3];

assign tmp_2769_fu_512_p3 = sth_V[ap_const_lv32_4];

assign tmp_2770_fu_520_p3 = sth_V[ap_const_lv32_5];

assign tmp_2_fu_288_p2 = ((p_Result_1231_2_fu_278_p4 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_3_fu_358_p2 = ((p_Result_1231_3_fu_348_p4 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_404_fu_136_p2 = ((dth_0_V_read < dth_1_V_read) ? 1'b1 : 1'b0);

assign tmp_405_fu_152_p2 = ((tmp_2762_fu_142_p1 == ap_const_lv2_1) ? 1'b1 : 1'b0);

assign tmp_406_fu_188_p2 = ((tmp_2762_fu_142_p1 == ap_const_lv2_0) ? 1'b1 : 1'b0);

assign tmp_407_fu_436_p2 = ((cmp1_V_load_fu_194_p3 < cmp1_V_load_3_fu_264_p3) ? 1'b1 : 1'b0);

assign tmp_fu_146_p2 = ((tmp_2762_fu_142_p1 == ap_const_lv2_3) ? 1'b1 : 1'b0);

assign tmp_s_fu_560_p2 = ((a_bth_V_fu_498_p3 < a_bth_V_1_fu_544_p3) ? 1'b1 : 1'b0);

endmodule //sp_best_delta_seg1
