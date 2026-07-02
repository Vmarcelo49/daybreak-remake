// Function: FUN_0064fdf0
// Address:  0x0064fdf0
// Source:   batch_decompile (mass dump)
// Hash:     26b20115e6814266


int __fastcall FUN_0064fdf0(int param_1)

{
  undefined4 local_8;
  
  FUN_00661670();
  FUN_0068d8d0();
  FUN_0068d8d0();
  FUN_0068d8d0();
  FUN_0068d8d0();
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x250));
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x284) = 0;
  *(undefined4 *)(param_1 + 0x288) = 0;
  *(undefined4 *)(param_1 + 0x27c) = 0;
  *(undefined4 *)(param_1 + 0x280) = 0;
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + local_8 * 4) = 0;
  }
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + 0x30 + local_8 * 4) = 0;
  }
  *(undefined4 *)(param_1 + 0x278) = 0;
  *(undefined1 *)(param_1 + 0x58) = 1;
  *(undefined1 *)(param_1 + 0x59) = 0;
  *(undefined4 *)(param_1 + 0x28c) = 0;
  return param_1;
}

