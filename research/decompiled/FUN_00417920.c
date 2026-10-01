// Function: FUN_00417920
// Address:  0x00417920
// Source:   batch_decompile (mass dump)
// Hash:     b9f333e67b1212a9


void __thiscall FUN_00417920(int param_1,int param_2)

{
  int local_c;
  char *local_8;
  
  local_8 = (char *)(param_2 + 1);
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(int *)(param_1 + 8 + local_c * 4) = (int)*local_8;
    *(int *)(param_1 + 0x18 + local_c * 4) = (int)local_8[1];
    *(int *)(param_1 + 0x28 + local_c * 4) = (int)local_8[2];
    *(int *)(param_1 + 0x38 + local_c * 4) = (int)local_8[3];
    *(int *)(param_1 + 0x48 + local_c * 4) = (int)local_8[4];
    *(int *)(param_1 + 0x58 + local_c * 4) = (int)local_8[5];
    local_8 = local_8 + 6;
  }
  *(int *)(param_1 + 0x68) = (int)*local_8;
  *(int *)(param_1 + 0x6c) = (int)*(short *)(local_8 + 1);
  *(int *)(param_1 + 0x70) = (int)*(short *)(local_8 + 3);
  *(int *)(param_1 + 0x74) = (int)*(short *)(local_8 + 5);
  *(int *)(param_1 + 0x78) = (int)*(short *)(local_8 + 7);
  *(int *)(param_1 + 0x7c) = (int)*(short *)(local_8 + 9);
  return;
}

