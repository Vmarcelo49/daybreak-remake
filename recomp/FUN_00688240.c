// ============================================
// Address:  0x00688240
// Original: FUN_00688240
// Status:   unreviewed
// ============================================


undefined4 FUN_00688240(int param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined2 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    if (*(int *)(param_1 + 0x30) == 0) {
      *param_2 = 0;
    }
    else {
      FUN_00692460(param_2,*(undefined4 *)(param_1 + 0x30),0x80);
    }
    *(undefined4 *)(param_2 + 0x80) = *(undefined4 *)(param_1 + 0x34);
    if (*(int *)(param_1 + 0x34) != 0) {
      (**(code **)(**(int **)(param_1 + 0x34) + 4))(*(undefined4 *)(param_1 + 0x34));
    }
    uVar1 = 0;
  }
  return uVar1;
}

