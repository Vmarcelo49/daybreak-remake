// Function: FUN_00697050
// Address:  0x00697050
// Source:   batch_decompile (mass dump)
// Hash:     88a26c4e0c2ff6e3


int __fastcall FUN_00697050(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fda0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068db90();
  local_8 = 0;
  FUN_0068dd80(0);
  local_8._0_1_ = 1;
  FUN_0068dd80(0);
  local_8._0_1_ = 2;
  FUN_00691d40(1);
  local_8 = CONCAT31(local_8._1_3_,3);
  *(undefined4 *)(param_1 + 0x54) = 0;
  FUN_0068d890();
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  FUN_0068d890();
  ExceptionList = local_10;
  return param_1;
}

