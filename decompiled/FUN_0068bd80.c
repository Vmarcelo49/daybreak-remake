// Function: FUN_0068bd80
// Address:  0x0068bd80
// Source:   batch_decompile (mass dump)
// Hash:     a3100aed26d202ff


undefined4 __fastcall FUN_0068bd80(int param_1)

{
  undefined4 uVar1;
  HANDLE local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  DWORD local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f6a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0xa4);
  local_8 = 0;
  do {
    if (*(int *)(param_1 + 0xc4) != 2) {
      *(int *)(param_1 + 0xcc) = *(int *)(param_1 + 0xcc) + 1;
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      ExceptionList = local_10;
      return 0;
    }
    FUN_0068d9c0();
    local_18 = 0;
    local_20 = 1;
    local_2c = *(HANDLE *)(param_1 + 0xbc);
    local_28 = *(undefined4 *)(param_1 + 0xd0);
    local_24 = 2;
    local_1c = WaitForMultipleObjects(2,&local_2c,0,0xffffffff);
    FUN_0068d980();
  } while (local_1c == 0);
  if (local_1c == 1) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0x80040223;
  }
  else if (local_1c == 0xffffffff) {
    uVar1 = FUN_00693210();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar1 = 0x8000ffff;
  }
  ExceptionList = local_10;
  return uVar1;
}

