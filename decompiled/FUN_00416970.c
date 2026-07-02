// Function: FUN_00416970
// Address:  0x00416970
// Source:   batch_decompile (mass dump)
// Hash:     8b99403e4aaac9fd


void __fastcall FUN_00416970(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069de9c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a1f08;
  param_1[1] = &PTR_FUN_006a1ef4;
  local_8 = 1;
  FUN_0065fee0(0);
  if (DAT_006cfdc8 != '\0') {
    FUN_00415d70(1,0);
  }
  FUN_00648cf0();
  local_8 = local_8 & 0xffffff00;
  if (param_1 == (undefined4 *)0x0) {
    param_1 = (undefined4 *)0x0;
  }
  else {
    param_1 = param_1 + 1;
  }
  FUN_00415e30(param_1);
  local_8 = 0xffffffff;
  FUN_00403b00();
  ExceptionList = local_10;
  return;
}

