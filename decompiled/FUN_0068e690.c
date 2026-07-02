// Function: FUN_0068e690
// Address:  0x0068e690
// Source:   batch_decompile (mass dump)
// Hash:     c2db8c3c6b85f4f8


undefined4 __fastcall FUN_0068e690(int *param_1)

{
  undefined4 uVar1;
  HANDLE local_10;
  undefined4 local_c;
  DWORD local_8;
  
  local_10 = (HANDLE)FUN_0068de10();
  local_c = FUN_0068de10();
  local_8 = 0x102;
  (**(code **)(*param_1 + 0x48))();
  while (local_8 == 0x102) {
    local_8 = WaitForMultipleObjects(2,&local_10,0,10000);
  }
  (**(code **)(*param_1 + 0x4c))();
  if (local_8 == 0) {
    uVar1 = 0x80040223;
  }
  else {
    FUN_0068f210();
    uVar1 = 0;
  }
  return uVar1;
}

