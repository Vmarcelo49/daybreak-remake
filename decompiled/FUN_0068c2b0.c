// Function: FUN_0068c2b0
// Address:  0x0068c2b0
// Source:   batch_decompile (mass dump)
// Hash:     d02d92a998454d43


int __thiscall FUN_0068c2b0(int *param_1,undefined4 param_2)

{
  int iVar1;
  int *local_20;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    local_20 = (int *)0x0;
  }
  else {
    local_20 = param_1 + 3;
  }
  local_8 = (**(code **)(*(int *)param_1[6] + 0x10))(param_1[6],local_20,param_2);
  if ((-1 < local_8) && (local_8 = (**(code **)(*param_1 + 0x24))(param_2), -1 < local_8)) {
    if (param_1[0x27] != 0) {
      local_10 = 0;
      local_14 = 0;
      local_c = 0;
      local_18 = 0;
      (**(code **)(*(int *)param_1[0x27] + 0x14))(param_1[0x27],&local_18);
      if (local_10 == 0) {
        local_10 = 1;
      }
      local_8 = (**(code **)(*(int *)param_1[0x26] + 0x18))(param_1[0x26]);
      if (local_8 < 0) {
        return local_8;
      }
      local_8 = (**(code **)(*param_1 + 0x3c))(param_1[0x26],&local_18);
      if (local_8 < 0) {
        return local_8;
      }
      local_8 = (**(code **)(*(int *)param_1[0x26] + 0x14))(param_1[0x26]);
      if (local_8 < 0) {
        return local_8;
      }
      iVar1 = (**(code **)(*(int *)param_1[0x27] + 0x10))(param_1[0x27],param_1[0x26],param_1[0x36])
      ;
      if (iVar1 < 0) {
        return iVar1;
      }
    }
    local_8 = 0;
  }
  return local_8;
}

