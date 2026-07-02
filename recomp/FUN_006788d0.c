// ============================================
// Address:  0x006788d0
// Original: FUN_006788d0
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00678c32) */
/* WARNING: Removing unreachable block (ram,0x00678a2e) */
/* WARNING: Removing unreachable block (ram,0x00678941) */
/* WARNING: Removing unreachable block (ram,0x00678b66) */
/* WARNING: Removing unreachable block (ram,0x00678e59) */
/* WARNING: Removing unreachable block (ram,0x00678c67) */

undefined4 FUN_006788d0(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  undefined4 uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int extraout_EDX;
  uint extraout_EDX_00;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  bool bVar17;
  longlong lVar18;
  undefined8 uVar19;
  longlong lVar20;
  longlong lVar21;
  int local_84;
  int local_80;
  undefined4 local_7c;
  uint local_74;
  uint local_6c;
  int local_68;
  uint local_58;
  int local_54;
  uint local_40;
  int local_3c;
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  uint local_10;
  uint local_c;
  
  lVar18 = FUN_006784b0(param_1,0xffffffff);
  if (1 < *(int *)(param_1 + 0x58)) {
    if (*(int *)(param_1 + 4) == 0) {
      return 0xffffff76;
    }
    if ((-1 < param_3) && (CONCAT44(param_3,param_2) <= lVar18)) {
      iVar7 = *(int *)(param_1 + 0x34) + -1;
      lVar20 = lVar18;
      if (-1 < iVar7) {
        puVar8 = (uint *)(*(int *)(param_1 + 0x44) + 8 + iVar7 * 0x10);
        do {
          uVar15 = (uint)lVar18;
          iVar11 = ((int)((ulonglong)lVar18 >> 0x20) - puVar8[1]) - (uint)(uVar15 < *puVar8);
          lVar3 = lVar18 - *(longlong *)puVar8;
          lVar2 = lVar18 - *(longlong *)puVar8;
          lVar20 = lVar18 - *(longlong *)puVar8;
          lVar18 = lVar18 - *(longlong *)puVar8;
          if ((iVar11 < param_3) ||
             ((iVar11 <= param_3 && (lVar20 = lVar2, uVar15 - *puVar8 <= param_2)))) break;
          iVar7 = iVar7 + -1;
          puVar8 = puVar8 + -4;
          lVar20 = lVar3;
        } while (-1 < iVar7);
      }
      local_68 = (int)((ulonglong)lVar20 >> 0x20);
      local_6c = (uint)lVar20;
      iVar11 = *(int *)(param_1 + 0x38);
      iVar14 = *(int *)(iVar11 + 0xc + iVar7 * 8);
      uVar15 = *(uint *)(iVar11 + 8 + iVar7 * 8);
      iVar12 = *(int *)(iVar11 + 4 + iVar7 * 8);
      local_74 = *(uint *)(iVar11 + iVar7 * 8);
      lVar20 = CONCAT44(iVar12,local_74);
      puVar8 = (uint *)(iVar7 * 0x10 + *(int *)(param_1 + 0x44));
      uVar16 = *puVar8;
      iVar13 = puVar8[2] + uVar16;
      iVar9 = puVar8[3] + puVar8[1] + (uint)CARRY4(puVar8[2],uVar16);
      uVar10 = (uVar16 - local_6c) + param_2;
      iVar11 = ((puVar8[1] - local_68) - (uint)(uVar16 < local_6c)) + param_3 +
               (uint)CARRY4(uVar16 - local_6c,param_2);
      lVar18 = lVar20;
      if ((iVar12 <= iVar14) &&
         ((lVar2 = *(longlong *)puVar8, lVar5 = CONCAT44(iVar9,iVar13),
          lVar18 = CONCAT44(iVar12,local_74), lVar3 = CONCAT44(iVar14,uVar15), iVar12 < iVar14 ||
          (lVar2 = *(longlong *)puVar8, lVar5 = CONCAT44(iVar9,iVar13), lVar18 = lVar20,
          lVar3 = CONCAT44(iVar14,uVar15), local_74 < uVar15)))) {
        do {
          local_54 = (int)((ulonglong)lVar2 >> 0x20);
          local_58 = (uint)lVar2;
          lVar20 = lVar3 - CONCAT44(iVar12,local_74);
          iVar14 = iVar12;
          uVar15 = local_74;
          if (0x2133 < lVar20) {
            uVar19 = __allmul(uVar10 - local_58,(iVar11 - local_54) - (uint)(uVar10 < local_58),
                              lVar20);
            lVar20 = __alldiv(uVar19,lVar5 - lVar2);
            lVar20 = lVar20 + CONCAT44(iVar12,local_74);
            uVar16 = (uint)lVar20;
            uVar15 = uVar16 - 0x2134;
            iVar14 = (int)((ulonglong)lVar20 >> 0x20) - (uint)(uVar16 < 0x2134);
            if ((iVar14 <= iVar12) && ((iVar14 < iVar12 || (uVar15 <= local_74)))) {
              iVar14 = iVar12 + (uint)(0xfffffffe < local_74);
              uVar15 = local_74 + 1;
            }
          }
          FUN_00677f40(param_1,uVar15,iVar14);
LAB_00678aaa:
          local_80 = (int)((ulonglong)lVar3 >> 0x20);
          local_84 = (int)lVar3;
          lVar20 = FUN_00677ba0(param_1,local_30,lVar3 - *(longlong *)(param_1 + 8));
          local_7c = (undefined4)lVar20;
          if (lVar20 == -0x80) goto LAB_00678e8b;
          if ((lVar20 < 0x100000000) && (lVar20 < 0)) {
            iVar9 = iVar12 + (uint)(0xfffffffe < local_74);
            if ((iVar14 < iVar9) || ((iVar14 <= iVar9 && (uVar15 <= local_74 + 1)))) break;
            if (uVar15 == 0 && iVar14 == 0) goto LAB_00678e8b;
            uVar16 = uVar15 - 0x2134;
            iVar14 = iVar14 + -1 + (uint)(0x2133 < uVar15);
            uVar15 = uVar16;
            lVar20 = lVar3;
            if ((iVar14 <= iVar12) && ((iVar14 < iVar12 || (uVar16 <= local_74)))) {
              iVar14 = iVar9;
              uVar15 = local_74 + 1;
            }
LAB_00678c1b:
            FUN_00677f40(param_1,uVar15,iVar14);
            lVar3 = lVar20;
LAB_00678c26:
            if (lVar3 <= CONCAT44(iVar12,local_74)) break;
            goto LAB_00678aaa;
          }
          lVar21 = FUN_0069ca20(local_30);
          if (lVar21 == -1) goto LAB_00678c26;
          if (lVar21 < CONCAT44(iVar11,uVar10)) {
            uVar15 = *(uint *)(param_1 + 8);
            iVar12 = *(int *)(param_1 + 0xc);
            uVar16 = (uint)(uVar10 < (uint)lVar21);
            uVar1 = iVar11 - (int)((ulonglong)lVar21 >> 0x20);
            bVar17 = -1 < (int)(uVar1 - uVar16);
            local_74 = uVar15;
            lVar2 = lVar21;
            lVar4 = lVar5;
            lVar18 = lVar20;
            if ((uVar1 != uVar16 && bVar17) ||
               ((iVar14 = iVar12, bVar17 && (0xac44 < uVar10 - (uint)lVar21)))) goto LAB_00678c5b;
            goto LAB_00678c26;
          }
          local_40 = local_74 + 1;
          local_3c = iVar12 + (uint)(0xfffffffe < local_74);
          if ((iVar14 < local_3c) || ((iVar14 <= local_3c && (uVar15 <= local_40)))) break;
          lVar4 = lVar21;
          lVar3 = lVar20;
          if ((local_84 == *(int *)(param_1 + 8)) && (local_80 == *(int *)(param_1 + 0xc))) {
            uVar16 = uVar15 - 0x2134;
            iVar14 = iVar14 + -1 + (uint)(0x2133 < uVar15);
            uVar15 = uVar16;
            if ((iVar14 <= iVar12) && ((iVar14 < iVar12 || (uVar16 <= local_74)))) {
              iVar14 = local_3c;
              uVar15 = local_40;
            }
            goto LAB_00678c1b;
          }
LAB_00678c5b:
          lVar5 = lVar4;
        } while (CONCAT44(iVar12,local_74) < lVar3);
      }
      FUN_00677f40(param_1,lVar18);
      *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x54) = 0xffffffff;
      FUN_00677ba0(param_1,&local_40,0xffffffff,0xffffffff);
      if ((extraout_EDX < 1) && (extraout_EDX < 0)) {
        return 0xfffffffe;
      }
      if (iVar7 == *(int *)(param_1 + 0x60)) {
        FUN_0067a9d0(param_1 + 0x1e0);
      }
      else {
        FUN_00678480(param_1);
        *(int *)(param_1 + 0x60) = iVar7;
        uVar6 = FUN_0069cb00(&local_40);
        *(undefined4 *)(param_1 + 0x5c) = uVar6;
        *(undefined4 *)(param_1 + 0x58) = 3;
      }
      iVar7 = param_1 + 0x78;
      FUN_0069d2f0(iVar7,*(undefined4 *)(param_1 + 0x5c));
      FUN_0069cf90(iVar7,&local_40);
      do {
        iVar11 = FUN_0069d460(iVar7,local_20);
        if (iVar11 == 0) {
          FUN_00677f40(param_1,lVar18);
          while( true ) {
            lVar18 = FUN_00677e20(param_1,&local_40);
            local_7c = (undefined4)lVar18;
            if (lVar18 < 0) break;
            FUN_0069ca20(&local_40);
            if ((extraout_EDX_00 < 0x80000000) || (iVar7 = FUN_0069c9f0(&local_40), iVar7 == 0)) {
              uVar6 = FUN_006785b0(param_1,lVar18);
              return uVar6;
            }
            *(longlong *)(param_1 + 8) = lVar18;
          }
LAB_00678e8b:
          *(undefined4 *)(param_1 + 0x50) = 0xffffffff;
          *(undefined4 *)(param_1 + 0x54) = 0xffffffff;
          FUN_00678480(param_1);
          return local_7c;
        }
        if (iVar11 >> 0x1f < 0) {
          local_7c = 0xffffff78;
          goto LAB_00678e8b;
        }
        if ((local_10 & local_c) != 0xffffffff) {
          puVar8 = (uint *)(*(int *)(param_1 + 0x60) * 0x10 + *(int *)(param_1 + 0x44));
          uVar15 = *puVar8;
          uVar16 = puVar8[1];
          *(uint *)(param_1 + 0x50) = local_10 - *puVar8;
          iVar7 = (local_c - uVar16) - (uint)(local_10 < uVar15);
          *(int *)(param_1 + 0x54) = iVar7;
          if ((iVar7 < 1) && (iVar7 < 0)) {
            *(undefined4 *)(param_1 + 0x50) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
          }
          uVar15 = *(uint *)(param_1 + 0x50);
          *(uint *)(param_1 + 0x50) = uVar15 + local_6c;
          iVar7 = *(int *)(param_1 + 0x54) + local_68 + (uint)CARRY4(uVar15,local_6c);
          *(int *)(param_1 + 0x54) = iVar7;
          if ((iVar7 <= param_3) &&
             (((iVar7 < param_3 || (*(uint *)(param_1 + 0x50) <= param_2)) &&
              (lVar18 = FUN_006784b0(param_1,0xffffffff), CONCAT44(param_3,param_2) <= lVar18)))) {
            *(undefined4 *)(param_1 + 0x68) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            return 0;
          }
          local_7c = 0xffffff7f;
          goto LAB_00678e8b;
        }
        FUN_0069d310(iVar7,0);
      } while( true );
    }
  }
  return 0xffffff7d;
}

