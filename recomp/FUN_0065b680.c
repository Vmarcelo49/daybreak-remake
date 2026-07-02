// ============================================
// Address:  0x0065b680
// Original: FUN_0065b680
// Status:   unreviewed
// ============================================


void __fastcall FUN_0065b680(undefined4 *param_1)

{
  HANDLE pvVar1;
  
  *(undefined1 *)(param_1 + 0x4d3) = 1;
  *(undefined1 *)((int)param_1 + 0x134d) = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  *param_1 = pvVar1;
  pvVar1 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0065bb00,(LPVOID)0x0,0,param_1 + 2);
  param_1[1] = pvVar1;
  SetThreadPriority((HANDLE)param_1[1],0xf);
  return;
}

