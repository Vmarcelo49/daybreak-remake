// ============================================
// Address:  0x0042ea40
// Original: FUN_0042ea40
// Status:   unreviewed
// ============================================


void __fastcall FUN_0042ea40(int param_1)

{
  int iVar1;
  int local_8;
  
  if (*(int *)(param_1 + 0x30) != 0) {
    if (*(int *)(param_1 + 0x30) != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    if (*(int *)(param_1 + 0x34) != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    for (local_8 = 0; local_8 < 100; local_8 = local_8 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x38) + local_8 * 4) != 0) {
        if (*(int *)(*(int *)(param_1 + 0x38) + local_8 * 4) != 0) {
          FUN_00402010(1);
        }
        *(undefined4 *)(*(int *)(param_1 + 0x38) + local_8 * 4) = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  iVar1 = FUN_0068de10();
  if (iVar1 != 0) {
    FUN_00656200(*(undefined4 *)(param_1 + 0x2c));
  }
  return;
}

