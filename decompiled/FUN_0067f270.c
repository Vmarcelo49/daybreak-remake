// Function: FUN_0067f270
// Address:  0x0067f270
// Source:   batch_decompile (mass dump)
// Hash:     579017c8e2d547e0


void FUN_0067f270(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      _free((void *)*param_1);
    }
    if ((void *)param_1[1] != (void *)0x0) {
      _free((void *)param_1[1]);
    }
    if ((void *)param_1[5] != (void *)0x0) {
      _free((void *)param_1[5]);
    }
    if ((void *)param_1[0xc] != (void *)0x0) {
      _free((void *)param_1[0xc]);
    }
    if ((void *)param_1[0xd] != (void *)0x0) {
      _free((void *)param_1[0xd]);
    }
    if ((void *)param_1[0xe] != (void *)0x0) {
      _free((void *)param_1[0xe]);
    }
    if (param_1[0x18] != 0) {
      if (param_1[2] == 0) {
        FUN_0069d5e0(param_1[0x18]);
      }
      else {
        iVar1 = 0;
        if (0 < (int)param_1[2]) {
          iVar2 = 0;
          do {
            FUN_0069d5e0(iVar2 + param_1[0x18]);
            iVar1 = iVar1 + 1;
            iVar2 = iVar2 + 0x14;
          } while (iVar1 < (int)param_1[2]);
        }
      }
      _free((void *)param_1[0x18]);
    }
    if ((void *)param_1[0x19] != (void *)0x0) {
      _free((void *)param_1[0x19]);
    }
    for (iVar1 = 0x1a; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_1 = 0;
      param_1 = param_1 + 1;
    }
  }
  return;
}

