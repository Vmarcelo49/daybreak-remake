// ============================================
// Address:  0x00650640
// Original: FUN_00650640
// Status:   unreviewed
// ============================================


void __fastcall FUN_00650640(int param_1)

{
  undefined4 local_10;
  
  if (*(int *)(param_1 + 0x27c) != 0) {
    (**(code **)(*DAT_006d16f8 + 0x94))(DAT_006d16f8,0,*(undefined4 *)(param_1 + 0x27c));
  }
  if (*(int *)(param_1 + 0x280) != 0) {
    (**(code **)(*DAT_006d16f8 + 0x9c))(DAT_006d16f8,*(undefined4 *)(param_1 + 0x280));
  }
  if (*(int *)(param_1 + 0x27c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x27c) + 8))(*(undefined4 *)(param_1 + 0x27c));
    *(undefined4 *)(param_1 + 0x27c) = 0;
  }
  if (*(int *)(param_1 + 0x280) != 0) {
    (**(code **)(**(int **)(param_1 + 0x280) + 8))(*(undefined4 *)(param_1 + 0x280));
    *(undefined4 *)(param_1 + 0x280) = 0;
  }
  if (*(int *)(param_1 + 0x284) != 0) {
    (**(code **)(**(int **)(param_1 + 0x284) + 8))(*(undefined4 *)(param_1 + 0x284));
    *(undefined4 *)(param_1 + 0x284) = 0;
  }
  if (*(int *)(param_1 + 0x288) != 0) {
    (**(code **)(**(int **)(param_1 + 0x288) + 8))(*(undefined4 *)(param_1 + 0x288));
    *(undefined4 *)(param_1 + 0x288) = 0;
  }
  for (local_10 = 1; local_10 < 10; local_10 = local_10 + 1) {
    if (*(int *)(param_1 + 0x30 + local_10 * 4) != 0) {
      (**(code **)(**(int **)(param_1 + 0x30 + local_10 * 4) + 8))
                (*(undefined4 *)(param_1 + 0x30 + local_10 * 4));
      *(undefined4 *)(param_1 + 0x30 + local_10 * 4) = 0;
    }
  }
  return;
}

