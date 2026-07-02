// Function: FUN_004041a0
// Address:  0x004041a0
// Source:   batch_decompile (mass dump)
// Hash:     2df89eb2328519a8


void __fastcall FUN_004041a0(undefined4 *param_1)

{
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069dacd;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a1494;
  local_8 = 0;
  for (local_14 = 0; local_14 < 5; local_14 = local_14 + 1) {
    FUN_00656200(param_1[local_14 + 0x169]);
  }
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

