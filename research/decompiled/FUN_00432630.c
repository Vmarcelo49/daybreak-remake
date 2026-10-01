// Function: FUN_00432630
// Address:  0x00432630
// Source:   batch_decompile (mass dump)
// Hash:     77ef894c8a75c7b7


void __fastcall FUN_00432630(int param_1)

{
  char cVar1;
  uint local_c;
  
  cVar1 = Empty();
  if (cVar1 == '\0') {
    local_c = *(int *)(param_1 + 0x10) + -1 + *(int *)(param_1 + 0xc);
    if (*(uint *)(param_1 + 8) <= local_c) {
      local_c = local_c - *(int *)(param_1 + 8);
    }
    FUN_00432bf0(*(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4));
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    if (*(int *)(param_1 + 0x10) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
  }
  return;
}

