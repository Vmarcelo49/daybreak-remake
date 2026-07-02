// ============================================
// Address:  0x004332f0
// Original: FUN_004332f0
// Status:   unreviewed
// ============================================


void __thiscall
FUN_004332f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 auStack_118 [8];
  undefined1 auStack_110 [8];
  undefined1 auStack_108 [8];
  undefined1 auStack_100 [8];
  undefined1 auStack_f8 [8];
  undefined1 auStack_f0 [8];
  undefined1 auStack_e8 [8];
  undefined1 auStack_e0 [8];
  undefined1 auStack_d8 [8];
  undefined1 auStack_d0 [8];
  undefined1 auStack_c8 [8];
  undefined1 local_c0 [8];
  undefined1 local_b8 [8];
  undefined1 local_b0 [8];
  undefined1 local_a8 [8];
  undefined1 local_a0 [8];
  undefined1 local_98 [8];
  undefined1 local_90 [8];
  undefined1 local_88 [8];
  undefined1 local_80 [8];
  undefined1 local_78 [8];
  undefined1 local_70 [8];
  undefined1 local_68 [8];
  undefined1 local_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e540;
  pvStack_10 = ExceptionList;
  local_14 = &stack0xfffffe70;
  ExceptionList = &pvStack_10;
  uVar2 = FUN_00425ae0(local_60);
  local_28 = FUN_00433aa0(uVar2);
  local_24 = *(int *)(param_1 + 0x10) - local_28;
  local_18 = *(undefined4 *)(param_1 + 0x10);
  local_20 = 0;
  FUN_004280e0(param_4,param_5,param_6,param_7,&local_20);
  if (local_28 < local_24) {
    local_8 = 0;
    if (local_28 < local_20) {
      local_30 = param_4;
      local_2c = param_5;
      FUN_00428120(&local_30,local_20 - local_28);
      local_38 = local_30;
      local_34 = local_2c;
      while( true ) {
        cVar1 = FUN_00433b00(&local_38);
        if (cVar1 == '\0') break;
        FUN_004280c0();
        uVar2 = FUN_0040fde0();
        FUN_00433900(uVar2);
      }
      for (local_1c = local_28; local_1c != 0; local_1c = local_1c - 1) {
        FUN_00425ae0(local_68);
        uVar2 = FUN_00433ad0(local_20 - 1);
        FUN_00433900(uVar2);
      }
      FUN_00425ae0(local_70);
      puVar3 = (undefined4 *)FUN_004372b0(local_78,local_20);
      FUN_00433b30(local_80,local_30,local_2c,param_6,param_7,*puVar3,puVar3[1]);
    }
    else {
      for (local_1c = local_20; local_1c != 0; local_1c = local_1c - 1) {
        FUN_00425ae0(local_88);
        uVar2 = FUN_00433ad0(local_20 - 1);
        FUN_00433900(uVar2);
      }
      FUN_00425ae0(local_90);
      FUN_004372b0(&local_40,local_20);
      puVar3 = (undefined4 *)FUN_004372b0(local_98,local_28);
      puVar4 = (undefined4 *)FUN_004372b0(local_a0,local_20);
      FUN_00433b80(local_a8,*puVar4,puVar4[1],*puVar3,puVar3[1],local_40,local_3c);
      FUN_00425ae0(local_b0);
      puVar3 = (undefined4 *)FUN_004372b0(local_b8,local_28);
      FUN_00433b30(local_c0,param_4,param_5,param_6,param_7,*puVar3,puVar3[1]);
    }
    FUN_00433631();
    return;
  }
  local_8 = 2;
  if (local_24 < local_20) {
    uStack_48 = param_4;
    uStack_44 = param_5;
    FUN_00428120(&uStack_48,local_24);
    uStack_50 = uStack_48;
    uStack_4c = uStack_44;
    while( true ) {
      cVar1 = FUN_00433b00(&param_6);
      if (cVar1 == '\0') break;
      uVar2 = FUN_0040fde0();
      FUN_004326f0(uVar2);
      iterator__operator__();
    }
    for (local_1c = 0; local_1c < local_24; local_1c = local_1c + 1) {
      FUN_00425ae0(auStack_c8);
      uVar2 = FUN_00433ad0(local_28 + local_1c);
      FUN_004326f0(uVar2);
    }
    FUN_00425ae0(auStack_d0);
    puVar3 = (undefined4 *)FUN_004372b0(auStack_d8,local_28);
    FUN_00433b30(auStack_e0,param_4,param_5,uStack_48,uStack_44,*puVar3,puVar3[1]);
  }
  else {
    for (local_1c = 0; local_1c < local_20; local_1c = local_1c + 1) {
      FUN_00425ae0(auStack_e8);
      uVar2 = FUN_00433ad0(((local_28 + local_24) - local_20) + local_1c);
      FUN_004326f0(uVar2);
    }
    FUN_00425ae0(auStack_f0);
    FUN_004372b0(&uStack_58,local_28);
    puVar3 = (undefined4 *)FUN_004372b0(auStack_f8,local_24);
    FUN_004372b0(auStack_100,local_24);
    puVar4 = (undefined4 *)FUN_004250e0(auStack_108,local_20);
    FUN_00433bd0(auStack_110,uStack_58,uStack_54,*puVar4,puVar4[1],*puVar3,puVar3[1]);
    FUN_00433b30(auStack_118,param_4,param_5,param_6,param_7,uStack_58,uStack_54);
  }
  FUN_004338df();
  return;
}

