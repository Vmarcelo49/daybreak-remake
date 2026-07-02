// ============================================
// Address:  0x00683e20
// Original: FUN_00683e20
// Status:   unreviewed
// ============================================

int *FUN_00683e20(int param_1, int *param_2, int *param_3, float param_4)

{
    int *piVar1;
    int iVar2;
    int iVar3;
    float fVar4;
    int iVar5;
    int iVar6;
    int *piVar7;
    uint uVar8;
    undefined4 *puVar9;
    int iVar10;
    int *piVar11;
    float *pfVar12;
    int iVar13;
    int local_14;
    int local_10;

    iVar5   = (int)param_4;
    piVar1  = (int *)*param_2;
    iVar2   = piVar1[3];
    iVar10  = piVar1[1];
    iVar3   = piVar1[2];
    iVar13  = *piVar1;
    iVar6   = (iVar10 - iVar13) / iVar3;
    piVar7  = (int *)FUN_0067a2c0(param_1, 4);
    uVar8   = ((iVar10 - iVar13) * (int)param_4) / iVar3;
    puVar9  = (undefined4 *)FUN_0067a2c0(param_1, uVar8 << 2);
    *piVar7 = (int)puVar9;
    for (uVar8 = uVar8 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1)
    {
        *puVar9 = 0;
        puVar9  = puVar9 + 1;
    }
    for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1)
    {
        *(undefined1 *)puVar9 = 0;
        puVar9                = (undefined4 *)((int)puVar9 + 1);
    }
    param_1  = *piVar1 / (int)param_4;
    local_10 = 0;
    if (0 < iVar6)
    {
        do
        {
            param_4  = 0.0;
            fVar4    = 0.0;
            local_14 = 0;
            if (0 < iVar3)
            {
                iVar10 = param_1 * 4;
                do
                {
                    if (param_4 < ABS(*(float *)(iVar10 + *param_3)))
                    {
                        param_4 = ABS(*(float *)(iVar10 + *param_3));
                    }
                    if (1 < iVar5)
                    {
                        iVar13  = iVar5 + -1;
                        piVar11 = param_3;
                        do
                        {
                            piVar11 = piVar11 + 1;
                            if (fVar4 < ABS(*(float *)(*piVar11 + iVar10)))
                            {
                                fVar4 = ABS(*(float *)(*piVar11 + iVar10));
                            }
                            iVar13 = iVar13 + -1;
                        } while (iVar13 != 0);
                    }
                    param_1  = param_1 + 1;
                    iVar10   = iVar10 + 4;
                    local_14 = local_14 + iVar5;
                } while (local_14 < iVar3);
            }
            iVar10 = 0;
            if (0 < iVar2 + -1)
            {
                pfVar12 = (float *)(piVar1 + 0x185);
                do
                {
                    if ((param_4 <= pfVar12[-0x40]) && (fVar4 <= *pfVar12))
                        break;
                    iVar10  = iVar10 + 1;
                    pfVar12 = pfVar12 + 1;
                } while (iVar10 < iVar2 + -1);
            }
            local_10                              = local_10 + 1;
            *(int *)(*piVar7 + -4 + local_10 * 4) = iVar10;
        } while (local_10 < iVar6);
    }
    param_2[10] = param_2[10] + 1;
    return piVar7;
}
