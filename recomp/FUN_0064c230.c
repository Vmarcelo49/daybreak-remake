// ============================================
// Address:  0x0064c230
// Original: FUN_0064c230
// Status:   unreviewed
// ============================================


bool __fastcall FUN_0064c230(int param_1)

{
  bool bVar1;
  
  bVar1 = *(char *)(param_1 + 0xa6) != '\0';
  if (bVar1) {
    *(undefined1 *)(param_1 + 0xa5) = 0;
    *(undefined1 *)(param_1 + 0xa6) = 0;
  }
  return bVar1;
}

