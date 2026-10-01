// Function: FUN_0041d230
// Address:  0x0041d230
// Source:   batch_decompile (mass dump)
// Hash:     a9e321832bfdd29d


undefined4 __fastcall FUN_0041d230(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  cVar1 = FUN_0041af70();
  if ((cVar1 == '\0') && (*(char *)(param_1 + 0x6f0) == '\0')) {
    if (*(int *)(param_1 + 0x6e8) == 1) {
      if (*(int *)(param_1 + 0x6ec) != 0) {
        return 0x11;
      }
    }
    else if (*(int *)(param_1 + 0x6e8) == 0) {
      iVar3 = FUN_00411ae0();
      if (iVar3 == 9) {
        return 0x11;
      }
      *(undefined4 *)(param_1 + 0x6e8) = 1;
      return 0x11;
    }
    if (*(char *)(param_1 + 0x6f0) == '\0') {
      uVar2 = 0x13;
    }
    else {
      FUN_0065f8b0();
      if (*(int *)(param_1 + 0x6e8) == 1) {
        FUN_00648cf0();
      }
      FUN_0065b870("data/bgm/title.ogg");
      uVar2 = 0xb;
    }
  }
  else {
    FUN_0065f8b0();
    if (*(int *)(param_1 + 0x6e8) == 1) {
      FUN_00648cf0();
    }
    FUN_0065b870("data/bgm/title.ogg");
    uVar2 = 0xb;
  }
  return uVar2;
}

