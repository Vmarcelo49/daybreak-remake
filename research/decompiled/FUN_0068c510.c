// Function: FUN_0068c510
// Address:  0x0068c510
// Source:   batch_decompile (mass dump)
// Hash:     3aafbd574e863715


undefined4 FUN_0068c510(HANDLE param_1)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  DVar1 = WaitForSingleObject(param_1,0xffffffff);
  if (DVar1 == 0) {
    uVar2 = 0;
  }
  else if (DVar1 == 0xffffffff) {
    uVar2 = FUN_00693210(0xffffffff,uVar2);
  }
  else {
    uVar2 = 0x8000ffff;
  }
  return uVar2;
}

