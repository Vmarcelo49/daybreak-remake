// Function: FUN_0068b1c0
// Address:  0x0068b1c0
// Source:   batch_decompile (mass dump)
// Hash:     746462de3fa0a128


undefined4 FUN_0068b1c0(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffffe;
  }
  else {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
  }
  return 0;
}

