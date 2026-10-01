// Function: FUN_006885b0
// Address:  0x006885b0
// Source:   batch_decompile (mass dump)
// Hash:     f30a3a24e2f2566e


HRESULT FUN_006885b0(int param_1)

{
  int iVar1;
  int *local_c;
  HRESULT local_8;
  
  iVar1 = (**(code **)(*(int *)(param_1 + -0x10) + 0x20))();
  if (iVar1 == 0) {
    local_8 = 1;
  }
  else {
    local_8 = CoInitialize((LPVOID)0x0);
    local_8 = CoCreateInstance((IID *)&DAT_006ad1d4,(LPUNKNOWN)0x0,1,(IID *)&DAT_006acfd4,&local_c);
    if (-1 < local_8) {
      local_8 = FUN_0068d600(iVar1,local_c,0);
      (**(code **)(*local_c + 8))(local_c);
    }
    CoFreeUnusedLibraries();
    CoUninitialize();
    if (local_8 == -0x7ff8fffe) {
      local_8 = 0;
    }
  }
  return local_8;
}

