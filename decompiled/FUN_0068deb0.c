// Function: FUN_0068deb0
// Address:  0x0068deb0
// Source:   batch_decompile (mass dump)
// Hash:     69078b922beb695e


HMODULE FUN_0068deb0(void)

{
  if (DAT_006d894c == (HMODULE)0x0) {
    DAT_006d894c = LoadLibraryA("OleAut32.dll");
  }
  return DAT_006d894c;
}

