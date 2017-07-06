// segments per chamber
#define seg_ch 2

// bit widths of ph and th outputs, reduced precision
// have to be derived from pattern width on top level
#define bw_ph   8
#define bw_th   7

// bit widths of ph and th, full precision
#define bw_fph   13
#define bw_fth   8

// wiregroup input bit width (0..111)
#define bw_wg    7

// bit width of dblstrip input (max 80 for ME234/1 with double-width strips)
#define bw_ds    7
// width of halfstrip input
#define bw_hs    8

// pattern half-width for stations 3,4
#define pat_w_st3   3 //4
	// pattern half-width for station 1
	#define pat_w_st1   pat_w_st3 + 1
	// number of input bits for stations 3,4
	#define full_pat_w_st3 ((1 << (pat_w_st3+1)) - 1)
	// number of input bits for st 1
	#define full_pat_w_st1 ((1 << (pat_w_st1+1)) - 1)
	// width of zero padding for station copies
	#define padding_w_st1 (full_pat_w_st1/2)
	#define padding_w_st3 (full_pat_w_st3/2)
	// full pattern widths (aka reduced pattern)
	#define red_pat_w_st3   pat_w_st3 * 2 + 1
	#define red_pat_w_st1   pat_w_st1 * 2 + 1

	// number of folds for pattern detectors, do not set to 1
	#define fold   4
// number of th outputs for ME1/1
#define th_ch11   seg_ch*seg_ch
#define bw_q   4
#define bw_addr   7

// strips per section, calculated so ph pattern would cover +/- 8 deg in st 1
#define ph_raw_w   160  // this is determined by chamber coverage in zones.sv
// should also be divisible by 2

// max possible drifttime
#define max_drift   3

// bit widths of precise phi and eta outputs
#define bw_phi   12
#define bw_eta   7
// width of ph raw hits, max coverage +8 to cover possible chamber displacement
#define ph_hit_w   40+4 //80 + 8

	// for 20 deg chambers
	#define ph_hit_w20   ph_hit_w
	// for 10 deg chambers
#define ph_hit_w10   20+4 //40 + 8

// width of th raw hits, max coverage +8 to cover possible chamber displacement
#define th_hit_w   56 + 8
	#define n_strips   (station <  1 && (cscid <  2 || cscid    12)) ? 64 : \
						 (station <  1 && ((cscid >  6 && cscid <  8) || cscid    14) ) ? 64 :\
						 80  // all others

//	#define n_wg   (station <  1 && cscid <  3) ? 48  : // ME1/1
//					 (station <  1 && cscid >  6) ? 32  : // ME1/3
//					 (station    2 && cscid <  3) ? 112 : // ME2/1
//					 (station >  3 && cscid <  3) ? 96  : // ME34/1
//					 64  // all others

//	// theta range (take +1 because th_coverage contains max th value starting from 0)
//	#define th_coverage
//						 (station <  1 && cscid <  2) ? 45  : // ME1/1
//						 (station <  1 && cscid >  6) ? 27  : // ME1/3
//						 (station <  1 && cscid >  3) ? 39  : // ME2/3
//						 (station    2 && cscid <  2) ? 43  : // ME2/1
//						 (station    2 && cscid >  3) ? 56  : // ME2/2
//						 (station    3 && cscid <  2) ? 34  : // ME3/1
//						 (station    3 && cscid >  3) ? 52  : // ME3/2
//						 (station    4 && cscid <  2) ? 28  : // ME4/1
//						 (station    4 && cscid >  3) ? 50  : // ME4/2
//						 0

	// phi range
//	#define ph_coverage   (station <  1 && ((cscid >  6 && cscid <  8) || cscid    14)) ? 15 :\
//						   (station >  2 && (cscid <  2 || cscid    9)) ? 40 :\
//						   20  // all others

	// number of th outputs takes ME1/1 th duplication into account
	#define th_ch   (station <  1 && (cscid <  2 || cscid    12)) ? (seg_ch*seg_ch) : seg_ch  // all others

	// is this chamber mounted in reverse direction?
//	#define ph_reverse   (endcap    1 && station >  3) ? 1 :
//			   			   (endcap    2 && station <  3) ? 1 : 0

	#define th_mem_sz   (1 << bw_addr)
	#define th_corr_mem_sz   (1 << bw_addr)

	// multiplier bit width (phi + factor)
	#define mult_bw   bw_fph + 11

	// ph zone boundaries for chambers that cover more than one zone
	// hardcoded boundaries must match boundaries in ph_th_match module

//	#define ph_zone_bnd1	(station <  1 && (cscid <  2 || cscid    12)) ? 41 :\
//							(station    2 && (cscid <  2 || cscid    9)) ? 41 : \
//							(station    2 && ((cscid >  3 && cscid <  8) || cscid    10)) ? 87 : \
//							(station    3 && ((cscid >  3 && cscid <  8) || cscid    10)) ? 49 : \
//							(station    4 && ((cscid >  3 && cscid <  8) || cscid    10)) ? 49 : \
//							127


//	#define ph_zone_bnd2 (station    3 && ((cscid >  3 && cscid <  8) || cscid    10)) ? 87 : 127

	#define zone_overlap   2

// sorter parameters
	#define bwr   6  // rank width
	#define bpow   7  // (1 << bpow) is count of input ranks
	#define cnr   (1 << bpow)  // internal rank count
	#define cnrex   ph_raw_w  // actual input rank count, must be even

