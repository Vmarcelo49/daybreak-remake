// Function: FUN_00683880
// Address:  0x00683880
// Source:   batch_decompile (mass dump)
// Hash:     c86195246a71db01


undefined4 FUN_00683880(int param_1,int *param_2,int param_3,int param_4,int *param_5,code *param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int *local_430;
  int local_42c;
  int local_428;
  int local_41c;
  int local_400 [128];
  int local_200 [128];
  
  piVar1 = (int *)*param_2;
  iVar2 = piVar1[3];
  iVar3 = *(int *)param_2[4];
  iVar4 = piVar1[2];
  iVar6 = (piVar1[1] - *piVar1) / iVar4;
  piVar10 = local_200;
  for (iVar8 = 0x80; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar10 = 0;
    piVar10 = piVar10 + 1;
  }
  piVar10 = local_400;
  for (iVar8 = 0x80; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar10 = 0;
    piVar10 = piVar10 + 1;
  }
  local_42c = 0;
  if (0 < param_2[2]) {
    do {
      iVar8 = 0;
      local_41c = 0;
      if (0 < iVar6) {
        do {
          if ((local_42c == 0) && (0 < param_4)) {
            local_428 = param_4;
            local_430 = param_5;
            do {
              iVar9 = 1;
              iVar7 = *(int *)(*local_430 + iVar8 * 4);
              if (1 < iVar3) {
                piVar10 = (int *)(*local_430 + 4 + iVar8 * 4);
                do {
                  iVar7 = iVar7 * iVar2;
                  if (iVar9 + iVar8 < iVar6) {
                    iVar7 = iVar7 + *piVar10;
                  }
                  iVar9 = iVar9 + 1;
                  piVar10 = piVar10 + 1;
                } while (iVar9 < iVar3);
              }
              if (iVar7 < *(int *)(param_2[4] + 4)) {
                iVar7 = FUN_0067e830(param_2[4],iVar7,param_1 + 4);
                param_2[9] = param_2[9] + iVar7;
              }
              local_430 = local_430 + 1;
              local_428 = local_428 + -1;
            } while (local_428 != 0);
          }
          local_430 = (int *)0x0;
          if (0 < iVar3) {
            iVar7 = iVar8 * 4;
            iVar9 = iVar8 * iVar4;
            do {
              if (iVar6 <= iVar8) goto LAB_00683ac9;
              iVar5 = *piVar1;
              if (0 < param_4) {
                local_428 = param_4;
                piVar10 = param_5;
                do {
                  if (local_42c == 0) {
                    local_400[*(int *)(iVar7 + *piVar10)] =
                         local_400[*(int *)(iVar7 + *piVar10)] + iVar4;
                  }
                  if (((piVar1[*(int *)(*piVar10 + iVar7) + 5] & 1 << ((byte)local_42c & 0x1f)) != 0
                      ) && (iVar8 = *(int *)(*(int *)(param_2[5] + *(int *)(*piVar10 + iVar7) * 4) +
                                            local_42c * 4), iVar8 != 0)) {
                    iVar8 = (*param_6)(param_1 + 4,
                                       *(int *)((param_3 - (int)param_5) + (int)piVar10) +
                                       (iVar9 + iVar5) * 4,iVar4,iVar8,0);
                    param_2[8] = param_2[8] + iVar8;
                    local_200[*(int *)(iVar7 + *piVar10)] =
                         local_200[*(int *)(iVar7 + *piVar10)] + iVar8;
                  }
                  piVar10 = piVar10 + 1;
                  local_428 = local_428 + -1;
                  iVar8 = local_41c;
                } while (local_428 != 0);
              }
              local_430 = (int *)((int)local_430 + 1);
              iVar8 = iVar8 + 1;
              iVar9 = iVar9 + iVar4;
              iVar7 = iVar7 + 4;
              local_41c = iVar8;
            } while ((int)local_430 < iVar3);
          }
        } while (iVar8 < iVar6);
      }
LAB_00683ac9:
      local_42c = local_42c + 1;
    } while (local_42c < param_2[2]);
  }
  return 0;
}

