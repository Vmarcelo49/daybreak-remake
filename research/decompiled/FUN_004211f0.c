// Function: FUN_004211f0
// Address:  0x004211f0
// Source:   batch_decompile (mass dump)
// Hash:     88375f8cf8104bb1


void __thiscall FUN_004211f0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x684) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xadec) = param_2;
  FUN_00421240(0);
  *(int *)(param_1 + 0xade0) = param_1 + 0x880 + *(int *)(param_1 + 0xadec) * 0x1c;
  return;
}

