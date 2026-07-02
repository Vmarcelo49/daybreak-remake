// Function: FUN_0064e130
// Address:  0x0064e130
// Source:   batch_decompile (mass dump)
// Hash:     7862f2f68a0fc3a5


void FUN_0064e130(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = *(int *)(param_1 + 0x44); local_8 != 0; local_8 = *(int *)(local_8 + 0x20)) {
    FUN_0064e110(local_8,param_1);
  }
  if (*(int *)(param_1 + 0x48) != 0) {
    FUN_0064e130(*(undefined4 *)(param_1 + 0x48));
  }
  if (*(int *)(param_1 + 0x4c) != 0) {
    FUN_0064e130(*(undefined4 *)(param_1 + 0x4c));
  }
  return;
}

