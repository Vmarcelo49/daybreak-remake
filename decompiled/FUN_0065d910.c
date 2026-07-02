// Function: FUN_0065d910
// Address:  0x0065d910
// Source:   batch_decompile (mass dump)
// Hash:     ec7e2041ac30f64a


void __fastcall FUN_0065d910(undefined4 *param_1)

{
  HGDIOBJ ho;
  
  if (param_1[4] != 0) {
    _free((void *)param_1[4]);
    param_1[4] = 0;
  }
  ho = SelectObject((HDC)param_1[1],(HGDIOBJ)param_1[3]);
  DeleteObject(ho);
  ReleaseDC((HWND)*param_1,(HDC)param_1[1]);
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[1] = 0;
  return;
}

