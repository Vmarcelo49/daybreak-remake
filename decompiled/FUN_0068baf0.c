// Function: FUN_0068baf0
// Address:  0x0068baf0
// Source:   batch_decompile (mass dump)
// Hash:     836afeb4b444eed7


undefined4 __thiscall FUN_0068baf0(int *param_1,HANDLE param_2)

{
  char cVar1;
  DWORD DVar2;
  HANDLE hTargetProcessHandle;
  HANDLE hSourceProcessHandle;
  undefined4 uVar3;
  LPHANDLE lpTargetHandle;
  BOOL BVar4;
  DWORD dwOptions;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f684;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x29);
  local_8 = 0;
  if (param_1[0x31] == 0) {
    dwOptions = 0;
    BVar4 = 0;
    DVar2 = 2;
    lpTargetHandle = (LPHANDLE)(param_1 + 0x30);
    hTargetProcessHandle = GetCurrentProcess();
    hSourceProcessHandle = GetCurrentProcess();
    BVar4 = DuplicateHandle(hSourceProcessHandle,param_2,hTargetProcessHandle,lpTargetHandle,DVar2,
                            BVar4,dwOptions);
    if (BVar4 == 0) {
      uVar3 = FUN_00693210();
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
    else {
      param_1[0x31] = 1;
      DVar2 = GetCurrentThreadId();
      param_1[0x32] = DVar2;
      cVar1 = (**(code **)(*param_1 + 100))();
      if (cVar1 == '\0') {
        FUN_0068bc30();
      }
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar3 = 0;
    }
  }
  else {
    DVar2 = GetCurrentThreadId();
    if (param_1[0x32] == DVar2) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar3 = 0x80040293;
    }
    else {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar3 = 0x80040294;
    }
  }
  ExceptionList = local_10;
  return uVar3;
}

