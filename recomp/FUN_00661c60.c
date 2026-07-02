// ============================================
// Address:  0x00661c60
// Original: FUN_00661c60
// Status:   unreviewed
// ============================================


void __fastcall FUN_00661c60(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    (**(code **)(**(int **)(param_1 + 0xc) + 8))(*(undefined4 *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(**(int **)(param_1 + 4) + 8))(*(undefined4 *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  if (*(int *)(param_1 + 8) != 0) {
    (**(code **)(**(int **)(param_1 + 8) + 8))(*(undefined4 *)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

