// Function: FUN_00654030
// Address:  0x00654030
// Source:   batch_decompile (mass dump)
// Hash:     100e01e4c526155b


void FUN_00654030(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  void *pvStack_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ed21;
  pvStack_10 = ExceptionList;
  ExceptionList = &pvStack_10;
  uVar1 = FUN_00667580(1);
  local_8 = 0;
  iVar2 = FUN_00410cf0(0xc,uVar1);
  local_8._0_1_ = 1;
  if (iVar2 != 0) {
    FUN_00654220(param_1,param_2,param_3);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006540cd();
  return;
}

