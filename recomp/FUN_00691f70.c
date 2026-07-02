// ============================================
// Address:  0x00691f70
// Original: FUN_00691f70
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00691f70(LPVOID param_1)

{
  int iVar1;
  HANDLE pvVar2;
  undefined4 uVar3;
  DWORD local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fb29;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950((int)param_1 + 0x18);
  local_8 = 0;
  iVar1 = FUN_006933b0();
  if (iVar1 == 0) {
    pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00691f30,param_1,0,local_18);
    *(HANDLE *)((int)param_1 + 0x14) = pvVar2;
    if (*(int *)((int)param_1 + 0x14) == 0) {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar3 = 0;
    }
    else {
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar3 = 1;
    }
  }
  else {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar3 = 0;
  }
  ExceptionList = local_10;
  return uVar3;
}

