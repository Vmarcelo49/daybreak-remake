// Function: FUN_0065fdc0
// Address:  0x0065fdc0
// Source:   batch_decompile (mass dump)
// Hash:     31cd4855fd1e6cb0


undefined4 FUN_0065fdc0(void)

{
  undefined4 uStack_8;
  
  CoInitialize((LPVOID)0x0);
  uStack_8 = CONCAT13(0xff,(undefined3)uStack_8);
  while (DAT_006d764c != '\0') {
    FUN_0065fb10((int)&uStack_8 + 3,1,0,0x82);
    WaitForSingleObject(DAT_006d7650,500);
    DAT_006d7660 = DAT_006d7660 + 1;
  }
  CoUninitialize();
  return 0;
}

