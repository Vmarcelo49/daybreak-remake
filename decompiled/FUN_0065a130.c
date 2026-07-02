// Function: FUN_0065a130
// Address:  0x0065a130
// Source:   batch_decompile (mass dump)
// Hash:     b7486aaabeccc273


void __thiscall FUN_0065a130(int param_1,undefined4 param_2)

{
  undefined4 local_8;
  
  *(undefined4 *)(param_1 + 0x3ec) = param_2;
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    FUN_0065a390((*(int *)(param_1 + 1000) * *(int *)(param_1 + 0x3ec)) / 10000 + -10000);
    FUN_0065a390((*(int *)(param_1 + 1000) * *(int *)(param_1 + 0x3ec)) / 10000 + -10000);
  }
  return;
}

