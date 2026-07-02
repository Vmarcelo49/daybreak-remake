// Function: FUN_006999e0
// Address:  0x006999e0
// Source:   batch_decompile (mass dump)
// Hash:     276f8a1eabd0efd6


DWORD __fastcall FUN_006999e0(LPVOID param_1)

{
  DWORD DVar1;
  HANDLE pvVar2;
  DWORD local_8;
  
  if (*(int *)((int)param_1 + 0x80) == 0) {
    FUN_006919c0();
    pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00699fa0,param_1,0,&local_8);
    *(HANDLE *)((int)param_1 + 0x80) = pvVar2;
    if (*(int *)((int)param_1 + 0x80) == 0) {
      DVar1 = GetLastError();
      if (0 < (int)DVar1) {
        DVar1 = DVar1 & 0xffff | 0x80070000;
      }
    }
    else {
      DVar1 = 0;
    }
  }
  else {
    DVar1 = 0;
  }
  return DVar1;
}

