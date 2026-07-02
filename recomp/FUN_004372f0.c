// ============================================
// Address:  0x004372f0
// Original: FUN_004372f0
// Status:   unreviewed
// ============================================


void FUN_004372f0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = *param_2;
  local_10 = param_2[1];
  local_c = param_2[2];
  local_8 = param_2[3];
  puVar1 = (undefined4 *)FUN_00425150(local_1c);
  uVar4 = puVar1[1];
  uVar3 = *puVar1;
  uVar5 = extraout_var;
  puVar1 = (undefined4 *)FUN_00425ae0(local_24);
  FUN_00437710(local_2c,*puVar1,puVar1[1],uVar3,uVar4);
  puVar1 = &local_14;
  puVar2 = (undefined4 *)FUN_00425ae0(local_34);
  FUN_00437820(*puVar2,puVar2[1],param_1,puVar1,uVar5);
  return;
}

