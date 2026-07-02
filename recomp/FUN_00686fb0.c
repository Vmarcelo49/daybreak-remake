// ============================================
// Address:  0x00686fb0
// Original: FUN_00686fb0
// Status:   unreviewed
// ============================================


void FUN_00686fb0(int param_1)

{
  if (*(int *)(param_1 + 0x40) != 0) {
    CoTaskMemFree(*(LPVOID *)(param_1 + 0x44));
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x3c) + 8))(*(undefined4 *)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return;
}

