// ============================================
// Address:  0x00653540
// Original: FUN_00653540
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00653540(int *param_1,LPCSTR param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  HANDLE pvVar4;
  LPCSTR pCVar5;
  undefined1 local_c [4];
  int local_8;
  
  iVar2 = FUN_00699fc0();
  if (iVar2 == 0) {
    if (*param_1 != 0) {
      CloseHandle((HANDLE)*param_1);
    }
    pvVar4 = CreateFileA(param_2,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    *param_1 = (int)pvVar4;
    if (*param_1 != -1) {
      return 1;
    }
    *param_1 = 0;
  }
  else {
    local_8 = param_1[0x1d];
    while (cVar1 = const_iterator__operator__(param_1 + 0x1e), cVar1 != '\0') {
      pCVar5 = param_2;
      FUN_00653d70(param_2);
      cVar1 = FUN_00662f70(pCVar5);
      if (cVar1 != '\0') {
        piVar3 = (int *)FUN_00653d70();
        param_1[0x1f] = *piVar3;
        return 1;
      }
      FUN_0042fc40(local_c,0);
    }
    param_1[0x1f] = 0;
  }
  return 0;
}

