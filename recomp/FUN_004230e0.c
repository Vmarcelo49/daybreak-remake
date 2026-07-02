// ============================================
// Address:  0x004230e0
// Original: FUN_004230e0
// Status:   unreviewed
// ============================================


void __fastcall FUN_004230e0(int param_1)

{
  int *piVar1;
  
  if (*(int *)(*(int *)(param_1 + 0x308) + 0x308) == param_1) {
    *(int *)(param_1 + 0xaf08) = *(int *)(param_1 + 0xaf08) + 1;
    *(int *)(*(int *)(param_1 + 0x308) + 0xaf00) = *(int *)(*(int *)(param_1 + 0x308) + 0xaf00) + 1;
  }
  else {
    *(int *)(param_1 + 0xaf0c) = *(int *)(param_1 + 0xaf0c) + 1;
    *(int *)(*(int *)(param_1 + 0x308) + 0xaf04) = *(int *)(*(int *)(param_1 + 0x308) + 0xaf04) + 1;
  }
  piVar1 = (int *)FUN_00658a10(0);
  if (*(int *)(param_1 + 0x308) == *(int *)(*piVar1 + 0x308)) {
    *(int *)(param_1 + 0xaf10) = *(int *)(param_1 + 0xaf10) + 1;
  }
  *(int *)(param_1 + 0xaf14) = *(int *)(param_1 + 0xaf14) + 1;
  return;
}

