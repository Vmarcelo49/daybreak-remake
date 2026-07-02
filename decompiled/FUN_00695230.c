// Function: FUN_00695230
// Address:  0x00695230
// Source:   batch_decompile (mass dump)
// Hash:     b0ea6d7d9cd5a207


int FUN_00695230(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x28))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

