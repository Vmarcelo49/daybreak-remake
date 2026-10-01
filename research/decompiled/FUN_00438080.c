// Function: FUN_00438080
// Address:  0x00438080
// Source:   batch_decompile (mass dump)
// Hash:     862d41e4d949a77e


int __thiscall FUN_00438080(int param_1,int param_2)

{
  undefined4 local_c;
  
  if (*(uint *)(param_1 + 4) < *(uint *)(param_2 + 4)) {
    local_c = -(*(int *)(param_2 + 4) - *(int *)(param_1 + 4));
  }
  else {
    local_c = *(int *)(param_1 + 4) - *(int *)(param_2 + 4);
  }
  return local_c;
}

