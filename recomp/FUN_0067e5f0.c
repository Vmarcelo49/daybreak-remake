// ============================================
// Address:  0x0067e5f0
// Original: FUN_0067e5f0
// Status:   unreviewed
// ============================================


undefined4 FUN_0067e5f0(undefined4 param_1,int *param_2)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  piVar6 = param_2;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  param_2[0xc] = 1;
  iVar4 = FUN_0069d720(param_1,0x18);
  if (iVar4 == 0x564342) {
    iVar4 = FUN_0069d720(param_1,0x10);
    *param_2 = iVar4;
    iVar4 = FUN_0069d720(param_1,0x18);
    param_2[1] = iVar4;
    if (iVar4 != -1) {
      iVar4 = FUN_0069d720(param_1,1);
      if (iVar4 == 0) {
        pvVar2 = _malloc(param_2[1] << 2);
        param_2[2] = (int)pvVar2;
        iVar4 = FUN_0069d720(param_1,1);
        if (iVar4 == 0) {
          iVar4 = 0;
          if (0 < param_2[1]) {
            do {
              iVar1 = FUN_0069d720(param_1,5);
              if (iVar1 == -1) goto LAB_0067e816;
              *(int *)(param_2[2] + iVar4 * 4) = iVar1 + 1;
              iVar4 = iVar4 + 1;
            } while (iVar4 < param_2[1]);
          }
        }
        else {
          iVar4 = 0;
          if (0 < param_2[1]) {
            do {
              iVar1 = FUN_0069d720(param_1,1);
              if (iVar1 == 0) {
                *(undefined4 *)(param_2[2] + iVar4 * 4) = 0;
              }
              else {
                iVar1 = FUN_0069d720(param_1,5);
                if (iVar1 == -1) goto LAB_0067e816;
                *(int *)(param_2[2] + iVar4 * 4) = iVar1 + 1;
              }
              iVar4 = iVar4 + 1;
            } while (iVar4 < param_2[1]);
          }
        }
      }
      else {
        if (iVar4 != 1) {
          return 0xffffffff;
        }
        iVar1 = FUN_0069d720(param_1,5);
        pvVar2 = _malloc(param_2[1] << 2);
        param_2[2] = (int)pvVar2;
        iVar4 = param_2[1];
        iVar7 = 0;
        if (0 < iVar4) {
          do {
            iVar1 = iVar1 + 1;
            uVar3 = FUN_00682f70(iVar4 - iVar7);
            iVar4 = FUN_0069d720(param_1,uVar3);
            if (iVar4 == -1) goto LAB_0067e816;
            iVar5 = 0;
            if (0 < iVar4) {
              do {
                if (param_2[1] <= iVar7) break;
                iVar5 = iVar5 + 1;
                *(int *)(param_2[2] + iVar7 * 4) = iVar1;
                iVar7 = iVar7 + 1;
              } while (iVar5 < iVar4);
            }
            iVar4 = param_2[1];
          } while (iVar7 < iVar4);
        }
      }
      iVar4 = FUN_0069d720(param_1,4);
      param_2[3] = iVar4;
      if (iVar4 == 0) {
        return 0;
      }
      if ((0 < iVar4) && (iVar4 < 3)) {
        iVar4 = FUN_0069d720(param_1,0x20);
        param_2[4] = iVar4;
        iVar4 = FUN_0069d720(param_1,0x20);
        param_2[5] = iVar4;
        iVar4 = FUN_0069d720(param_1,4);
        param_2[6] = iVar4 + 1;
        iVar4 = FUN_0069d720(param_1,1);
        param_2[7] = iVar4;
        iVar4 = 0;
        if (param_2[3] == 1) {
          iVar4 = FUN_0067dd90(param_2);
        }
        else if (param_2[3] == 2) {
          iVar4 = *param_2 * param_2[1];
        }
        pvVar2 = _malloc(iVar4 * 4);
        iVar1 = 0;
        param_2[8] = (int)pvVar2;
        if (0 < iVar4) {
          do {
            uVar3 = FUN_0069d720(param_1,param_2[6]);
            *(undefined4 *)(param_2[8] + iVar1 * 4) = uVar3;
            iVar1 = iVar1 + 1;
          } while (iVar1 < iVar4);
        }
        if (iVar4 == 0) {
          return 0;
        }
        if (*(int *)((iVar4 * 4 - 4U) + param_2[8]) != -1) {
          return 0;
        }
      }
    }
  }
LAB_0067e816:
  FUN_0067dff0(param_2);
  return 0xffffffff;
}

