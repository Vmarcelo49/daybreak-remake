// Function: FUN_00699c00
// Address:  0x00699c00
// Source:   batch_decompile (mass dump)
// Hash:     b6008b917ba85b53


undefined4 __thiscall FUN_00699c00(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_006a00bd;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x1c);
  local_8 = 0;
  if (*(int *)(param_1 + 0x34) == 0) {
    iVar1 = FUN_00698250(param_2);
    if (iVar1 == 0) {
      local_18 = 0x8007000e;
    }
    else {
      FUN_006919a0();
      local_18 = FUN_006999e0();
    }
  }
  else {
    local_18 = 0x80040227;
  }
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return local_18;
}

