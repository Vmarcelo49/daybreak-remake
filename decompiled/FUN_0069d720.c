// Function: FUN_0069d720
// Address:  0x0069d720
// Source:   batch_decompile (mass dump)
// Hash:     66f300c1dc1a582a


uint FUN_0069d720(int *param_1,int param_2)

{
  byte *pbVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar3 = param_1[1];
  uVar4 = param_2 + iVar3;
  if ((*param_1 + 4 < param_1[4]) ||
     (uVar5 = 0xffffffff, (int)(uVar4 + *param_1 * 8) <= param_1[4] * 8)) {
    pbVar1 = (byte *)param_1[3];
    uVar5 = (uint)(*pbVar1 >> (*(byte *)(param_1 + 1) & 0x1f));
    if (((8 < (int)uVar4) &&
        (((cVar2 = (char)iVar3, uVar5 = uVar5 | (uint)pbVar1[1] << (8U - cVar2 & 0x1f),
          0x10 < (int)uVar4 &&
          (uVar5 = uVar5 | (uint)pbVar1[2] << (0x10U - cVar2 & 0x1f), 0x18 < (int)uVar4)) &&
         (uVar5 = uVar5 | (uint)pbVar1[3] << (0x18U - cVar2 & 0x1f), 0x20 < (int)uVar4)))) &&
       (iVar3 != 0)) {
      uVar5 = uVar5 | (uint)pbVar1[4] << (0x20U - cVar2 & 0x1f);
    }
    uVar5 = uVar5 & *(uint *)(&DAT_006c77d8 + param_2 * 4);
  }
  param_1[1] = uVar4 & 7;
  iVar3 = (int)(uVar4 + ((int)uVar4 >> 0x1f & 7U)) >> 3;
  param_1[3] = param_1[3] + iVar3;
  *param_1 = iVar3 + *param_1;
  return uVar5;
}

