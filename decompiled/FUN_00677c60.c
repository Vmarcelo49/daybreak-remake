// Function: FUN_00677c60
// Address:  0x00677c60
// Source:   batch_decompile (mass dump)
// Hash:     d3a3a31ae6aa63fa


int FUN_00677c60(int *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  puVar1 = (undefined4 *)FUN_0066ef57();
  *puVar1 = 0;
  if (*param_1 == 0) {
    return 0;
  }
  uVar2 = FUN_0069cda0(param_1 + 6,0x2134);
  iVar3 = (*(code *)param_1[0xb0])(uVar2,1,0x2134,*param_1);
  if (0 < iVar3) {
    FUN_0069ce20(param_1 + 6,iVar3);
  }
  if (iVar3 == 0) {
    piVar4 = (int *)FUN_0066ef57();
    if (*piVar4 != 0) {
      return -1;
    }
  }
  return iVar3;
}

