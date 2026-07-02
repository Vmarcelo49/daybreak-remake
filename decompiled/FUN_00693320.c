// Function: FUN_00693320
// Address:  0x00693320
// Source:   batch_decompile (mass dump)
// Hash:     48404bc0c01fa5b6


bool __thiscall FUN_00693320(undefined4 *param_1,DWORD param_2)

{
  DWORD DVar1;
  
  DVar1 = WaitForSingleObject((HANDLE)*param_1,param_2);
  return DVar1 == 0;
}

