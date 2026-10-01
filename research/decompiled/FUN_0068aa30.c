// Function: FUN_0068aa30
// Address:  0x0068aa30
// Source:   batch_decompile (mass dump)
// Hash:     e73120bb5d61dd4b


uint FUN_0068aa30(int param_1)

{
  int *local_24;
  int *local_20;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = (**(code **)(**(int **)(param_1 + -0x70) + 0x18))();
  local_8 = 0;
  local_10 = 0;
  do {
    if (local_c <= local_10) {
      return (uint)(local_8 != 0);
    }
    local_18 = (**(code **)(**(int **)(param_1 + -0x70) + 0x1c))(local_10);
    local_1c = (**(code **)(*(int *)(local_18 + 0xc) + 0x24))(local_18 + 0xc,&local_14);
    if ((int)local_1c < 0) {
      return local_1c;
    }
    if ((local_14 == 1) &&
       (local_1c = (**(code **)(*(int *)(local_18 + 0xc) + 0x18))(local_18 + 0xc,&local_20),
       -1 < (int)local_1c)) {
      local_8 = local_8 + 1;
      local_1c = (**(code **)*local_20)(local_20,&LAB_006ad003_1,&local_24);
      (**(code **)(*local_20 + 8))(local_20);
      if ((int)local_1c < 0) {
        return 0;
      }
      local_1c = (**(code **)(*local_24 + 0x20))(local_24);
      (**(code **)(*local_24 + 8))(local_24);
      if (local_1c != 1) {
        return 0;
      }
    }
    local_10 = local_10 + 1;
  } while( true );
}

