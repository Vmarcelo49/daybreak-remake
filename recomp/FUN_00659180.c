// ============================================
// Address:  0x00659180
// Original: FUN_00659180
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00659180(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint local_84;
  uint local_70;
  undefined4 local_6c [21];
  undefined4 local_18;
  undefined1 *local_14;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069eeb0;
  pvStack_10 = ExceptionList;
  local_18 = DAT_006b77f4;
  local_14 = &stack0xffffff68;
  puVar4 = local_6c;
  for (iVar3 = 0x14; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *param_4;
    param_4 = param_4 + 1;
    puVar4 = puVar4 + 1;
  }
  ExceptionList = &pvStack_10;
  local_84 = FUN_00659500();
  if (param_3 != 0) {
    iVar3 = FUN_00659540();
    iVar1 = FUN_00658d50();
    if ((uint)(iVar1 - iVar3) < param_3) {
      FUN_00658cf0();
    }
    else {
      iVar3 = FUN_00659540();
      if (local_84 < iVar3 + param_3) {
        iVar3 = FUN_00658d50();
        if (iVar3 - (local_84 >> 1) < local_84) {
          local_84 = 0;
        }
        else {
          local_84 = (local_84 >> 1) + local_84;
        }
        local_70 = local_84;
        iVar3 = FUN_00659540();
        if (local_84 < iVar3 + param_3) {
          iVar3 = FUN_00659540();
          local_70 = iVar3 + param_3;
        }
        uVar2 = FUN_00658e40(local_70);
        local_8 = 0;
        uVar2 = DoMessageBox(*(undefined4 *)(param_1 + 4),param_2,uVar2);
        uVar2 = FUN_00659580(uVar2,param_3,local_6c);
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),uVar2);
        FUN_006592fd();
        return;
      }
      if ((uint)((*(int *)(param_1 + 8) - param_2) / 0x50) < param_3) {
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),param_3 * 0x50 + param_2);
        local_8 = 2;
        FUN_00659580(*(undefined4 *)(param_1 + 8),param_3 - (*(int *)(param_1 + 8) - param_2) / 0x50
                     ,local_6c);
        FUN_00659415();
        return;
      }
      iVar3 = *(int *)(param_1 + 8);
      uVar2 = DoMessageBox(iVar3 + param_3 * -0x50,iVar3,*(undefined4 *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = uVar2;
      FUN_00659780(param_2,iVar3 + param_3 * -0x50,iVar3);
      FUN_00659750(param_2,param_3 * 0x50 + param_2,local_6c);
    }
  }
  ExceptionList = pvStack_10;
  return;
}

