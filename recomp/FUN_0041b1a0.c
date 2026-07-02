// ============================================
// Address:  0x0041b1a0
// Original: FUN_0041b1a0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0041b1a0(int param_1)

{
  char cVar1;
  undefined1 local_c [8];
  
  FUN_006584e0();
  FUN_006585f0();
  cVar1 = FUN_0041af70();
  if ((cVar1 != '\0') || (cVar1 = FUN_0064c230(), cVar1 != '\0')) {
    FUN_0065f8b0();
    return 0xb;
  }
  if (*(int *)(param_1 + 0x128) != 0) {
    if (*(int *)(param_1 + 0x128) == 2) {
      FUN_004176d0();
      FUN_0041afb0(local_c,0,0x88);
      *(undefined4 *)(param_1 + 0x128) = 3;
    }
    return 0x13;
  }
  FUN_00657390();
  *(undefined2 *)(param_1 + 0x110) = 0;
  cVar1 = FUN_00645e10();
  if ((cVar1 == '\0') && (cVar1 = FUN_0064c090(), cVar1 == '\0')) {
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006cae98 < 0);
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(0 < DAT_006cae98) << 1;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006cae94 < 0) << 2;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(0 < DAT_006cae94) << 3;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006cae9c != 0) << 4;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caea0 != 0) << 5;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caea4 != 0) << 6;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caea8 != 0) << 7;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caeac != 0) << 8;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caeb0 != 0) << 9;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caeb4 != 0) << 10;
    *(ushort *)(param_1 + 0x110) = *(ushort *)(param_1 + 0x110) | (ushort)(DAT_006caeb8 != 0) << 0xb
    ;
    FUN_0041b8b0(param_1 + 0x108,0x10,2);
  }
  FUN_0063dad0();
  if (DAT_006cfa2c == '\0') {
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') &&
       ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
      FUN_0064ad70();
    }
    return 0x13;
  }
  return 0xf;
}

