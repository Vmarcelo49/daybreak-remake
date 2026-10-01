// Function: FUN_0040d130
// Address:  0x0040d130
// Source:   batch_decompile (mass dump)
// Hash:     b6e7b631e75494b3


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint __fastcall FUN_0040d130(uint param_1)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  undefined4 local_58;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  char local_1c [8];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dbcf;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  DAT_006cfba0 = 0;
  if (DAT_006cfdb0 == '\0') {
    ExceptionList = &local_10;
    for (local_2c = 0; local_2c < 8; local_2c = local_2c + 1) {
      local_1c[local_2c] = '\0';
      (&DAT_006cfdd9)[local_2c] = 0;
    }
  }
  else {
    ExceptionList = &local_10;
    for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
      if ((local_20 == 0) || (local_20 == 2)) {
        local_24 = local_20 + 1;
      }
      else {
        local_24 = local_20 + -1;
      }
      if (((*(char *)(param_1 + local_24 + 0x3cd4) == '\x01') &&
          ((((&DAT_006b72a0)[*(int *)(param_1 + 0x3d08 + local_20 * 4)] == '\0' ||
            (*(int *)(param_1 + 0x3d08 + local_20 * 4) == 2)) &&
           (*(char *)(param_1 + local_20 + 0x3cd4) == '\0')))) &&
         (*(int *)(param_1 + 0x3d08 + local_24 * 4) != 2)) {
        *(undefined1 *)(param_1 + local_20 + 0x3cd4) = 2;
      }
    }
    for (local_28 = 0; local_28 < 8; local_28 = local_28 + 1) {
      local_1c[local_28] = '\x01';
      (&DAT_006cfdd9)[local_28] = 0;
    }
  }
  for (local_30 = 0; local_30 < 4; local_30 = local_30 + 1) {
    *(undefined4 *)(&DAT_006cfb08 + local_30 * 4) = 0xffffffff;
  }
  for (local_34 = 0; local_34 < 4; local_34 = local_34 + 1) {
    if (*(int *)(param_1 + 0x3d08 + local_34 * 4) < 0) {
      uVar1 = FUN_0065d150();
      (&DAT_006cfb28)[local_34] = uVar1 % 0x10;
      (&DAT_006cfaf8)[local_34] = 4;
      (&DAT_006cfb54)[local_34] = 0;
      if ((int)(&DAT_006cfb28)[local_34] < 0xe) {
        uVar1 = FUN_0065d150();
        *(uint *)(&DAT_006cfb38 + local_34 * 4) = uVar1 % 3;
      }
      else {
        uVar1 = FUN_0065d150();
        *(uint *)(&DAT_006cfb38 + local_34 * 4) = uVar1 % 2;
      }
      uVar1 = FUN_0065d150();
      (&DAT_006cfb48)[local_34] = (char)((ulonglong)uVar1 % 3);
      uVar1 = FUN_0065d150();
      *(uint *)(param_1 + 0x3d38 + local_34 * 4) =
           uVar1 % (uint)(int)(char)(&DAT_006b7290)[(&DAT_006cfb28)[local_34]];
    }
    else {
      (&DAT_006cfb28)[local_34] = *(undefined4 *)(param_1 + 0x3d08 + local_34 * 4);
      (&DAT_006cfaf8)[local_34] = *(undefined4 *)(param_1 + 0x3cf8 + local_34 * 4);
      (&DAT_006cfb54)[local_34] = *(undefined1 *)(param_1 + local_34 + 0x3cd4);
      if (((-1 < *(int *)(param_1 + 0x3cf8 + local_34 * 4)) &&
          (*(int *)(param_1 + 0x3cf8 + local_34 * 4) < 4)) &&
         ((*(int *)(&DAT_006cfb08 + *(int *)(param_1 + 0x3cf8 + local_34 * 4) * 4) = local_34,
          DAT_006cfdb0 != '\0' &&
          (-1 < (int)(&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)])))) {
        *(int *)(&DAT_006cfdfc + (&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)] * 4) =
             *(int *)(&DAT_006cfdfc + (&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)] * 4
                     ) + 1;
        local_1c[(&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)]] = '\0';
        if ((&DAT_006cfb54)[local_34] == '\x01') {
          (&DAT_006cfdf1)[(&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)]] = 0;
        }
        (&DAT_006cfdd9)[(&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_34 * 4)]] =
             (undefined1)local_34;
      }
      *(undefined4 *)(&DAT_006cfb38 + local_34 * 4) =
           *(undefined4 *)(param_1 + 0x3d18 + local_34 * 4);
      (&DAT_006cfb48)[local_34] = *(undefined1 *)(param_1 + 0x3d28 + local_34 * 4);
      if ((int)(&DAT_006cfaf8)[local_34] < 4) {
        (&DAT_006cfba4)[DAT_006cfba0] = local_34;
        DAT_006cfba0 = DAT_006cfba0 + 1;
      }
    }
    (&DAT_006cfb4c)[local_34] = *(undefined1 *)(param_1 + 0x3d38 + local_34 * 4);
  }
  if (DAT_006cfba0 == 0) {
    DAT_006cfba4 = 0;
    DAT_006cfba0 = 1;
    local_1c[0] = '\x01';
  }
  for (local_38 = 0; local_38 < 8; local_38 = local_38 + 1) {
    if (*(int *)(DAT_006cfa24 + local_38 * 4) != 0) {
      if (*(int *)(DAT_006cfa24 + local_38 * 4) != 0) {
        FUN_0040dce0(1);
      }
      *(undefined4 *)(DAT_006cfa24 + local_38 * 4) = 0;
    }
    if (local_1c[local_38] != '\0') {
      pvVar2 = operator_new(0x180);
      local_8 = 0;
      if (pvVar2 == (void *)0x0) {
        local_58 = 0;
      }
      else {
        local_58 = FUN_0040dab0();
      }
      local_8 = 0xffffffff;
      *(undefined4 *)(DAT_006cfa24 + local_38 * 4) = local_58;
      if (local_38 < 1) {
        FUN_00657330(&DAT_006cfe20);
      }
      else {
        FUN_0040da90();
      }
      (&DAT_006cfdd9)[local_38] = 0;
    }
  }
  if (*(int *)(param_1 + 0x3d48) == 0) {
    uVar1 = FUN_0065d150();
    uVar3 = uVar1 / 0xd;
    uVar1 = uVar1 % 0xd;
    if (uVar1 < 6) {
      DAT_006cfaf4 = uVar1 + 1;
    }
    else if (uVar1 < 0xc) {
      uVar3 = uVar1 + 5;
      DAT_006cfaf4 = uVar3;
    }
    else {
      DAT_006cfaf4 = 0x15;
    }
    *(uint *)(param_1 + 0x3d4c) = DAT_006cfaf4;
    param_1 = uVar3;
  }
  else {
    DAT_006cfaf4 = *(int *)(param_1 + 0x3d4c) * 10 + *(int *)(param_1 + 0x3d48);
  }
  ExceptionList = local_10;
  return param_1;
}

