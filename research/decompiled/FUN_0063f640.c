// Function: FUN_0063f640
// Address:  0x0063f640
// Source:   batch_decompile (mass dump)
// Hash:     3418f9549634a933


undefined4 __thiscall FUN_0063f640(int param_1,undefined1 *param_2)

{
  undefined2 uVar1;
  
  *param_2 = 0x1a;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 2) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 4) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 6) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 8) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 10) = uVar1;
  return 0xc;
}

