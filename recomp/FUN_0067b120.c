// ============================================
// Address:  0x0067b120
// Original: FUN_0067b120
// Status:   unreviewed
// ============================================


undefined4 FUN_0067b120(int param_1,int param_2)

{
  if ((param_2 != 0) && (*(int *)(param_1 + 0x14) < *(int *)(param_1 + 0x18) + param_2)) {
    return 0xffffff7d;
  }
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + param_2;
  return 0;
}

