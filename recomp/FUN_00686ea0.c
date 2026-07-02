// ============================================
// Address:  0x00686ea0
// Original: FUN_00686ea0
// Status:   unreviewed
// ============================================


void FUN_00686ea0(LPVOID param_1)

{
  if (param_1 != (LPVOID)0x0) {
    FUN_00686fb0(param_1);
    CoTaskMemFree(param_1);
  }
  return;
}

