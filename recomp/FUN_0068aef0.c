// ============================================
// Address:  0x0068aef0
// Original: FUN_0068aef0
// Status:   unreviewed
// ============================================


int FUN_0068aef0(int *param_1)

{
  int local_8;
  
  if (param_1[0x11] == 1) {
    local_8 = 0;
    param_1[0x11] = 0;
  }
  else {
    local_8 = InterlockedDecrement(param_1 + 0x11);
  }
  if (local_8 == 0) {
    if ((param_1[1] & 8U) != 0) {
      (**(code **)(*param_1 + 0x38))(param_1,0);
    }
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[0x10] = 0;
    (**(code **)(*(int *)(param_1[6] + 0xc) + 0x20))(param_1[6] + 0xc,param_1);
  }
  return local_8;
}

