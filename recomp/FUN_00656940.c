// ============================================
// Address:  0x00656940
// Original: FUN_00656940
// Status:   unreviewed
// ============================================


void __thiscall FUN_00656940(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_30;
  uint local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ede0;
  pvStack_10 = ExceptionList;
  local_14 = &stack0xffffffbc;
  local_18 = *param_4;
  ExceptionList = &pvStack_10;
  local_30 = FUN_0065aa30();
  if (param_3 != 0) {
    iVar1 = FUN_0064f010();
    iVar2 = FUN_0065a6b0();
    if ((uint)(iVar2 - iVar1) < param_3) {
      FUN_00656620();
    }
    else {
      iVar1 = FUN_0064f010();
      if (local_30 < iVar1 + param_3) {
        iVar1 = FUN_0065a6b0();
        if (iVar1 - (local_30 >> 1) < local_30) {
          local_30 = 0;
        }
        else {
          local_30 = (local_30 >> 1) + local_30;
        }
        local_1c = local_30;
        iVar1 = FUN_0064f010();
        if (local_30 < iVar1 + param_3) {
          iVar1 = FUN_0064f010();
          local_1c = iVar1 + param_3;
        }
        uVar3 = FUN_004107e0(local_1c);
        local_8 = 0;
        uVar3 = DoMessageBox(*(undefined4 *)(param_1 + 4),param_2,uVar3);
        uVar3 = FUN_00654640(uVar3,param_3,&local_18);
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),uVar3);
        FUN_00656aa4();
        return;
      }
      if ((uint)(*(int *)(param_1 + 8) - param_2 >> 2) < param_3) {
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),param_2 + param_3 * 4);
        local_8 = 2;
        FUN_00654640(*(undefined4 *)(param_1 + 8),param_3 - (*(int *)(param_1 + 8) - param_2 >> 2),
                     &local_18);
        FUN_00656bab();
        return;
      }
      iVar1 = *(int *)(param_1 + 8);
      uVar3 = DoMessageBox(iVar1 + param_3 * -4,iVar1,*(undefined4 *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = uVar3;
      FUN_006596e0(param_2,iVar1 + param_3 * -4,iVar1);
      FUN_006596b0(param_2,param_2 + param_3 * 4,&local_18);
    }
  }
  ExceptionList = pvStack_10;
  return;
}

