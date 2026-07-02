// Function: FUN_00689470
// Address:  0x00689470
// Source:   batch_decompile (mass dump)
// Hash:     b5a7c3c45cda5927


int __thiscall FUN_00689470(int *param_1,int *param_2,undefined4 param_3)

{
  int *local_10;
  int local_8;
  
  local_8 = (**(code **)(*param_1 + 0x28))(param_2);
  if (local_8 < 0) {
    (**(code **)(*param_1 + 0x2c))();
  }
  else {
    FUN_0068da70(param_2,param_3);
    local_8 = (**(code **)(*param_1 + 0x20))(param_3);
    if (local_8 == 0) {
      param_1[6] = (int)param_2;
      (**(code **)(*(int *)param_1[6] + 4))(param_1[6]);
      local_8 = (**(code **)(*param_1 + 0x24))(param_3);
      if (-1 < local_8) {
        if (param_1 == (int *)0x0) {
          local_10 = (int *)0x0;
        }
        else {
          local_10 = param_1 + 3;
        }
        local_8 = (**(code **)(*param_2 + 0x10))(param_2,local_10,param_3);
        if (-1 < local_8) {
          local_8 = (**(code **)(*param_1 + 0x30))(param_2);
          if (-1 < local_8) {
            return local_8;
          }
          (**(code **)(*param_2 + 0x14))(param_2);
        }
      }
    }
    else if (((-1 < local_8) || (local_8 == -0x7fffbffb)) || (local_8 == -0x7ff8ffa9)) {
      local_8 = -0x7ffbfdd6;
    }
    (**(code **)(*param_1 + 0x2c))();
    if (param_1[6] != 0) {
      (**(code **)(*(int *)param_1[6] + 8))(param_1[6]);
      param_1[6] = 0;
    }
  }
  return local_8;
}

