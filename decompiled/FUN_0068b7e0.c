// Function: FUN_0068b7e0
// Address:  0x0068b7e0
// Source:   batch_decompile (mass dump)
// Hash:     8a1afd2f1a5b72b5


void __fastcall FUN_0068b7e0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069f660;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006ad370;
  param_1[3] = &PTR_FUN_006ad328;
  param_1[4] = &PTR_LAB_006ad310;
  param_1[0x28] = &PTR_LAB_006ad300;
  local_8 = 0;
  if (param_1[0x2f] != 0) {
    CloseHandle((HANDLE)param_1[0x2f]);
  }
  if (param_1[0x30] != 0) {
    CloseHandle((HANDLE)param_1[0x30]);
  }
  FUN_0068dbb0();
  local_8 = 0xffffffff;
  FUN_0068dbe0();
  ExceptionList = local_10;
  return;
}

