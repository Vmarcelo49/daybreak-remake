// ============================================
// Address:  0x00653730
// Original: FUN_00653730
// Status:   unreviewed
// ============================================


bool __fastcall FUN_00653730(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = param_1[0x1f];
  if (iVar1 == 0) {
    CloseHandle((HANDLE)*param_1);
    *param_1 = 0;
  }
  return iVar1 == 0;
}

