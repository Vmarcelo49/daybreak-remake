// ============================================
// Address:  0x006609a0
// Original: FUN_006609a0
// Status:   unreviewed
// ============================================


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

