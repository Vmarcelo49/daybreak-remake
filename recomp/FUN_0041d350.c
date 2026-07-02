// ============================================
// Address:  0x0041d350
// Original: FUN_0041d350
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0041d350(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_d4 [8];
  undefined4 local_cc;
  undefined1 local_c8 [8];
  undefined4 local_c0;
  undefined1 local_bc [8];
  undefined4 local_b4;
  undefined4 local_a8;
  int local_98;
  int local_94;
  int local_90;
  undefined1 auStack_84 [8];
  undefined1 auStack_7c [72];
  undefined1 auStack_34 [8];
  char acStack_2c [20];
  undefined4 local_18;
  int local_14;
  undefined4 local_8;
  
  local_18 = DAT_006b77f4;
  uVar2 = FUN_004165e0(param_2);
  switch(uVar2) {
  case 1:
    FUN_00416410();
    FUN_0041d7e0(param_2);
    switch(local_a8) {
    case 0xe:
      FUN_00416410();
      local_cc = 0xf;
      FUN_0041afb0(local_d4,0,8);
    case 0xc:
      *(undefined1 *)(param_1 + 0x10c) = 1;
      break;
    case 0x10:
      if (*(int *)(param_1 + 0x104) == 1) {
        FUN_00416410();
        local_c0 = 0x11;
        FUN_0041afb0(local_c8,0,8);
      }
      break;
    case 0x12:
      *(undefined4 *)(param_1 + 0x108) = 0;
      FUN_00416410();
      local_b4 = 0x13;
      FUN_0041afb0(local_bc,0,8);
    }
    break;
  case 7:
    FUN_0041d810();
    FUN_0041d7e0(param_2);
    FUN_0065d0c0(local_8);
    break;
  case 0xb:
    FUN_00416760();
    FUN_0041d7e0(param_2);
    (&DAT_006cfdd1)[local_98] = 0;
    _memset(&DAT_006cfb58 + local_98 * 9,0,9);
    FUN_00645dc0(local_98,&DAT_006cfb58 + local_98 * 9);
    if (-1 < (char)(&DAT_006cfde1)[local_98]) {
      cVar1 = (&DAT_006cfb08)[(char)(&DAT_006cfde1)[local_98] * 4];
      if (-1 < cVar1) {
        *(undefined4 *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[local_98] * 4) = 0xffffffff;
        (&DAT_006cfaf8)[cVar1] = 4;
      }
      (&DAT_006cfb18)[(char)(&DAT_006cfde1)[local_98]] = 0xffffffff;
      (&DAT_006cfde1)[local_98] = 0xff;
    }
    break;
  case 0x10:
    FUN_00415ea0();
    FUN_00416030(param_2);
    local_14 = -1;
    for (local_90 = 0; local_90 < 8; local_90 = local_90 + 1) {
      (&DAT_006cfdd1)[local_90] = auStack_84[local_90];
      if ((&DAT_006cfdd1)[local_90] == '\0') {
        _memset(&DAT_006cfb58 + local_90 * 9,0,9);
      }
      else {
        _memcpy(&DAT_006cfb58 + local_90 * 9,auStack_7c + local_90 * 9,9);
        local_14 = local_14 + 1;
      }
      FUN_00645dc0(local_90,&DAT_006cfb58 + local_90 * 9);
      (&DAT_006cfde1)[local_90] = auStack_34[local_90];
    }
    DAT_006cfdcc = local_14;
    for (local_94 = 0; local_94 < 4; local_94 = local_94 + 1) {
      (&DAT_006cfb18)[local_94] = (int)acStack_2c[local_94];
    }
    FUN_0064bf60();
    break;
  case 0x18:
    *(undefined4 *)(param_1 + 0x108) = 0;
    *(undefined1 *)(param_1 + 0x10d) = 1;
  }
  return;
}

