// Function: FUN_0041bae0
// Address:  0x0041bae0
// Source:   batch_decompile (mass dump)
// Hash:     c94eea4eeb411beb


undefined4 __fastcall FUN_0041bae0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined4 local_58;
  undefined4 local_50;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e04a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006584e0();
  FUN_006585f0();
  *(int *)(param_1 + 0x3c3c) = *(int *)(param_1 + 0x3c3c) + 1;
  cVar1 = FUN_006586d0(0x1c);
  if ((cVar1 != '\0') &&
     ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0')))) {
    FUN_0064ad70();
  }
  cVar1 = FUN_0041af70();
  if (((cVar1 == '\0') && (*(int *)(param_1 + 0x3fcc) != 3)) &&
     (cVar1 = FUN_0064c230(), cVar1 == '\0')) {
    for (local_14 = 0; local_14 < 0x10; local_14 = local_14 + 1) {
      if ((*(float *)(param_1 + 0x3d50 + local_14 * 4) < 1.0) &&
         (local_14 + 5 < *(int *)(param_1 + 0x3c3c))) {
        *(float *)(param_1 + 0x3d50 + local_14 * 4) =
             *(float *)(param_1 + 0x3d50 + local_14 * 4) + 0.1;
      }
    }
    if (*(char *)(param_1 + 0x3c40) == *(char *)(param_1 + 0x3c41)) {
      if (*(char *)(param_1 + 0x3c42) != '\0') {
        *(char *)(param_1 + 0x3c42) = *(char *)(param_1 + 0x3c42) + -0xf;
      }
    }
    else {
      *(char *)(param_1 + 0x3c42) = *(char *)(param_1 + 0x3c42) + '\x0f';
      if (*(char *)(param_1 + 0x3c42) == -1) {
        *(undefined1 *)(param_1 + 0x3c41) = *(undefined1 *)(param_1 + 0x3c40);
      }
    }
    if (*(int *)(param_1 + 0x3fcc) == 1) {
      DAT_006cfba0 = 1;
      if ((char)(&DAT_006cfde1)[DAT_006cfdb4] < '\0') {
        DAT_006cfba4 = 0;
        if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
          if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
            FUN_0040dce0(1);
          }
          *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = 0;
        }
        pvVar3 = operator_new(0x180);
        local_8 = 1;
        if (pvVar3 == (void *)0x0) {
          local_58 = 0;
        }
        else {
          local_58 = FUN_0040dab0();
        }
        local_8 = 0xffffffff;
        *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = local_58;
        FUN_00657330(&DAT_006cfe20);
      }
      else if (*(int *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[DAT_006cfdb4] * 4) < 0) {
        DAT_006cfba4 = 0;
        if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
          if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
            FUN_0040dce0(1);
          }
          *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = 0;
        }
        pvVar3 = operator_new(0x180);
        local_8 = 0;
        if (pvVar3 == (void *)0x0) {
          local_50 = 0;
        }
        else {
          local_50 = FUN_0040dab0();
        }
        local_8 = 0xffffffff;
        *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = local_50;
        FUN_00657330(&DAT_006cfe20);
      }
      else {
        if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
          if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0) {
            FUN_0040dce0(1);
          }
          *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = 0;
        }
        DAT_006cfba4 = *(undefined4 *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[DAT_006cfdb4] * 4);
      }
      uVar2 = 0x11;
    }
    else if (*(int *)(param_1 + 0x3fcc) == 2) {
      FUN_0065b870("data/bgm/title.ogg");
      uVar2 = 0xd;
    }
    else {
      for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
        if (1.0 < *(float *)(param_1 + 0x3cb4 + local_18 * 4)) {
          *(float *)(param_1 + 0x3cb4 + local_18 * 4) =
               *(float *)(param_1 + 0x3cb4 + local_18 * 4) - 0.2;
        }
        if (0.0 < *(float *)(param_1 + 0x3cc4 + local_18 * 4)) {
          *(float *)(param_1 + 0x3cc4 + local_18 * 4) =
               *(float *)(param_1 + 0x3cc4 + local_18 * 4) - 20.0;
        }
      }
      cVar1 = FUN_00645e10();
      if (cVar1 == '\0') {
        FUN_00657390();
        cVar1 = FUN_0064c090();
        if (cVar1 == '\0') {
          *(undefined2 *)(param_1 + 0x3fb4) = 0;
          *(ushort *)(param_1 + 0x3fb4) = *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006cae98 < 0)
          ;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(0 < DAT_006cae98) << 1;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006cae94 < 0) << 2;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(0 < DAT_006cae94) << 3;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006cae9c != 0) << 4;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caea0 != 0) << 5;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caea4 != 0) << 6;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caea8 != 0) << 7;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caeac != 0) << 8;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caeb0 != 0) << 9;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caeb4 != 0) << 10;
          *(ushort *)(param_1 + 0x3fb4) =
               *(ushort *)(param_1 + 0x3fb4) | (ushort)(DAT_006caeb8 != 0) << 0xb;
          FUN_0041afb0(param_1 + 0x3fac,0x1e,2);
        }
      }
      uVar2 = 0xf;
    }
  }
  else {
    FUN_0065f8b0();
    FUN_0065b870("data/bgm/title.ogg");
    uVar2 = 0xb;
  }
  ExceptionList = local_10;
  return uVar2;
}

