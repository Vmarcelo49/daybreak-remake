// ============================================
// Address:  0x00422ed0
// Original: FUN_00422ed0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00422ed0(int param_1)

{
  undefined1 local_14 [8];
  undefined1 local_c;
  undefined1 local_b;
  undefined4 local_8;
  
  *(undefined1 *)(param_1 + 0x2dc) = 1;
  FUN_00434c30();
  if (DAT_006cfdb0 == '\x01') {
    FUN_004240b0();
    local_c = *(undefined1 *)(param_1 + 8);
    local_b = 1;
    local_8 = *(undefined4 *)(param_1 + 0x7a0);
    FUN_00415d30(0,local_14,0,8);
  }
  return;
}

