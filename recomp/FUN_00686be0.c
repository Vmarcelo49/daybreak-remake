// ============================================
// Address:  0x00686be0
// Original: FUN_00686be0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00686be0(int param_1)

{
  if (*(int *)(param_1 + 0x40) != 0) {
    CoTaskMemFree(*(LPVOID *)(param_1 + 0x44));
  }
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return;
}

