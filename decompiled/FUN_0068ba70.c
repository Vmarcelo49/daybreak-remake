// Function: FUN_0068ba70
// Address:  0x0068ba70
// Source:   batch_decompile (mass dump)
// Hash:     bc7f0be23b963603


int FUN_0068ba70(void)

{
  HANDLE hObject;
  int iVar1;
  undefined4 extraout_var;
  
  hObject = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  if (hObject == (HANDLE)0x0) {
    iVar1 = FUN_00693210(extraout_var);
  }
  else {
    iVar1 = FUN_0068baf0(hObject);
    if (iVar1 < 0) {
      CloseHandle(hObject);
    }
    else {
      iVar1 = FUN_0068c510(hObject);
      CloseHandle(hObject);
      if (-1 < iVar1) {
        iVar1 = 0;
      }
    }
  }
  return iVar1;
}

