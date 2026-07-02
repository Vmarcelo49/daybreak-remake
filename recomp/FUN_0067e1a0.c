// ============================================
// Address:  0x0067e1a0
// Original: FUN_0067e1a0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

undefined4 FUN_0067e1a0(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  byte bVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  void *pvVar7;
  int *piVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  size_t asStack_3c [4];
  undefined4 local_2c;
  int local_28;
  int local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  puVar4 = param_2;
  puVar3 = param_1;
  iVar16 = 0;
  puVar5 = param_1;
  for (iVar14 = 0xb; iVar14 != 0; iVar14 = iVar14 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  iVar14 = param_2[1];
  if (0 < iVar14) {
    piVar8 = (int *)param_2[2];
    iVar15 = iVar14;
    do {
      if (0 < *piVar8) {
        iVar16 = iVar16 + 1;
      }
      piVar8 = piVar8 + 1;
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
  }
  param_1[1] = iVar14;
  param_1[2] = iVar16;
  *param_1 = *param_2;
  local_2c = param_2[1];
  asStack_3c[3] = param_2[2];
  asStack_3c[2] = 0x67e1ec;
  local_28 = iVar16;
  puVar5 = (undefined4 *)FUN_0067dc10();
  local_28 = 0x67e206;
  iVar14 = iVar16 * -4;
  piVar8 = (int *)(&stack0xffffffdc + iVar16 * -8);
  if (puVar5 == (undefined4 *)0x0) {
    asStack_3c[5 - iVar16] = (size_t)param_1;
    asStack_3c[4 - iVar16] = 0x67e218;
    FUN_0067e0e0();
    return 0xffffffff;
  }
  if (0 < iVar16) {
    param_1 = puVar5;
    local_c = (int *)iVar16;
    do {
      asStack_3c[5 - iVar16] = *param_1;
      asStack_3c[4 - iVar16] = 0x67e242;
      uVar6 = FUN_0067e570();
      *param_1 = uVar6;
      *(int **)(&stack0xffffffdc + (iVar14 - (int)puVar5) + (int)param_1) = param_1;
      param_1 = param_1 + 1;
      local_c = (int *)((int)local_c + -1);
    } while (local_c != (int *)0x0);
  }
  asStack_3c[5 - iVar16] = (size_t)&LAB_0067e5d0;
  asStack_3c[4 - iVar16] = 4;
  asStack_3c[3 - iVar16] = iVar16;
  asStack_3c[2 - iVar16] = (size_t)(&stack0xffffffdc + iVar14);
  asStack_3c[1 - iVar16] = 0x67e270;
  _qsort((void *)asStack_3c[2 - iVar16],asStack_3c[3 - iVar16],asStack_3c[4 - iVar16],
         (_PtFuncCompare *)asStack_3c[5 - iVar16]);
  asStack_3c[5 - iVar16] = 0x67e280;
  asStack_3c[iVar16 * -2 + 5] = iVar16 * 4;
  asStack_3c[iVar16 * -2 + 4] = 0x67e28c;
  pvVar7 = _malloc(asStack_3c[iVar16 * -2 + 5]);
  puVar3[5] = pvVar7;
  iVar15 = 0;
  local_c = (int *)(&stack0xffffffdc + iVar14);
  if (0 < iVar16) {
    do {
      *(int *)(&stack0xffffffdc + (*local_c - (int)puVar5 >> 2) * 4 + iVar16 * -8) = iVar15;
      iVar15 = iVar15 + 1;
      local_c = local_c + 1;
    } while (iVar15 < iVar16);
    if (0 < iVar16) {
      local_14 = iVar16;
      do {
        iVar14 = *piVar8;
        puVar1 = (undefined4 *)(((int)puVar5 - (int)(&stack0xffffffdc + iVar16 * -8)) + (int)piVar8)
        ;
        piVar8 = piVar8 + 1;
        *(undefined4 *)(puVar3[5] + iVar14 * 4) = *puVar1;
        local_14 = local_14 + -1;
      } while (local_14 != 0);
    }
  }
  asStack_3c[iVar16 * -2 + 5] = (size_t)puVar5;
  asStack_3c[iVar16 * -2 + 4] = 0x67e2f9;
  _free((void *)asStack_3c[iVar16 * -2 + 5]);
  asStack_3c[iVar16 * -2 + 4] = (size_t)(&stack0xffffffdc + iVar16 * -8);
  asStack_3c[iVar16 * -2 + 3] = iVar16;
  asStack_3c[iVar16 * -2 + 2] = (size_t)param_2;
  asStack_3c[iVar16 * -2 + 1] = 0x67e304;
  uVar6 = FUN_0067de00();
  puVar3[4] = uVar6;
  asStack_3c[iVar16 * -2 + 1] = iVar16 * 4;
  asStack_3c[iVar16 * -2] = 0x67e310;
  pvVar7 = _malloc(asStack_3c[iVar16 * -2 + 1]);
  puVar3[6] = pvVar7;
  piVar8 = param_2 + 1;
  iVar15 = 0;
  iVar14 = 0;
  param_2 = (int *)(&stack0xffffffdc + iVar16 * -8);
  if (0 < *piVar8) {
    do {
      if (0 < *(int *)(puVar4[2] + iVar14 * 4)) {
        iVar15 = iVar15 + 1;
        *(int *)(puVar3[6] + *param_2 * 4) = iVar14;
        param_2 = param_2 + 1;
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < (int)puVar4[1]);
  }
  asStack_3c[iVar16 * -2 + 5] = iVar15;
  asStack_3c[iVar16 * -2 + 4] = 0x67e353;
  pvVar7 = _malloc(asStack_3c[iVar16 * -2 + 5]);
  puVar3[7] = pvVar7;
  iVar14 = 0;
  param_2 = (int *)0x0;
  param_1 = (int *)(&stack0xffffffdc + iVar16 * -8);
  if (0 < (int)puVar4[1]) {
    do {
      if (0 < *(int *)(puVar4[2] + iVar14 * 4)) {
        *(undefined1 *)(puVar3[7] + *param_1) = *(undefined1 *)(puVar4[2] + iVar14 * 4);
        param_2 = (int *)((int)param_2 + 1);
        param_1 = param_1 + 1;
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < (int)puVar4[1]);
  }
  asStack_3c[iVar16 * -2 + 5] = puVar3[2];
  asStack_3c[iVar16 * -2 + 4] = 0x67e3a6;
  iVar14 = FUN_00682f70();
  puVar3[9] = iVar14 + -4;
  if (iVar14 + -4 < 5) {
    puVar3[9] = 5;
  }
  if (8 < (int)puVar3[9]) {
    puVar3[9] = 8;
  }
  iVar15 = 1 << ((byte)puVar3[9] & 0x1f);
  asStack_3c[iVar16 * -2 + 5] = 4;
  asStack_3c[iVar16 * -2 + 4] = iVar15;
  asStack_3c[iVar16 * -2 + 3] = 0x67e3df;
  pvVar7 = _calloc(asStack_3c[iVar16 * -2 + 4],asStack_3c[iVar16 * -2 + 5]);
  puVar3[8] = pvVar7;
  iVar14 = 0;
  puVar3[10] = 0;
  if (0 < (int)param_2) {
    do {
      iVar9 = (int)*(char *)(puVar3[7] + iVar14);
      if ((int)puVar3[10] < iVar9) {
        puVar3[10] = iVar9;
      }
      if ((int)*(char *)(puVar3[7] + iVar14) <= (int)puVar3[9]) {
        asStack_3c[iVar16 * -2 + 5] = *(undefined4 *)(puVar3[5] + iVar14 * 4);
        asStack_3c[iVar16 * -2 + 4] = 0x67e41d;
        uVar10 = FUN_0067e570();
        iVar9 = 0;
        bVar2 = *(byte *)(puVar3[7] + iVar14);
        if (0 < 1 << ((char)puVar3[9] - bVar2 & 0x1f)) {
          do {
            uVar11 = iVar9 << (bVar2 & 0x1f);
            iVar9 = iVar9 + 1;
            *(int *)(puVar3[8] + (uVar11 | uVar10) * 4) = iVar14 + 1;
            bVar2 = *(byte *)(puVar3[7] + iVar14);
          } while (iVar9 < 1 << ((char)puVar3[9] - bVar2 & 0x1f));
        }
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < (int)param_2);
  }
  uVar6 = puVar3[9];
  uVar10 = 0;
  param_1 = (int *)0x0;
  local_8 = 0;
  local_10 = 0;
  if (0 < iVar15) {
    do {
      uVar11 = local_10 << (0x20U - (char)puVar3[9] & 0x1f);
      asStack_3c[iVar16 * -2 + 5] = uVar11;
      asStack_3c[iVar16 * -2 + 4] = 0x67e4b1;
      iVar14 = FUN_0067e570();
      if (*(int *)(puVar3[8] + iVar14 * 4) == 0) {
        iVar14 = uVar10 + 1;
        if (iVar14 < (int)param_2) {
          puVar12 = (uint *)(puVar3[5] + iVar14 * 4);
          do {
            param_1 = (int *)uVar10;
            if (uVar11 < *puVar12) break;
            uVar10 = uVar10 + 1;
            iVar14 = iVar14 + 1;
            puVar12 = puVar12 + 1;
            param_1 = (int *)uVar10;
          } while (iVar14 < (int)param_2);
        }
        if (local_8 < (int)param_2) {
          puVar12 = (uint *)(puVar3[5] + local_8 * 4);
          do {
            uVar10 = (uint)param_1;
            if (uVar11 < (*puVar12 & -2 << (0x1fU - (char)uVar6 & 0x1f))) break;
            puVar12 = puVar12 + 1;
            local_8 = local_8 + 1;
          } while (local_8 < (int)param_2);
        }
        uVar13 = (int)param_2 - local_8;
        if (0x7fff < param_1) {
          uVar10 = 0x7fff;
        }
        if (0x7fff < uVar13) {
          uVar13 = 0x7fff;
        }
        asStack_3c[iVar16 * -2 + 5] = uVar11;
        asStack_3c[iVar16 * -2 + 4] = 0x67e53e;
        iVar14 = FUN_0067e570();
        *(uint *)(puVar3[8] + iVar14 * 4) = (uVar10 | 0xffff0000) << 0xf | uVar13;
        uVar10 = (uint)param_1;
      }
      local_10 = local_10 + 1;
    } while (local_10 < iVar15);
  }
  return 0;
}

