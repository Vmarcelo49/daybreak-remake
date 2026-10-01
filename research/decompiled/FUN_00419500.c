// Function: FUN_00419500
// Address:  0x00419500
// Source:   batch_decompile (mass dump)
// Hash:     ef194877c079b01a


undefined4 __fastcall FUN_00419500(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_10 [8];
  undefined4 local_8;
  
  FUN_00416180();
  if (*(int *)(param_1 + 0x74c) == 1) {
    FUN_00416280(0x10);
    cVar1 = FUN_00416330();
    if (cVar1 == '\0') {
      uVar2 = 0x10;
    }
    else {
      FUN_00416410();
      local_8 = 0x12;
      FUN_00415d30(0,local_10,0,8);
      uVar2 = 0x12;
    }
  }
  else {
    iVar3 = FUN_00411ae0();
    if (iVar3 == 9) {
      uVar2 = 0x10;
    }
    else {
      *(undefined4 *)(param_1 + 0x74c) = 1;
      uVar2 = 0x10;
    }
  }
  return uVar2;
}

