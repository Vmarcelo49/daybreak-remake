// Function: FUN_00691e30
// Address:  0x00691e30
// Source:   batch_decompile (mass dump)
// Hash:     16f83c3aa882db68


int __fastcall FUN_00691e30(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fae1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00691d40(1);
  local_8 = 0;
  FUN_00691d40(0);
  local_8._0_1_ = 1;
  FUN_0068db90();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0068db90();
  *(undefined4 *)(param_1 + 0x14) = 0;
  ExceptionList = local_10;
  return param_1;
}

