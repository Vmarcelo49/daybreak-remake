// Function: FUN_00692180
// Address:  0x00692180
// Source:   batch_decompile (mass dump)
// Hash:     3fb4574e95ae0f22


int FUN_00692180(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int local_c;
  
  local_c = -0x7fffbffb;
  hModule = GetModuleHandleA("ole32.dll");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"CoInitializeEx");
    if (pFVar1 != (FARPROC)0x0) {
      local_c = (*pFVar1)(0,4);
    }
  }
  return local_c;
}

