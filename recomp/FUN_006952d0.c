// ============================================
// Address:  0x006952d0
// Original: FUN_006952d0
// Status:   unreviewed
// ============================================


int FUN_006952d0(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x30))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

