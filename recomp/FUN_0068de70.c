// ============================================
// Address:  0x0068de70
// Original: FUN_0068de70
// Status:   unreviewed
// ============================================


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

