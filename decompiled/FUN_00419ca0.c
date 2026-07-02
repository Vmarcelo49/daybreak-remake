// Function: FUN_00419ca0
// Address:  0x00419ca0
// Source:   batch_decompile (mass dump)
// Hash:     e669df1922002ffc


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00419ca0(int param_1,int param_2)

{
  int iVar1;
  int local_80;
  undefined1 local_7c [8];
  int local_74;
  int local_70;
  undefined1 local_6c [8];
  char local_64;
  undefined1 local_63;
  undefined1 local_62 [90];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  if (((0 < param_2) && (param_2 < 8)) && ((&DAT_006cfdd1)[param_2] != '\0')) {
    FUN_00416670();
    local_64 = (char)param_2;
    local_63 = 3;
    FUN_0066b860(local_62,&DAT_006a1fcc);
    FUN_00415d30(0,local_6c,0,8);
    FUN_00646110((int)local_64,local_62,local_63);
    FUN_0065d670();
    *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 0;
    *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 0;
    (&DAT_006cfdd1)[param_2] = 0;
    local_70 = 0;
    for (local_80 = 1; local_80 < 8; local_80 = local_80 + 1) {
      if ((&DAT_006cfdd1)[local_80] != '\0') {
        local_70 = local_70 + 1;
      }
    }
    DAT_006cfdcc = local_70;
    _memset(&DAT_006cfdfc,0,0x20);
    if (-1 < (char)(&DAT_006cfde1)[param_2]) {
      iVar1 = *(int *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[param_2] * 4);
      if (-1 < iVar1) {
        (&DAT_006cfaf8)[iVar1] = 4;
        FUN_00414670();
        *(undefined1 *)(*(int *)(&DAT_006cc288 + iVar1 * 4) + 0x860) = 1;
        *(undefined4 *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[param_2] * 4) = 0xffffffff;
      }
      (&DAT_006cfb18)[(char)(&DAT_006cfde1)[param_2]] = 0xffffffff;
      (&DAT_006cfde1)[param_2] = 0xff;
    }
    _memset(&DAT_006cfb58 + param_2 * 9,0,9);
    FUN_00645dc0(param_2,&DAT_006cfb58 + param_2 * 9);
    FUN_0065d6a0();
    FUN_00416760();
    local_74 = param_2;
    FUN_00415d30(0,local_7c,0,0x88);
    FUN_0064aed0(1);
  }
  return;
}

