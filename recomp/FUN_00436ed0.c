// ============================================
// Address:  0x00436ed0
// Original: FUN_00436ed0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00436ed0(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 local_b8 [16];
  undefined1 local_a8 [16];
  undefined1 local_98 [8];
  undefined1 local_90 [16];
  undefined1 local_80 [16];
  undefined1 local_70 [8];
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined1 local_48 [8];
  undefined1 local_40 [16];
  undefined1 local_30 [8];
  float local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [8];
  
  FUN_00425ae0(local_c);
  local_20 = 0;
  while (local_20 <= *(int *)(param_1 + 0xc)) {
    for (local_24 = 0; local_24 < *(int *)(param_1 + 8); local_24 = local_24 + 1) {
      local_28 = (float)local_24 / (float)*(int *)(param_1 + 8);
      if (local_20 == 0) {
        FUN_0065d2f0(local_28,&local_1c);
      }
      else if (local_20 == 1) {
        FUN_0065d380(local_28,&local_1c);
      }
      else if (local_20 == *(int *)(param_1 + 0xc) + -1) {
        FUN_0065d4d0(local_28,&local_1c);
      }
      else if (local_20 == *(int *)(param_1 + 0xc)) {
        FUN_0065d580(local_28,&local_1c);
      }
      else {
        FUN_0065d430(local_28,&local_1c);
      }
      puVar8 = local_a8;
      uVar7 = local_10;
      FUN_004372b0(local_98,3);
      FUN_00437250(puVar8,uVar7);
      uVar1 = FUN_00430790(puVar8,uVar7);
      puVar10 = local_b8;
      puVar8 = local_80;
      uVar7 = local_14;
      FUN_004372b0(local_70,2);
      FUN_00437250(puVar8,uVar7,puVar10,uVar1);
      uVar2 = FUN_00430790(puVar8,uVar7);
      puVar9 = local_90;
      puVar8 = local_58;
      uVar7 = local_18;
      FUN_004372b0(local_48,1);
      FUN_00437250(puVar8,uVar7,puVar9,uVar2);
      uVar3 = FUN_00430790(puVar8,uVar7);
      puVar8 = local_68;
      puVar6 = local_40;
      uVar7 = local_1c;
      FUN_00437250(puVar6,local_1c,puVar8,uVar3);
      FUN_00430790(puVar6,uVar7);
      FUN_004306f0(puVar8,uVar3);
      FUN_004306f0(puVar9,uVar2);
      puVar4 = (undefined4 *)FUN_004306f0(puVar10,uVar1);
      puVar5 = (undefined4 *)
               (*(int *)(param_1 + 0x30) + (local_20 * *(int *)(param_1 + 8) + local_24) * 0x10);
      *puVar5 = *puVar4;
      puVar5[1] = puVar4[1];
      puVar5[2] = puVar4[2];
      puVar5[3] = puVar4[3];
    }
    local_20 = local_20 + 1;
    FUN_00437270(local_30,0);
  }
  return;
}

