// Function: FUN_00640290
// Address:  0x00640290
// Source:   batch_decompile (mass dump)
// Hash:     2a9bf02461e9c4a5


int __fastcall FUN_00640290(int *param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = param_1[1];
  iVar1 = param_1[1] - local_8;
  if (*(uint *)(*param_1 + 8) <= local_8) {
    local_8 = local_8 - *(int *)(*param_1 + 8);
  }
  return iVar1 * 0x9c + *(int *)(*(int *)(*param_1 + 4) + local_8 * 4);
}

