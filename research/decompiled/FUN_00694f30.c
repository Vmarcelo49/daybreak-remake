// Function: FUN_00694f30
// Address:  0x00694f30
// Source:   batch_decompile (mass dump)
// Hash:     3100a572baf47c6a


int FUN_00694f30(code *param_1,undefined4 param_2)

{
  undefined4 extraout_var;
  int local_c;
  int *local_8;
  
  local_c = FUN_00694b70(&local_8);
  if (-1 < local_c) {
    local_c = (*param_1)(local_8,param_2,extraout_var);
    (**(code **)(*local_8 + 8))(local_8);
  }
  return local_c;
}

