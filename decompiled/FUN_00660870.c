// Function: FUN_00660870
// Address:  0x00660870
// Source:   batch_decompile (mass dump)
// Hash:     d9980ddf3f52fbd9


undefined4 FUN_00660870(void)

{
  HRESULT HVar1;
  uint local_c;
  undefined1 local_5;
  
  HVar1 = CoInitialize((LPVOID)0x0);
  if (-1 < HVar1) {
    local_5 = 0xff;
    while (DAT_006d79d0 != '\0') {
      FUN_006603b0(&local_5,1,0,0x82);
      WaitForSingleObject(DAT_006d79d4,500);
      for (local_c = 1; local_c < 8; local_c = local_c + 1) {
        *(int *)(local_c * 4 + 0x6d79e0) = *(int *)(local_c * 4 + 0x6d79e0) + 1;
      }
    }
    CoUninitialize();
  }
  return 0;
}

