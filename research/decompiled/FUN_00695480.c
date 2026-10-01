// Function: FUN_00695480
// Address:  0x00695480
// Source:   batch_decompile (mass dump)
// Hash:     799af8d1ad1362d2


int FUN_00695480(undefined4 param_1,undefined4 param_2)

{
  int *local_c;
  int local_8;
  
  local_8 = FUN_00694af0(&local_c);
  if (-1 < local_8) {
    local_8 = (**(code **)(*local_c + 0x44))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return local_8;
}

