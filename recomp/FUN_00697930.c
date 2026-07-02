// ============================================
// Address:  0x00697930
// Original: FUN_00697930
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00697a47) */

undefined4 __thiscall FUN_00697930(int param_1,int *param_2,DWORD param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  HANDLE hHandle;
  DWORD DVar4;
  longlong lVar5;
  longlong lVar6;
  undefined1 local_48 [8];
  undefined1 local_40 [8];
  undefined1 local_38 [12];
  undefined4 local_2c;
  int local_20;
  undefined4 local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fe5f;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  do {
    FUN_0068d950(param_1 + 8);
    local_8 = 0;
    local_18 = 0;
    iVar1 = FUN_00699fc0();
    if (0 < iVar1) {
      local_1c = FUN_0068de10();
      local_18 = FUN_006981f0(local_1c);
    }
    if ((*(int *)(param_1 + 100) != 0) && (iVar1 = FUN_00699fc0(), 0 < iVar1)) {
      local_2c = FUN_0068de10();
      local_20 = FUN_006981f0(local_2c);
      FUN_006981a0(local_38);
      lVar5 = FUN_00697fc0();
      lVar6 = FUN_00697fc0();
      FUN_0068d8f0(lVar5 + lVar6);
      if (local_18 != 0) {
        lVar5 = FUN_00697fc0();
        FUN_006981a0(local_40);
        lVar6 = FUN_00697fc0();
        if (lVar6 <= lVar5) goto LAB_00697a55;
      }
      local_18 = local_20;
    }
LAB_00697a55:
    if (local_18 != 0) {
      uVar2 = FUN_00698070();
      puVar3 = (undefined4 *)FUN_006981a0(local_48);
      iVar1 = FUN_00698090(*puVar3,puVar3[1],uVar2);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(local_18 + 0xc) + 4))(local_18 + 0xc);
        *param_2 = local_18;
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return 0;
      }
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    DVar4 = param_3;
    hHandle = (HANDLE)FUN_0068de10();
    DVar4 = WaitForSingleObject(hHandle,DVar4);
    if (DVar4 != 0) {
      ExceptionList = local_10;
      return 0x80004004;
    }
  } while( true );
}

