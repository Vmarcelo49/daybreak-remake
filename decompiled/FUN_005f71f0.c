// Function: FUN_005f71f0
// Address:  0x005f71f0
// Source:   batch_decompile (mass dump)
// Hash:     0860427dfb35cb00


void __fastcall FUN_005f71f0(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined1 local_1c [8];
  undefined1 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x2e0;
  local_c = 0;
  while ((iVar1 = FUN_0064f010(), local_c < iVar1 &&
         (iVar1 = *(int *)(param_1 + 0x38), piVar2 = (int *)FUN_005f7a80(local_c),
         *(int *)(iVar1 + 8) == *(int *)(*piVar2 + 8)))) {
    local_c = local_c + 1;
  }
  puVar3 = (undefined4 *)FUN_005f7a80(local_c);
  *(undefined4 *)(param_1 + 0x38) = *puVar3;
  if ((DAT_006cfdb0 == '\x01') && (*(int *)(param_1 + 0x160) != 0)) {
    FUN_005f77b0();
    local_14 = *(undefined1 *)(param_1 + 8);
    local_10 = *(undefined4 *)(param_1 + 0x160);
    FUN_00415d30(0,local_1c,0,0x88);
  }
  return;
}

