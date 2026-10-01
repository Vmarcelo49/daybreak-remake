// ============================================
// Address:  0x00679ff0
// Original: FUN_00679ff0
// Status:   unreviewed
// ============================================

undefined4 FUN_00679ff0(int param_1, undefined4 param_2)

{
    int iVar1;
    void *pvVar2;
    int iVar3;
    undefined4 uVar4;
    int iVar5;
    int iVar6;
    undefined4 *puVar7;
    int *piVar8;

    iVar5 = *(int *)(param_1 + 0x1c);
    if (iVar5 == 0)
    {
        return 0xffffff7f;
    }
    iVar1                  = FUN_0069d720(param_2, 8);
    iVar6                  = 0;
    *(int *)(iVar5 + 0x18) = iVar1 + 1;
    if (0 < iVar1 + 1)
    {
        puVar7 = (undefined4 *)(iVar5 + 0x720);
        do
        {
            pvVar2  = _calloc(1, 0x34);
            *puVar7 = pvVar2;
            iVar1   = FUN_0067e5f0(param_2, pvVar2);
            if (iVar1 != 0)
                goto LAB_0067a249;
            iVar6  = iVar6 + 1;
            puVar7 = puVar7 + 1;
        } while (iVar6 < *(int *)(iVar5 + 0x18));
    }
    iVar1 = FUN_0069d720(param_2, 6);
    iVar6 = 0;
    if (0 < iVar1 + 1)
    {
        do
        {
            iVar3 = FUN_0069d720(param_2, 0x10);
            if ((iVar3 < 0) || (0 < iVar3))
                goto LAB_0067a249;
            iVar6 = iVar6 + 1;
        } while (iVar6 < iVar1 + 1);
    }
    iVar1                  = FUN_0069d720(param_2, 6);
    iVar6                  = 0;
    *(int *)(iVar5 + 0x10) = iVar1 + 1;
    if (0 < iVar1 + 1)
    {
        piVar8 = (int *)(iVar5 + 0x420);
        do
        {
            iVar1         = FUN_0069d720(param_2, 0x10);
            piVar8[-0x40] = iVar1;
            if ((iVar1 < 0) || (1 < iVar1))
                goto LAB_0067a249;
            iVar1   = (**(code **)((&PTR_DAT_006be800)[iVar1] + 4))(param_1, param_2);
            *piVar8 = iVar1;
            if (iVar1 == 0)
                goto LAB_0067a249;
            iVar6  = iVar6 + 1;
            piVar8 = piVar8 + 1;
        } while (iVar6 < *(int *)(iVar5 + 0x10));
    }
    iVar1                  = FUN_0069d720(param_2, 6);
    iVar6                  = 0;
    *(int *)(iVar5 + 0x14) = iVar1 + 1;
    if (0 < iVar1 + 1)
    {
        piVar8 = (int *)(iVar5 + 0x620);
        do
        {
            iVar1         = FUN_0069d720(param_2, 0x10);
            piVar8[-0x40] = iVar1;
            if ((iVar1 < 0) || (2 < iVar1))
                goto LAB_0067a249;
            iVar1   = (**(code **)((&PTR_DAT_006be808)[iVar1] + 4))(param_1, param_2);
            *piVar8 = iVar1;
            if (iVar1 == 0)
                goto LAB_0067a249;
            iVar6  = iVar6 + 1;
            piVar8 = piVar8 + 1;
        } while (iVar6 < *(int *)(iVar5 + 0x14));
    }
    iVar1                 = FUN_0069d720(param_2, 6);
    iVar6                 = 0;
    *(int *)(iVar5 + 0xc) = iVar1 + 1;
    if (0 < iVar1 + 1)
    {
        piVar8 = (int *)(iVar5 + 0x220);
        do
        {
            iVar1         = FUN_0069d720(param_2, 0x10);
            piVar8[-0x40] = iVar1;
            if ((iVar1 < 0) || (0 < iVar1))
                goto LAB_0067a249;
            iVar1   = (**(code **)((&PTR_PTR_006be814)[iVar1] + 4))(param_1, param_2);
            *piVar8 = iVar1;
            if (iVar1 == 0)
                goto LAB_0067a249;
            iVar6  = iVar6 + 1;
            piVar8 = piVar8 + 1;
        } while (iVar6 < *(int *)(iVar5 + 0xc));
    }
    iVar1               = FUN_0069d720(param_2, 6);
    iVar6               = 0;
    *(int *)(iVar5 + 8) = iVar1 + 1;
    if (0 < iVar1 + 1)
    {
        piVar8 = (int *)(iVar5 + 0x20);
        do
        {
            pvVar2                         = _calloc(1, 0x10);
            *piVar8                        = (int)pvVar2;
            uVar4                          = FUN_0069d720(param_2, 1);
            *(undefined4 *)*piVar8         = uVar4;
            uVar4                          = FUN_0069d720(param_2, 0x10);
            *(undefined4 *)(*piVar8 + 4)   = uVar4;
            uVar4                          = FUN_0069d720(param_2, 0x10);
            *(undefined4 *)(*piVar8 + 8)   = uVar4;
            uVar4                          = FUN_0069d720(param_2, 8);
            *(undefined4 *)(*piVar8 + 0xc) = uVar4;
            iVar1                          = *piVar8;
            if (((0 < *(int *)(iVar1 + 4)) || (0 < *(int *)(iVar1 + 8))) ||
                (*(int *)(iVar5 + 0xc) <= *(int *)(iVar1 + 0xc)))
                goto LAB_0067a249;
            iVar6  = iVar6 + 1;
            piVar8 = piVar8 + 1;
        } while (iVar6 < *(int *)(iVar5 + 8));
    }
    iVar5 = FUN_0069d720(param_2, 1);
    if (iVar5 == 1)
    {
        return 0;
    }
LAB_0067a249:
    FUN_00679b90(param_1);
    return 0xffffff7b;
}
