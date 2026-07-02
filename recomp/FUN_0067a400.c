// ============================================
// Address:  0x0067a400
// Original: FUN_0067a400
// Status:   unreviewed
// ============================================


undefined4 FUN_0067a400(undefined4 *param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  void *pvVar3;
  undefined4 uVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  
  puVar2 = param_1;
  piVar1 = *(int **)(param_2 + 0x1c);
  if (piVar1 != (int *)0x0) {
    iVar6 = piVar1[0x39e];
    puVar9 = param_1;
    for (iVar7 = 0x1c; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    pvVar3 = _calloc(1,0xc0);
    param_1[0x1a] = pvVar3;
    param_1[1] = param_2;
    uVar4 = FUN_00681ed0(piVar1[2]);
    *(undefined4 *)((int)pvVar3 + 0x2c) = uVar4;
    pvVar5 = _calloc(1,4);
    *(void **)((int)pvVar3 + 0xc) = pvVar5;
    pvVar5 = _calloc(1,4);
    *(void **)((int)pvVar3 + 0x10) = pvVar5;
    pvVar5 = _calloc(1,0x14);
    **(undefined4 **)((int)pvVar3 + 0xc) = pvVar5;
    pvVar5 = _calloc(1,0x14);
    **(undefined4 **)((int)pvVar3 + 0x10) = pvVar5;
    FUN_006809c0(**(undefined4 **)((int)pvVar3 + 0xc),*piVar1 >> ((byte)iVar6 & 0x1f));
    FUN_006809c0(**(undefined4 **)((int)pvVar3 + 0x10),piVar1[1] >> ((byte)iVar6 & 0x1f));
    iVar6 = FUN_00681ed0(*piVar1);
    *(int *)((int)pvVar3 + 4) = iVar6 + -6;
    iVar6 = FUN_00681ed0(piVar1[1]);
    *(int *)((int)pvVar3 + 8) = iVar6 + -6;
    if (param_3 == 0) {
      if (piVar1[0x2c8] == 0) {
        pvVar5 = _calloc(piVar1[6],0x2c);
        piVar1[0x2c8] = (int)pvVar5;
        param_1 = (undefined4 *)0x0;
        if (0 < piVar1[6]) {
          param_3 = 0;
          piVar8 = piVar1 + 0x1c8;
          do {
            FUN_0067e1a0(piVar1[0x2c8] + param_3,*piVar8);
            FUN_0067e0c0(*piVar8);
            *piVar8 = 0;
            param_1 = (undefined4 *)((int)param_1 + 1);
            piVar8 = piVar8 + 1;
            param_3 = param_3 + 0x2c;
          } while ((int)param_1 < piVar1[6]);
        }
      }
    }
    else {
      FUN_00680790((int)pvVar3 + 0x14,*piVar1);
      FUN_00680790((int)pvVar3 + 0x20,piVar1[1]);
      if (piVar1[0x2c8] == 0) {
        pvVar5 = _calloc(piVar1[6],0x2c);
        piVar1[0x2c8] = (int)pvVar5;
        param_1 = (undefined4 *)0x0;
        if (0 < piVar1[6]) {
          param_3 = 0;
          piVar8 = piVar1 + 0x1c8;
          do {
            FUN_0067e140(piVar1[0x2c8] + param_3,*piVar8);
            param_1 = (undefined4 *)((int)param_1 + 1);
            piVar8 = piVar8 + 1;
            param_3 = param_3 + 0x2c;
          } while ((int)param_1 < piVar1[6]);
        }
      }
      pvVar5 = _calloc(piVar1[7],0x30);
      *(void **)((int)pvVar3 + 0x38) = pvVar5;
      param_1 = (undefined4 *)0x0;
      if (0 < piVar1[7]) {
        param_3 = 0;
        piVar8 = piVar1 + 0x2c9;
        do {
          FUN_0067b440(*(int *)((int)pvVar3 + 0x38) + param_3,(int *)*piVar8,piVar1 + 0x2cd,
                       piVar1[*(int *)*piVar8] / 2,*(undefined4 *)(param_2 + 8));
          param_1 = (undefined4 *)((int)param_1 + 1);
          piVar8 = piVar8 + 1;
          param_3 = param_3 + 0x30;
        } while ((int)param_1 < piVar1[7]);
      }
      *puVar2 = 1;
    }
    puVar2[4] = piVar1[1];
    pvVar5 = _malloc(*(int *)(param_2 + 4) << 2);
    puVar2[2] = pvVar5;
    pvVar5 = _malloc(*(int *)(param_2 + 4) << 2);
    puVar2[3] = pvVar5;
    iVar6 = 0;
    if (0 < *(int *)(param_2 + 4)) {
      do {
        pvVar5 = _calloc(puVar2[4],4);
        *(void **)(puVar2[2] + iVar6 * 4) = pvVar5;
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(param_2 + 4));
    }
    puVar2[9] = 0;
    puVar2[10] = 0;
    iVar6 = piVar1[1];
    puVar2[0xc] = iVar6 / 2;
    puVar2[5] = iVar6 / 2;
    pvVar5 = _calloc(piVar1[4],4);
    *(void **)((int)pvVar3 + 0x30) = pvVar5;
    pvVar5 = _calloc(piVar1[5],4);
    *(void **)((int)pvVar3 + 0x34) = pvVar5;
    param_1 = (undefined4 *)0x0;
    if (0 < piVar1[4]) {
      piVar8 = piVar1 + 0x108;
      do {
        uVar4 = (**(code **)((&PTR_DAT_006be800)[piVar8[-0x40]] + 8))(puVar2,*piVar8);
        *(undefined4 *)((int)piVar8 + *(int *)((int)pvVar3 + 0x30) + (-0x420 - (int)piVar1)) = uVar4
        ;
        param_1 = (undefined4 *)((int)param_1 + 1);
        piVar8 = piVar8 + 1;
      } while ((int)param_1 < piVar1[4]);
    }
    param_1 = (undefined4 *)0x0;
    if (0 < piVar1[5]) {
      piVar8 = piVar1 + 0x188;
      do {
        uVar4 = (**(code **)((&PTR_DAT_006be808)[piVar8[-0x40]] + 8))(puVar2,*piVar8);
        *(undefined4 *)((int)piVar8 + *(int *)((int)pvVar3 + 0x34) + (-0x620 - (int)piVar1)) = uVar4
        ;
        param_1 = (undefined4 *)((int)param_1 + 1);
        piVar8 = piVar8 + 1;
      } while ((int)param_1 < piVar1[5]);
    }
    return 0;
  }
  return 1;
}

