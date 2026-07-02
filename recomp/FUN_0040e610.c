// ============================================
// Address:  0x0040e610
// Original: FUN_0040e610
// Status:   unreviewed
// ============================================


void __fastcall FUN_0040e610(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = (DAT_006cfd04 & 0xf) + 1;
  if (0xf < local_8) {
    local_8 = 0xf;
  }
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    if (((1 << ((char)local_c + 8U & 0x1f) & DAT_006cfd04) == 0) &&
       (((DAT_006cfb28 == local_c && (DAT_006cfaf8 < 4)) ||
        ((DAT_006cfb2c == local_c && (DAT_006cfafc < 4)))))) {
      *(int *)(param_1 + 0x200) = local_c;
    }
  }
  if (-1 < *(int *)(param_1 + 0x200)) {
    DAT_006cfd04 = 1 << ((char)*(undefined4 *)(param_1 + 0x200) + 8U & 0x1f) | DAT_006cfd04;
  }
  DAT_006cfd04 = DAT_006cfd04 & 0xfffffff0 | local_8;
  FUN_006488d0();
  return;
}

