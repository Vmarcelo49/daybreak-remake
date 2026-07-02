// ============================================
// Address:  0x00657c80
// Original: FUN_00657c80
// Status:   unreviewed
// ============================================


void __thiscall FUN_00657c80(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == DAT_006b77b8) {
    if (*(int *)(param_1 + 0x60) != 0) {
      *(undefined4 *)(param_1 + 100) = 1;
      *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + -1;
      if (*(int *)(param_1 + 0x60) < 0x18) {
        if (*(int *)(param_1 + 0x68) == 2) {
          FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000 | 0xffffff);
        }
        else {
          FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000);
        }
      }
      else if (*(int *)(param_1 + 0x68) == 2) {
        FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000 | 0xffffff);
      }
      else {
        FUN_00650d50(0xff000000);
      }
    }
  }
  else {
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
    if (*(int *)(param_1 + 0x60) < 0x19) {
      *(undefined4 *)(param_1 + 100) = 0;
      if (*(int *)(param_1 + 0x68) == 2) {
        FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000 | 0xffffff);
      }
      else {
        FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x60) = 0x19;
      if (*(int *)(param_1 + 0x68) == 2) {
        FUN_00650d50((*(int *)(param_1 + 0x60) * 10 + 5) * 0x1000000 | 0xffffff);
      }
      else {
        FUN_00650d50(0xff000000);
      }
      FUN_0065d670();
      if (*(int *)(param_1 + 0x3c) != 0) {
        if (*(undefined4 **)(param_1 + 0x3c) != (undefined4 *)0x0) {
          (**(code **)**(undefined4 **)(param_1 + 0x3c))(1);
        }
        *(undefined4 *)(param_1 + 0x3c) = 0;
      }
      uVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 8))(param_2);
      *(undefined4 *)(param_1 + 0x3c) = uVar1;
      FUN_00654170(0);
      FUN_00656300(param_1);
      FUN_0065d6a0();
      DAT_006b77b8 = param_2;
    }
  }
  return;
}

