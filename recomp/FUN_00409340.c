// ============================================
// Address:  0x00409340
// Original: FUN_00409340
// Status:   unreviewed
// ============================================


void __thiscall FUN_00409340(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  if (DAT_006cfdb0 == '\0') {
    FUN_00657390();
  }
  else if ((&DAT_006cfb18)[param_2] == 0) {
    cVar1 = FUN_00645e10();
    if (cVar1 != '\0') {
      return;
    }
    FUN_00657390();
  }
  else {
    if ((int)(&DAT_006cfb18)[param_2] < 1) {
      return;
    }
    FUN_00657390();
  }
  local_c = &DAT_006cae94 + param_2 * 0x19;
  local_8 = *(int *)(param_1 + 0x3c48 + param_2 * 4) % 3 +
            (*(int *)(param_1 + 0x3c48 + param_2 * 4) / 3) * 2;
  local_10 = *(int *)(param_1 + 0x3c90 + param_2 * 4);
  switch(*(undefined4 *)(param_1 + 0x3c90 + param_2 * 4)) {
  case 0:
    if (*(int *)(param_1 + 0x3c48 + param_2 * 4) < 0) {
      if (((*local_c != 0) || ((&DAT_006cae98)[param_2 * 0x19] != 0)) ||
         ((&DAT_006cae9c)[param_2 * 0x19] != 0)) {
        *(uint *)(param_1 + 0x3c48 + param_2 * 4) = (uint)(1 < param_2) + param_2;
      }
    }
    else {
      iVar2 = FUN_00403aa0(*local_c);
      if (iVar2 == 1) {
        if ((*(int *)(param_1 + 0x3c48 + param_2 * 4) == 5) && (*local_c == 1)) {
          *(undefined4 *)(param_1 + 0x3c48 + param_2 * 4) = 4;
        }
        else if ((*(int *)(param_1 + 0x3c48 + param_2 * 4) == 2) && (*local_c == -1)) {
          *(undefined4 *)(param_1 + 0x3c48 + param_2 * 4) = 1;
        }
        else {
          uVar5 = *(int *)(param_1 + 0x3c48 + param_2 * 4) / 3 + 2 + *local_c & 0x80000001;
          if ((int)uVar5 < 0) {
            uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
          }
          *(uint *)(param_1 + 0x3c48 + param_2 * 4) =
               uVar5 * 3 + *(int *)(param_1 + 0x3c48 + param_2 * 4) % 3;
        }
        FUN_0064aed0(2);
      }
      else {
        iVar2 = FUN_00403aa0(local_c[1]);
        if (iVar2 == 1) {
          *(int *)(param_1 + 0x3c48 + param_2 * 4) =
               (*(int *)(param_1 + 0x3c48 + param_2 * 4) + 3 + local_c[1]) % 3 +
               (*(int *)(param_1 + 0x3c48 + param_2 * 4) / 3) * 3;
          FUN_0064aed0(2);
        }
      }
      local_8 = *(int *)(param_1 + 0x3c48 + param_2 * 4) % 3 +
                (*(int *)(param_1 + 0x3c48 + param_2 * 4) / 3) * 2;
      if ((*(int *)(param_1 + 0x3c48 + param_2 * 4) == 2) ||
         (*(int *)(param_1 + 0x3c48 + param_2 * 4) == 5)) {
        if (local_c[2] == 1) {
          if ((((*(int *)(param_1 + 0x3c48 + param_2 * 4) == 2) && (*(int *)(param_1 + 0x3c90) == 0)
               ) && (*(int *)(param_1 + 0x3c94) == 0)) &&
             ((*(int *)(param_1 + 0x3c98) == 0 && (*(int *)(param_1 + 0x3c9c) == 0)))) {
            FUN_0064aed0(0);
            *(undefined4 *)(param_1 + 0x3c58) = 0;
            *(undefined1 *)(param_1 + 0x3c40) = 1;
          }
          if ((*(int *)(param_1 + 0x3c48 + param_2 * 4) == 5) ||
             (cVar1 = FUN_006586d0(1), cVar1 != '\0')) {
            FUN_0064aed0(1);
            *(undefined1 *)(param_1 + 0x3c43) = 1;
          }
        }
      }
      else if (((local_c[3] == 1) && (*(int *)(param_1 + 0x3c80 + local_8 * 4) < 0)) &&
              ((*(int *)(param_1 + 0x3cf8 + local_8 * 4) == param_2 ||
               (*(int *)(param_1 + 0x3cf8 + local_8 * 4) == 4)))) {
        *(undefined4 *)(param_1 + 0x3d08 + local_8 * 4) = 0xffffffff;
        if (*(int *)(param_1 + 0x3cf8 + local_8 * 4) == param_2) {
          *(undefined4 *)(param_1 + 0x3ca0 + param_2 * 4) = 0xffffffff;
        }
        *(undefined4 *)(param_1 + 0x3cf8 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3d18 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3d28 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3d38 + local_8 * 4) = 0;
        *(undefined1 *)(param_1 + local_8 + 0x3cd4) = 0;
        *(undefined1 *)(param_1 + local_8 + 0x3cb0) = 0;
      }
      else if (((local_c[2] == 1) && (*(int *)(param_1 + 0x3c80 + local_8 * 4) < 0)) &&
              (*(int *)(param_1 + 0x3cf8 + local_8 * 4) < 0)) {
        FUN_0064aed0(0);
        *(undefined1 *)(param_1 + local_8 + 0x3cb0) = 0;
        *(int *)(param_1 + 0x3c80 + local_8 * 4) = param_2;
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 2;
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) = 0;
        *(undefined4 *)(param_1 + 0x3d38 + local_8 * 4) = 0;
        *(undefined1 *)(param_1 + local_8 + 0x3cd4) = 0;
        *(float *)(param_1 + 0x3cd8 + local_8 * 4) =
             *(float *)(&DAT_006b71d0 + *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 48.0;
        *(float *)(param_1 + 0x3ce8 + local_8 * 4) =
             *(float *)(&DAT_006b7210 + *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 36.0;
      }
      if (((local_c[8] == 1) && (*(int *)(param_1 + 0x3c90) == 0)) &&
         ((*(int *)(param_1 + 0x3c94) == 0 &&
          ((*(int *)(param_1 + 0x3c98) == 0 && (*(int *)(param_1 + 0x3c9c) == 0)))))) {
        FUN_0064aed0(0);
        *(undefined4 *)(param_1 + 0x3c58) = 0;
        *(undefined1 *)(param_1 + 0x3c40) = 1;
      }
    }
    break;
  case 1:
    if (((&DAT_006caea8)[param_2 * 0x19] == 0) ||
       (((&DAT_006cae9c)[param_2 * 0x19] == 0 && ((&DAT_006caea0)[param_2 * 0x19] == 0)))) {
      iVar2 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
      if ((iVar2 == 1) && (*(int *)(param_1 + 0x3ca0 + param_2 * 4) < 0)) {
        FUN_0064aed0(2);
        uVar5 = *(int *)(param_1 + 0x3c58 + local_8 * 4) + 2 + local_c[1] & 0x80000001;
        if ((int)uVar5 < 0) {
          uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
        }
        *(uint *)(param_1 + 0x3c58 + local_8 * 4) = uVar5;
      }
      if (local_c[2] == 1) {
        *(undefined1 *)(param_1 + local_8 + 0x3cd4) = 0;
        FUN_0064aed0(0);
        if (*(int *)(param_1 + 0x3c58 + local_8 * 4) == 0) {
          *(int *)(param_1 + 0x3ca0 + param_2 * 4) = local_8;
          *(int *)(param_1 + 0x3cf8 + local_8 * 4) = param_2;
          if (DAT_006cfdb0 != '\0') {
            if ((local_8 == 0) || (local_8 == 2)) {
              local_1c = local_8 + 1;
            }
            else {
              local_1c = local_8 + -1;
            }
            if ((*(char *)(param_1 + local_1c + 0x3cd4) == '\x01') &&
               ((((&DAT_006b72a0)[*(int *)(param_1 + 0x3d08 + local_8 * 4)] == '\0' ||
                 (*(int *)(param_1 + 0x3d08 + local_8 * 4) == 2)) &&
                (*(int *)(param_1 + 0x3d08 + local_1c * 4) != 2)))) {
              *(undefined1 *)(param_1 + local_8 + 0x3cd4) = 2;
            }
            if (((-1 < (int)(&DAT_006cfb18)[param_2]) &&
                ((&DAT_006cfdf1)[(&DAT_006cfb18)[param_2]] != '\0')) &&
               ((&DAT_006b72a0)[*(int *)(param_1 + 0x3d08 + local_8 * 4)] != '\0')) {
              *(int *)(param_1 + 0x3d38 + local_8 * 4) =
                   (int)(char)(&DAT_006b72a0)[*(int *)(param_1 + 0x3d08 + local_8 * 4)];
              *(undefined1 *)(param_1 + local_8 + 0x3cd4) = 1;
            }
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x3cf8 + local_8 * 4) = 4;
        }
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 8;
        *(undefined4 *)(param_1 + 0x3cb4 + local_8 * 4) = 0x40800000;
        *(undefined1 *)(param_1 + local_8 + 0x3cb0) = 1;
        FUN_0065b1d0(*(undefined4 *)(param_1 + 0x3c38));
        if (*(char *)(param_1 + local_8 + 0x3cd4) == '\x02') {
          uVar5 = FUN_0065d150();
          uVar5 = uVar5 % 2;
          uVar3 = FUN_00649770(*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
          wsprintfA((LPSTR)(param_1 + 0x3b34),"data/voice/entry/%s_C%02d.wav",uVar3,uVar5);
        }
        else if (*(char *)(param_1 + local_8 + 0x3cd4) == '\x01') {
          if (((*(int *)(param_1 + 0x3d08 + local_8 * 4) == 0) ||
              (*(int *)(param_1 + 0x3d08 + local_8 * 4) == 4)) &&
             (*(int *)(param_1 + 0x3d18 + local_8 * 4) == 2)) {
            uVar5 = FUN_0065d150();
            uVar5 = uVar5 % 2;
            uVar3 = FUN_00649770(*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
            wsprintfA((LPSTR)(param_1 + 0x3b34),"data/voice/entry/%sB_B%02d.wav",uVar3,uVar5);
          }
          else {
            uVar5 = FUN_0065d150();
            uVar5 = uVar5 % 2;
            uVar3 = FUN_00649770(*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
            wsprintfA((LPSTR)(param_1 + 0x3b34),"data/voice/entry/%s_B%02d.wav",uVar3,uVar5);
          }
        }
        else if (((*(int *)(param_1 + 0x3d08 + local_8 * 4) == 0) ||
                 (*(int *)(param_1 + 0x3d08 + local_8 * 4) == 4)) &&
                (*(int *)(param_1 + 0x3d18 + local_8 * 4) == 2)) {
          uVar3 = FUN_00649770(*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
          wsprintfA((LPSTR)(param_1 + 0x3b34),"data/voice/entry/%sB.wav",uVar3);
        }
        else {
          uVar3 = FUN_00649770(*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
          wsprintfA((LPSTR)(param_1 + 0x3b34),"data/voice/entry/%s.wav",uVar3);
        }
        puVar4 = (undefined4 *)FUN_0065b0d0(local_20,param_1 + 0x3b34);
        *(undefined4 *)(param_1 + 0x3c38) = *puVar4;
        FUN_0065b330(*(undefined4 *)(param_1 + 0x3c38),0);
      }
      else if (local_c[3] == 1) {
        FUN_0064aed0(1);
        if (*(int *)(param_1 + 0x3ca0 + param_2 * 4) == local_8) {
          *(undefined4 *)(param_1 + 0x3ca0 + param_2 * 4) = 0xffffffff;
        }
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 4;
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) =
             *(undefined4 *)(param_1 + 0x3d28 + local_8 * 4);
        *(undefined4 *)(param_1 + 0x3cf8 + local_8 * 4) = 0xffffffff;
      }
    }
    break;
  case 2:
    if ((int)(&DAT_006cae98)[param_2 * 0x19] < 0) {
      *(float *)(param_1 + 0x3ce8 + local_8 * 4) = *(float *)(param_1 + 0x3ce8 + local_8 * 4) - 3.0;
    }
    else if (0 < (int)(&DAT_006cae98)[param_2 * 0x19]) {
      *(float *)(param_1 + 0x3ce8 + local_8 * 4) = *(float *)(param_1 + 0x3ce8 + local_8 * 4) + 3.0;
    }
    if (*local_c < 0) {
      *(float *)(param_1 + 0x3cd8 + local_8 * 4) = *(float *)(param_1 + 0x3cd8 + local_8 * 4) - 4.0;
    }
    else if (0 < *local_c) {
      *(float *)(param_1 + 0x3cd8 + local_8 * 4) = *(float *)(param_1 + 0x3cd8 + local_8 * 4) + 4.0;
    }
    if (200.0 < *(float *)(param_1 + 0x3cd8 + local_8 * 4)) {
      *(undefined4 *)(param_1 + 0x3cd8 + local_8 * 4) = 0x43480000;
    }
    if (*(float *)(param_1 + 0x3cd8 + local_8 * 4) < -200.0) {
      *(undefined4 *)(param_1 + 0x3cd8 + local_8 * 4) = 0xc3480000;
    }
    if (300.0 < *(float *)(param_1 + 0x3ce8 + local_8 * 4)) {
      *(undefined4 *)(param_1 + 0x3ce8 + local_8 * 4) = 0x43960000;
    }
    if (*(float *)(param_1 + 0x3ce8 + local_8 * 4) < -60.0) {
      *(undefined4 *)(param_1 + 0x3ce8 + local_8 * 4) = 0xc2700000;
    }
    if (((-1 < *(int *)(param_1 + 0x3c58 + local_8 * 4)) && (*local_c == 0)) &&
       ((&DAT_006cae98)[param_2 * 0x19] == 0)) {
      fVar6 = (float10)FUN_0040da40(*(float *)(&DAT_006b71d0 +
                                              *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 48.0 -
                                    *(float *)(param_1 + 0x3cd8 + local_8 * 4),2);
      fVar7 = (float10)FUN_0040da40(*(float *)(&DAT_006b7210 +
                                              *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 36.0 -
                                    *(float *)(param_1 + 0x3ce8 + local_8 * 4),2);
      if (fVar7 + (float10)(float)fVar6 < (float10)400.0) {
        *(float *)(param_1 + 0x3cd8 + local_8 * 4) =
             *(float *)(&DAT_006b71d0 + *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 48.0;
        *(float *)(param_1 + 0x3ce8 + local_8 * 4) =
             *(float *)(&DAT_006b7210 + *(int *)(param_1 + 0x3c58 + local_8 * 4) * 4) * 36.0;
      }
    }
    for (local_14 = 0; local_14 < 0x10; local_14 = local_14 + 1) {
      fVar6 = (float10)FUN_0040da40(*(float *)(&DAT_006b71d0 + local_14 * 4) * 48.0 -
                                    *(float *)(param_1 + 0x3cd8 + local_8 * 4),2);
      fVar7 = (float10)FUN_0040da40(*(float *)(&DAT_006b7210 + local_14 * 4) * 36.0 -
                                    *(float *)(param_1 + 0x3ce8 + local_8 * 4),2);
      if (fVar7 + (float10)(float)fVar6 < (float10)2500.0) break;
    }
    for (local_18 = 0; local_18 < 0x10; local_18 = local_18 + 1) {
      fVar6 = (float10)FUN_0040da40(*(float *)(&DAT_006b71d0 + local_18 * 4) * 48.0 -
                                    *(float *)(param_1 + 0x3cd8 + local_8 * 4),2);
      fVar7 = (float10)FUN_0040da40(*(float *)(&DAT_006b7210 + local_18 * 4) * 36.0 -
                                    *(float *)(param_1 + 0x3ce8 + local_8 * 4),2);
      if (fVar7 + (float10)(float)fVar6 < (float10)900.0) {
        if (*(int *)(param_1 + 0x3c58 + local_8 * 4) != local_18) {
          FUN_0064aed0(2);
          *(int *)(param_1 + 0x3c58 + local_8 * 4) = local_18;
        }
        break;
      }
    }
    if (local_18 == 0x10) {
      if (local_14 == 0x10) {
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) = 0xffffffff;
      }
      else if (*(int *)(param_1 + 0x3c58 + local_8 * 4) != local_14) {
        FUN_0064aed0(2);
        *(int *)(param_1 + 0x3c58 + local_8 * 4) = local_14;
      }
    }
    *(undefined4 *)(param_1 + 0x3d08 + local_8 * 4) =
         *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4);
    if (local_c[2] == 1) {
      FUN_0064aed0(0);
      if (*(int *)(param_1 + 0x3d08 + local_8 * 4) < 0) {
        uVar5 = FUN_0065d150();
        *(uint *)(param_1 + 0x3d08 + local_8 * 4) = uVar5 % 0x10;
        if (*(int *)(param_1 + 0x3d08 + local_8 * 4) < 0xe) {
          uVar5 = FUN_0065d150();
          *(uint *)(param_1 + 0x3d18 + local_8 * 4) = uVar5 % 3;
        }
        else {
          uVar5 = FUN_0065d150();
          *(uint *)(param_1 + 0x3d18 + local_8 * 4) = uVar5 % 2;
        }
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 4;
      }
      else {
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 3;
      }
      *(undefined4 *)(param_1 + 0x3d38 + local_8 * 4) = 0;
      *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) = 0;
      FUN_0040d700(local_8,*(undefined4 *)(param_1 + 0x3d08 + local_8 * 4));
    }
    else if (local_c[3] == 1) {
      *(undefined4 *)(param_1 + 0x3d38 + local_8 * 4) = 0;
      FUN_0064aed0(1);
      if (*(int *)(param_1 + 0x3ca0 + param_2 * 4) == local_8) {
        *(undefined4 *)(param_1 + 0x3ca0 + param_2 * 4) = 0xffffffff;
      }
      *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 0;
      *(undefined4 *)(param_1 + 0x3c80 + local_8 * 4) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x3cf8 + local_8 * 4) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x3d08 + local_8 * 4) = 0xffffffff;
    }
    break;
  case 3:
    if (((&DAT_006caea8)[param_2 * 0x19] == 0) ||
       (((&DAT_006cae9c)[param_2 * 0x19] == 0 && ((&DAT_006caea0)[param_2 * 0x19] == 0)))) {
      if ((&DAT_006caea4)[param_2 * 0x19] != 0) {
        if (*(int *)(param_1 + 0x3d08 + local_8 * 4) < 0xe) {
          *(int *)(param_1 + 0x3c58 + local_8 * 4) =
               (*(int *)(param_1 + 0x3c58 + local_8 * 4) + 1) % 3;
        }
        else {
          uVar5 = *(int *)(param_1 + 0x3c58 + local_8 * 4) + 1U & 0x80000001;
          if ((int)uVar5 < 0) {
            uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
          }
          *(uint *)(param_1 + 0x3c58 + local_8 * 4) = uVar5;
        }
      }
      iVar2 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
      if (iVar2 == 1) {
        FUN_0064aed0(2);
        if (*(int *)(param_1 + 0x3d08 + local_8 * 4) < 0xe) {
          *(int *)(param_1 + 0x3c58 + local_8 * 4) =
               (*(int *)(param_1 + 0x3c58 + local_8 * 4) + 3 + local_c[1]) % 3;
        }
        else {
          uVar5 = *(int *)(param_1 + 0x3c58 + local_8 * 4) + 2 + local_c[1] & 0x80000001;
          if ((int)uVar5 < 0) {
            uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
          }
          *(uint *)(param_1 + 0x3c58 + local_8 * 4) = uVar5;
        }
      }
      *(undefined4 *)(param_1 + 0x3d18 + local_8 * 4) =
           *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4);
      if (local_c[2] == 1) {
        FUN_0064aed0(0);
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 4;
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) = 0;
      }
      else if (local_c[3] == 1) {
        FUN_0064aed0(1);
        *(undefined4 *)(param_1 + 0x3d18 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 2;
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) =
             *(undefined4 *)(param_1 + 0x3d08 + local_8 * 4);
        *(undefined4 *)(param_1 + 0x3d08 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3d38 + local_8 * 4) = 0;
      }
    }
    break;
  case 4:
    if (((&DAT_006caea8)[param_2 * 0x19] == 0) ||
       (((&DAT_006cae9c)[param_2 * 0x19] == 0 && ((&DAT_006caea0)[param_2 * 0x19] == 0)))) {
      if ((&DAT_006caea4)[param_2 * 0x19] != 0) {
        *(int *)(param_1 + 0x3c58 + local_8 * 4) =
             (*(int *)(param_1 + 0x3c58 + local_8 * 4) + 1) % 3;
      }
      iVar2 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
      if (iVar2 == 1) {
        FUN_0064aed0(2);
        *(int *)(param_1 + 0x3c58 + local_8 * 4) =
             (*(int *)(param_1 + 0x3c58 + local_8 * 4) + 3 + local_c[1]) % 3;
      }
      *(undefined4 *)(param_1 + 0x3d28 + local_8 * 4) =
           *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4);
      if (local_c[2] == 1) {
        FUN_0064aed0(0);
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 1;
        if (*(int *)(param_1 + 0x3ca0 + param_2 * 4) == local_8) {
          *(undefined4 *)(param_1 + 0x3ca0 + param_2 * 4) = 0xffffffff;
          *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) = 0;
        }
        else {
          *(uint *)(param_1 + 0x3c58 + local_8 * 4) =
               (uint)(-1 < *(int *)(param_1 + 0x3ca0 + param_2 * 4));
        }
      }
      else if (local_c[3] == 1) {
        FUN_0064aed0(1);
        *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 3;
        *(undefined4 *)(param_1 + 0x3d28 + local_8 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3c58 + local_8 * 4) =
             *(undefined4 *)(param_1 + 0x3d18 + local_8 * 4);
      }
    }
    break;
  case 8:
    if (*(float *)(param_1 + 0x3cb4 + local_8 * 4) <= 1.0) {
      FUN_0064aed0(3);
      *(undefined4 *)(param_1 + 0x3c90 + param_2 * 4) = 0;
      *(undefined4 *)(param_1 + 0x3c80 + local_8 * 4) = 0xffffffff;
    }
    else {
      *(float *)(param_1 + 0x3cb4 + local_8 * 4) = *(float *)(param_1 + 0x3cb4 + local_8 * 4) - 0.2;
    }
  }
  if (((*(int *)(param_1 + 0x3c90 + param_2 * 4) == 4) ||
      (*(int *)(param_1 + 0x3c90 + param_2 * 4) == 3)) ||
     (*(int *)(param_1 + 0x3c90 + param_2 * 4) == 1)) {
    if (local_c[5] == 0) {
      *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
    }
    else {
      switch(*(undefined4 *)(&DAT_006c7884 + param_2 * 4)) {
      case 0:
        *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        break;
      case 1:
        if (((*local_c != 0) || (0 < local_c[1])) || ((local_c[2] != 0 || (local_c[3] != 0)))) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
        break;
      case 3:
      case 4:
        if ((((*local_c != 0) || (local_c[1] < 0)) || (local_c[2] != 0)) || (local_c[3] != 0)) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
        break;
      case 6:
      case 10:
        if (((0 < *local_c) || (local_c[1] != 0)) || ((local_c[2] != 0 || (local_c[3] != 0)))) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
        break;
      case 8:
      case 0xc:
        if (((*local_c < 0) || (local_c[1] != 0)) || ((local_c[2] != 0 || (local_c[3] != 0)))) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
        break;
      case 0xe:
        if (((*local_c != 0) || (local_c[1] != 0)) || (local_c[2] != 0)) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
        break;
      case 0x10:
        if (((*local_c != 0) || (local_c[1] != 0)) || (local_c[3] != 0)) {
          *(undefined4 *)(&DAT_006c7884 + param_2 * 4) = 0;
        }
      }
      switch(*(undefined4 *)(&DAT_006c7884 + param_2 * 4)) {
      case 0:
        if (local_c[1] == -1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 1:
        if (local_c[1] == -1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 2:
        if (local_c[1] == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 3:
        if (local_c[1] == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 4:
        if (local_c[1] == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 5:
        if (local_c[1] == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 6:
        if (*local_c == -1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 7:
        if (*local_c == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 8:
        if (*local_c == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 9:
        if (*local_c == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 10:
        if (*local_c == -1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0xb:
        if (*local_c == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0xc:
        if (*local_c == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0xd:
        if (*local_c == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0xe:
        if (local_c[3] == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0xf:
        if (local_c[3] == 0) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0x10:
        if (local_c[2] == 1) {
          *(int *)(&DAT_006c7884 + param_2 * 4) = *(int *)(&DAT_006c7884 + param_2 * 4) + 1;
        }
        break;
      case 0x11:
        *(int *)(param_1 + 0x3d38 + local_8 * 4) =
             (int)(char)(&DAT_006b72a0)[*(int *)(param_1 + 0x3d08 + local_8 * 4)];
      }
    }
    if (*local_c == 1) {
      *(int *)(param_1 + 0x3d38 + local_8 * 4) =
           (*(int *)(param_1 + 0x3d38 + local_8 * 4) + 1) %
           (int)(char)(&DAT_006b7290)[*(int *)(param_1 + 0x3d08 + local_8 * 4)];
    }
    else if (*local_c == -1) {
      *(int *)(param_1 + 0x3d38 + local_8 * 4) =
           (*(int *)(param_1 + 0x3d38 + local_8 * 4) + -1 +
           (int)(char)(&DAT_006b7290)[*(int *)(param_1 + 0x3d08 + local_8 * 4)]) %
           (int)(char)(&DAT_006b7290)[*(int *)(param_1 + 0x3d08 + local_8 * 4)];
    }
  }
  if (*(int *)(param_1 + 0x3c90 + param_2 * 4) != local_10) {
    *(undefined4 *)(param_1 + 0x3cc4 + param_2 * 4) = 0x43960000;
  }
  if (0.0 < *(float *)(param_1 + 0x3cc4 + param_2 * 4)) {
    *(float *)(param_1 + 0x3cc4 + param_2 * 4) = *(float *)(param_1 + 0x3cc4 + param_2 * 4) - 20.0;
  }
  return;
}

