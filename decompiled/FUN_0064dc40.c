// Function: FUN_0064dc40
// Address:  0x0064dc40
// Source:   batch_decompile (mass dump)
// Hash:     59e84ccb607e728c


void __fastcall FUN_0064dc40(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_34 [4];
  void *local_30;
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  if (*(int *)(param_1 + 8) != 0) {
    FUN_00661e70(param_1);
    D3DXFrameDestroy(*(undefined4 *)(param_1 + 8),local_1c);
    *(undefined4 *)(param_1 + 8) = 0;
  }
  if (*(int *)(param_1 + 4) != 0) {
    local_28 = *(undefined4 *)(param_1 + 4);
    FUN_0064edd0(local_28);
    *(undefined4 *)(param_1 + 4) = 0;
  }
  for (local_20 = 0; local_20 < 2; local_20 = local_20 + 1) {
    if (*(int *)(param_1 + 0xc + local_20 * 4) != 0) {
      local_24 = (**(code **)(**(int **)(param_1 + 0xc + local_20 * 4) + 8))
                           (*(undefined4 *)(param_1 + 0xc + local_20 * 4));
      *(undefined4 *)(param_1 + 0xc + local_20 * 4) = 0;
    }
  }
  FUN_00654620(local_8);
  FUN_00654670(local_10);
  while( true ) {
    cVar1 = const_iterator__operator__(local_10);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00654770();
    FUN_00656200(*puVar2);
    FUN_0064f050(local_2c,0);
  }
  FUN_0064ef00();
  FUN_0065a5e0();
  FUN_00654620(local_14);
  FUN_00654670(local_c);
  while( true ) {
    cVar1 = const_iterator__operator__(local_c);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00654770();
    local_30 = (void *)*puVar2;
    _free(local_30);
    FUN_0064f050(local_34,0);
  }
  FUN_0065a5e0();
  return;
}

