// ============================================
// Address:  0x0067c3a0
// Original: FUN_0067c3a0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0067c3a0(
    int param_1, float *param_2, float *param_3, float *param_4, float param_5, float *param_6)

{
    int iVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float *pfVar9;
    int iVar10;
    int iVar11;
    float *pfVar12;
    float *pfVar13;
    uint uVar14;
    uint uVar15;
    int iVar16;
    int iVar17;
    undefined4 uStack_40;
    int local_28;
    uint *local_24;
    int local_20;
    float local_10;
    float local_c;
    float local_8;

    iVar10                     = (int)param_6;
    pfVar9                     = param_3;
    iVar1                      = param_1 * -4;
    (&uStack_40)[-param_1]     = 0x67c3cd;
    (&uStack_40)[param_1 * -2] = 0x67c3e3;
    (&uStack_40)[param_1 * -3] = 0x67c3f7;
    (&uStack_40)[param_1 * -4] = 0x67c40b;
    param_3                    = (float *)(param_5 + *param_3);
    if ((float)param_3 < 1.0)
    {
        param_3 = (float *)0x3f800000;
    }
    fVar5                                               = (float)param_3 * (float)param_3 * 0.5;
    fVar3                                               = fVar5 * (float)param_3;
    param_3                                             = (float *)0x3f800000;
    *(float *)(&stack0xffffffc4 + iVar1)                = fVar5;
    *(float *)(&stack0xffffffc4 + param_1 * -8)         = fVar5;
    *(undefined4 *)(&stack0xffffffc4 + param_1 * -0xc)  = 0;
    *(float *)(&stack0xffffffc4 + param_1 * -0x10)      = fVar3;
    fVar4                                               = 0.0;
    fVar2                                               = 0.0;
    *(undefined4 *)(&stack0xffffffc4 + param_1 * -0x14) = 0;
    if (1 < param_1)
    {
        local_10 = (float)(param_1 + -1);
        pfVar12  = (float *)(&stack0xffffffc8 + iVar1);
        fVar7    = fVar5;
        do
        {
            fVar8 = param_5 +
                    *(float *)(((int)pfVar9 - (int)(&stack0xffffffc4 + iVar1)) + (int)pfVar12);
            if (fVar8 < 1.0)
            {
                fVar8 = 1.0;
            }
            fVar6                      = fVar8 * fVar8;
            pfVar13                    = pfVar12 + 1;
            fVar7                      = fVar6 + fVar7;
            fVar5                      = (float)param_3 * fVar6 + fVar5;
            fVar4                      = (float)param_3 * (float)param_3 * fVar6 + fVar4;
            fVar3                      = fVar6 * fVar8 + fVar3;
            fVar2                      = (float)param_3 * fVar6 * fVar8 + fVar2;
            *pfVar12                   = fVar7;
            pfVar13[-1 - param_1]      = fVar5;
            pfVar13[param_1 * -2 + -1] = fVar4;
            pfVar13[param_1 * -3 + -1] = fVar3;
            pfVar13[param_1 * -4 + -1] = fVar2;
            param_3                    = (float *)((float)param_3 + 1.0);
            local_10                   = (float)((int)local_10 + -1);
            pfVar12                    = pfVar13;
            local_c                    = (float)(param_1 * -8);
            local_8                    = (float)(param_1 * -0xc);
        } while (local_10 != 0.0);
    }
    uVar14  = (uint)*param_2;
    param_3 = (float *)0x0;
    fVar2   = 0.0;
    iVar11  = (int)uVar14 >> 0x10;
    if (iVar11 < 0)
    {
        local_24 = (uint *)param_2;
        param_3  = (float *)0x0;
        do
        {
            iVar11   = iVar11 * -4;
            uVar14   = uVar14 & 0xffff;
            fVar3    = *(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -8) -
                       *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -8);
            local_c  = (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10) +
                        *(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0x10)) *
                           (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc) +
                            *(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0xc)) -
                       (*(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0x14) -
                        *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14)) *
                           fVar3;
            local_8  = (*(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0x14) -
                        *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14)) *
                           (*(float *)(&stack0xffffffc4 + iVar11 + iVar1) +
                            *(float *)(&stack0xffffffc4 + uVar14 * 4 + iVar1)) -
                       (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10) +
                        *(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0x10)) *
                           fVar3;
            local_10 = (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc) +
                        *(float *)(&stack0xffffffc4 + uVar14 * 4 + param_1 * -0xc)) *
                           (*(float *)(&stack0xffffffc4 + iVar11 + iVar1) +
                            *(float *)(&stack0xffffffc4 + uVar14 * 4 + iVar1)) -
                       fVar3 * fVar3;
            fVar3    = (local_8 * fVar2 + local_c) / local_10;
            if (fVar3 < 0.0)
            {
                fVar3 = 0.0;
            }
            local_24 = local_24 + 1;
            param_3  = (float *)((int)param_3 + 1);
            *(float *)((int)param_4 + (-4 - (int)param_2) + (int)local_24) = fVar3 - param_5;
            uVar14                                                         = *local_24;
            fVar2                                                          = fVar2 + 1.0;
            iVar11                                                         = (int)uVar14 >> 0x10;
        } while (iVar11 < 0);
    }
    uVar14 = (uint)param_2[(int)param_3];
    uVar15 = uVar14 & 0xffff;
    if ((int)uVar15 < param_1)
    {
        local_24 = (uint *)(param_2 + (int)param_3);
        do
        {
            iVar11   = (int)uVar14 >> 0x10;
            fVar3    = *(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -8) -
                       *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -8);
            local_c  = (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0x10) -
                        *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0x10)) *
                           (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0xc) -
                            *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0xc)) -
                       (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0x14) -
                        *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0x14)) *
                           fVar3;
            local_8  = (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0x14) -
                        *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0x14)) *
                           (*(float *)(&stack0xffffffc4 + uVar15 * 4 + iVar1) -
                            *(float *)(&stack0xffffffc4 + iVar11 * 4 + iVar1)) -
                       (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0x10) -
                        *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0x10)) *
                           fVar3;
            local_10 = (*(float *)(&stack0xffffffc4 + uVar15 * 4 + param_1 * -0xc) -
                        *(float *)(&stack0xffffffc4 + iVar11 * 4 + param_1 * -0xc)) *
                           (*(float *)(&stack0xffffffc4 + uVar15 * 4 + iVar1) -
                            *(float *)(&stack0xffffffc4 + iVar11 * 4 + iVar1)) -
                       fVar3 * fVar3;
            fVar3    = (local_8 * fVar2 + local_c) / local_10;
            if (fVar3 < 0.0)
            {
                fVar3 = 0.0;
            }
            param_3                                                   = (float *)((int)param_3 + 1);
            *(float *)((int)local_24 + ((int)param_4 - (int)param_2)) = fVar3 - param_5;
            uVar14                                                    = local_24[1];
            fVar2                                                     = fVar2 + 1.0;
            uVar15                                                    = uVar14 & 0xffff;
            local_24                                                  = local_24 + 1;
        } while ((int)uVar15 < param_1);
    }
    if ((int)param_3 < param_1)
    {
        iVar11  = param_1 - (int)param_3;
        param_2 = param_4 + (int)param_3;
        do
        {
            fVar3 = (local_8 * fVar2 + local_c) / local_10;
            if (fVar3 < 0.0)
            {
                fVar3 = 0.0;
            }
            iVar11   = iVar11 + -1;
            *param_2 = fVar3 - param_5;
            fVar2    = fVar2 + 1.0;
            param_2  = param_2 + 1;
        } while (iVar11 != 0);
    }
    if (0 < (int)param_6)
    {
        fVar2    = 0.0;
        local_28 = (int)param_6 / 2;
        param_3  = (float *)0x0;
        if (local_28 - (int)param_6 < 0)
        {
            iVar11   = local_28 * 4;
            param_2  = param_4;
            iVar16   = (local_28 - (int)param_6) * -4;
            iVar17   = ((int)param_6 / 2) * -4;
            local_24 = (uint *)(local_28 << 2);
            local_20 = local_28;
            do
            {
                fVar3    = *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -8) -
                           *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -8);
                local_c  = (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10) +
                            *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0x10)) *
                               (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc) +
                                *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0xc)) -
                           (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14) -
                            *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0x14)) *
                               fVar3;
                local_8  = (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14) -
                            *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0x14)) *
                               (*(float *)(&stack0xffffffc4 + iVar11 + iVar1) +
                                *(float *)(&stack0xffffffc4 + iVar16 + iVar1)) -
                           (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10) +
                            *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0x10)) *
                               fVar3;
                local_10 = (*(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc) +
                            *(float *)(&stack0xffffffc4 + iVar16 + param_1 * -0xc)) *
                               (*(float *)(&stack0xffffffc4 + iVar11 + iVar1) +
                                *(float *)(&stack0xffffffc4 + iVar16 + iVar1)) -
                           fVar3 * fVar3;
                fVar3    = (local_8 * fVar2 + local_c) / local_10 - param_5;
                if (fVar3 < *param_2)
                {
                    *param_2 = fVar3;
                }
                param_3  = (float *)((int)param_3 + 1);
                param_2  = param_2 + 1;
                iVar17   = iVar17 + -4;
                iVar11   = (int)local_24 + 4;
                local_20 = local_20 + 1;
                fVar2    = fVar2 + 1.0;
                iVar16   = iVar17 + (int)param_6 * 4;
                local_24 = (uint *)iVar11;
            } while (local_20 - (int)param_6 < 0);
        }
        local_28 = local_28 + (int)param_3;
        if (local_28 < param_1)
        {
            iVar11  = (local_28 - (int)param_6) * 4;
            param_2 = (float *)(local_28 * 4);
            param_6 = param_4 + (int)param_3;
            do
            {
                fVar3    = *(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -8) -
                           *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -8);
                local_c  = (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0x10) -
                            *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10)) *
                               (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0xc) -
                                *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc)) -
                           (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0x14) -
                            *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14)) *
                               fVar3;
                local_8  = (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0x14) -
                            *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x14)) *
                               (*(float *)(&stack0xffffffc4 + (int)param_2 + iVar1) -
                                *(float *)(&stack0xffffffc4 + iVar11 + iVar1)) -
                           (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0x10) -
                            *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0x10)) *
                               fVar3;
                local_10 = (*(float *)(&stack0xffffffc4 + (int)param_2 + param_1 * -0xc) -
                            *(float *)(&stack0xffffffc4 + iVar11 + param_1 * -0xc)) *
                               (*(float *)(&stack0xffffffc4 + (int)param_2 + iVar1) -
                                *(float *)(&stack0xffffffc4 + iVar11 + iVar1)) -
                           fVar3 * fVar3;
                fVar3    = (local_8 * fVar2 + local_c) / local_10 - param_5;
                if (fVar3 < *param_6)
                {
                    *param_6 = fVar3;
                }
                param_3  = (float *)((int)param_3 + 1);
                param_6  = param_6 + 1;
                fVar2    = fVar2 + 1.0;
                param_2  = (float *)((int)param_2 + 4);
                local_28 = local_28 + 1;
                iVar11   = (int)param_2 + iVar10 * -4;
            } while (local_28 < param_1);
        }
        if ((int)param_3 < param_1)
        {
            param_1 = param_1 - (int)param_3;
            param_4 = param_4 + (int)param_3;
            do
            {
                fVar3 = (local_8 * fVar2 + local_c) / local_10 - param_5;
                if (fVar3 < *param_4)
                {
                    *param_4 = fVar3;
                }
                fVar2   = fVar2 + 1.0;
                param_4 = param_4 + 1;
                param_1 = param_1 + -1;
            } while (param_1 != 0);
        }
    }
    return;
}
