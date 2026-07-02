// Function: FUN_00699de0
// Address:  0x00699de0
// Source:   batch_decompile (mass dump)
// Hash:     e5a24b704d70d51f


undefined4 __fastcall FUN_00699de0(undefined4 param_1)

{
  DWORD DVar1;
  HANDLE local_c;
  undefined4 local_8;
  
  local_c = (HANDLE)FUN_0068de10(param_1);
  local_8 = FUN_0068de10();
  while( true ) {
    DVar1 = WaitForMultipleObjects(2,&local_c,0,0xffffffff);
    if (DVar1 != 1) break;
    FUN_00699ce0();
  }
  return 0;
}

