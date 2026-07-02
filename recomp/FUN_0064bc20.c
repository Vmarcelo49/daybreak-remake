// ============================================
// Address:  0x0064bc20
// Original: FUN_0064bc20
// Status:   unreviewed
// ============================================


void __thiscall FUN_0064bc20(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_14;
  int local_10;
  int local_8;
  
  if ((*(char *)(param_1 + param_2 + 0x55c1) < '\0') && (*(int *)(param_1 + 0x5304) < 0)) {
    *(int *)(param_1 + 0x5304) = param_2;
    *(undefined1 *)(param_1 + param_2 + 0x55c1) = 3;
    for (local_8 = 2;
        (-1 < local_8 &&
        ((*(int *)(param_1 + 0x52fc + local_8 * 4) < *(int *)(param_1 + 0x52f8 + local_8 * 4) ||
         (*(int *)(param_1 + 0x52f8 + local_8 * 4) == -1)))); local_8 = local_8 + -1) {
      uVar1 = *(undefined4 *)(param_1 + 0x52fc + local_8 * 4);
      *(undefined4 *)(param_1 + 0x52fc + local_8 * 4) =
           *(undefined4 *)(param_1 + 0x52f8 + local_8 * 4);
      *(undefined4 *)(param_1 + 0x52f8 + local_8 * 4) = uVar1;
    }
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x55c1) = 0xff;
    }
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
      if (-1 < *(int *)(param_1 + 0x52f8 + local_14 * 4)) {
        *(undefined1 *)(param_1 + 0x55c1 + *(int *)(param_1 + 0x52f8 + local_14 * 4)) =
             (undefined1)local_14;
      }
    }
    FUN_0064bf60();
  }
  return;
}

