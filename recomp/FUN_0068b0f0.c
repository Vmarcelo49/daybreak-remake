// ============================================
// Address:  0x0068b0f0
// Original: FUN_0068b0f0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068b0f0(int param_1,undefined4 *param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  if ((*(uint *)(param_1 + 4) & 0x20) == 0) {
    uVar4 = 0x80040251;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 0x30);
    param_2[1] = *(undefined4 *)(param_1 + 0x34);
    uVar1 = *(uint *)(param_1 + 0x38);
    uVar2 = *(uint *)(param_1 + 0x30);
    iVar3 = *(int *)(param_1 + 0x34);
    *param_3 = uVar1 + *(uint *)(param_1 + 0x30);
    param_3[1] = iVar3 + ((int)uVar1 >> 0x1f) + (uint)CARRY4(uVar1,uVar2);
    uVar4 = 0;
  }
  return uVar4;
}

