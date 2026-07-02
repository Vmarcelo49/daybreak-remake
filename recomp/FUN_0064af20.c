// ============================================
// Address:  0x0064af20
// Original: FUN_0064af20
// Status:   unreviewed
// ============================================


void __thiscall FUN_0064af20(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_39;
  uint local_38;
  undefined1 local_34 [8];
  undefined2 local_2c;
  int local_28;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069eb19;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_006cfdb0 == '\x01') {
    ExceptionList = &local_10;
    FUN_004248f0();
    local_8 = 0;
    FUN_00424940();
    for (local_28 = 1; local_28 < 8; local_28 = local_28 + 1) {
      if ((*(char *)(param_1 + local_28 + 0x55b1) != '\0') &&
         (param_2 == *(char *)(param_1 + local_28 + 0x55b9))) {
        local_39 = (undefined1)local_28;
        FUN_004249a0(&local_39);
      }
    }
    iVar1 = FUN_0063bf40();
    if (iVar1 != 0) {
      FUN_0041d090();
      local_2c = (undefined2)param_3;
      local_38 = 0;
      while( true ) {
        uVar2 = FUN_0063bf40();
        if (uVar2 <= local_38) break;
        uVar6 = 2;
        uVar5 = 0x10;
        puVar4 = local_34;
        pcVar3 = (char *)FUN_00424960(local_38);
        FUN_00415d30((int)*pcVar3,puVar4,uVar5,uVar6);
        local_38 = local_38 + 1;
      }
    }
    local_8 = 0xffffffff;
    FUN_00424940();
  }
  if ((-1 < (int)(&DAT_006cfaf8)[param_2]) && ((int)(&DAT_006cfaf8)[param_2] < 4)) {
    FUN_0064ade0(param_3);
  }
  ExceptionList = local_10;
  return;
}

