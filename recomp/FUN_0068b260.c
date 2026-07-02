// ============================================
// Address:  0x0068b260
// Original: FUN_0068b260
// Status:   unreviewed
// ============================================


undefined4 FUN_0068b260(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffffd;
  }
  else {
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 2;
  }
  return 0;
}

