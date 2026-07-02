// ============================================
// Address:  0x0068a2b0
// Original: FUN_0068a2b0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068a2b0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x9c) == 0) {
    uVar1 = 0x80040209;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 0x9c) + 0x18))
                      (*(undefined4 *)(param_1 + 0x9c),param_2);
  }
  return uVar1;
}

