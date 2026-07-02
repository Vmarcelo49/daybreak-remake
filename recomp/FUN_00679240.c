// ============================================
// Address:  0x00679240
// Original: FUN_00679240
// Status:   unreviewed
// ============================================


int FUN_00679240(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined1 *puVar9;
  int *piVar10;
  bool bVar11;
  undefined1 local_30 [4];
  int local_2c;
  undefined1 local_20 [32];
  
  do {
    if (*(int *)(param_1 + 0x58) == 4) {
      while( true ) {
        puVar9 = param_2;
        if (param_2 == (undefined1 *)0x0) {
          puVar9 = local_20;
        }
        iVar1 = FUN_0069d310(param_1 + 0x78,puVar9);
        param_2 = (undefined1 *)0x0;
        if (iVar1 == -1) {
          return -3;
        }
        if (iVar1 < 1) break;
        uVar5 = *(uint *)(puVar9 + 0x10);
        uVar7 = *(uint *)(puVar9 + 0x14);
        iVar1 = FUN_0067b150(param_1 + 0x250,puVar9);
        if (iVar1 == 0) {
          iVar1 = FUN_0067b0c0(param_1 + 0x1e0,0);
          if (iVar1 == 0) {
            FUN_0067aa70(param_1 + 0x1e0,param_1 + 0x250);
            iVar1 = FUN_0067b0c0(param_1 + 0x1e0,0);
            *(double *)(param_1 + 0x70) = (double)iVar1 + *(double *)(param_1 + 0x70);
            *(double *)(param_1 + 0x68) =
                 (double)(*(int *)(puVar9 + 4) << 3) + *(double *)(param_1 + 0x68);
            if (((uVar5 & uVar7) != 0xffffffff) && (*(int *)(puVar9 + 0xc) == 0)) {
              if (*(int *)(param_1 + 4) == 0) {
                iVar1 = 0;
              }
              else {
                iVar1 = *(int *)(param_1 + 0x60);
                if (0 < iVar1) {
                  puVar2 = (uint *)(iVar1 * 0x10 + *(int *)(param_1 + 0x44));
                  uVar3 = *puVar2;
                  bVar11 = uVar5 < uVar3;
                  uVar5 = uVar5 - uVar3;
                  uVar7 = (uVar7 - puVar2[1]) - (uint)bVar11;
                }
              }
              if (((int)uVar7 < 1) && ((int)uVar7 < 0)) {
                uVar5 = 0;
                uVar7 = 0;
              }
              uVar3 = FUN_0067b0c0(param_1 + 0x1e0,0);
              uVar6 = uVar5 - uVar3;
              iVar8 = (uVar7 - ((int)uVar3 >> 0x1f)) - (uint)(uVar5 < uVar3);
              if (0 < iVar1) {
                puVar2 = (uint *)(*(int *)(param_1 + 0x44) + 8);
                do {
                  bVar11 = CARRY4(uVar6,*puVar2);
                  uVar6 = uVar6 + *puVar2;
                  iVar8 = iVar8 + puVar2[1] + (uint)bVar11;
                  puVar2 = puVar2 + 4;
                  iVar1 = iVar1 + -1;
                } while (iVar1 != 0);
              }
              *(uint *)(param_1 + 0x50) = uVar6;
              *(int *)(param_1 + 0x54) = iVar8;
            }
            return 1;
          }
          return -0x81;
        }
      }
    }
    if (1 < *(int *)(param_1 + 0x58)) {
      if (param_3 == 0) {
        return 0;
      }
      iVar1 = FUN_00677ba0(param_1,local_30,0xffffffff,0xffffffff);
      if (iVar1 < 0) {
        return -2;
      }
      *(double *)(param_1 + 0x68) = (double)(local_2c * 8) + *(double *)(param_1 + 0x68);
      if ((*(int *)(param_1 + 0x58) == 4) &&
         (iVar1 = FUN_0069cb00(local_30), *(int *)(param_1 + 0x5c) != iVar1)) {
        if (param_4 == 0) {
          return -2;
        }
        FUN_00678480(param_1);
        if (*(int *)(param_1 + 4) == 0) {
          FUN_00679b90(*(undefined4 *)(param_1 + 0x48));
          FUN_00679ad0(*(undefined4 *)(param_1 + 0x4c));
        }
      }
    }
    if (*(int *)(param_1 + 0x58) != 4) {
      if (*(int *)(param_1 + 0x58) < 3) {
        if (*(int *)(param_1 + 4) == 0) {
          iVar1 = FUN_00677a50(param_1,*(undefined4 *)(param_1 + 0x48),
                               *(undefined4 *)(param_1 + 0x4c),param_1 + 0x5c,local_30);
          if (iVar1 != 0) {
            return iVar1;
          }
          *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
        }
        else {
          iVar8 = FUN_0069cb00(local_30);
          iVar1 = *(int *)(param_1 + 0x34);
          iVar4 = 0;
          *(int *)(param_1 + 0x5c) = iVar8;
          if (0 < iVar1) {
            piVar10 = *(int **)(param_1 + 0x40);
            do {
              if (*piVar10 == iVar8) break;
              iVar4 = iVar4 + 1;
              piVar10 = piVar10 + 1;
            } while (iVar4 < iVar1);
          }
          if (iVar4 == iVar1) {
            return -0x89;
          }
          *(int *)(param_1 + 0x60) = iVar4;
          FUN_0069d2f0(param_1 + 0x78,iVar8);
          *(undefined4 *)(param_1 + 0x58) = 3;
        }
      }
      iVar1 = FUN_006791c0(param_1);
      if (iVar1 < 0) {
        return iVar1;
      }
    }
    FUN_0069cf90(param_1 + 0x78,local_30);
  } while( true );
}

