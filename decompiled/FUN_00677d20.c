// Function: FUN_00677d20
// Address:  0x00677d20
// Source:   batch_decompile (mass dump)
// Hash:     d57887eaf107f6a2


undefined4 FUN_00677d20(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined1 auStack_10 [16];
  
  uVar4 = param_1[2];
  uVar1 = param_1[3];
  iVar3 = param_1[0x17];
  (*(code *)param_1[0xb1])(*param_1,0,0,2);
  iVar2 = (*(code *)param_1[0xb3])(*param_1);
  param_1[4] = iVar2;
  param_1[5] = iVar2 >> 0x1f;
  param_1[2] = param_1[4];
  param_1[3] = iVar2 >> 0x1f;
  lVar5 = FUN_00677e20(param_1,auStack_10);
  if ((lVar5 < 0x100000000) && (lVar5 < 0)) {
    return (int)lVar5;
  }
  iVar2 = FUN_0069cb00(auStack_10);
  if (iVar2 == iVar3) {
    iVar3 = FUN_00677f80(param_1,0,0,lVar5,lVar5 + 1,iVar3,0);
    if (iVar3 != 0) {
      return 0xffffff80;
    }
  }
  else {
    iVar3 = FUN_00677f80(param_1,0,0,0,0,lVar5 + 1,iVar3,0);
    if (iVar3 < 0) {
      return 0xffffff80;
    }
  }
  FUN_006781a0(param_1,uVar4,uVar1);
  uVar4 = FUN_006785b0(param_1,0,0);
  return uVar4;
}

