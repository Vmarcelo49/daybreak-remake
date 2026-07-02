// Function: FUN_0064f100
// Address:  0x0064f100
// Source:   batch_decompile (mass dump)
// Hash:     094b44e21e1e888c


void __fastcall FUN_0064f100(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    FUN_0064f370(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
    deallocate(*(undefined4 *)(param_1 + 4),*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4) >> 2);
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

