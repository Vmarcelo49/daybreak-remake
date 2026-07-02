// Function: FUN_00422560
// Address:  0x00422560
// Source:   batch_decompile (mass dump)
// Hash:     7891ace3520a8a85


void __thiscall
FUN_00422560(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_41;
  uint local_40;
  undefined1 local_3c [8];
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined2 local_30;
  undefined1 local_2e;
  int local_2c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e239;
  local_10 = ExceptionList;
  local_14 = param_1 + 0xae1c;
  if ((((*(char *)(param_1 + 0x845) != '\0') || (*(char *)(param_1 + 0x846) != '\0')) ||
      (*(char *)(param_1 + 0x844) != '\0')) && (*(int *)(param_1 + 0xaeb4) != 0)) {
    local_14 = *(int *)(param_1 + 0xaeb4);
  }
  if (DAT_006cfdb0 == '\x01') {
    ExceptionList = &local_10;
    FUN_004248f0();
    local_8 = 0;
    FUN_00424940();
    for (local_2c = 1; local_2c < 8; local_2c = local_2c + 1) {
      if (((&DAT_006cfdd1)[local_2c] != '\0') && (param_2 == (&DAT_006cfdd9)[local_2c])) {
        local_41 = (undefined1)local_2c;
        FUN_004249a0(&local_41);
      }
    }
    iVar1 = FUN_0063bf40();
    if (iVar1 != 0) {
      FUN_00423cc0();
      local_34 = *(undefined1 *)(param_1 + 8);
      local_33 = (undefined1)param_3;
      local_32 = 0xff;
      local_30 = (undefined2)param_4;
      local_2e = param_5;
      local_40 = 0;
      while( true ) {
        uVar2 = FUN_0063bf40();
        if (uVar2 <= local_40) break;
        uVar6 = 8;
        uVar5 = 0;
        puVar4 = local_3c;
        pcVar3 = (char *)FUN_00424960(local_40);
        FUN_00415d30((int)*pcVar3,puVar4,uVar5,uVar6);
        local_40 = local_40 + 1;
      }
    }
    if (param_2 == DAT_006cfdd9) {
      FUN_00432330(param_3,param_4,param_5);
    }
    local_8 = 0xffffffff;
    FUN_00424940();
  }
  else if ((-1 < (int)(&DAT_006cfaf8)[param_2]) && ((int)(&DAT_006cfaf8)[param_2] < 4)) {
    ExceptionList = &local_10;
    FUN_00432330(param_3,param_4,param_5);
  }
  ExceptionList = local_10;
  return;
}

