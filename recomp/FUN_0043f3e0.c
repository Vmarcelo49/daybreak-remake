// ============================================
// Address:  0x0043f3e0
// Original: FUN_0043f3e0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0043f3e0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x38) = 1;
    if (*(int *)(param_1 + 0x28) == 0) {
      *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
      if (0x1d < *(int *)(param_1 + 0x1c)) {
        if (*(int *)(param_1 + 0x2c) == 1) {
          *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x2c);
          *(undefined4 *)(param_1 + 0x1c) = 0x1e;
        }
        else {
          *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
        }
      }
    }
    else if ((1 < *(int *)(param_1 + 0x2c)) &&
            (*(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1,
            *(int *)(param_1 + 0x24) <= *(int *)(param_1 + 0x20))) {
      if (*(int *)(param_1 + 0x28) + 1 < *(int *)(param_1 + 0x2c)) {
        *(undefined4 *)(param_1 + 0x20) = 0;
        *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x2c);
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x24);
      }
    }
    uVar1 = *(undefined4 *)(param_1 + 0x28);
  }
  return uVar1;
}

