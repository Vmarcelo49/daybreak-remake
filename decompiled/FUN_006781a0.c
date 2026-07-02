// Function: FUN_006781a0
// Address:  0x006781a0
// Source:   batch_decompile (mass dump)
// Hash:     7dc3988e1e178cb1


void FUN_006781a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  longlong *plVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int extraout_EDX;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  bool bVar10;
  longlong lVar11;
  longlong lVar12;
  uint local_38;
  int local_34;
  undefined1 local_30 [16];
  undefined1 local_20 [32];
  
  pvVar3 = _realloc(*(void **)(param_1 + 0x48),*(int *)(param_1 + 0x34) << 5);
  *(void **)(param_1 + 0x48) = pvVar3;
  pvVar3 = _realloc(*(void **)(param_1 + 0x4c),*(int *)(param_1 + 0x34) << 4);
  *(void **)(param_1 + 0x4c) = pvVar3;
  pvVar3 = _malloc(*(int *)(param_1 + 0x34) << 3);
  *(void **)(param_1 + 0x3c) = pvVar3;
  pvVar3 = _malloc(*(int *)(param_1 + 0x34) << 4);
  *(void **)(param_1 + 0x44) = pvVar3;
  iVar7 = 0;
  if (0 < *(int *)(param_1 + 0x34)) {
    do {
      if (iVar7 == 0) {
        puVar8 = *(undefined4 **)(param_1 + 0x3c);
        *puVar8 = param_2;
        puVar8[1] = param_3;
        FUN_00677f40(param_1,param_2,param_3);
      }
      else {
        iVar1 = iVar7 * 8;
        FUN_00677f40(param_1,*(undefined4 *)(*(int *)(param_1 + 0x38) + iVar1),
                     *(undefined4 *)(*(int *)(param_1 + 0x38) + 4 + iVar1));
        iVar9 = FUN_00677a50(param_1,iVar7 * 0x20 + *(int *)(param_1 + 0x48),
                             iVar7 * 0x10 + *(int *)(param_1 + 0x4c),0,0);
        if (iVar9 < 0) {
          puVar8 = (undefined4 *)(iVar1 + *(int *)(param_1 + 0x3c));
          *puVar8 = 0xffffffff;
          puVar8[1] = 0xffffffff;
        }
        else {
          puVar8 = (undefined4 *)(iVar1 + *(int *)(param_1 + 0x3c));
          *puVar8 = *(undefined4 *)(param_1 + 8);
          puVar8[1] = *(undefined4 *)(param_1 + 0xc);
        }
      }
      if ((*(uint *)(*(int *)(param_1 + 0x3c) + iVar7 * 8) &
          *(uint *)(*(int *)(param_1 + 0x3c) + 4 + iVar7 * 8)) != 0xffffffff) {
        local_38 = 0;
        local_34 = 0;
        iVar1 = param_1 + 0x78;
        iVar9 = -1;
        FUN_0069d2f0(iVar1,*(undefined4 *)(*(int *)(param_1 + 0x40) + iVar7 * 4));
        do {
          FUN_00677ba0(param_1,local_30,0xffffffff,0xffffffff);
          lVar11 = CONCAT44(local_34,local_38);
          if ((extraout_EDX < 0) ||
             (iVar4 = FUN_0069cb00(local_30), lVar11 = CONCAT44(local_34,local_38),
             iVar4 != *(int *)(*(int *)(param_1 + 0x40) + iVar7 * 4))) goto LAB_0067839e;
          FUN_0069cf90(iVar1,local_30);
          iVar4 = FUN_0069d310(iVar1,local_20);
          while (iVar4 != 0) {
            iVar5 = iVar9;
            if ((0 < iVar4) &&
               (iVar5 = FUN_0067b380(iVar7 * 0x20 + *(int *)(param_1 + 0x48),local_20), iVar9 != -1)
               ) {
              uVar6 = iVar5 + iVar9 >> 2;
              bVar10 = CARRY4(local_38,uVar6);
              local_38 = local_38 + uVar6;
              local_34 = local_34 + (iVar5 + iVar9 >> 0x1f) + (uint)bVar10;
            }
            iVar4 = FUN_0069d310(iVar1,local_20);
            iVar9 = iVar5;
          }
          lVar11 = FUN_0069ca20(local_30);
        } while (lVar11 == -1);
        lVar11 = FUN_0069ca20(local_30);
        lVar11 = lVar11 - CONCAT44(local_34,local_38);
LAB_0067839e:
        local_34 = (int)((ulonglong)lVar11 >> 0x20);
        if ((local_34 < 1) && (lVar11 < 0)) {
          lVar11 = 0;
        }
        *(longlong *)(iVar7 * 0x10 + *(int *)(param_1 + 0x44)) = lVar11;
      }
      FUN_00677f40(param_1,*(undefined4 *)(*(int *)(param_1 + 0x38) + 8 + iVar7 * 8),
                   *(undefined4 *)(*(int *)(param_1 + 0x38) + 0xc + iVar7 * 8));
      while (lVar11 = FUN_00677e20(param_1,local_30), -1 < lVar11) {
        lVar12 = FUN_0069ca20(local_30);
        if (lVar12 != -1) {
          plVar2 = (longlong *)(iVar7 * 0x10 + *(int *)(param_1 + 0x44));
          lVar11 = FUN_0069ca20(local_30);
          plVar2[1] = lVar11 - *plVar2;
          goto LAB_00678469;
        }
        *(longlong *)(param_1 + 8) = lVar11;
      }
      FUN_00679b90(iVar7 * 0x20 + *(int *)(param_1 + 0x48));
      FUN_00679ad0(iVar7 * 0x10 + *(int *)(param_1 + 0x4c));
LAB_00678469:
      iVar7 = iVar7 + 1;
    } while (iVar7 < *(int *)(param_1 + 0x34));
  }
  return;
}

