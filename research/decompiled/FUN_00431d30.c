// Function: FUN_00431d30
// Address:  0x00431d30
// Source:   batch_decompile (mass dump)
// Hash:     74c055c66f239486


undefined4 __fastcall FUN_00431d30(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e4a1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0065aed0();
  local_8 = 0;
  FUN_004248f0();
  local_8._0_1_ = 1;
  FUN_004248f0();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0065afb0();
  ExceptionList = local_10;
  return param_1;
}

