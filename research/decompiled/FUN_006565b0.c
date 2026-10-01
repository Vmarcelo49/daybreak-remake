// Function: FUN_006565b0
// Address:  0x006565b0
// Source:   batch_decompile (mass dump)
// Hash:     9da7f5e8c908e557


void __fastcall FUN_006565b0(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    FUN_006541f0(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
    deallocate(*(undefined4 *)(param_1 + 4),*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4) >> 2);
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

