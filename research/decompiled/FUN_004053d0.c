// Function: FUN_004053d0
// Address:  0x004053d0
// Source:   batch_decompile (mass dump)
// Hash:     4f0c45d9be36ac58


undefined4 __fastcall FUN_004053d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int local_8;
  
  cVar1 = FUN_00405250();
  if (cVar1 == '\0') {
    if (*(int *)(param_1 + 4) == 0) {
      FUN_0065c950();
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_0065c9d0();
    if (cVar1 == '\0') {
      uVar2 = 0x15;
    }
    else {
      for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
        FUN_00657390();
        if ((&DAT_006caeb8)[local_8 * 0x19] == 1) {
          FUN_0065c990();
          return 0x15;
        }
      }
      uVar2 = 2;
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

