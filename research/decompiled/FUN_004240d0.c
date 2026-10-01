// Function: FUN_004240d0
// Address:  0x004240d0
// Source:   batch_decompile (mass dump)
// Hash:     ea669ec1da0c4835


undefined4 __thiscall FUN_004240d0(int param_1,undefined1 *param_2)

{
  *param_2 = 0x22;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  param_2[2] = *(undefined1 *)(param_1 + 9);
  *(undefined4 *)(param_2 + 3) = *(undefined4 *)(param_1 + 0xc);
  return 7;
}

