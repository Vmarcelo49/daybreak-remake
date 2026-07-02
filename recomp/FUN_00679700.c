// ============================================
// Address:  0x00679700
// Original: FUN_00679700
// Status:   unreviewed
// ============================================


int FUN_00679700(int param_1,int param_2)

{
  if (*(int *)(param_1 + 4) != 0) {
    if (-1 < param_2) {
      if (*(int *)(param_1 + 0x34) <= param_2) {
        return 0;
      }
      return *(int *)(param_1 + 0x48) + param_2 * 0x20;
    }
    if (2 < *(int *)(param_1 + 0x58)) {
      return *(int *)(param_1 + 0x60) * 0x20 + *(int *)(param_1 + 0x48);
    }
  }
  return *(int *)(param_1 + 0x48);
}

