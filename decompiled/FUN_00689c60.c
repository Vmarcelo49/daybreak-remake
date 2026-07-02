// Function: FUN_00689c60
// Address:  0x00689c60
// Source:   batch_decompile (mass dump)
// Hash:     9afc3abba0f3784d


undefined4 FUN_00689c60(int param_1,int *param_2)

{
  undefined4 uVar1;
  int local_8;
  
  if (param_2 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    if (*(int *)(param_1 + 0x1c) == 0) {
      local_8 = 0;
    }
    else {
      local_8 = *(int *)(param_1 + 0x1c) + 0xc;
    }
    *param_2 = local_8;
    if (*(int *)(param_1 + 0x1c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0xc) + 4))(*(int *)(param_1 + 0x1c) + 0xc);
    }
    if (*(int *)(param_1 + 8) == 0) {
      *(undefined2 *)(param_2 + 2) = 0;
    }
    else {
      FUN_00692460(param_2 + 2,*(undefined4 *)(param_1 + 8),0x80);
    }
    param_2[1] = *(int *)(param_1 + 0x10);
    uVar1 = 0;
  }
  return uVar1;
}

