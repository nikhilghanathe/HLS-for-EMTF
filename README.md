# HLS-for-EMTF
High-level synthesis source code of EMTF module of CMS particle detector 

1. sources folder contains HLS C++ source files for synthesis
2. test_bench folder contains test bench for C Sim
3. interface folder contains HLS header files
4. doc folder contains HLS guidelines and CMSSW integration guidelines
5. CMSSW_Wrapper folder contains;
  a. HLS libraries in "include" folder
  b. src and interface folders which also contains the wrapper (SectorProcessorHLS.h and SectorProcessorHLS.cpp)
  c. BuildFile.xml which needs to be copied in config/ directory
  d. compile script named compile.sh

