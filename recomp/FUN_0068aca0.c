// ============================================
// Address:  0x0068aca0
// Original: FUN_0068aca0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068aca0(int param_1,undefined4 *param_2)

{
  int local_18;
  int local_14;
  undefined4 local_c;
  int *local_8;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    local_c = 0x80040216;
    if ((*(int *)(param_1 + 0x18) != 0) &&
       ((**(code **)**(undefined4 **)(param_1 + 0x18))
                  (*(undefined4 *)(param_1 + 0x18),&DAT_006acfc4,&local_8), local_8 != (int *)0x0))
    {
      if (*(int *)(param_1 + 0x28) == 0) {
        local_18 = 0;
      }
      else {
        local_18 = *(int *)(param_1 + 0x28) + 0xc;
      }
      local_c = (**(code **)(*local_8 + 0xc))
                          (local_8,local_18,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],
                           param_2[5]);
      (**(code **)(*local_8 + 8))(local_8);
    }
  }
  else {
    if (*(int *)(param_1 + 0x28) == 0) {
      local_14 = 0;
    }
    else {
      local_14 = *(int *)(param_1 + 0x28) + 0xc;
    }
    local_c = (**(code **)(**(int **)(param_1 + 0x2c) + 0xc))
                        (*(undefined4 *)(param_1 + 0x2c),local_14,*param_2,param_2[1],param_2[2],
                         param_2[3],param_2[4],param_2[5]);
  }
  return local_c;
}

