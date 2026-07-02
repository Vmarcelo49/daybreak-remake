// ============================================
// Address:  0x00654d90
// Original: FUN_00654d90
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00654dd5) */

undefined4 __fastcall FUN_00654d90(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    uVar1 = 0;
  }
  else if (*(int *)(param_1 + 0x20) == 0) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x44) == 0) {
      *(undefined4 *)(param_1 + 0x2c) = 0x16;
    }
    else {
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x68);
    }
    iVar2 = (**(code **)(**(int **)(param_1 + 0x20) + 0x40))
                      (*(undefined4 *)(param_1 + 0x20),param_1 + 0x24);
    if (iVar2 == 0) {
      FUN_00654f00();
      if (*(int *)(param_1 + 0x44) == 0) {
        SetWindowPos(*(HWND *)(param_1 + 0x40),(HWND)0x0,0,0,*(int *)(param_1 + 0x24),
                     *(int *)(param_1 + 0x28),0x20);
      }
      else {
        iVar3 = GetSystemMetrics(0x2d);
        iVar2 = *(int *)(param_1 + 0x24);
        iVar4 = GetSystemMetrics(5);
        iVar5 = GetSystemMetrics(7);
        iVar5 = iVar2 + iVar3 + iVar4 + iVar5;
        iVar3 = GetSystemMetrics(0x2e);
        iVar2 = *(int *)(param_1 + 0x28);
        iVar4 = GetSystemMetrics(6);
        iVar6 = GetSystemMetrics(8);
        iVar7 = GetSystemMetrics(4);
        iVar8 = GetSystemMetrics(0);
        iVar8 = (iVar8 - iVar5) / 2;
        GetSystemMetrics(1);
        SetWindowPos(*(HWND *)(param_1 + 0x40),(HWND)0xfffffffe,iVar8,iVar8,iVar5,
                     iVar2 + iVar3 + iVar4 + iVar6 + iVar7,0x20);
      }
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

