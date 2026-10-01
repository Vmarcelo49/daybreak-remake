// ============================================
// Address:  0x006807f0
// Original: FUN_006807f0
// Status:   unreviewed
// ============================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006807f0(int param_1, int param_2, int *param_3)

{
    float fVar1;
    int iVar2;
    int *piVar3;
    float *pfVar4;
    int iVar5;
    uint uVar6;
    undefined **ppuVar7;
    int *piVar8;
    undefined *puVar9;
    int iVar10;
    int iVar11;
    float *pfVar12;
    float10 fVar13;
    float10 fVar14;
    float10 fVar15;
    int *local_14;
    int local_10;
    int local_c;

    local_14 = param_3;
    puVar9   = (undefined *)0x0;
    iVar11   = 0;
    ppuVar7  = &PTR_PTR_006be814;
    iVar2    = param_1;
    do
    {
        do
        {
            ppuVar7 = ppuVar7 + 1;
            if ((int)ppuVar7 < 0x6be828)
            {
                puVar9 = *ppuVar7;
            }
            else
            {
                puVar9 = puVar9 + 2;
            }
        } while (iVar2 != (iVar2 / (int)puVar9) * (int)puVar9);
        iVar5   = iVar2 / (int)puVar9;
        piVar8  = param_3 + iVar11;
        local_c = iVar11;
        do
        {
            iVar2     = iVar5;
            iVar11    = local_c + 1;
            piVar8[2] = (int)puVar9;
            if ((puVar9 == (undefined *)0x2) && (iVar11 != 1))
            {
                piVar3 = piVar8 + 1;
                iVar5  = local_c;
                if (1 < iVar11)
                {
                    do
                    {
                        piVar3[1] = *piVar3;
                        iVar5     = iVar5 + -1;
                        piVar3    = piVar3 + -1;
                    } while (iVar5 != 0);
                }
                param_3[2] = 2;
            }
            if (iVar2 == 1)
            {
                *param_3   = param_1;
                param_3[1] = iVar11;
                param_3    = (int *)0x0;
                fVar1      = _DAT_006be828 / (float)param_1;
                if ((local_c != 0) && (0 < local_c))
                {
                    local_14 = local_14 + 2;
                    iVar2    = 1;
                    do
                    {
                        iVar5    = 0;
                        iVar10   = *local_14 * iVar2;
                        iVar11   = param_1 / iVar10;
                        local_10 = *local_14 + -1;
                        if (0 < local_10)
                        {
                            pfVar12 = (float *)(param_2 + (int)param_3 * 4);
                            param_3 = (int *)((int)param_3 + local_10 * iVar11);
                            do
                            {
                                iVar5  = iVar5 + iVar2;
                                fVar13 = (float10)0.0;
                                if (2 < iVar11)
                                {
                                    uVar6  = iVar11 - 1U >> 1;
                                    pfVar4 = pfVar12;
                                    do
                                    {
                                        fVar13    = fVar13 + (float10)1.0;
                                        uVar6     = uVar6 - 1;
                                        fVar14    = fVar13 * (float10)((float)iVar5 * fVar1);
                                        fVar15    = (float10)fcos(fVar14);
                                        *pfVar4   = (float)fVar15;
                                        fVar14    = (float10)fsin(fVar14);
                                        pfVar4[1] = (float)fVar14;
                                        pfVar4    = pfVar4 + 2;
                                    } while (uVar6 != 0);
                                }
                                pfVar12  = pfVar12 + iVar11;
                                local_10 = local_10 + -1;
                            } while (local_10 != 0);
                        }
                        local_14 = local_14 + 1;
                        local_c  = local_c + -1;
                        iVar2    = iVar10;
                    } while (local_c != 0);
                }
                return;
            }
            iVar5   = iVar2 / (int)puVar9;
            piVar8  = piVar8 + 1;
            local_c = iVar11;
        } while (iVar2 == (iVar2 / (int)puVar9) * (int)puVar9);
    } while (true);
}
