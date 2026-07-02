// Function: FUN_0069d6f0
// Address:  0x0069d6f0
// Source:   batch_decompile (mass dump)
// Hash:     2d409198e10b089f


void FUN_0069d6f0(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_2 + param_1[1];
  param_1[1] = uVar2 & 7;
  iVar1 = (int)(uVar2 + ((int)uVar2 >> 0x1f & 7U)) >> 3;
  param_1[3] = param_1[3] + iVar1;
  *param_1 = *param_1 + iVar1;
  return;
}

