// ============================================
// Address:  0x00423700
// Original: FUN_00423700
// Status:   unreviewed
// ============================================


byte __fastcall FUN_00423700(int param_1)

{
  byte bVar1;
  
  if ((*(int *)(param_1 + 0xadec) < 0x7c) || (0x81 < *(int *)(param_1 + 0xadec))) {
    bVar1 = 0;
  }
  else {
    bVar1 = 1;
  }
  return *(int *)(param_1 + 0xadec) == 0xc2 | bVar1;
}

