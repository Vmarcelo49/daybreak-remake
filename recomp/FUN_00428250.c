// ============================================
// Address:  0x00428250
// Original: FUN_00428250
// Status:   unreviewed
// ============================================


void __fastcall FUN_00428250(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(param_1 + 0xadec) < 100) {
    if ((*(int *)(param_1 + 0x7a4) < 0x9c4) && (*(char *)(param_1 + 0xaebd) < '\x04')) {
      *(undefined1 *)(param_1 + 0xaebd) = 4;
      uVar6 = 0;
      uVar5 = 0x19;
      uVar4 = 3;
      uVar3 = 0xe;
      piVar1 = (int *)FUN_00658a10(0);
      FUN_00422730(*(undefined4 *)(*piVar1 + 8),uVar3,uVar4,uVar5,uVar6);
      FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,3,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 5000) && (*(char *)(param_1 + 0xaebd) < '\x03')) {
      *(undefined1 *)(param_1 + 0xaebd) = 3;
      uVar6 = 0;
      uVar5 = 0x19;
      uVar4 = 2;
      uVar3 = 0xe;
      piVar1 = (int *)FUN_00658a10(0);
      FUN_00422730(*(undefined4 *)(*piVar1 + 8),uVar3,uVar4,uVar5,uVar6);
      FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,2,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 0x1d4c) && (*(char *)(param_1 + 0xaebd) < '\x02')) {
      *(undefined1 *)(param_1 + 0xaebd) = 2;
      uVar6 = 0;
      uVar5 = 0x19;
      uVar4 = 1;
      uVar3 = 0xe;
      piVar1 = (int *)FUN_00658a10(0);
      FUN_00422730(*(undefined4 *)(*piVar1 + 8),uVar3,uVar4,uVar5,uVar6);
      FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,1,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 10000) && (*(char *)(param_1 + 0xaebd) < '\x01')) {
      *(undefined1 *)(param_1 + 0xaebd) = 1;
      uVar6 = 0;
      uVar5 = 0x19;
      uVar4 = 0;
      uVar3 = 0xe;
      piVar1 = (int *)FUN_00658a10(0);
      FUN_00422730(*(undefined4 *)(*piVar1 + 8),uVar3,uVar4,uVar5,uVar6);
      FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,0,0xf,0);
    }
    if (*(char *)(param_1 + 0xaebf) == '\x01') {
      *(undefined1 *)(param_1 + 0xaebf) = 0;
      FUN_00422240(0x10,0x14,0);
    }
    if (*(char *)(param_1 + 0xaeb8) == '\x01') {
      iVar2 = FUN_00421930();
      if (0 < iVar2) {
        *(undefined1 *)(param_1 + 0xaeb8) = 0;
        iVar2 = FUN_00421930();
        if (iVar2 < 0x15) {
          FUN_004223d0(0x12,0xf,0);
        }
        else {
          FUN_004223d0(4,0xf,0);
        }
      }
    }
    if (*(char *)(param_1 + 0xaec0) == '\x01') {
      *(undefined1 *)(param_1 + 0xaec0) = 0;
      FUN_004223d0(0x15,0xf,0);
    }
    if (*(char *)(param_1 + 0xaec1) == '\x01') {
      *(undefined1 *)(param_1 + 0xaec1) = 0;
      FUN_004223d0(0x26,0xf,0);
    }
  }
  if ((*(int *)(param_1 + 0xadec) < 100) && (*(char *)(param_1 + 0xaec2) == '\x01')) {
    *(undefined1 *)(param_1 + 0xaec2) = 0;
    FUN_004223d0(0x25,0xf,0);
  }
  return;
}

