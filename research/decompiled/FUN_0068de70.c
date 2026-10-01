// Function: FUN_0068de70
// Address:  0x0068de70
// Source:   batch_decompile (mass dump)
// Hash:     4171db523127e99f


void FUN_0068de70(void)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement((LONG *)&DAT_006d8950);
  if ((LVar1 == 0) && (DAT_006d894c != (HMODULE)0x0)) {
    FreeLibrary(DAT_006d894c);
    DAT_006d894c = (HMODULE)0x0;
  }
  return;
}

