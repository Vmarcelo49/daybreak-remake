// ============================================
// Address:  0x00684df0
// Original: FUN_00684df0
// Status:   unreviewed
// ============================================


int FUN_00684df0(int param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  
  param_3 = param_3 & 0x7fff;
  uVar2 = (param_4 & 0x7fff) - param_3;
  iVar1 = (int)(((uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)) * (param_5 - param_1)) /
          (param_2 - param_1);
  if ((int)uVar2 < 0) {
    return param_3 - iVar1;
  }
  return iVar1 + param_3;
}

