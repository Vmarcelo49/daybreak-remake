// ============================================
// Address:  0x005f5e00
// Original: FUN_005f5e00
// Status:   unreviewed
// ============================================


void __fastcall FUN_005f5e00(int param_1)

{
  undefined1 local_14 [8];
  undefined1 local_c;
  undefined4 local_8;
  
  if ((DAT_006cfdb0 == '\x01') && (*(int *)(param_1 + 0x160) != 0)) {
    FUN_005f7690();
    local_c = *(undefined1 *)(param_1 + 8);
    local_8 = *(undefined4 *)(param_1 + 0x160);
    FUN_00415d30(0,local_14,0,0x88);
  }
  if ((*(int *)(param_1 + 0x13c) != 0) && (*(int *)(param_1 + 0x13c) != 0)) {
    FUN_005f7700(1);
  }
  FUN_00435e40();
  return;
}

