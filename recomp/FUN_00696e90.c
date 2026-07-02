// ============================================
// Address:  0x00696e90
// Original: FUN_00696e90
// Status:   unreviewed
// ============================================


int FUN_00696e90(int param_1,undefined8 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00697f90(param_2);
  uVar1 = FUN_00698070(local_c,local_8);
  iVar2 = FUN_00698090(local_c,local_8,uVar1);
  if (iVar2 == 0) {
    iVar2 = (**(code **)(**(int **)(param_1 + 4) + 0xc))();
    if (-1 < iVar2) {
      uVar3 = FUN_00697fc0();
      *(undefined8 *)(param_1 + 0xc) = uVar3;
      iVar2 = (**(code **)(**(int **)(param_1 + 4) + 8))(param_1 + -0xc);
    }
  }
  else {
    iVar2 = -0x7ffbfdcd;
  }
  return iVar2;
}

