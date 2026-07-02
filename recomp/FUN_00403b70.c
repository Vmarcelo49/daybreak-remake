// ============================================
// Address:  0x00403b70
// Original: FUN_00403b70
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00403b70(undefined4 param_1)

{
  char cVar1;
  
  FUN_00634f60(param_1);
  if (DAT_006cfa2c == '\0') {
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') &&
       ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
      FUN_0064ad70();
    }
    return 10;
  }
  if (DAT_006cfce9 == '\x01') {
    if (DAT_006cc3f4 == 1) {
      return 0x14;
    }
    return 8;
  }
  return 3;
}

