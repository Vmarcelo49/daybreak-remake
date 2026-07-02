// ============================================
// Address:  0x006537b0
// Original: FUN_006537b0
// Status:   unreviewed
// ============================================


BOOL __thiscall FUN_006537b0(undefined4 *param_1,undefined4 param_2,LPVOID param_3,DWORD param_4)

{
  char cVar1;
  int iVar2;
  BOOL BVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  LPDWORD lpNumberOfBytesRead;
  LPOVERLAPPED lpOverlapped;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    iVar2 = FUN_006543d0(param_2);
    if (iVar2 == 0) {
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesRead = param_1 + 1;
      puVar5 = (undefined4 *)FUN_006543d0(param_2);
      BVar3 = ReadFile((HANDLE)*puVar5,param_3,param_4,lpNumberOfBytesRead,lpOverlapped);
    }
    else {
      BVar3 = FUN_00663030(param_3,param_4);
      uVar4 = FUN_00653b30();
      param_1[1] = uVar4;
    }
  }
  else {
    BVar3 = ReadFile((HANDLE)*param_1,param_3,param_4,param_1 + 1,(LPOVERLAPPED)0x0);
  }
  return BVar3;
}

