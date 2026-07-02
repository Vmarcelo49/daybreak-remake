// Function: FUN_00422730
// Address:  0x00422730
// Source:   batch_decompile (mass dump)
// Hash:     06c862b7e2666857


void __thiscall
FUN_00422730(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            undefined1 param_6)

{
  char *pcVar1;
  undefined8 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
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
  puStack_c = &LAB_0069e24b;
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
    uVar2 = FUN_0063bf40();
    uVar4 = (undefined4)((ulonglong)uVar2 >> 0x20);
    if ((int)uVar2 != 0) {
      FUN_00423cc0();
      local_34 = *(undefined1 *)(param_1 + 8);
      local_33 = (undefined1)param_3;
      local_32 = (undefined1)param_4;
      local_30 = (undefined2)param_5;
      local_2e = param_6;
      local_40 = 0;
      while( true ) {
        uVar2 = FUN_0063bf40();
        uVar4 = (undefined4)((ulonglong)uVar2 >> 0x20);
        if ((uint)uVar2 <= local_40) break;
        uVar5 = 8;
        uVar4 = 0;
        puVar3 = local_3c;
        pcVar1 = (char *)FUN_00424960(local_40);
        FUN_00415d30((int)*pcVar1,puVar3,uVar4,uVar5);
        local_40 = local_40 + 1;
      }
    }
    if (param_2 == DAT_006cfdd9) {
      FUN_004322b0(param_3,param_4,param_5,CONCAT31((int3)((uint)uVar4 >> 8),param_6));
    }
    local_8 = 0xffffffff;
    FUN_00424940();
  }
  else if ((-1 < (int)(&DAT_006cfaf8)[param_2]) && ((int)(&DAT_006cfaf8)[param_2] < 4)) {
    ExceptionList = &local_10;
    FUN_004322b0(param_3,param_4,param_5,param_6);
  }
  ExceptionList = local_10;
  return;
}

