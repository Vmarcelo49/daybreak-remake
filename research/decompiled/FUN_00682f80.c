// Function: FUN_00682f80
// Address:  0x00682f80
// Source:   batch_decompile (mass dump)
// Hash:     c491457a5db9c175


int FUN_00682f80(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 >> 1) {
    iVar1 = iVar1 + (param_1 & 1);
  }
  return iVar1;
}

