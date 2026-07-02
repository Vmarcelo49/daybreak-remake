// ============================================
// Address:  0x004072b0
// Original: FUN_004072b0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_004072b0(int param_1)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_6c;
  undefined4 local_68;
  int local_3c;
  int local_38;
  int local_34;
  uint local_28;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (*(int *)(param_1 + 0x2e18) < 3) {
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    cVar6 = FUN_00650f70();
    if (cVar6 != '\0') {
      FUN_00650f40();
      if (0 < *(int *)(param_1 + 0x2e18)) {
        for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
          FUN_00655d60(0x44160000,(float)local_8 * 300.0 + 300.0);
        }
      }
      FUN_00655d60(0,0);
      if (0 < *(int *)(param_1 + 0x2e18)) {
        for (local_c = 0; local_c < 2; local_c = local_c + 1) {
          if (*(int *)(param_1 + 0x2e28 + local_c * 4) < 2) {
            FUN_00655830(0x44180000,(float)*(int *)(param_1 + 0x2e28 + local_c * 4) * 304.0,0,0);
          }
        }
      }
      for (local_10 = 0; local_10 < 0xe; local_10 = local_10 + 1) {
        local_18 = 0;
        local_14 = 0;
        if (*(int *)(param_1 + 0x2e20) < 5) {
          if ((local_10 == *(int *)(param_1 + 0x2e20)) ||
             (local_10 == *(int *)(param_1 + 0x2e20) + 1)) {
            iVar8 = (*(int *)(param_1 + 0x2e14) % 0x28) / 10;
            local_18 = (iVar8 + 1) % 3;
            local_14 = (iVar8 + 1) / 3;
            FUN_004082f0(0xffffffff);
          }
          else {
            FUN_004082f0(0xff808080);
          }
        }
        else if (*(int *)(param_1 + 0x2e20) == 5) {
          if ((local_10 == 5) || (local_10 == 0)) {
            iVar8 = (*(int *)(param_1 + 0x2e14) % 0x28) / 10;
            local_18 = (iVar8 + 1) % 3;
            local_14 = (iVar8 + 1) / 3;
            FUN_004082f0(0xffffffff);
          }
          else {
            FUN_004082f0(0xff808080);
          }
        }
        else if ((local_10 == *(int *)(param_1 + 0x2e20) * 2 + -6) ||
                (local_10 == *(int *)(param_1 + 0x2e20) * 2 + -5)) {
          iVar8 = (*(int *)(param_1 + 0x2e14) % 0x28) / 10;
          local_18 = (iVar8 + 1) % 3;
          local_14 = (iVar8 + 1) / 3;
          FUN_004082f0(0xffffffff);
        }
        else {
          FUN_004082f0(0xff808080);
        }
        FUN_00655830(*(float *)(&DAT_006b7120 + local_10 * 4) * 47.0 + 112.0,
                     *(float *)(&DAT_006b7158 + local_10 * 4) * 34.0 + 112.0,local_18,local_14);
      }
      FUN_00655d60(0x43c80000,0x43960000);
      FUN_00655d60(0x43c80000,0x43960000);
      if (0 < *(int *)(param_1 + 0x2e18)) {
        for (local_28 = 0; (int)local_28 < 2; local_28 = local_28 + 1) {
          if ((*(char *)(param_1 + local_28 + 0x2ea8) != '\0') ||
             (-1 < *(int *)(param_1 + 0x2e90 + local_28 * 4))) {
            uVar9 = local_28 & 0x80000001;
            if ((int)uVar9 < 0) {
              uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830(0x44368000,(float)(int)uVar9 * 300.0 + 120.0,
                         *(int *)(param_1 + 0x2e80 + local_28 * 4) % 3,
                         *(int *)(param_1 + 0x2e80 + local_28 * 4) / 3);
          }
          bVar4 = true;
          bVar5 = false;
          bVar3 = true;
          bVar2 = true;
          if (-1 < *(int *)(param_1 + 0x2e90 + local_28 * 4)) {
            bVar5 = true;
            iVar8 = *(int *)(param_1 + 0x2e98 + *(int *)(param_1 + 0x2e90 + local_28 * 4) * 4);
            if (iVar8 == 1) {
              bVar2 = false;
            }
            else if (iVar8 == 3) {
              bVar4 = false;
            }
            else if (iVar8 == 4) {
              bVar3 = false;
            }
          }
          if ((-1 < *(int *)(param_1 + 0x2e40 + local_28 * 4)) && (bVar2)) {
            if (*(int *)(param_1 + 0x2e40 + local_28 * 4) < 4) {
              uVar9 = local_28 & 0x80000001;
              if ((int)uVar9 < 0) {
                uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
              }
              FUN_00655830(0x44368000,(float)(int)uVar9 * 300.0 + 180.0,
                           *(undefined4 *)(param_1 + 0x2e40 + local_28 * 4),0);
            }
            else {
              uVar9 = local_28 & 0x80000001;
              if ((int)uVar9 < 0) {
                uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
              }
              FUN_00655830(0x44368000,(float)(int)uVar9 * 300.0 + 180.0,0,2);
            }
          }
          if ((-1 < *(int *)(param_1 + 0x2e70 + local_28 * 4)) && (bVar3)) {
            FUN_00408250(0x3f000000);
            uVar9 = local_28 & 0x80000001;
            if ((int)uVar9 < 0) {
              uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830(0x44368000,(float)(int)uVar9 * 300.0 + 265.0,0,
                         *(undefined4 *)(param_1 + 0x2e70 + local_28 * 4));
            FUN_00408250(0x3f800000);
          }
          if ((-1 < *(int *)(param_1 + 0x2e60 + local_28 * 4)) && (bVar4)) {
            FUN_00408250(0x3f000000);
            uVar9 = local_28 & 0x80000001;
            if ((int)uVar9 < 0) {
              uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830(0x44368000,(float)(int)uVar9 * 300.0 + 240.0,0,
                         *(undefined4 *)(param_1 + 0x2e60 + local_28 * 4));
            FUN_00408250(0x3f800000);
          }
          if (((-1 < (char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + local_28]) && (bVar5))
             || (-1 < *(int *)(param_1 + 0x2e40 + local_28 * 4))) {
            uVar9 = (int)(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + local_28] &
                    0x80000007;
            if ((int)uVar9 < 0) {
              uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
            }
            uVar10 = local_28 & 0x80000001;
            if ((int)uVar10 < 0) {
              uVar10 = (uVar10 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830(0x44368000,(float)(int)uVar10 * 300.0 + 210.0,
                         (int)((int)(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + local_28]
                              + ((int)(char)(&DAT_006b710c)
                                            [*(int *)(param_1 + 0x2e20) * 2 + local_28] >> 0x1f & 7U
                                )) >> 3,uVar9);
          }
          if (-1 < *(int *)(param_1 + 0x2e90 + local_28 * 4)) {
            fVar1 = *(float *)(param_1 + 0x2eb4 + *(int *)(param_1 + 0x2e90 + local_28 * 4) * 4);
            iVar8 = *(int *)(param_1 + 0x2e98 + *(int *)(param_1 + 0x2e90 + local_28 * 4) * 4);
            if (iVar8 == 1) {
              FUN_00655830(fVar1 + 610.0,(float)(int)local_28 * 300.0 + 50.0,0,4);
              FUN_004082f0(0x80ffffff);
              if ((*(int *)(param_1 + 0x2ea0 + *(int *)(param_1 + 0x2e90 + local_28 * 4) * 4) < 0)
                 || (*(int *)(param_1 + 0x2e30 + local_28 * 4) != 1)) {
                local_68 = 0;
              }
              else {
                local_68 = 1;
              }
              FUN_00655830(fVar1 + 618.0,(float)(int)local_28 * 300.0 + 130.0,local_68,
                           (1 - *(int *)(param_1 + 0x2e30 + local_28 * 4)) * 2);
              FUN_004082f0(0xffffffff);
              if ((*(int *)(param_1 + 0x2ea0 + *(int *)(param_1 + 0x2e90 + local_28 * 4) * 4) < 0)
                 || (*(int *)(param_1 + 0x2e30 + local_28 * 4) != 0)) {
                local_6c = 0;
              }
              else {
                local_6c = 1;
              }
              FUN_00655830(0x44188000,(float)(int)local_28 * 300.0 + 110.0,local_6c,
                           *(int *)(param_1 + 0x2e30 + local_28 * 4) << 1);
              FUN_00655d60(0x44188000,(float)(int)local_28 * 300.0 + 110.0);
            }
            else if (iVar8 == 3) {
              FUN_00655830(fVar1 + 610.0,(float)(int)local_28 * 300.0 + 50.0,0,1);
              for (local_34 = 2; -1 < local_34; local_34 = local_34 + -1) {
                FUN_004082f0((0xff >> ((byte)local_34 & 0x1f)) << 0x18 | 0xffffff);
                uVar9 = local_28 & 0x80000001;
                if ((int)uVar9 < 0) {
                  uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)local_34 * 8.0 + 100.0 + 510.0,
                             (float)(int)uVar9 * 300.0 + (float)local_34 * 20.0 + 110.0,0,
                             (*(int *)(param_1 + 0x2e30 + local_28 * 4) + local_34) % 3);
              }
              FUN_00655830(0x44188000,(float)(int)local_28 * 300.0 + 200.0,1,
                           *(undefined4 *)(param_1 + 0x2e30 + local_28 * 4));
              FUN_00655d60(0x44188000,(float)(int)local_28 * 300.0 + 110.0);
            }
            else if (iVar8 == 4) {
              FUN_00655830(fVar1 + 610.0,(float)(int)local_28 * 300.0 + 50.0,0,3);
              for (local_38 = 2; -1 < local_38; local_38 = local_38 + -1) {
                FUN_004082f0((0xff >> ((byte)local_38 & 0x1f)) << 0x18 | 0xffffff);
                FUN_00655830((float)local_38 * 8.0 + 100.0 + 510.0,
                             (float)(int)local_28 * 300.0 + (float)local_38 * 20.0 + 110.0,0,
                             (*(int *)(param_1 + 0x2e30 + local_28 * 4) + local_38) % 3);
              }
              FUN_00655830(0x44188000,(float)(int)local_28 * 300.0 + 200.0,0,
                           *(int *)(param_1 + 0x2e30 + local_28 * 4) + 2);
              FUN_00655d60(0x44188000,(float)(int)local_28 * 300.0 + 110.0);
            }
          }
          if (*(char *)(param_1 + local_28 + 0x2ea8) != '\0') {
            FUN_00408250(*(undefined4 *)(param_1 + 0x2eac + local_28 * 4));
            FUN_00655d60(0x44160000,(float)(int)local_28 * 300.0 + 110.0);
          }
        }
        FUN_00655830(0x43a80000,0x44098000,0,1);
        FUN_00655830(0x43e80000,0x44098000,1,1);
        for (local_3c = 0; local_3c < 2; local_3c = local_3c + 1) {
          if (1 < *(int *)(param_1 + 0x2e28 + local_3c * 4)) {
            FUN_00655830((float)((*(int *)(param_1 + 0x2e28 + local_3c * 4) + -2) * 2 + -1) * 64.0 +
                         400.0,0x44098000,local_3c,0);
          }
        }
      }
      if (*(char *)(param_1 + 0x2ebc) != '\0') {
        FUN_00651860(0,0,0x44480000,0x44160000,(uint)*(byte *)(param_1 + 0x2ebc) << 0x18);
      }
      FUN_00650fd0();
    }
    uVar7 = 1;
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}

