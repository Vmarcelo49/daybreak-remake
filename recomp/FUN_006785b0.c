// ============================================
// Address:  0x006785b0
// Original: FUN_006785b0
// Status:   unreviewed
// ============================================


undefined4 FUN_006785b0(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int extraout_EDX;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  undefined8 uVar10;
  int local_1a4;
  uint local_1a0;
  int local_19c;
  undefined1 local_198 [16];
  undefined1 local_188 [16];
  uint local_178;
  uint local_174;
  undefined1 local_168 [360];
  
  if (1 < *(int *)(param_1 + 0x58)) {
    if (*(int *)(param_1 + 4) == 0) {
      return 0xffffff76;
    }
    if (((-1 < param_3) && (param_3 <= *(int *)(param_1 + 0x14))) &&
       ((param_3 < *(int *)(param_1 + 0x14) || (param_2 <= *(uint *)(param_1 + 0x10))))) {
      iVar5 = param_1 + 0x78;
      *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x54) = 0xffffffff;
      FUN_0069d2f0(iVar5,*(undefined4 *)(param_1 + 0x5c));
      FUN_0067a9d0(param_1 + 0x1e0);
      FUN_00677f40(param_1,param_2,param_3);
      local_1a4 = 0;
      local_1a0 = 0;
      FUN_0069cb60(local_168,*(undefined4 *)(param_1 + 0x5c));
      FUN_0069d2a0(local_168);
      iVar7 = 0;
      do {
        while ((*(int *)(param_1 + 0x58) < 3 ||
               (iVar1 = FUN_0069d310(local_168,local_188), iVar1 < 1))) {
LAB_0067871a:
          if (iVar7 != 0) {
            *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
            *(undefined4 *)(param_1 + 0x54) = 0xffffffff;
            goto LAB_0067888d;
          }
          FUN_00677ba0(param_1,local_198,0xffffffff,0xffffffff);
          if (extraout_EDX < 0) {
            uVar10 = FUN_006784b0(param_1,0xffffffff);
            *(undefined8 *)(param_1 + 0x50) = uVar10;
            goto LAB_0067888d;
          }
          if (*(int *)(param_1 + 0x58) < 3) {
LAB_00678777:
            iVar2 = FUN_0069cb00(local_198);
            iVar1 = *(int *)(param_1 + 0x34);
            iVar4 = 0;
            *(int *)(param_1 + 0x5c) = iVar2;
            if (0 < iVar1) {
              piVar6 = *(int **)(param_1 + 0x40);
              do {
                iVar7 = local_1a4;
                if (*piVar6 == iVar2) break;
                iVar4 = iVar4 + 1;
                piVar6 = piVar6 + 1;
              } while (iVar4 < iVar1);
            }
            if (iVar4 == iVar1) {
              *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
              *(undefined4 *)(param_1 + 0x54) = 0xffffffff;
              FUN_0069cbd0(local_168);
              FUN_00678480(param_1);
              return 0xffffff77;
            }
            *(int *)(param_1 + 0x60) = iVar4;
            FUN_0069d2f0(iVar5,iVar2);
            FUN_0069d2f0(local_168,*(undefined4 *)(param_1 + 0x5c));
            *(undefined4 *)(param_1 + 0x58) = 3;
          }
          else {
            iVar1 = FUN_0069cb00(local_198);
            if (*(int *)(param_1 + 0x5c) != iVar1) {
              FUN_00678480(param_1);
              FUN_0069cbd0(local_168);
            }
            if (*(int *)(param_1 + 0x58) < 3) goto LAB_00678777;
          }
          FUN_0069cf90(iVar5,local_198);
          FUN_0069cf90(local_168,local_198);
          local_19c = FUN_0069ca10(local_198);
        }
        iVar1 = *(int *)(param_1 + 0x60) * 0x20;
        if (*(int *)(iVar1 + 0x1c + *(int *)(param_1 + 0x48)) == 0) {
          FUN_0069d310(iVar5,0);
          goto LAB_0067871a;
        }
        local_1a4 = FUN_0067b380(iVar1 + *(int *)(param_1 + 0x48),local_188);
        if (local_1a4 < 0) {
          FUN_0069d310(iVar5,0);
          local_1a4 = 0;
        }
        else if (local_19c == 0) {
          if (iVar7 != 0) {
            local_1a0 = local_1a0 + (local_1a4 + iVar7 >> 2);
          }
        }
        else {
          FUN_0069d310(iVar5,0);
        }
        iVar7 = local_1a4;
      } while ((local_178 & local_174) == 0xffffffff);
      iVar5 = *(int *)(param_1 + 0x60);
      iVar7 = *(int *)(param_1 + 0x44);
      puVar3 = (uint *)(iVar5 * 0x10 + iVar7);
      uVar8 = local_178 - *puVar3;
      iVar1 = (local_174 - *(int *)(iVar5 * 0x10 + 4 + iVar7)) - (uint)(local_178 < *puVar3);
      if ((iVar1 < 1) && (iVar1 < 0)) {
        uVar8 = 0;
        iVar1 = 0;
      }
      if (0 < iVar5) {
        puVar3 = (uint *)(iVar7 + 8);
        do {
          bVar9 = CARRY4(uVar8,*puVar3);
          uVar8 = uVar8 + *puVar3;
          iVar1 = iVar1 + puVar3[1] + (uint)bVar9;
          puVar3 = puVar3 + 4;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      *(uint *)(param_1 + 0x50) = uVar8 - local_1a0;
      *(uint *)(param_1 + 0x54) = (iVar1 - ((int)local_1a0 >> 0x1f)) - (uint)(uVar8 < local_1a0);
LAB_0067888d:
      FUN_0069cbd0(local_168);
      *(undefined4 *)(param_1 + 0x68) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      return 0;
    }
  }
  return 0xffffff7d;
}

