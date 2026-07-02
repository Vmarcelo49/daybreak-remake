// Function: FUN_00653730
// Address:  0x00653730
// Source:   batch_decompile (mass dump)
// Hash:     1f8026c162adb7f9


bool __fastcall FUN_00653730(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = param_1[0x1f];
  if (iVar1 == 0) {
    CloseHandle((HANDLE)*param_1);
    *param_1 = 0;
  }
  return iVar1 == 0;
}

