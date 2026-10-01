// Function: FUN_00699820
// Address:  0x00699820
// Source:   batch_decompile (mass dump)
// Hash:     d7a271215c0a700a


undefined4 __fastcall FUN_00699820(int param_1)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_006a0075;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x1c);
  local_8 = 0;
  *(undefined4 *)(param_1 + 0x34) = 1;
  while( true ) {
    iVar1 = FUN_00699ad0();
    if (iVar1 == 0) break;
    FUN_00691c30();
    FUN_00699ca0(iVar1);
  }
  if (*(int *)(param_1 + 0x70) < 1) {
    FUN_006919a0();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    *(undefined4 *)(param_1 + 0x74) = 1;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    while( true ) {
      FUN_00693320(0xffffffff);
      FUN_0068d950(param_1 + 0x1c);
      local_8 = 1;
      if (*(int *)(param_1 + 0x70) == 0) break;
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
    *(undefined4 *)(param_1 + 0x74) = 0;
    FUN_006919a0();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  ExceptionList = local_10;
  return 0;
}

