// ============================================
// Address:  0x0065bb00
// Original: FUN_0065bb00
// Status:   unreviewed
// ============================================


undefined4 FUN_0065bb00(void)

{
  HRESULT HVar1;
  
  HVar1 = CoInitialize((LPVOID)0x0);
  if (-1 < HVar1) {
    FUN_0065bb30();
    CoUninitialize();
  }
  return 0;
}

