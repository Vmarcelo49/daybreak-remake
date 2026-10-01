// Function: FUN_0067c170
// Address:  0x0067c170
// Source:   batch_decompile (mass dump)
// Hash:     4bdf4f44befecbc9


void FUN_0067c170(float *param_1,float param_2)

{
  int iVar1;
  
  iVar1 = 0x38;
  do {
    iVar1 = iVar1 + -1;
    *param_1 = param_2 + *param_1;
    param_1 = param_1 + 1;
  } while (iVar1 != 0);
  return;
}

