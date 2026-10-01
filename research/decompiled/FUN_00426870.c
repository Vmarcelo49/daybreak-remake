// Function: FUN_00426870
// Address:  0x00426870
// Source:   batch_decompile (mass dump)
// Hash:     12a1cefd452d1069


void __thiscall FUN_00426870(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_38;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e310;
  pvStack_10 = ExceptionList;
  local_14 = &stack0xffffffb4;
  local_20 = *param_4;
  local_1c = param_4[1];
  local_18 = param_4[2];
  ExceptionList = &pvStack_10;
  local_38 = FUN_004258a0();
  if (param_3 != 0) {
    iVar1 = FUN_004258e0();
    iVar2 = FUN_00426820();
    if ((uint)(iVar2 - iVar1) < param_3) {
      FUN_004267c0();
    }
    else {
      iVar1 = FUN_004258e0();
      if (local_38 < iVar1 + param_3) {
        iVar1 = FUN_00426820();
        if (iVar1 - (local_38 >> 1) < local_38) {
          local_38 = 0;
        }
        else {
          local_38 = (local_38 >> 1) + local_38;
        }
        local_24 = local_38;
        iVar1 = FUN_004258e0();
        if (local_38 < iVar1 + param_3) {
          iVar1 = FUN_004258e0();
          local_24 = iVar1 + param_3;
        }
        uVar3 = FUN_00667580(local_24);
        local_8 = 0;
        uVar3 = DoMessageBox(*(undefined4 *)(param_1 + 4),param_2,uVar3);
        uVar3 = FUN_00425a90(uVar3,param_3,&local_20);
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),uVar3);
        FUN_004269e0();
        return;
      }
      if ((uint)((*(int *)(param_1 + 8) - param_2) / 0xc) < param_3) {
        DoMessageBox(param_2,*(undefined4 *)(param_1 + 8),param_3 * 0xc + param_2);
        local_8 = 2;
        FUN_00425a90(*(undefined4 *)(param_1 + 8),param_3 - (*(int *)(param_1 + 8) - param_2) / 0xc,
                     &local_20);
        FUN_00426af6();
        return;
      }
      iVar1 = *(int *)(param_1 + 8);
      uVar3 = DoMessageBox(iVar1 + param_3 * -0xc,iVar1,*(undefined4 *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = uVar3;
      FUN_00427200(param_2,iVar1 + param_3 * -0xc,iVar1);
      FUN_004271d0(param_2,param_3 * 0xc + param_2,&local_20);
    }
  }
  ExceptionList = pvStack_10;
  return;
}

