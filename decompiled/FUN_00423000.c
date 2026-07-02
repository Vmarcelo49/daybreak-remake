// Function: FUN_00423000
// Address:  0x00423000
// Source:   batch_decompile (mass dump)
// Hash:     ebf4fa6ad9c5bc29


void __fastcall FUN_00423000(int param_1)

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
  *(int *)(param_1 + 0xaf18) = *(int *)(param_1 + 0xaf18) + 1;
  return;
}

