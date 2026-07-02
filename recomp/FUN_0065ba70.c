// ============================================
// Address:  0x0065ba70
// Original: FUN_0065ba70
// Status:   unreviewed
// ============================================


void __thiscall FUN_0065ba70(int param_1,int param_2)

{
  if (param_2 < 0) {
    *(undefined4 *)(param_1 + 0x1360) = 0;
  }
  else if (param_2 < 0x2711) {
    *(int *)(param_1 + 0x1360) = param_2;
  }
  else {
    *(undefined4 *)(param_1 + 0x1360) = 10000;
  }
  if (*(int *)(param_1 + 0x10) != 0) {
    (**(code **)(**(int **)(param_1 + 0x10) + 0x3c))
              (*(undefined4 *)(param_1 + 0x10),
               (*(int *)(param_1 + 0x135c) * *(int *)(param_1 + 0x1360)) / 10000 + -10000);
  }
  return;
}

