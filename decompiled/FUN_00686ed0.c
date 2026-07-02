// Function: FUN_00686ed0
// Address:  0x00686ed0
// Source:   batch_decompile (mass dump)
// Hash:     6d3ca04e06cd618b


LPVOID FUN_00686ed0(undefined4 param_1)

{
  LPVOID pv;
  int iVar1;
  
  pv = CoTaskMemAlloc(0x48);
  if (pv == (LPVOID)0x0) {
    pv = (LPVOID)0x0;
  }
  else {
    iVar1 = FUN_00686f20(pv,param_1);
    if (iVar1 < 0) {
      CoTaskMemFree(pv);
      pv = (LPVOID)0x0;
    }
  }
  return pv;
}

