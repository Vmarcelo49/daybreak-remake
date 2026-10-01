// Function: FUN_00695190
// Address:  0x00695190
// Source:   batch_decompile (mass dump)
// Hash:     b069455ec4aeb85e


int FUN_00695190(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x24))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

