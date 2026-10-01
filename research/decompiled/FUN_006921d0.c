// Function: FUN_006921d0
// Address:  0x006921d0
// Source:   batch_decompile (mass dump)
// Hash:     1029d4396edb70de


void __fastcall FUN_006921d0(int param_1)

{
  void *_Memory;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069fb5b;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 8) != 0) {
    ExceptionList = &local_10;
    WaitForSingleObject(*(HANDLE *)(param_1 + 8),0xffffffff);
    CloseHandle(*(HANDLE *)(param_1 + 8));
  }
  local_14 = FUN_0068de10();
  while (local_14 != 0) {
    _Memory = (void *)FUN_006981d0(&local_14);
    _free(_Memory);
  }
  FUN_00693630();
  if (*(int *)(param_1 + 0x3c) != 0) {
    CloseHandle(*(HANDLE *)(param_1 + 0x3c));
  }
  local_8 = local_8 & 0xffffff00;
  FUN_0068dbb0();
  local_8 = 0xffffffff;
  FUN_00693440();
  ExceptionList = local_10;
  return;
}

