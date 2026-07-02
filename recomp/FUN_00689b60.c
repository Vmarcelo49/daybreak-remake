// ============================================
// Address:  0x00689b60
// Original: FUN_00689b60
// Status:   unreviewed
// ============================================


undefined4 FUN_00689b60(int param_1,int *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  if (param_2 == (int *)0x0) {
    uVar2 = 0x80004003;
  }
  else {
    piVar1 = *(int **)(param_1 + 0xc);
    *param_2 = (int)piVar1;
    if (piVar1 == (int *)0x0) {
      uVar2 = 0x80040209;
    }
    else {
      (**(code **)(*piVar1 + 4))(piVar1);
      uVar2 = 0;
    }
  }
  return uVar2;
}

