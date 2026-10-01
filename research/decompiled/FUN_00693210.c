// Function: FUN_00693210
// Address:  0x00693210
// Source:   batch_decompile (mass dump)
// Hash:     0841e235123922f0


DWORD FUN_00693210(void)

{
  DWORD DVar1;
  
  DVar1 = GetLastError();
  if (DVar1 == 0) {
    DVar1 = 0x80004005;
  }
  else if (0 < (int)DVar1) {
    DVar1 = DVar1 & 0xffff | 0x80070000;
  }
  return DVar1;
}

