// Function: FUN_00653860
// Address:  0x00653860
// Source:   batch_decompile (mass dump)
// Hash:     5bbd1a9ec0aca9eb


undefined4 __fastcall FUN_00653860(undefined4 *param_1)

{
  undefined4 local_8;
  
  local_8 = 0;
  if (param_1[0x1f] == 0) {
    ReadFile((HANDLE)*param_1,&local_8,4,param_1 + 1,(LPOVERLAPPED)0x0);
  }
  else {
    FUN_00663030(&local_8,4);
  }
  return local_8;
}

