// ============================================
// Address:  0x00697630
// Original: FUN_00697630
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00697744) */
/* WARNING: Removing unreachable block (ram,0x00697772) */

void __fastcall FUN_00697630(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined1 *puVar6;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined1 local_c [8];
  
  if (*(int *)(param_1 + 0x60) == 0) {
    return;
  }
  FUN_006919c0();
  FUN_0068d890();
  iVar1 = FUN_00699fc0();
  if (0 < iVar1) {
    local_10 = FUN_0068de10();
    puVar6 = local_2c;
    FUN_006981f0(local_10);
    uVar2 = FUN_006981a0(puVar6);
    FUN_00697ec0(uVar2);
  }
  if (*(int *)(param_1 + 100) != 0) {
    FUN_0068d890();
    iVar1 = FUN_00699fc0();
    if (0 < iVar1) {
      local_20 = FUN_0068de10();
      puVar6 = local_34;
      FUN_006981f0(local_20);
      uVar2 = FUN_006981a0(puVar6);
      FUN_00697ec0(uVar2);
      FUN_00697ee0(param_1 + 0x68);
      lVar3 = FUN_00697fc0();
      if (lVar3 != 0) {
        lVar3 = FUN_00697fc0();
        lVar4 = FUN_00697fc0();
        if (lVar4 <= lVar3) goto LAB_00697758;
      }
      FUN_00697ec0(local_1c);
    }
  }
LAB_00697758:
  lVar3 = FUN_00697fc0();
  if (0 < lVar3) {
    lVar3 = FUN_00697fc0();
    lVar4 = FUN_00697fc0();
    if (lVar3 != lVar4) {
      if (*(int *)(param_1 + 0x54) != 0) {
        (**(code **)(**(int **)(param_1 + 0x60) + 0x18))
                  (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x54));
        FUN_006919c0();
      }
      uVar2 = FUN_0068de10(param_1 + 0x54);
      uVar5 = FUN_00697fc0(0,0,uVar2);
      local_24 = (**(code **)(**(int **)(param_1 + 0x60) + 0x10))
                           (*(undefined4 *)(param_1 + 0x60),uVar5);
      FUN_00697ec0(local_c);
    }
  }
  return;
}

