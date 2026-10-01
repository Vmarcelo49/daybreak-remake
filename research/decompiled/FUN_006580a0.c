// Function: FUN_006580a0
// Address:  0x006580a0
// Source:   batch_decompile (mass dump)
// Hash:     9a97a9d124612e79


undefined4 FUN_006580a0(void)

{
  bool bVar1;
  char cVar2;
  HRESULT HVar3;
  
  HVar3 = CoInitialize((LPVOID)0x0);
  if (-1 < HVar3) {
    bVar1 = false;
    while (DAT_006d18ac != '\0') {
      FUN_0065d670();
      if (DAT_006d18cc == (int *)0x0) {
        bVar1 = true;
      }
      else {
        cVar2 = (**(code **)(*DAT_006d18cc + 4))();
        if (cVar2 == '\0') {
          bVar1 = true;
        }
        else {
          DAT_006d18a8 = DAT_006d18a8 + 1;
        }
      }
      FUN_0065d6a0();
      if (bVar1) {
        WaitForSingleObject(DAT_006d18c4,10);
        bVar1 = false;
      }
    }
    CoUninitialize();
  }
  return 0;
}

