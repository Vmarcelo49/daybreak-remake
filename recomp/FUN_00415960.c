// ============================================
// Address:  0x00415960
// Original: FUN_00415960
// Status:   unreviewed
// ============================================


void __thiscall FUN_00415960(int param_1,int param_2)

{
  int local_18;
  undefined1 local_14 [8];
  int local_c;
  int local_8;
  
  if (((0 < param_2) && (param_2 < 8)) && ((&DAT_006cfdd1)[param_2] != '\0')) {
    FUN_0065d670();
    *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 0;
    *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 0;
    (&DAT_006cfdd1)[param_2] = 0;
    local_8 = 0;
    for (local_18 = 1; local_18 < 8; local_18 = local_18 + 1) {
      if ((&DAT_006cfdd1)[local_18] != '\0') {
        local_8 = local_8 + 1;
      }
    }
    DAT_006cfdcc = local_8;
    _memset(&DAT_006cfdfc,0,0x20);
    _memset(&DAT_006cfb58 + param_2 * 9,0,9);
    FUN_00645dc0(param_2,&DAT_006cfb58 + param_2 * 9);
    *(undefined1 *)(param_1 + param_2 + 0x18c) = 0;
    FUN_00415be0(param_2);
    FUN_0065d6a0();
    _memset((void *)(param_1 + 0x194 + param_2 * 9),0,9);
    FUN_00415d30(0,param_1 + 0x184,0,8);
    FUN_00416760();
    local_c = param_2;
    FUN_00415d30(0,local_14,0,0x88);
    FUN_0064aed0(1);
  }
  return;
}

