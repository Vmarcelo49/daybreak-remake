// ============================================
// Address:  0x00695140
// Original: FUN_00695140
// Status:   unreviewed
// ============================================


int FUN_00695140(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x1c))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

