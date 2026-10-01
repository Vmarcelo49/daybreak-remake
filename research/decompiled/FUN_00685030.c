// Function: FUN_00685030
// Address:  0x00685030
// Source:   batch_decompile (mass dump)
// Hash:     4d36f5de6166f30e


uint FUN_00685030(void)

{
  uint uVar1;
  
  uVar1 = __ftol();
  if (0x3ff < (int)uVar1) {
    return 0x3ff;
  }
  return uVar1 & ((int)uVar1 < 0) - 1;
}

