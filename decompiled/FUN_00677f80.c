// Function: FUN_00677f80
// Address:  0x00677f80
// Source:   batch_decompile (mass dump)
// Hash:     5d3f2b43f820a006


/* WARNING: Removing unreachable block (ram,0x00678097) */
/* WARNING: Removing unreachable block (ram,0x006780e3) */

undefined4
FUN_00677f80(int param_1,undefined4 param_2,undefined4 param_3,uint param_4,int param_5,uint param_6
            ,int param_7,int param_8,int param_9)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  longlong lVar4;
  longlong lVar5;
  int iVar6;
  undefined4 uVar7;
  void *pvVar8;
  bool bVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  uint local_28;
  int local_24;
  undefined1 local_10 [4];
  uint local_c;
  uint local_4;
  
  lVar12 = CONCAT44(param_5,param_4);
  local_28 = param_6;
  local_24 = param_7;
  lVar4 = CONCAT44(param_5,param_4);
  lVar5 = CONCAT44(param_7,param_6);
  if ((param_5 <= param_7) &&
     ((lVar4 = lVar12, lVar12 = CONCAT44(param_7,param_6), param_5 < param_7 ||
      (lVar5 = CONCAT44(param_7,param_6), lVar12 = CONCAT44(param_7,param_6), param_4 < param_6))))
  {
    do {
      uVar2 = (uint)(local_28 < (uint)lVar4);
      uVar3 = local_24 - (int)((ulonglong)lVar4 >> 0x20);
      bVar9 = -1 < (int)(uVar3 - uVar2);
      if ((uVar3 != uVar2 && bVar9) ||
         ((lVar10 = lVar4, bVar9 && (0x2133 < local_28 - (uint)lVar4)))) {
        lVar10 = __alldiv(lVar4 + CONCAT44(local_24,local_28),2,0);
      }
      param_5 = (int)((ulonglong)lVar10 >> 0x20);
      FUN_00677f40(param_1,lVar10);
      lVar11 = FUN_00677ba0(param_1,local_10,0xffffffff,0xffffffff);
      if (lVar11 == -0x80) {
        return 0xffffff80;
      }
      lVar5 = lVar12;
      if ((lVar11 < 0) || (iVar6 = FUN_0069cb00(local_10), iVar6 != param_8)) {
        local_24 = param_5;
        local_28 = (uint)lVar10;
        if (-1 < lVar11) {
          lVar5 = lVar11;
        }
      }
      else {
        lVar4 = lVar11 + CONCAT44(((int)local_4 >> 0x1f) + ((int)local_c >> 0x1f) +
                                  (uint)CARRY4(local_4,local_c),local_4 + local_c);
      }
      lVar12 = lVar5;
    } while (lVar4 < CONCAT44(local_24,local_28));
  }
  FUN_00677f40(param_1,lVar5);
  lVar12 = FUN_00677ba0(param_1,local_10,0xffffffff,0xffffffff);
  if (lVar12 == -0x80) {
    return 0xffffff80;
  }
  if ((lVar4 < CONCAT44(param_7,param_6)) && (-1 < lVar12)) {
    uVar7 = FUN_0069cb00(local_10,param_9 + 1);
    iVar6 = FUN_00677f80(param_1,lVar5,*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                         param_6,param_7,uVar7);
    if (iVar6 == -0x80) {
      return 0xffffff80;
    }
  }
  else {
    iVar6 = param_9 + 1;
    *(int *)(param_1 + 0x34) = iVar6;
    pvVar8 = _malloc(iVar6 * 8 + 8);
    *(void **)(param_1 + 0x38) = pvVar8;
    pvVar8 = _malloc(*(int *)(param_1 + 0x34) << 2);
    *(void **)(param_1 + 0x40) = pvVar8;
    iVar1 = *(int *)(param_1 + 0x38);
    *(int *)(iVar1 + iVar6 * 8) = (int)lVar4;
    *(int *)(iVar1 + 4 + iVar6 * 8) = (int)((ulonglong)lVar4 >> 0x20);
  }
  iVar6 = *(int *)(param_1 + 0x38);
  *(undefined4 *)(iVar6 + param_9 * 8) = param_2;
  *(undefined4 *)(iVar6 + 4 + param_9 * 8) = param_3;
  *(int *)(*(int *)(param_1 + 0x40) + param_9 * 4) = param_8;
  return 0;
}

