// Function: FUN_00699290
// Address:  0x00699290
// Source:   batch_decompile (mass dump)
// Hash:     69a0ddf3898f76a5


int __thiscall FUN_00699290(int param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ffea;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068db90();
  local_8 = 0;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  FUN_0068db90();
  local_8._0_1_ = 1;
  *(undefined4 *)(param_1 + 0x34) = 0;
  FUN_0068dd80(0);
  local_8._0_1_ = 2;
  FUN_0068dd80(0);
  local_8._0_1_ = 3;
  FUN_00691d40(1);
  local_8._0_1_ = 4;
  FUN_00691d40(1);
  local_8._0_1_ = 5;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  FUN_00691d40(0);
  local_8 = CONCAT31(local_8._1_3_,6);
  FUN_00691d40(1);
  *(undefined4 *)(param_1 + 0x80) = 0;
  ExceptionList = local_10;
  return param_1;
}

