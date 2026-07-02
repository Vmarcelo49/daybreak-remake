// Function: FUN_0069cf90
// Address:  0x0069cf90
// Source:   batch_decompile (mass dump)
// Hash:     47d1b754312cad95


undefined4 FUN_0069cf90(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  size_t _Size;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined8 uVar14;
  undefined4 *local_2c;
  uint local_28;
  int local_24;
  
  iVar12 = 0;
  iVar1 = *param_2;
  local_2c = (undefined4 *)param_2[2];
  local_28 = param_2[3];
  iVar2 = FUN_0069c9e0(param_2);
  iVar3 = FUN_0069c9f0(param_2);
  local_24 = FUN_0069ca00(param_2);
  iVar4 = FUN_0069ca10(param_2);
  uVar14 = FUN_0069ca20(param_2);
  iVar5 = FUN_0069cb00(param_2);
  iVar6 = FUN_0069cb30(param_2);
  uVar8 = (uint)*(byte *)(iVar1 + 0x1a);
  iVar11 = param_1[3];
  iVar9 = param_1[9];
  if (iVar11 != 0) {
    _Size = param_1[2] - iVar11;
    param_1[2] = _Size;
    if (_Size != 0) {
      _memmove((void *)*param_1,(void *)(*param_1 + iVar11),_Size);
    }
    param_1[3] = 0;
  }
  if (iVar9 != 0) {
    if (param_1[7] != iVar9) {
      _memmove((void *)param_1[4],(void *)(param_1[4] + iVar9 * 4),
               (iVar9 * 0x3fffffff + param_1[7]) * 4);
      _memmove((void *)param_1[5],(void *)(param_1[5] + iVar9 * 8),
               (iVar9 * 0x1fffffff + param_1[7]) * 8);
    }
    param_1[7] = param_1[7] - iVar9;
    param_1[8] = param_1[8] - iVar9;
    param_1[9] = 0;
  }
  if (iVar5 != param_1[0x54]) {
    return 0xffffffff;
  }
  if (0 < iVar2) {
    return 0xffffffff;
  }
  FUN_0069cd00(param_1,uVar8 + 1);
  if (iVar6 != param_1[0x55]) {
    iVar11 = param_1[8];
    if (iVar11 < param_1[7]) {
      iVar9 = param_1[7] - iVar11;
      puVar7 = (uint *)(param_1[4] + iVar11 * 4);
      do {
        uVar10 = *puVar7;
        puVar7 = puVar7 + 1;
        param_1[2] = param_1[2] - (uVar10 & 0xff);
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
    param_1[7] = iVar11;
    if (param_1[0x55] != -1) {
      *(undefined4 *)(param_1[4] + iVar11 * 4) = 0x400;
      param_1[7] = param_1[7] + 1;
      param_1[8] = param_1[8] + 1;
    }
    if ((iVar3 != 0) && (local_24 = 0, uVar8 != 0)) {
      do {
        uVar10 = (uint)*(byte *)(iVar1 + 0x1b + iVar12);
        local_2c = (undefined4 *)((int)local_2c + uVar10);
        local_28 = local_28 - uVar10;
        if (uVar10 < 0xff) {
          iVar12 = iVar12 + 1;
          break;
        }
        iVar12 = iVar12 + 1;
      } while (iVar12 < (int)uVar8);
    }
  }
  if (local_28 != 0) {
    FUN_0069ccd0(param_1,local_28);
    puVar13 = (undefined4 *)(param_1[2] + *param_1);
    for (uVar10 = local_28 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *puVar13 = *local_2c;
      local_2c = local_2c + 1;
      puVar13 = puVar13 + 1;
    }
    for (uVar10 = local_28 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined1 *)puVar13 = *(undefined1 *)local_2c;
      local_2c = (undefined4 *)((int)local_2c + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    }
    param_1[2] = param_1[2] + local_28;
  }
  iVar11 = -1;
  if (iVar12 < (int)uVar8) {
    do {
      uVar10 = (uint)*(byte *)(iVar1 + 0x1b + iVar12);
      *(uint *)(param_1[4] + param_1[7] * 4) = uVar10;
      iVar9 = param_1[7];
      iVar2 = param_1[5];
      *(undefined4 *)(iVar2 + iVar9 * 8) = 0xffffffff;
      *(undefined4 *)(iVar2 + 4 + iVar9 * 8) = 0xffffffff;
      if (local_24 != 0) {
        local_24 = 0;
        puVar7 = (uint *)(param_1[4] + param_1[7] * 4);
        *puVar7 = *puVar7 | 0x100;
      }
      if (uVar10 < 0xff) {
        iVar11 = param_1[7];
      }
      iVar9 = param_1[7];
      iVar12 = iVar12 + 1;
      param_1[7] = iVar9 + 1;
      if (uVar10 < 0xff) {
        param_1[8] = iVar9 + 1;
      }
    } while (iVar12 < (int)uVar8);
    if (iVar11 != -1) {
      iVar1 = param_1[5];
      *(int *)(iVar1 + iVar11 * 8) = (int)uVar14;
      *(int *)(iVar1 + 4 + iVar11 * 8) = (int)((ulonglong)uVar14 >> 0x20);
    }
  }
  if (iVar4 != 0) {
    iVar1 = param_1[7];
    param_1[0x52] = 1;
    if (0 < iVar1) {
      *(uint *)(param_1[4] + -4 + iVar1 * 4) = *(uint *)(param_1[4] + -4 + iVar1 * 4) | 0x200;
    }
  }
  param_1[0x55] = iVar6 + 1;
  return 0;
}

