// ============================================
// Address:  0x00415cb0
// Original: FUN_00415cb0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00415cb0(int param_1)

{
  int local_c;
  int local_8;
  
  FUN_0064be90();
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    *(undefined1 *)(param_1 + local_8 + 0x1e0) = (&DAT_006cfde1)[local_8];
  }
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x1e8) = *(undefined1 *)(&DAT_006cfb18 + local_c);
  }
  return;
}

