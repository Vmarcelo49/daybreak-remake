// ============================================
// Address:  0x00694410
// Original: FUN_00694410
// Status:   unreviewed
// ============================================


int FUN_00694410(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int local_c;
  int *local_8;
  
  local_c = FUN_006942c0(param_1,param_2,0,param_5,&local_8);
  if (-1 < local_c) {
    local_c = (**(code **)(*local_8 + 0x28))(local_8,param_3,param_4,param_6);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return local_c;
}

