// ============================================
// Address:  0x0063b650
// Original: FUN_0063b650
// Status:   unreviewed
// ============================================


void __fastcall FUN_0063b650(int param_1)

{
  if (*(int *)(param_1 + 0x40) < 0) {
    *(undefined4 *)(param_1 + 200) = 0;
    *(undefined4 *)(param_1 + 0xbc) = 0x41a00000;
  }
  else if (*(int *)(param_1 + 0x40) < 1) {
    if (*(int *)(param_1 + 0x3c) < 0) {
      *(undefined4 *)(param_1 + 200) = 0x42b40000;
      *(undefined4 *)(param_1 + 0xbc) = 0x41a00000;
    }
    else if (*(int *)(param_1 + 0x3c) < 1) {
      *(undefined4 *)(param_1 + 0xbc) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 200) = 0xc2b40000;
      *(undefined4 *)(param_1 + 0xbc) = 0x41a00000;
    }
  }
  else {
    *(undefined4 *)(param_1 + 200) = 0xc3340000;
    *(undefined4 *)(param_1 + 0xbc) = 0x41a00000;
  }
  if ((*(int *)(param_1 + 0x44) == 0) || (1600.0 <= *(float *)(param_1 + 0x80))) {
    if (*(int *)(param_1 + 0x48) == 0) {
      *(undefined4 *)(param_1 + 0xa8) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0xa8) = 0xc1a00000;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0xa8) = 0x41a00000;
  }
  return;
}

