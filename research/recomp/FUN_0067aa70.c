// ============================================
// Address:  0x0067aa70
// Original: FUN_0067aa70
// Status:   unreviewed
// ============================================

undefined4 FUN_0067aa70(int param_1, int *param_2)

{
    float *pfVar1;
    float fVar2;
    int iVar3;
    int *piVar4;
    int iVar5;
    uint uVar6;
    uint uVar7;
    byte bVar8;
    float *pfVar9;
    int iVar10;
    int iVar11;
    float *pfVar12;
    int iVar13;
    float *pfVar14;
    undefined4 *puVar15;
    int iVar16;
    uint uVar17;
    byte bVar18;
    float *pfVar19;
    int iVar20;
    uint uVar21;
    int iVar22;
    uint local_3c;
    float *local_30;
    uint local_2c;
    uint local_24;
    int local_20;

    iVar16 = *(int *)(param_1 + 4);
    iVar3  = *(int *)(param_1 + 0x68);
    piVar4 = *(int **)(iVar16 + 0x1c);
    iVar5  = piVar4[0x39e];
    if (param_2 == (int *)0x0)
    {
        return 0xffffff7d;
    }
    if ((*(int *)(param_1 + 0x18) < *(int *)(param_1 + 0x14)) && (*(int *)(param_1 + 0x18) != -1))
    {
        return 0xffffff7d;
    }
    uVar6                           = *(uint *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x28);
    *(int *)(param_1 + 0x28)        = param_2[7];
    *(undefined4 *)(param_1 + 0x2c) = 0xffffffff;
    if ((((uVar6 & *(uint *)(param_1 + 0x44)) == 0xffffffff) || (uVar6 + 1 != param_2[0xe])) ||
        (*(uint *)(param_1 + 0x44) + (uint)(0xfffffffe < uVar6) != param_2[0xf]))
    {
        *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb8)   = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xbc)   = 0xffffffff;
    }
    *(int *)(param_1 + 0x40) = param_2[0xe];
    *(int *)(param_1 + 0x44) = param_2[0xf];
    bVar8                    = (byte)iVar5;
    if (*param_2 != 0)
    {
        bVar18                    = bVar8 + 1;
        iVar10                    = piVar4[*(int *)(param_1 + 0x28)] >> (bVar18 & 0x1f);
        iVar22                    = *piVar4 >> (bVar18 & 0x1f);
        uVar21                    = piVar4[1] >> (bVar18 & 0x1f);
        uVar6                     = *(uint *)(param_1 + 0x48);
        uVar17                    = param_2[0x16];
        *(uint *)(param_1 + 0x48) = uVar6 + uVar17;
        uVar7                     = *(uint *)(param_1 + 0x50);
        *(uint *)(param_1 + 0x4c) =
            *(int *)(param_1 + 0x4c) + ((int)uVar17 >> 0x1f) + (uint)CARRY4(uVar6, uVar17);
        uVar6                     = param_2[0x17];
        *(uint *)(param_1 + 0x50) = uVar7 + uVar6;
        uVar17                    = *(uint *)(param_1 + 0x58);
        *(uint *)(param_1 + 0x54) =
            *(int *)(param_1 + 0x54) + ((int)uVar6 >> 0x1f) + (uint)CARRY4(uVar7, uVar6);
        uVar6                     = param_2[0x18];
        *(uint *)(param_1 + 0x58) = uVar17 + uVar6;
        uVar7                     = *(uint *)(param_1 + 0x60);
        *(uint *)(param_1 + 0x5c) =
            *(int *)(param_1 + 0x5c) + ((int)uVar6 >> 0x1f) + (uint)CARRY4(uVar17, uVar6);
        uVar6                     = param_2[0x19];
        *(uint *)(param_1 + 0x60) = uVar7 + uVar6;
        *(uint *)(param_1 + 100) =
            *(int *)(param_1 + 100) + ((int)uVar6 >> 0x1f) + (uint)CARRY4(uVar7, uVar6);
        if (*(int *)(param_1 + 0x30) == 0)
        {
            local_2c = 0;
            local_3c = uVar21;
        }
        else
        {
            local_3c = 0;
            local_2c = uVar21;
        }
        local_30 = (float *)0x0;
        if (0 < *(int *)(iVar16 + 4))
        {
            do
            {
                pfVar9   = local_30;
                local_24 = iVar22;
                if (*(int *)(param_1 + 0x24) == 0)
                {
                    if (*(int *)(param_1 + 0x28) == 0)
                    {
                        iVar11 = FUN_00681c20(*(int *)(iVar3 + 4) - iVar5);
                        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 8) + (int)local_30 * 4) +
                                           local_3c * 4);
                        iVar20 = *(int *)(*param_2 + (int)local_30 * 4);
                        if (0 < iVar22)
                        {
                            pfVar14  = pfVar1;
                            pfVar12  = (float *)(iVar11 + -4 + iVar22 * 4);
                            local_20 = iVar22;
                            do
                            {
                                pfVar19  = (float *)((iVar11 - (int)pfVar1) + (int)pfVar14);
                                local_20 = local_20 + -1;
                                *pfVar14 = *pfVar12 * *pfVar14 +
                                           *(float *)((int)pfVar19 + (iVar20 - iVar11)) * *pfVar19;
                                pfVar14  = pfVar14 + 1;
                                pfVar12  = pfVar12 + -1;
                            } while (local_20 != 0);
                        }
                    }
                    else
                    {
                        iVar13 = FUN_00681c20(*(int *)(iVar3 + 4) - iVar5);
                        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 8) + (int)local_30 * 4) +
                                           local_3c * 4);
                        iVar20 = *(int *)(*param_2 + (int)local_30 * 4) +
                                 ((int)uVar21 / 2 - iVar22 / 2) * 4;
                        iVar11 = 0;
                        if (0 < iVar22)
                        {
                            pfVar14 = (float *)(iVar13 + -4 + iVar22 * 4);
                            pfVar12 = pfVar1;
                            do
                            {
                                pfVar19  = (float *)((iVar13 - (int)pfVar1) + (int)pfVar12);
                                local_24 = local_24 + -1;
                                *pfVar12 = *pfVar14 * *pfVar12 +
                                           *(float *)((int)pfVar19 + (iVar20 - iVar13)) * *pfVar19;
                                pfVar14  = pfVar14 + -1;
                                pfVar12  = pfVar12 + 1;
                                iVar11   = iVar22;
                            } while (local_24 != 0);
                        }
                        iVar13 = (int)uVar21 / 2 + iVar22 / 2;
                        if (iVar11 < iVar13)
                        {
                            pfVar14 = pfVar1 + iVar11;
                            iVar13  = iVar13 - iVar11;
                            do
                            {
                                *pfVar14 = *(float *)((iVar20 - (int)pfVar1) + (int)pfVar14);
                                pfVar14  = pfVar14 + 1;
                                iVar13   = iVar13 + -1;
                            } while (iVar13 != 0);
                        }
                    }
                }
                else if (*(int *)(param_1 + 0x28) == 0)
                {
                    iVar11 = FUN_00681c20(*(int *)(iVar3 + 4) - iVar5);
                    pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 8) + (int)local_30 * 4) +
                                       (((int)uVar21 / 2 - iVar22 / 2) + local_3c) * 4);
                    iVar20 = *(int *)(*param_2 + (int)local_30 * 4);
                    if (0 < iVar22)
                    {
                        pfVar14 = pfVar1;
                        pfVar12 = (float *)(iVar11 + -4 + iVar22 * 4);
                        do
                        {
                            pfVar19  = (float *)((iVar11 - (int)pfVar1) + (int)pfVar14);
                            local_24 = local_24 + -1;
                            *pfVar14 = *pfVar12 * *pfVar14 +
                                       *(float *)((int)pfVar19 + (iVar20 - iVar11)) * *pfVar19;
                            pfVar14  = pfVar14 + 1;
                            pfVar12  = pfVar12 + -1;
                        } while (local_24 != 0);
                    }
                }
                else
                {
                    iVar11 = FUN_00681c20(*(int *)(iVar3 + 8) - iVar5);
                    pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 8) + (int)local_30 * 4) +
                                       local_3c * 4);
                    iVar20 = *(int *)(*param_2 + (int)local_30 * 4);
                    if (0 < (int)uVar21)
                    {
                        local_30 = (float *)(iVar11 + -4 + uVar21 * 4);
                        pfVar14  = pfVar1;
                        local_24 = uVar21;
                        do
                        {
                            pfVar12  = (float *)((iVar11 - (int)pfVar1) + (int)pfVar14);
                            fVar2    = *local_30;
                            local_30 = local_30 + -1;
                            local_24 = local_24 - 1;
                            *pfVar14 = fVar2 * *pfVar14 +
                                       *(float *)((int)pfVar12 + (iVar20 - iVar11)) * *pfVar12;
                            pfVar14  = pfVar14 + 1;
                        } while (local_24 != 0);
                    }
                }
                puVar15 = (undefined4 *)(*(int *)(*(int *)(param_1 + 8) + (int)pfVar9 * 4) +
                                         local_2c * 4);
                if (0 < iVar10)
                {
                    iVar20   = (*(int *)(*param_2 + (int)pfVar9 * 4) + iVar10 * 4) - (int)puVar15;
                    local_20 = iVar10;
                    do
                    {
                        *puVar15 = *(undefined4 *)(iVar20 + (int)puVar15);
                        puVar15  = puVar15 + 1;
                        local_20 = local_20 + -1;
                    } while (local_20 != 0);
                }
                local_30 = (float *)((int)pfVar9 + 1);
            } while ((int)local_30 < *(int *)(iVar16 + 4));
        }
        *(uint *)(param_1 + 0x30) = ~-(uint)(*(int *)(param_1 + 0x30) != 0) & uVar21;
        if (*(int *)(param_1 + 0x18) == -1)
        {
            *(uint *)(param_1 + 0x18) = local_2c;
            *(uint *)(param_1 + 0x14) = local_2c;
        }
        else
        {
            *(uint *)(param_1 + 0x18) = local_3c;
            *(uint *)(param_1 + 0x14) =
                (((int)(piVar4[*(int *)(param_1 + 0x24)] +
                        (piVar4[*(int *)(param_1 + 0x24)] >> 0x1f & 3U)) >>
                  2) +
                     ((int)(piVar4[*(int *)(param_1 + 0x28)] +
                            (piVar4[*(int *)(param_1 + 0x28)] >> 0x1f & 3U)) >>
                      2) >>
                 (bVar8 & 0x1f)) +
                local_3c;
        }
    }
    if ((*(uint *)(iVar3 + 0xb8) & *(uint *)(iVar3 + 0xbc)) == 0xffffffff)
    {
        *(undefined4 *)(iVar3 + 0xb8) = 0;
        *(undefined4 *)(iVar3 + 0xbc) = 0;
    }
    else
    {
        uVar17                  = ((int)(piVar4[*(int *)(param_1 + 0x28)] +
                                         (piVar4[*(int *)(param_1 + 0x28)] >> 0x1f & 3U)) >>
                                   2) +
                                  ((int)(piVar4[*(int *)(param_1 + 0x24)] +
                                         (piVar4[*(int *)(param_1 + 0x24)] >> 0x1f & 3U)) >>
                                   2);
        uVar6                   = *(uint *)(iVar3 + 0xb8);
        *(uint *)(iVar3 + 0xb8) = uVar17 + uVar6;
        *(uint *)(iVar3 + 0xbc) =
            ((int)uVar17 >> 0x1f) + *(int *)(iVar3 + 0xbc) + (uint)CARRY4(uVar17, uVar6);
    }
    uVar6 = *(uint *)(param_1 + 0x38);
    if ((uVar6 & *(uint *)(param_1 + 0x3c)) == 0xffffffff)
    {
        uVar6 = param_2[0xd];
        if ((param_2[0xc] & uVar6) != 0xffffffff)
        {
            *(int *)(param_1 + 0x38)  = param_2[0xc];
            *(uint *)(param_1 + 0x3c) = uVar6;
            if (((int)uVar6 <= *(int *)(iVar3 + 0xbc)) &&
                (((int)uVar6 < *(int *)(iVar3 + 0xbc) ||
                  (*(uint *)(param_1 + 0x38) < *(uint *)(iVar3 + 0xb8)))))
            {
                if (param_2[0xb] == 0)
                {
                    iVar16                   = __allshr();
                    iVar16                   = *(int *)(param_1 + 0x18) + iVar16;
                    *(int *)(param_1 + 0x18) = iVar16;
                    if (*(int *)(param_1 + 0x14) < iVar16)
                    {
                        *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x14);
                    }
                }
                else
                {
                    iVar16                   = __allshr();
                    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) - iVar16;
                }
            }
        }
    }
    else
    {
        uVar17                    = ((int)(piVar4[*(int *)(param_1 + 0x28)] +
                                           (piVar4[*(int *)(param_1 + 0x28)] >> 0x1f & 3U)) >>
                                     2) +
                                    ((int)(piVar4[*(int *)(param_1 + 0x24)] +
                                           (piVar4[*(int *)(param_1 + 0x24)] >> 0x1f & 3U)) >>
                                     2);
        *(uint *)(param_1 + 0x38) = uVar17 + uVar6;
        *(uint *)(param_1 + 0x3c) =
            ((int)uVar17 >> 0x1f) + *(int *)(param_1 + 0x3c) + (uint)CARRY4(uVar17, uVar6);
        uVar6  = param_2[0xc];
        uVar17 = param_2[0xd];
        if ((uVar6 & uVar17) != 0xffffffff)
        {
            uVar7 = *(uint *)(param_1 + 0x3c);
            if ((*(uint *)(param_1 + 0x38) != uVar6) || (uVar7 != uVar17))
            {
                if (((((int)uVar17 <= (int)uVar7) &&
                      (((int)uVar17 < (int)uVar7 || (uVar6 < *(uint *)(param_1 + 0x38))))) &&
                     (iVar16 = *(int *)(param_1 + 0x38) - param_2[0xc], iVar16 != 0)) &&
                    (param_2[0xb] != 0))
                {
                    *(int *)(param_1 + 0x14) =
                        *(int *)(param_1 + 0x14) - (iVar16 >> (bVar8 & 0x1f));
                }
                *(int *)(param_1 + 0x38) = param_2[0xc];
                *(int *)(param_1 + 0x3c) = param_2[0xd];
            }
        }
    }
    if (param_2[0xb] != 0)
    {
        *(undefined4 *)(param_1 + 0x20) = 1;
    }
    return 0;
}
