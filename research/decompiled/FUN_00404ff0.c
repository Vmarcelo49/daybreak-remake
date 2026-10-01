// Function: FUN_00404ff0
// Address:  0x00404ff0
// Source:   batch_decompile (mass dump)
// Hash:     b1b5905b8fd25fbc


undefined4 __fastcall FUN_00404ff0(int param_1)

{
  char cVar1;
  int local_8;
  
  cVar1 = FUN_00405250();
  if (cVar1 != '\0') {
    return 0;
  }
  FUN_006584e0();
  FUN_006585f0();
  cVar1 = FUN_006586d0(0x1c);
  if ((cVar1 != '\0') &&
     ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0')))) {
    FUN_0064ad70();
  }
  if (*(int *)(param_1 + 0xac) == 0) {
    *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + 1;
    FUN_0065c950();
    FUN_0065b870("data/bgm/titlesemi.ogg");
    FUN_00405290(2);
  }
  FUN_006584e0();
  FUN_006585f0();
  if ((*(int *)(param_1 + 0xac) == 1) && (cVar1 = FUN_0065c9d0(), cVar1 != '\0')) {
    local_8 = 0;
    while( true ) {
      if (3 < local_8) {
        return 0;
      }
      FUN_00657390();
      if (((((&DAT_006cae9c)[local_8 * 0x19] != 0) || ((&DAT_006caea0)[local_8 * 0x19] != 0)) ||
          ((&DAT_006caeb8)[local_8 * 0x19] != 0)) || (cVar1 = FUN_006586d0(1), cVar1 != '\0'))
      break;
      local_8 = local_8 + 1;
    }
    FUN_0065c990();
    FUN_0065b870("data/bgm/title.ogg");
    FUN_00405290(1);
    return 1;
  }
  *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + 1;
  return 1;
}

