// ============================================
// Address:  0x0040b2b0
// Original: FUN_0040b2b0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0040b2b0(int param_1)

{
    bool bVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    int iVar5;
    uint uVar6;
    uint uVar7;
    int iVar8;
    float fVar9;
    float fVar10;
    undefined4 local_14c;
    undefined4 local_140;
    int local_5c;
    int local_58;
    int local_54;
    int local_50;
    uint local_44;
    int local_40;
    float local_3c;
    undefined4 local_2c;
    int local_24;
    int local_10;
    uint local_c;
    bool local_8[4];

    if (0x23 < *(int *)(param_1 + 0x3c3c))
    {
        FUN_00655d60(0, 0);
    }
    for (local_c = 0; (int)local_c < 4; local_c = local_c + 1)
    {
        if ((*(int *)(param_1 + 0x3d08 + local_c * 4) < 0) ||
            (0xf < *(int *)(param_1 + 0x3d08 + local_c * 4)))
        {
            if ((-1 < *(int *)(param_1 + 0x3c80 + local_c * 4)) &&
                (*(int *)(param_1 + 0x3c90 + *(int *)(param_1 + 0x3c80 + local_c * 4) * 4) == 2))
            {
                uVar7 = local_c & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                fVar10 = (float)(int)uVar7 * 300.0 + 300.0;
                fVar9  = (float)((int)local_c / 2) * 400.0 + 200.0;
                FUN_0065d150(fVar9, fVar10);
                FUN_00655d60(fVar9, fVar10);
            }
        }
        else
        {
            if ((int)local_c < 2)
            {
                FUN_0040da60(0x3f800000, 0x3f800000);
            }
            else
            {
                FUN_0040da60(0xbf800000, 0x3f800000);
            }
            uVar7 = local_c & 0x80000001;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655d60((float)((int)local_c / 2) * 400.0 + 200.0,
                         (float)(int)uVar7 * 300.0 + 300.0);
        }
    }
    if (*(int *)(param_1 + 0x3c3c) < 0x23)
    {
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xf, 0);
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1b, 0);
    }
    FUN_00655d60(0, 0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xf, 1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1b, 1);
    if (0x23 < *(int *)(param_1 + 0x3c3c))
    {
        for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
        {
            iVar5 = *(int *)(param_1 + 0x3c48 + local_10 * 4) / 3;
            iVar8 = *(int *)(param_1 + 0x3c48 + local_10 * 4) % 3;
            if (iVar8 < 2)
            {
                uVar7 = iVar8 + iVar5 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)iVar5 * 400.0 + 200.0 + (float)(iVar5 == 1) * 5.0,
                             (float)iVar8 * 300.0 +
                                 (float)(iVar5 == 1) * 4.0 * (float)(iVar8 * 2 + -1),
                             0,
                             uVar7);
                if ((DAT_006cfdb0 != '\0') && (-1 < (int)(&DAT_006cfb18)[local_10]))
                {
                    FUN_00646bd0((&DAT_006cfb18)[local_10],
                                 (float)iVar5 * 416.0 + 100.0,
                                 (float)local_10 * 20.0 + (float)iVar8 * 320.0 + 90.0,
                                 1);
                }
            }
            else
            {
                FUN_00655830((float)(iVar5 * 2 + -1) * 64.0 + 400.0, 0x44098000, local_10, 0);
            }
        }
    }
    for (local_24 = 0; local_24 < 0x10; local_24 = local_24 + 1)
    {
        local_2c = 0;
        iVar5    = *(int *)(&DAT_006b7250 + local_24 * 4);
        bVar1    = *(float *)(param_1 + 0x3d50 + iVar5 * 4) < 1.0;
        if (bVar1)
        {
            local_2c = 2;
        }
        FUN_0040da60(*(undefined4 *)(param_1 + 0x3d50 + iVar5 * 4),
                     2.0 - *(float *)(param_1 + 0x3d50 + iVar5 * 4));
        if ((((*(int *)(param_1 + 0x3d08) == iVar5) || (*(int *)(param_1 + 0x3d0c) == iVar5)) ||
             (*(int *)(param_1 + 0x3d10) == iVar5)) ||
            (*(int *)(param_1 + 0x3d14) == iVar5))
        {
            if (iVar5 < 0x10)
            {
                iVar8 = (*(int *)(param_1 + 0x3c3c) % 0x28) / 10;
                FUN_00655830(*(float *)(&DAT_006b71d0 + iVar5 * 4) * 48.0 + 400.0,
                             *(float *)(&DAT_006b7210 + iVar5 * 4) * 36.0 + 150.0,
                             (iVar8 + 1) % 3,
                             (iVar8 + 1) / 3);
            }
            else
            {
                uVar7 = *(uint *)(param_1 + 0x3c3c) & 0x80000007;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(*(float *)(&DAT_006b71d0 + iVar5 * 4) * 48.0 + 400.0,
                             *(float *)(&DAT_006b7210 + iVar5 * 4) * 36.0 + 160.0,
                             ((int)uVar7 / 2 + 1) % 3,
                             ((int)uVar7 / 2 + 1) / 3);
            }
        }
        else
        {
            local_3c = 0.0;
            if (0xf < iVar5)
            {
                local_3c = 15.0 - ((float)iVar5 - 14.0) * 30.0;
            }
            FUN_00655830(*(float *)(&DAT_006b71d0 + iVar5 * 4) * 48.0 + local_3c + 400.0,
                         *(float *)(&DAT_006b7210 + iVar5 * 4) * 36.0 + 160.0,
                         local_2c,
                         bVar1);
        }
    }
    _memset(local_8, 0, 4);
    if ((&DAT_006cfde1)[DAT_006cfdb4] == -1)
    {
        local_8[3] = true;
        local_8[2] = true;
        local_8[1] = true;
        local_8[0] = true;
    }
    else
    {
        for (local_40 = 0; local_40 < 4; local_40 = local_40 + 1)
        {
            if ((int)(char)(&DAT_006cfde1)[DAT_006cfdb4] ==
                *(int *)(param_1 + 0x3cf8 + local_40 * 4))
            {
                bVar1 = 1 < local_40;
                if (bVar1)
                {
                    local_8[1] = false;
                    local_8[0] = false;
                    local_8[3] = true;
                    local_8[2] = true;
                }
                else
                {
                    local_8[1] = true;
                    local_8[0] = true;
                    local_8[3] = false;
                    local_8[2] = false;
                }
                local_8[1] = !bVar1;
                local_8[0] = !bVar1;
                local_8[2] = bVar1;
                local_8[3] = bVar1;
                break;
            }
        }
    }
    for (local_44 = 0; (int)local_44 < 4; local_44 = local_44 + 1)
    {
        if (*(char *)(param_1 + local_44 + 0x3cb0) != '\0')
        {
            if ((int)local_44 < 2)
            {
                FUN_0040da60(0xbf800000, 0x3f800000);
            }
            else
            {
                FUN_0040da60(0x3f800000, 0x3f800000);
            }
            uVar7 = local_44 & 0x80000001;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                         (float)(int)uVar7 * 300.0 + 120.0,
                         *(int *)(param_1 + 0x3d38 + local_44 * 4) % 3,
                         *(int *)(param_1 + 0x3d38 + local_44 * 4) / 3);
        }
        bVar3 = true;
        bVar4 = true;
        bVar2 = true;
        bVar1 = true;
        if (-1 < *(int *)(param_1 + 0x3c80 + local_44 * 4))
        {
            switch (
                *(undefined4 *)(param_1 + 0x3c90 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4))
            {
            case 1:
                bVar1 = false;
                break;
            case 2:
                bVar4 = false;
                break;
            case 3:
                bVar3 = false;
                break;
            case 4:
                bVar2 = false;
            }
        }
        if ((-1 < *(int *)(param_1 + 0x3cf8 + local_44 * 4)) && (bVar1))
        {
            if (*(int *)(param_1 + 0x3cf8 + local_44 * 4) < 4)
            {
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                             (float)(int)uVar7 * 300.0 + 180.0,
                             *(undefined4 *)(param_1 + 0x3cf8 + local_44 * 4),
                             0);
                if (DAT_006cfdb0 != '\0')
                {
                    uVar7 = local_44 & 0x80000001;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00646cf0((&DAT_006cfb18)[*(int *)(param_1 + 0x3cf8 + local_44 * 4)],
                                 (float)((int)local_44 / 2) * 660.0 + 20.0,
                                 (float)(int)uVar7 * 300.0 + 280.0);
                }
            }
            else
            {
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                             (float)(int)uVar7 * 300.0 + 180.0,
                             0,
                             2);
            }
        }
        if (((-1 < *(int *)(param_1 + 0x3d28 + local_44 * 4)) && (bVar2)) &&
            ((DAT_006cfdb0 == '\0' || (local_8[local_44] != false))))
        {
            FUN_00408250(0x3f000000);
            uVar7 = local_44 & 0x80000001;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                         (float)(int)uVar7 * 300.0 + 265.0,
                         0,
                         *(undefined4 *)(param_1 + 0x3d28 + local_44 * 4));
            FUN_00408250(0x3f800000);
        }
        if ((-1 < *(int *)(param_1 + 0x3d18 + local_44 * 4)) && (bVar3))
        {
            FUN_00408250(0x3f000000);
            uVar7 = local_44 & 0x80000001;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                         (float)(int)uVar7 * 300.0 + 240.0,
                         0,
                         *(undefined4 *)(param_1 + 0x3d18 + local_44 * 4));
            FUN_00408250(0x3f800000);
        }
        if ((-1 < *(int *)(param_1 + 0x3d08 + local_44 * 4)) && (bVar4))
        {
            uVar7 = *(uint *)(param_1 + 0x3d08 + local_44 * 4) & 0x80000007;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffff8) + 1;
            }
            iVar5 = *(int *)(param_1 + 0x3d08 + local_44 * 4);
            uVar6 = local_44 & 0x80000001;
            if ((int)uVar6 < 0)
            {
                uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                         (float)(int)uVar6 * 300.0 + 210.0,
                         (int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3,
                         uVar7);
        }
        if (-1 < *(int *)(param_1 + 0x3c80 + local_44 * 4))
        {
            if (*(int *)(param_1 + 0x3c90 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4) != 2)
            {
                if ((int)local_44 < 2)
                {
                    FUN_0040da60(0xbf800000, 0x3f800000);
                }
                else
                {
                    FUN_0040da60(0x3f800000, 0x3f800000);
                }
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 660.0 + 70.0,
                             (float)(int)uVar7 * 300.0 + 120.0,
                             *(int *)(param_1 + 0x3d38 + local_44 * 4) % 3,
                             *(int *)(param_1 + 0x3d38 + local_44 * 4) / 3);
            }
            fVar10 = (1.0 - ((float)((int)local_44 < 2) + (float)((int)local_44 < 2))) *
                     *(float *)(param_1 + 0x3cc4 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4);
            switch (
                *(undefined4 *)(param_1 + 0x3c90 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4))
            {
            case 1:
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 50.0,
                             0,
                             4);
                FUN_004082f0(0x80ffffff);
                if ((*(int *)(param_1 + 0x3ca0 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4) <
                     0) ||
                    (*(int *)(param_1 + 0x3c58 + local_44 * 4) != 1))
                {
                    local_140 = 0;
                }
                else
                {
                    local_140 = 1;
                }
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 198.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 130.0,
                             local_140,
                             (1 - *(int *)(param_1 + 0x3c58 + local_44 * 4)) * 2);
                FUN_004082f0(0xffffffff);
                if ((*(int *)(param_1 + 0x3ca0 + *(int *)(param_1 + 0x3c80 + local_44 * 4) * 4) <
                     0) ||
                    (*(int *)(param_1 + 0x3c58 + local_44 * 4) != 0))
                {
                    local_14c = 0;
                }
                else
                {
                    local_14c = 1;
                }
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 110.0,
                             local_14c,
                             *(int *)(param_1 + 0x3c58 + local_44 * 4) << 1);
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655d60((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 110.0);
                break;
            case 2:
                FUN_00655830(*(float *)(param_1 + 0x3cd8 + local_44 * 4) + 400.0,
                             *(float *)(param_1 + 0x3ce8 + local_44 * 4) + 150.0,
                             *(undefined4 *)(param_1 + 0x3c80 + local_44 * 4),
                             0);
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 50.0,
                             0,
                             0);
                if (*(int *)(param_1 + 0x3d08 + local_44 * 4) < 0)
                {
                    uVar7 = local_44 & 0x80000001;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                                 (float)(int)uVar7 * 300.0 + 90.0,
                                 0,
                                 0);
                }
                else
                {
                    FUN_00408250(0x3f800000);
                    uVar7 = *(uint *)(param_1 + 0x3d08 + local_44 * 4) & 0x80000007;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffff8) + 1;
                    }
                    iVar5 = *(int *)(param_1 + 0x3d08 + local_44 * 4);
                    uVar6 = local_44 & 0x80000001;
                    if ((int)uVar6 < 0)
                    {
                        uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                                 (float)(int)uVar6 * 300.0 + 90.0,
                                 (int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3,
                                 uVar7);
                    FUN_00408250(0x3f000000);
                }
                break;
            case 3:
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 50.0,
                             0,
                             1);
                if (*(int *)(param_1 + 0x3d08 + local_44 * 4) < 0xe)
                {
                    local_50 = 3;
                    local_54 = local_50;
                }
                else
                {
                    local_50 = 2;
                    local_54 = local_50;
                }
                while (local_54 = local_54 + -1, -1 < local_54)
                {
                    FUN_004082f0((0xff >> ((byte)local_54 & 0x1f)) << 0x18 | 0xffffff);
                    uVar7 = local_44 & 0x80000001;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00655830((float)((int)local_44 / 2) * 420.0 + (float)local_54 * 8.0 +
                                     190.0 + fVar10,
                                 (float)(int)uVar7 * 300.0 + (float)local_54 * 20.0 + 110.0,
                                 0,
                                 (*(int *)(param_1 + 0x3c58 + local_44 * 4) + local_54) % local_50);
                }
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 200.0,
                             1,
                             *(undefined4 *)(param_1 + 0x3c58 + local_44 * 4));
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655d60((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 110.0);
                break;
            case 4:
                uVar7 = local_44 & 0x80000001;
                if ((int)uVar7 < 0)
                {
                    uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                }
                FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                             (float)(int)uVar7 * 300.0 + 50.0,
                             0,
                             3);
                if (((DAT_006cfdb0 == '\0') || (*(int *)(param_1 + 0x3c80 + local_44 * 4) ==
                                                (int)(char)(&DAT_006cfde1)[DAT_006cfdb4])) ||
                    ((&DAT_006cfde1)[DAT_006cfdb4] == -1))
                {
                    for (local_58 = 2; -1 < local_58; local_58 = local_58 + -1)
                    {
                        FUN_004082f0((0xff >> ((byte)local_58 & 0x1f)) << 0x18 | 0xffffff);
                        uVar7 = local_44 & 0x80000001;
                        if ((int)uVar7 < 0)
                        {
                            uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                        }
                        FUN_00655830((float)((int)local_44 / 2) * 420.0 + (float)local_58 * 8.0 +
                                         190.0 + fVar10,
                                     (float)(int)uVar7 * 300.0 + (float)local_58 * 20.0 + 110.0,
                                     0,
                                     (*(int *)(param_1 + 0x3c58 + local_44 * 4) + local_58) % 3);
                    }
                    uVar7 = local_44 & 0x80000001;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00655830((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                                 (float)(int)uVar7 * 300.0 + 200.0,
                                 0,
                                 *(int *)(param_1 + 0x3c58 + local_44 * 4) + 2);
                    uVar7 = local_44 & 0x80000001;
                    if ((int)uVar7 < 0)
                    {
                        uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
                    }
                    FUN_00655d60((float)((int)local_44 / 2) * 420.0 + 190.0 + fVar10,
                                 (float)(int)uVar7 * 300.0 + 110.0);
                }
            }
        }
        if (*(char *)(param_1 + local_44 + 0x3cb0) != '\0')
        {
            FUN_00408250(*(undefined4 *)(param_1 + 0x3cb4 + local_44 * 4));
            uVar7 = local_44 & 0x80000001;
            if ((int)uVar7 < 0)
            {
                uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
            }
            FUN_00655d60((float)((int)local_44 / 2) * 400.0 + 200.0,
                         (float)(int)uVar7 * 300.0 + 110.0);
        }
    }
    if (0x23 < *(int *)(param_1 + 0x3c3c))
    {
        FUN_00655830(0x43a80000, 0x44098000, 0, 1);
        FUN_00655830(0x43e80000, 0x44098000, 1, 1);
    }
    if (DAT_006cfdb0 != '\0')
    {
        for (local_5c = 0; local_5c < 4; local_5c = local_5c + 1)
        {
            iVar5 = (int)*(char *)(param_1 + local_5c + 0x3d91);
            iVar8 = *(int *)(param_1 + 0x3c48 + iVar5 * 4) % 3;
            if (iVar8 < 2)
            {
                if (*(int *)(param_1 + 0x3c48 + iVar5 * 4) / 3 == 0)
                {
                    FUN_006467e0((&DAT_006cfb18)[iVar5], 0, (float)iVar8 * 300.0);
                }
                else
                {
                    FUN_006467e0((&DAT_006cfb18)[iVar5], 0x43f00000, (float)iVar8 * 300.0);
                }
            }
            else
            {
                FUN_006467e0((&DAT_006cfb18)[iVar5], 0x43700000, 0x43960000);
            }
        }
        FUN_00646870(0x42c80000);
        FUN_00646500(0x43500000, 0x44020000);
        if (DAT_006cfdb0 == '\x02')
        {
            FUN_0064c1e0();
        }
    }
    if ((0x22 < *(int *)(param_1 + 0x3c3c)) && (*(int *)(param_1 + 0x3c3c) < 0x37))
    {
        FUN_00651860(0,
                     0,
                     0x44480000,
                     0x44160000,
                     (uint)(byte)(('7' - (char)*(undefined4 *)(param_1 + 0x3c3c)) * '\f' + 0xf)
                             << 0x18 |
                         0xffffff);
    }
    if ((0x18 < *(int *)(param_1 + 0x3c3c)) && (*(int *)(param_1 + 0x3c3c) < 0x23))
    {
        FUN_00651860(0,
                     0,
                     0x44480000,
                     0x44160000,
                     (uint)(byte)(((char)*(undefined4 *)(param_1 + 0x3c3c) + -0x19) * '\x18' + 0xf)
                             << 0x18 |
                         0xffffff);
    }
    return;
}
