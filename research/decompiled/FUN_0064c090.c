// Function: FUN_0064c090
// Address:  0x0064c090
// Source:   batch_decompile (mass dump)
// Hash:     3d720258486acfcd


undefined4 __fastcall FUN_0064c090(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  cVar1 = FUN_006586d0(1);
  if (cVar1 == '\0') {
    *(undefined4 *)(param_1 + 0xa0) = 0;
  }
  else {
    *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + 1;
  }
  if (*(int *)(param_1 + 0xa0) == 1) {
    FUN_0064aed0(0x11);
    *(char *)(param_1 + 0xa5) = '\x01' - (*(char *)(param_1 + 0xa5) != '\0');
  }
  if (*(char *)(param_1 + 0xa5) == '\0') {
    *(undefined1 *)(param_1 + 0xa4) = 1;
    uVar3 = 0;
  }
  else {
    iVar2 = FUN_00403aa0(DAT_006cae94);
    if (iVar2 == 1) {
      uVar4 = (int)*(char *)(param_1 + 0xa4) + 1U & 0x80000001;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
      }
      *(char *)(param_1 + 0xa4) = (char)uVar4;
      FUN_0064aed0(2);
    }
    if (DAT_006caea0 == 1) {
      FUN_0064aed0(1);
      *(undefined1 *)(param_1 + 0xa5) = 0;
    }
    if (DAT_006cae9c == 1) {
      if (*(char *)(param_1 + 0xa4) == '\0') {
        FUN_0064aed0(0);
        *(undefined1 *)(param_1 + 0xa6) = 1;
      }
      else {
        FUN_0064aed0(1);
        *(undefined1 *)(param_1 + 0xa5) = 0;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

