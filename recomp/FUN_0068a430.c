// ============================================
// Address:  0x0068a430
// Original: FUN_0068a430
// Status:   unreviewed
// ============================================


undefined4 __thiscall
FUN_0068a430(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined8 param_6)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0x80040209;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0x44))
                      (*(undefined4 *)(param_1 + 0x18),param_2,param_3,param_4,param_5,param_6);
  }
  return uVar1;
}

