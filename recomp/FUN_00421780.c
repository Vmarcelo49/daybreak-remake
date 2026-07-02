// ============================================
// Address:  0x00421780
// Original: FUN_00421780
// Status:   unreviewed
// ============================================


void __fastcall FUN_00421780(int param_1)

{
  if (*(int *)(param_1 + 0x278) < 0) {
    if (*(int *)(param_1 + 0x27c) < 0) {
      FUN_0042db10(0x42340000,*(undefined4 *)(param_1 + 0x874));
    }
    else if (*(int *)(param_1 + 0x27c) < 1) {
      FUN_0042db10(0x42b40000,*(undefined4 *)(param_1 + 0x874));
    }
    else {
      FUN_0042db10(0x43070000,*(undefined4 *)(param_1 + 0x874));
    }
  }
  else if (*(int *)(param_1 + 0x278) < 1) {
    if (*(int *)(param_1 + 0x27c) < 0) {
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x874));
    }
    else if (0 < *(int *)(param_1 + 0x27c)) {
      FUN_0042db10(0x43340000,*(undefined4 *)(param_1 + 0x874));
    }
  }
  else if (*(int *)(param_1 + 0x27c) < 0) {
    FUN_0042db10(0xc2340000,*(undefined4 *)(param_1 + 0x874));
  }
  else if (*(int *)(param_1 + 0x27c) < 1) {
    FUN_0042db10(0xc2b40000,*(undefined4 *)(param_1 + 0x874));
  }
  else {
    FUN_0042db10(0xc3070000,*(undefined4 *)(param_1 + 0x874));
  }
  return;
}

