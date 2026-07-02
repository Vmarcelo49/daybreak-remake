// ============================================
// Address:  0x0041f580
// Original: FUN_0041f580
// Status:   unreviewed
// ============================================


void __fastcall FUN_0041f580(int param_1)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  float fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint local_38;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  int local_14;
  
  if (*(int *)(param_1 + 0x828) != 0) {
    *(int *)(param_1 + 0x828) = *(int *)(param_1 + 0x828) + -1;
  }
  if (*(int *)(param_1 + 0x82c) != 0) {
    *(int *)(param_1 + 0x82c) = *(int *)(param_1 + 0x82c) + -1;
  }
  if (*(int *)(param_1 + 0xa0) < 1) {
    iVar5 = FUN_00423700();
    if (iVar5 != 0) {
      *(undefined4 *)(param_1 + 0x7ac) = 0x1e;
      *(undefined4 *)(param_1 + 0x7c0) = 0;
      *(undefined4 *)(param_1 + 0x7c4) = 0;
      *(undefined4 *)(param_1 + 0x7b8) = 0;
      *(undefined4 *)(param_1 + 0x7bc) = 0;
    }
    iVar5 = FUN_004236c0();
    if (iVar5 == 0) {
      if (0 < *(int *)(param_1 + 0x7ac)) {
        *(int *)(param_1 + 0x7ac) = *(int *)(param_1 + 0x7ac) + -1;
      }
      if (*(int *)(param_1 + 0x7c4) < 1) {
        *(undefined4 *)(param_1 + 0x7b0) = 0;
        *(undefined4 *)(param_1 + 0x7c0) = 0;
        *(undefined4 *)(param_1 + 0x7c4) = 0;
      }
      else {
        *(int *)(param_1 + 0x7c4) = *(int *)(param_1 + 0x7c4) + -1;
      }
      if ((*(int *)(param_1 + 0x7a4) < *(int *)(param_1 + 0x7a8)) &&
         (*(int *)(param_1 + 0x7a8) = *(int *)(param_1 + 0x7a8) + -200,
         *(int *)(param_1 + 0x7a8) < *(int *)(param_1 + 0x7a4))) {
        *(undefined4 *)(param_1 + 0x7a8) = *(undefined4 *)(param_1 + 0x7a4);
      }
    }
    if (*(int *)(param_1 + 0x7bc) < 1) {
      *(undefined4 *)(param_1 + 0x7b8) = 0;
    }
    else {
      *(int *)(param_1 + 0x7bc) = *(int *)(param_1 + 0x7bc) + -1;
    }
  }
  else {
    *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + -1;
  }
  cVar1 = *(char *)(param_1 + 0x318);
  if (cVar1 == '\0') {
    if ((*(char *)(param_1 + 0x844) != '\0') &&
       (*(int *)(param_1 + 0x838) = *(int *)(param_1 + 0x838) + -1, *(int *)(param_1 + 0x838) < 1))
    {
      *(undefined4 *)(param_1 + 0x838) = 0;
      *(undefined1 *)(param_1 + 0x844) = 0;
    }
    if (*(char *)(param_1 + 0x334) != '\0') {
      *(char *)(param_1 + 0x334) = *(char *)(param_1 + 0x334) + -4;
    }
  }
  else if (cVar1 == '\x01') {
    if ((*(char *)(param_1 + 0x845) != '\0') &&
       (*(int *)(param_1 + 0x83c) = *(int *)(param_1 + 0x83c) + -1, *(int *)(param_1 + 0x83c) < 1))
    {
      *(undefined4 *)(param_1 + 0x83c) = 0;
      *(undefined1 *)(param_1 + 0x845) = 0;
    }
  }
  else if (cVar1 == '\x02') {
    if (*(char *)(param_1 + 0x846) != '\0') {
      if (*(int *)(param_1 + 0x834) < 1000) {
        *(int *)(param_1 + 0x834) = *(int *)(param_1 + 0x834) + 1;
      }
      if (*(int *)(param_1 + 0x7a4) < 1) {
        *(undefined4 *)(param_1 + 0x840) = 0;
        *(undefined1 *)(param_1 + 0x846) = 0;
      }
      else if (*(int *)(param_1 + 0x7a4) < 9) {
        *(undefined4 *)(param_1 + 0x7a4) = 1;
        *(undefined4 *)(param_1 + 0x840) = 0;
        *(undefined1 *)(param_1 + 0x846) = 0;
      }
      else {
        *(int *)(param_1 + 0x7a4) = *(int *)(param_1 + 0x7a4) + -7;
      }
    }
    if (*(char *)(param_1 + 0x334) != '\0') {
      *(char *)(param_1 + 0x334) = *(char *)(param_1 + 0x334) + -4;
    }
  }
  FUN_0065d670();
  FUN_0064e860();
  FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
  for (local_18 = 0; uVar3 = FUN_0063bf40(), local_18 < uVar3; local_18 = local_18 + 1) {
    piVar4 = (int *)FUN_00424230(local_18);
    local_1c = *(int *)(param_1 + 0xae04);
    if (0 < piVar4[2]) {
      local_1c = *(int *)(param_1 + 0xae04) % piVar4[2];
    }
    if ((*piVar4 <= local_1c) && (local_1c < piVar4[1])) {
      FUN_0064e820(piVar4[3],piVar4[4]);
    }
  }
  if ((*(char *)(param_1 + 0x844) != '\0') || (*(char *)(param_1 + 0x846) != '\0')) {
    FUN_0064e820(*(undefined4 *)(param_1 + 0x31c),*(undefined4 *)(param_1 + 800));
  }
  if (*(char *)(param_1 + 0x688) != '\0') {
    FUN_0064e820(*(undefined4 *)(param_1 + 0x68c),*(undefined4 *)(param_1 + 0x694));
    FUN_0064e820(*(undefined4 *)(param_1 + 0x690),*(undefined4 *)(param_1 + 0x698));
  }
  for (local_20 = 0; local_20 < 2; local_20 = local_20 + 1) {
    if (local_20 == 1) {
      piVar4 = (int *)FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
      local_14 = *piVar4;
    }
    else {
      piVar4 = (int *)FUN_004244e0(*(undefined4 *)(param_1 + 0xadf8));
      local_14 = *piVar4;
    }
    for (local_24 = 0; local_24 < 0x100; local_24 = local_24 + 1) {
      iVar5 = param_1 + 0x75e0 + local_24 * 0x38;
      if (*(float *)(iVar5 + 0xc + local_20 * 4) <= 0.0) {
        *(undefined4 *)(iVar5 + 4 + local_20 * 4) = 0;
      }
      else if (local_24 == local_14) {
        if (local_20 == 1) {
          *(float *)(iVar5 + 8) = (float)*(int *)(param_1 + 0xae04) * 0.016;
        }
        else {
          *(float *)(iVar5 + 4 + local_20 * 4) = (float)*(int *)(param_1 + 0xae08) * 0.016;
        }
      }
    }
    if (-1 < *(int *)(param_1 + 0xae14 + local_20 * 4)) {
      for (local_28 = 0; local_28 < 0x100; local_28 = local_28 + 1) {
        iVar5 = param_1 + 0x75e0 + local_28 * 0x38;
        if (local_28 == local_14) {
          *(float *)(iVar5 + 0xc + local_20 * 4) =
               ((1.0 - *(float *)(iVar5 + 0x14 + local_20 * 4)) *
               (float)(*(int *)(iVar5 + 0x1c) - *(int *)(param_1 + 0xae14 + local_20 * 4))) /
               (float)*(int *)(*(int *)(param_1 + 0xade4 + local_20 * 4) + 0x1c) +
               *(float *)(iVar5 + 0x14 + local_20 * 4);
        }
        else {
          *(float *)(iVar5 + 0xc + local_20 * 4) =
               ((float)*(int *)(param_1 + 0xae14 + local_20 * 4) *
               *(float *)(iVar5 + 0x14 + local_20 * 4)) /
               (float)*(int *)(*(int *)(param_1 + 0xade4 + local_20 * 4) + 0x1c);
        }
      }
      *(int *)(param_1 + 0xae14 + local_20 * 4) = *(int *)(param_1 + 0xae14 + local_20 * 4) + -1;
    }
  }
  FUN_0065d6a0();
  FUN_00434800();
  for (local_2c = 0; iVar5 = FUN_0064f010(), local_2c < iVar5; local_2c = local_2c + 1) {
    local_30 = 0;
    piVar4 = (int *)FUN_00658a10(local_2c);
    if (*(int *)(*piVar4 + 0x308) == param_1) {
      local_30 = 1;
      piVar4 = (int *)FUN_00658a10(local_2c);
      if (*(char *)(*piVar4 + 0xaec8) != '\0') {
        piVar4 = (int *)FUN_00658a10(local_2c);
        if (*piVar4 != *(int *)(param_1 + 0x308)) {
          FUN_0064af20(*(undefined4 *)(param_1 + 8),0x10);
        }
        local_30 = 2;
      }
    }
    if (local_30 == 0) {
      uVar10 = 0;
      uVar7 = 0;
      FUN_00424800(local_2c);
      FUN_004235d0(uVar7,uVar10);
    }
    else {
      piVar4 = (int *)FUN_00658a10(local_2c);
      fVar9 = *(float *)(*piVar4 + 0x14) - *(float *)(param_1 + 0x14);
      piVar4 = (int *)FUN_00658a10(local_2c);
      fVar6 = (float10)FUN_00423580(*(float *)(*piVar4 + 0x1c) - *(float *)(param_1 + 0x1c),fVar9);
      fVar9 = (float)((fVar6 / (float10)3.1415927) * (float10)180.0 -
                     (float10)*(float *)(param_1 + 0x5c));
      FUN_00424800(local_2c);
      FUN_004235d0(local_30,fVar9);
    }
  }
  if ((*(int *)(param_1 + 0x28c) == 0x1e) && (*(int *)(param_1 + 0x30c) == 0)) {
    FUN_00421f30(0);
  }
  piVar4 = (int *)FUN_00658a10(*(undefined4 *)(param_1 + 0x300));
  if (((((*(char *)(*piVar4 + 0xaecb) == '\0') || (-1 < *(int *)(param_1 + 0x304))) &&
       ((*(int *)(param_1 + 0x28c) != 1 || (*(int *)(param_1 + 0x30c) != 0)))) &&
      ((*(int *)(param_1 + 0x304) < 0 ||
       (piVar4 = (int *)FUN_00658a10(0), *(char *)(*piVar4 + 0xaecb) == '\0')))) &&
     ((*(char *)(*(int *)(param_1 + 0x308) + 0xaecc) == '\0' ||
      (*(int *)(param_1 + 0x308) != *(int *)(param_1 + 0xaed0))))) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    *(undefined4 *)(param_1 + 0x304) = 0xffffffff;
    iVar5 = *(int *)(param_1 + 0x300);
    local_38 = FUN_0064f010();
    local_38 = (iVar5 + 1U) % local_38;
    while ((piVar4 = (int *)FUN_00658a10(local_38), *(char *)(*piVar4 + 0xaecc) != '\0' &&
           (piVar4 = (int *)FUN_00658a10(local_38), *(int *)(*piVar4 + 0xaed0) == param_1))) {
      uVar3 = FUN_0064f010();
      local_38 = (local_38 + 1) % uVar3;
    }
    if (local_38 != *(uint *)(param_1 + 0x300)) {
      FUN_00421e30(local_38);
    }
  }
  piVar4 = (int *)FUN_00658a10(0);
  if (*(int *)(param_1 + 0x308) == *(int *)(*piVar4 + 0x308)) {
    *(undefined4 *)(param_1 + 0x848) = 0xb4;
  }
  else if (*(int *)(param_1 + 0x848) != 0) {
    *(int *)(param_1 + 0x848) = *(int *)(param_1 + 0x848) + -1;
  }
  if (*(int *)(param_1 + 0x298) == 1) {
    piVar4 = (int *)FUN_00658a10(0);
    if (*(char *)(*piVar4 + 0x860) == '\0') {
      if (DAT_006cfdb0 == '\x01') {
        if (*(int *)(param_1 + 0x7a4) < 0x9c4) {
          uVar11 = 1;
          uVar8 = 0x19;
          uVar10 = 3;
          uVar7 = 0xe;
          piVar4 = (int *)FUN_00658a10(0);
          FUN_00422730(*(undefined4 *)(*piVar4 + 8),uVar7,uVar10,uVar8,uVar11);
          FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,3,0xf,0);
        }
        else if (*(int *)(param_1 + 0x7a4) < 5000) {
          uVar11 = 1;
          uVar8 = 0x19;
          uVar10 = 2;
          uVar7 = 0xe;
          piVar4 = (int *)FUN_00658a10(0);
          FUN_00422730(*(undefined4 *)(*piVar4 + 8),uVar7,uVar10,uVar8,uVar11);
          FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,2,0xf,0);
        }
        else if (*(int *)(param_1 + 0x7a4) < 0x1d4c) {
          uVar11 = 1;
          uVar8 = 0x19;
          uVar10 = 1;
          uVar7 = 0xe;
          piVar4 = (int *)FUN_00658a10(0);
          FUN_00422730(*(undefined4 *)(*piVar4 + 8),uVar7,uVar10,uVar8,uVar11);
          FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,1,0xf,0);
        }
        else {
          uVar11 = 1;
          uVar8 = 0x19;
          uVar10 = 0;
          uVar7 = 0xe;
          piVar4 = (int *)FUN_00658a10(0);
          FUN_00422730(*(undefined4 *)(*piVar4 + 8),uVar7,uVar10,uVar8,uVar11);
          FUN_00422730(*(undefined4 *)(param_1 + 8),0xe,0,0xf,0);
        }
      }
    }
    else if (-1 < *(char *)(param_1 + 0x310)) {
      *(char *)(param_1 + 0x310) = (char)((*(char *)(param_1 + 0x310) + 1) % 6);
      piVar4 = (int *)FUN_00658a10(0);
      *(undefined1 *)(*piVar4 + 0x310) = *(undefined1 *)(param_1 + 0x310);
      *(undefined4 *)(param_1 + 0x314) = 0x40000000;
    }
  }
  return;
}

