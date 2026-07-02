// Function: FUN_00679f10
// Address:  0x00679f10
// Source:   batch_decompile (mass dump)
// Hash:     991bca42b718923c


undefined4 FUN_00679f10(int *param_1,undefined4 param_2)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  
  iVar1 = FUN_0069d720(param_2,0x20);
  if (-1 < iVar1) {
    pvVar2 = _calloc(iVar1 + 1,1);
    param_1[3] = (int)pvVar2;
    FUN_00679e00(param_2,pvVar2,iVar1);
    iVar1 = FUN_0069d720(param_2,0x20);
    param_1[2] = iVar1;
    if (-1 < iVar1) {
      pvVar2 = _calloc(iVar1 + 1,4);
      *param_1 = (int)pvVar2;
      pvVar2 = _calloc(param_1[2] + 1,4);
      param_1[1] = (int)pvVar2;
      iVar1 = 0;
      if (0 < param_1[2]) {
        do {
          iVar3 = FUN_0069d720(param_2,0x20);
          if (iVar3 < 0) goto LAB_00679fce;
          *(int *)(param_1[1] + iVar1 * 4) = iVar3;
          pvVar2 = _calloc(iVar3 + 1,1);
          *(void **)(*param_1 + iVar1 * 4) = pvVar2;
          FUN_00679e00(param_2,*(undefined4 *)(*param_1 + iVar1 * 4),iVar3);
          iVar1 = iVar1 + 1;
        } while (iVar1 < param_1[2]);
      }
      iVar1 = FUN_0069d720(param_2,1);
      if (iVar1 == 1) {
        return 0;
      }
    }
  }
LAB_00679fce:
  FUN_00679ad0(param_1);
  return 0xffffff7b;
}

