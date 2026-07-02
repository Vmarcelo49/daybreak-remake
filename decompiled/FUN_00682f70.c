// Function: FUN_00682f70
// Address:  0x00682f70
// Source:   batch_decompile (mass dump)
// Hash:     d10d6344d16f1a69


int FUN_00682f70(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 >> 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

