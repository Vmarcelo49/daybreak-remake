// ============================================
// Address:  0x00685060
// Original: FUN_00685060
// Status:   unreviewed
// ============================================

void FUN_00685060(int *param_1, int param_2, int *param_3, int *param_4)

{
    int iVar1;
    double dVar2;
    double dVar3;
    double dVar4;
    int *piVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    int local_28;
    int local_24;
    int local_20;
    int local_1c;

    iVar6    = *param_1;
    iVar7    = 0;
    iVar8    = 0;
    iVar1    = param_1[param_2 * 8 + -7];
    iVar10   = 0;
    iVar11   = 0;
    iVar9    = 0;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    if (0 < param_2)
    {
        piVar5 = param_1 + 3;
        do
        {
            iVar8    = iVar8 + piVar5[-1];
            iVar10   = iVar10 + *piVar5;
            iVar11   = iVar11 + piVar5[1];
            iVar9    = iVar9 + piVar5[3];
            iVar7    = iVar7 + piVar5[4];
            param_2  = param_2 + -1;
            piVar5   = piVar5 + 8;
            local_28 = iVar8;
            local_24 = iVar10;
            local_20 = iVar11;
            local_1c = iVar9;
        } while (param_2 != 0);
    }
    iVar8 = *param_3;
    if (-1 < iVar8)
    {
        local_24 = local_24 + iVar8;
        local_28 = local_28 + iVar6;
        local_20 = local_20 + iVar6 * iVar6;
        local_1c = local_1c + iVar8 * iVar6;
        iVar7    = iVar7 + 1;
    }
    iVar8 = *param_4;
    if (-1 < iVar8)
    {
        local_28 = local_28 + iVar1;
        local_24 = local_24 + iVar8;
        local_20 = local_20 + iVar1 * iVar1;
        local_1c = local_1c + iVar8 * iVar1;
        iVar7    = iVar7 + 1;
    }
    if (iVar7 == 0)
    {
        *param_3 = 0;
        *param_4 = 0;
    }
    else
    {
        dVar4 = (double)local_28;
        dVar2 = 1.0 / ((double)iVar7 * (double)local_20 - dVar4 * dVar4);
        dVar3 = ((double)local_20 * (double)local_24 - (double)local_1c * dVar4) * dVar2;
        dVar2 = ((double)iVar7 * (double)local_1c - (double)local_24 * dVar4) * dVar2;
        FUN_0069a090((double)iVar6 * dVar2 + dVar3 + 0.5);
        iVar6    = __ftol();
        *param_3 = iVar6;
        FUN_0069a090((double)iVar1 * dVar2 + dVar3 + 0.5);
        iVar6    = __ftol();
        *param_4 = iVar6;
        if (0x3ff < *param_3)
        {
            *param_3 = 0x3ff;
        }
        if (0x3ff < *param_4)
        {
            *param_4 = 0x3ff;
        }
        if (*param_3 < 0)
        {
            *param_3 = 0;
        }
        if (*param_4 < 0)
        {
            *param_4 = 0;
            return;
        }
    }
    return;
}
