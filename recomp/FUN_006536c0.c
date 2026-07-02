// ============================================
// Address:  0x006536c0
// Original: FUN_006536c0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_006536c0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  
  cVar1 = FUN_0064d6e0(param_1);
  if ((cVar1 == '\0') && (iVar2 = FUN_006543d0(param_2), iVar2 == 0)) {
    puVar3 = (undefined4 *)FUN_006543d0(param_2);
    CloseHandle((HANDLE)*puVar3);
    FUN_0065a7f0(param_2);
    return 1;
  }
  return 0;
}

