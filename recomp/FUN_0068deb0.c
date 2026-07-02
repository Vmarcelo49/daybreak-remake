// ============================================
// Address:  0x0068deb0
// Original: FUN_0068deb0
// Status:   unreviewed
// ============================================


HMODULE FUN_0068deb0(void)

{
  if (DAT_006d894c == (HMODULE)0x0) {
    DAT_006d894c = LoadLibraryA("OleAut32.dll");
  }
  return DAT_006d894c;
}

