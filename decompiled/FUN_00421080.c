// Function: FUN_00421080
// Address:  0x00421080
// Source:   batch_decompile (mass dump)
// Hash:     eb6437887696dbb8


void __thiscall FUN_00421080(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x684) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xadf0) = param_2;
  *(undefined4 *)(param_1 + 0xadec) = param_2;
  FUN_00421100(0);
  *(int *)(param_1 + 0xade0) = param_1 + 0x880 + *(int *)(param_1 + 0xadec) * 0x1c;
  return;
}

