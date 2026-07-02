// Function: FUN_00416a20
// Address:  0x00416a20
// Source:   batch_decompile (mass dump)
// Hash:     4618d56fe9897e70


undefined4 __fastcall FUN_00416a20(int param_1)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  int local_c;
  int local_8;
  
  FUN_00416180();
  FUN_00416280(0x12);
  if (*(int *)(param_1 + 0x16c) != 0) {
    local_8 = 0;
    for (local_c = 1; local_c < 8; local_c = local_c + 1) {
      if (*(int *)(param_1 + 0x124 + local_c * 4) != 0) {
        local_8 = local_8 + 1;
      }
    }
    if (local_8 < DAT_006cfdcc) {
      FUN_004176d0();
      FUN_00415d30(0,local_1c,0x10,2);
      return 0x12;
    }
    FUN_00417680();
    FUN_00415d30(0,local_14,0,0x88);
    *(undefined4 *)(param_1 + 0x16c) = 0;
  }
  FUN_00634f60();
  bVar1 = DAT_006cfa2c;
  bVar2 = FUN_00416330();
  if ((bVar1 & bVar2) == 0) {
    cVar3 = FUN_006586d0(0x1c);
    if ((cVar3 != '\0') &&
       ((cVar3 = FUN_006586d0(0xb8), cVar3 != '\0' || (cVar3 = FUN_006586d0(0x38), cVar3 != '\0'))))
    {
      FUN_0064ad70();
    }
    FUN_00640ea0();
    return 0x12;
  }
  FUN_004167c0();
  FUN_00415d30(0,local_24,0,0x88);
  return 0xe;
}

