// Function: FUN_006609a0
// Address:  0x006609a0
// Source:   batch_decompile (mass dump)
// Hash:     2d2616a0b39d15de


void __fastcall FUN_006609a0(undefined4 *param_1)

{
  HIMC pHVar1;
  HWND pHVar2;
  
  pHVar1 = ImmGetContext(DAT_006d1850);
  *param_1 = pHVar1;
  pHVar2 = ImmGetDefaultIMEWnd((HWND)0x0);
  param_1[1] = pHVar2;
  return;
}

