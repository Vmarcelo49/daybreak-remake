// Function: FUN_00419470
// Address:  0x00419470
// Source:   batch_decompile (mass dump)
// Hash:     1961f0f06292f7de


void __fastcall FUN_00419470(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069df71;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a1ff4;
  param_1[0x179] = &PTR_FUN_006a1fe0;
  local_8 = 1;
  FUN_0065fee0(0);
  local_8 = local_8 & 0xffffff00;
  if (param_1 == (undefined4 *)0x0) {
    param_1 = (undefined4 *)0x0;
  }
  else {
    param_1 = param_1 + 0x179;
  }
  FUN_00415e30(param_1);
  local_8 = 0xffffffff;
  FUN_004119f0();
  ExceptionList = local_10;
  return;
}

