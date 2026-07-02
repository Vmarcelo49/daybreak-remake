// ============================================
// Address:  0x0041efe0
// Original: FUN_0041efe0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0041efe0(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int local_84;
  int local_80;
  int local_7c;
  uint local_78;
  int local_74;
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  int local_3c;
  int local_38;
  undefined4 local_34;
  int local_30 [10];
  undefined4 local_8;
  
  if ((char)param_1[0x218] == '\0') {
    piVar3 = param_1 + 0x9e;
    piVar5 = local_30;
    for (iVar4 = 10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar5 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar5 = piVar5 + 1;
    }
    FUN_00657390();
    if ((uint)param_1[0xa5] < (uint)param_1[0xa0]) {
      local_74 = param_1[0xa0];
    }
    else {
      local_74 = param_1[0xa5];
    }
    param_1[0xa0] = local_74;
    if ((uint)param_1[0xa4] < (uint)param_1[0xa1]) {
      local_78 = param_1[0xa1];
    }
    else {
      local_78 = param_1[0xa4];
    }
    if ((uint)param_1[0xa5] < local_78) {
      if ((uint)param_1[0xa4] < (uint)param_1[0xa1]) {
        local_7c = param_1[0xa1];
      }
      else {
        local_7c = param_1[0xa4];
      }
      local_80 = local_7c;
    }
    else {
      local_80 = param_1[0xa5];
    }
    param_1[0xa1] = local_80;
    if ((uint)param_1[0xa4] < (uint)param_1[0xa2]) {
      local_84 = param_1[0xa2];
    }
    else {
      local_84 = param_1[0xa4];
    }
    param_1[0xa2] = local_84;
    if (((DAT_006cfdb0 == '\x01') && ((int)DAT_006cfde1 == (&DAT_006cfaf8)[param_1[2]])) &&
       (cVar1 = FUN_00645e10(), cVar1 != '\0')) {
      _memset(local_30,0,0x28);
      _memset(param_1 + 0x9e,0,0x28);
    }
    for (local_3c = 0; local_3c < 4; local_3c = local_3c + 1) {
      if ((local_30[local_3c + 2] == 0) || (param_1[local_3c + 0xa0] != 0)) {
        param_1[local_3c + 0xac] = 0;
      }
      else {
        param_1[local_3c + 0xac] = local_30[local_3c + 2];
      }
    }
    if (param_1[0x1fa] != 0) {
      param_1[0xa1] = 0;
      param_1[0xa2] = 0;
      param_1[0xad] = 0;
      param_1[0xae] = 0;
    }
    local_38 = 0;
    FUN_004246c0(param_1 + 0x9e);
    FUN_00424690();
    FUN_004248b0();
    FUN_004248b0();
    param_1[0x20c] = 0;
    local_38 = 0;
    puVar2 = (undefined4 *)FUN_00653d10(local_40);
    local_8 = *puVar2;
    puVar2 = (undefined4 *)FUN_00654620(local_44);
    local_34 = *puVar2;
    while (cVar1 = const_iterator__operator__(&local_34), cVar1 != '\0') {
      iVar4 = FUN_004248d0();
      if ((*(int *)(iVar4 + 4) == -1) && (local_38 == 2)) {
        param_1[0x20c] = 1;
      }
      else {
        iVar4 = FUN_004248d0();
        if ((*(int *)(iVar4 + 4) == 0) && (local_38 == 1)) {
          local_38 = 2;
        }
        else {
          iVar4 = FUN_004248d0();
          if ((*(int *)(iVar4 + 4) == -1) && (local_38 == 0)) {
            local_38 = 1;
          }
        }
      }
      FUN_0042fc40(local_48,0);
    }
    local_38 = 0;
    puVar2 = (undefined4 *)FUN_00653d10(local_4c);
    local_8 = *puVar2;
    puVar2 = (undefined4 *)FUN_00654620(local_50);
    local_34 = *puVar2;
    while (cVar1 = const_iterator__operator__(&local_34), cVar1 != '\0') {
      iVar4 = FUN_004248d0();
      if ((*(int *)(iVar4 + 4) == 1) && (local_38 == 2)) {
        param_1[0x20c] = 2;
      }
      else {
        iVar4 = FUN_004248d0();
        if ((*(int *)(iVar4 + 4) == 0) && (local_38 == 1)) {
          local_38 = 2;
        }
        else {
          iVar4 = FUN_004248d0();
          if ((*(int *)(iVar4 + 4) == 1) && (local_38 == 0)) {
            local_38 = 1;
          }
        }
      }
      FUN_0042fc40(local_54,0);
    }
    local_38 = 0;
    puVar2 = (undefined4 *)FUN_00653d10(local_58);
    local_8 = *puVar2;
    puVar2 = (undefined4 *)FUN_00654620(local_5c);
    local_34 = *puVar2;
    while (cVar1 = const_iterator__operator__(&local_34), cVar1 != '\0') {
      piVar3 = (int *)FUN_004248d0();
      if ((*piVar3 == -1) && (local_38 == 2)) {
        param_1[0x20c] = 3;
      }
      else {
        piVar3 = (int *)FUN_004248d0();
        if ((*piVar3 == 0) && (local_38 == 1)) {
          local_38 = 2;
        }
        else {
          piVar3 = (int *)FUN_004248d0();
          if ((*piVar3 == -1) && (local_38 == 0)) {
            local_38 = 1;
          }
        }
      }
      FUN_0042fc40(local_60,0);
    }
    local_38 = 0;
    puVar2 = (undefined4 *)FUN_00653d10(local_64);
    local_8 = *puVar2;
    puVar2 = (undefined4 *)FUN_00654620(local_68);
    local_34 = *puVar2;
    while (cVar1 = const_iterator__operator__(&local_34), cVar1 != '\0') {
      piVar3 = (int *)FUN_004248d0();
      if ((*piVar3 == 1) && (local_38 == 2)) {
        param_1[0x20c] = 4;
      }
      else {
        piVar3 = (int *)FUN_004248d0();
        if ((*piVar3 == 0) && (local_38 == 1)) {
          local_38 = 2;
        }
        else {
          piVar3 = (int *)FUN_004248d0();
          if ((*piVar3 == 1) && (local_38 == 0)) {
            local_38 = 1;
          }
        }
      }
      FUN_0042fc40(local_6c,0);
    }
  }
  else {
    (**(code **)(*param_1 + 0x14))();
    if (param_1[0x1fa] != 0) {
      param_1[0xa1] = 0;
      param_1[0xa2] = 0;
      param_1[0xad] = 0;
      param_1[0xae] = 0;
    }
  }
  return;
}

