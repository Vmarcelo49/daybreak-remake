// ============================================
// Address:  0x00690bc0
// Original: FUN_00690bc0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00690bc0(int param_1)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  
  DVar1 = timeGetTime();
  iVar2 = (DVar1 - *(int *)(param_1 + 0xfc)) * 10000;
  if ((iVar2 < *(int *)(param_1 + 0xf4) * 2) || (iVar2 < *(int *)(param_1 + 0xf8) * 2)) {
    iVar3 = *(int *)(param_1 + 0xf4) * 3 + iVar2;
    *(int *)(param_1 + 0xf4) = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  }
  *(int *)(param_1 + 0xf8) = iVar2;
  FUN_00690ad0();
  return;
}

