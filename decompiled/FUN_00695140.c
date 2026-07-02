// Function: FUN_00695140
// Address:  0x00695140
// Source:   batch_decompile (mass dump)
// Hash:     d2803a0969f4ccde


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

