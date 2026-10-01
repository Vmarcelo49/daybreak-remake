// Function: FUN_0040fde0
// Address:  0x0040fde0
// Source:   batch_decompile (mass dump)
// Hash:     5b76b699424f6421


int __fastcall FUN_0040fde0(int *param_1)

{
  int iVar1;
  uint local_8;
  
  local_8 = (uint)param_1[1] >> 2;
  iVar1 = local_8 * -4;
  if (*(uint *)(*param_1 + 8) <= local_8) {
    local_8 = local_8 - *(int *)(*param_1 + 8);
  }
  return *(int *)(*(int *)(*param_1 + 4) + local_8 * 4) + (param_1[1] + iVar1) * 4;
}

