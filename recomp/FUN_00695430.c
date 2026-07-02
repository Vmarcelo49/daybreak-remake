// ============================================
// Address:  0x00695430
// Original: FUN_00695430
// Status:   unreviewed
// ============================================


int FUN_00695430(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x40))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

