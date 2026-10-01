// Function: FUN_0069d640
// Address:  0x0069d640
// Source:   batch_decompile (mass dump)
// Hash:     ba8c9a6417fcaf75


uint FUN_0069d640(int *param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  
  iVar1 = param_1[1];
  iVar5 = param_2 + iVar1;
  if ((param_1[4] <= *param_1 + 4) && (param_1[4] * 8 < iVar5 + *param_1 * 8)) {
    return 0xffffffff;
  }
  pbVar2 = (byte *)param_1[3];
  uVar4 = (uint)(*pbVar2 >> (*(byte *)(param_1 + 1) & 0x1f));
  if (((8 < iVar5) &&
      (((cVar3 = (char)iVar1, uVar4 = uVar4 | (uint)pbVar2[1] << (8U - cVar3 & 0x1f), 0x10 < iVar5
        && (uVar4 = uVar4 | (uint)pbVar2[2] << (0x10U - cVar3 & 0x1f), 0x18 < iVar5)) &&
       (uVar4 = uVar4 | (uint)pbVar2[3] << (0x18U - cVar3 & 0x1f), 0x20 < iVar5)))) && (iVar1 != 0))
  {
    uVar4 = uVar4 | (uint)pbVar2[4] << (0x20U - cVar3 & 0x1f);
  }
  return uVar4 & *(uint *)(&DAT_006c77d8 + param_2 * 4);
}

