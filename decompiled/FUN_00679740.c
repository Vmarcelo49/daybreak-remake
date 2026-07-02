// Function: FUN_00679740
// Address:  0x00679740
// Source:   batch_decompile (mass dump)
// Hash:     e2194156d8569f50


uint FUN_00679740(int param_1,short *param_2,int param_3,int param_4,int param_5,int param_6,
                 undefined4 *param_7)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  short *psVar10;
  int local_8;
  
  iVar1 = FUN_00679aa0();
  if (*(int *)(param_1 + 0x58) < 2) {
    return 0xffffff7d;
  }
  do {
    if ((*(int *)(param_1 + 0x58) == 4) &&
       (uVar2 = FUN_0067b0c0(param_1 + 0x1e0,&local_8), uVar2 != 0)) {
      if ((int)uVar2 < 1) {
        return uVar2;
      }
      iVar3 = FUN_00679700(param_1,0xffffffff);
      iVar3 = *(int *)(iVar3 + 4);
      iVar7 = iVar3 * param_5;
      uVar4 = param_3 / iVar7;
      if ((int)uVar4 < (int)uVar2) {
        uVar2 = uVar4;
      }
      if (0 < (int)uVar2) {
        if (param_5 == 1) {
          iVar1 = 0;
          if (0 < (int)uVar2) {
            do {
              iVar5 = 0;
              if (0 < iVar3) {
                do {
                  iVar8 = (int)ROUND(*(float *)(*(int *)(local_8 + iVar5 * 4) + iVar1 * 4) * 128.0);
                  if (iVar8 < 0x80) {
                    if (iVar8 < -0x80) {
                      iVar8 = -0x80;
                    }
                  }
                  else {
                    iVar8 = 0x7f;
                  }
                  *(byte *)param_2 = (-(param_6 != 0) & 0x80U) + 0x80 + (char)iVar8;
                  param_2 = (short *)((int)param_2 + 1);
                  iVar5 = iVar5 + 1;
                } while (iVar5 < iVar3);
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < (int)uVar2);
          }
        }
        else {
          iVar5 = (-(uint)(param_6 != 0) & 0xffff8000) + 0x8000;
          if (iVar1 == param_4) {
            if (param_6 == 0) {
              param_5 = 0;
              if (0 < iVar3) {
                do {
                  pfVar9 = *(float **)(local_8 + param_5 * 4);
                  psVar10 = param_2;
                  uVar4 = uVar2;
                  if (0 < (int)uVar2) {
                    do {
                      iVar1 = (int)ROUND(*pfVar9 * 32768.0);
                      if (iVar1 < 0x8000) {
                        if (iVar1 < -0x8000) {
                          iVar1 = -0x8000;
                        }
                      }
                      else {
                        iVar1 = 0x7fff;
                      }
                      pfVar9 = pfVar9 + 1;
                      *psVar10 = (short)iVar1 + -0x8000;
                      uVar4 = uVar4 - 1;
                      psVar10 = psVar10 + iVar3;
                    } while (uVar4 != 0);
                  }
                  param_5 = param_5 + 1;
                  param_2 = param_2 + 1;
                } while (param_5 < iVar3);
              }
            }
            else {
              iVar1 = 0;
              if (0 < iVar3) {
                do {
                  pfVar9 = *(float **)(local_8 + iVar1 * 4);
                  psVar10 = param_2;
                  uVar4 = uVar2;
                  if (0 < (int)uVar2) {
                    do {
                      iVar5 = (int)ROUND(*pfVar9 * 32768.0);
                      if (iVar5 < 0x8000) {
                        if (iVar5 < -0x8000) {
                          iVar5 = -0x8000;
                        }
                      }
                      else {
                        iVar5 = 0x7fff;
                      }
                      *psVar10 = (short)iVar5;
                      pfVar9 = pfVar9 + 1;
                      uVar4 = uVar4 - 1;
                      psVar10 = psVar10 + iVar3;
                    } while (uVar4 != 0);
                  }
                  iVar1 = iVar1 + 1;
                  param_2 = param_2 + 1;
                } while (iVar1 < iVar3);
              }
            }
          }
          else {
            iVar1 = 0;
            if (param_4 == 0) {
              param_5 = 0;
              if (0 < (int)uVar2) {
                do {
                  iVar1 = 0;
                  if (0 < iVar3) {
                    do {
                      iVar8 = (int)ROUND(*(float *)(*(int *)(local_8 + iVar1 * 4) + param_5 * 4) *
                                         32768.0);
                      if (iVar8 < 0x8000) {
                        if (iVar8 < -0x8000) {
                          iVar8 = -0x8000;
                        }
                      }
                      else {
                        iVar8 = 0x7fff;
                      }
                      iVar8 = iVar8 + iVar5;
                      *(char *)param_2 = (char)iVar8;
                      *(char *)((int)param_2 + 1) = (char)((uint)iVar8 >> 8);
                      param_2 = param_2 + 1;
                      iVar1 = iVar1 + 1;
                    } while (iVar1 < iVar3);
                  }
                  param_5 = param_5 + 1;
                } while (param_5 < (int)uVar2);
              }
            }
            else if (0 < (int)uVar2) {
              do {
                iVar8 = 0;
                if (0 < iVar3) {
                  do {
                    iVar6 = (int)ROUND(*(float *)(*(int *)(local_8 + iVar8 * 4) + iVar1 * 4) *
                                       32768.0);
                    if (iVar6 < 0x8000) {
                      if (iVar6 < -0x8000) {
                        iVar6 = -0x8000;
                      }
                    }
                    else {
                      iVar6 = 0x7fff;
                    }
                    iVar6 = iVar6 + iVar5;
                    *(char *)param_2 = (char)((uint)iVar6 >> 8);
                    *(char *)((int)param_2 + 1) = (char)iVar6;
                    param_2 = param_2 + 1;
                    iVar8 = iVar8 + 1;
                  } while (iVar8 < iVar3);
                }
                iVar1 = iVar1 + 1;
              } while (iVar1 < (int)uVar2);
            }
          }
        }
        FUN_0067b120(param_1 + 0x1e0,uVar2);
        uVar4 = *(uint *)(param_1 + 0x50);
        *(uint *)(param_1 + 0x50) = uVar4 + uVar2;
        *(uint *)(param_1 + 0x54) =
             *(int *)(param_1 + 0x54) + ((int)uVar2 >> 0x1f) + (uint)CARRY4(uVar4,uVar2);
        if (param_7 != (undefined4 *)0x0) {
          *param_7 = *(undefined4 *)(param_1 + 0x60);
        }
        return iVar7 * uVar2;
      }
      return 0xffffff7d;
    }
    uVar2 = FUN_00679240(param_1,0,1,1);
    if (uVar2 == 0xfffffffe) {
      return 0;
    }
  } while (0 < (int)uVar2);
  return uVar2;
}

