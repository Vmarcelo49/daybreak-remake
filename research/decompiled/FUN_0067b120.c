// Function: FUN_0067b120
// Address:  0x0067b120
// Source:   batch_decompile (mass dump)
// Hash:     876da9dfbd367d5c


undefined4 FUN_0067b120(int param_1,int param_2)

{
  if ((param_2 != 0) && (*(int *)(param_1 + 0x14) < *(int *)(param_1 + 0x18) + param_2)) {
    return 0xffffff7d;
  }
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + param_2;
  return 0;
}

