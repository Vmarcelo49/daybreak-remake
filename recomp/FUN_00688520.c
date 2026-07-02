// ============================================
// Address:  0x00688520
// Original: FUN_00688520
// Status:   unreviewed
// ============================================


undefined4 FUN_00688520(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *local_c;
  HRESULT local_8;
  
  iVar1 = (**(code **)(*(int *)(param_1 + -0x10) + 0x20))();
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    local_8 = CoInitialize((LPVOID)0x0);
    local_8 = CoCreateInstance((IID *)&DAT_006ad1d4,(LPUNKNOWN)0x0,1,(IID *)&DAT_006acfd4,&local_c);
    if (-1 < local_8) {
      local_8 = FUN_0068d600(iVar1,local_c,1);
      (**(code **)(*local_c + 8))(local_c);
    }
    CoFreeUnusedLibraries();
    CoUninitialize();
    uVar2 = 0;
  }
  return uVar2;
}

