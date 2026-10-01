// Function: FUN_00647130
// Address:  0x00647130
// Source:   batch_decompile (mass dump)
// Hash:     7295e0c24a0cbc6d


undefined1 * __fastcall FUN_00647130(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_10;
  int local_8;
  
  iVar1 = *(int *)(param_1 + 0x414);
  local_8 = iVar1 + -8;
  if (local_8 < 0) {
    local_8 = 0;
  }
  *param_1 = 0;
  for (local_10 = local_8; local_10 < iVar1; local_10 = local_10 + 1) {
    uVar2 = FUN_00647400(local_10);
    FUN_0066b870(param_1,uVar2);
  }
  return param_1;
}

