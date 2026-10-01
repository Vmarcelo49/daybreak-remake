// Function: FUN_00418f90
// Address:  0x00418f90
// Source:   batch_decompile (mass dump)
// Hash:     bb1c957a7bde258b


undefined4 __thiscall FUN_00418f90(int param_1,undefined1 *param_2)

{
  *param_2 = 0x13;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  param_2[2] = *(undefined1 *)(param_1 + 0xc);
  param_2[3] = *(undefined1 *)(param_1 + 0x10);
  param_2[4] = *(undefined1 *)(param_1 + 0x14);
  param_2[5] = *(undefined1 *)(param_1 + 0x15);
  *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x18);
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_1 + 0x1c);
  *(undefined2 *)(param_2 + 10) = *(undefined2 *)(param_1 + 0x20);
  *(undefined2 *)(param_2 + 0xc) = *(undefined2 *)(param_1 + 0x24);
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_1 + 0x28);
  return 0x10;
}

