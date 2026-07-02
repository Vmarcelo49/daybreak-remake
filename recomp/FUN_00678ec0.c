// ============================================
// Address:  0x00678ec0
// Original: FUN_00678ec0
// Status:   unreviewed
// ============================================

int FUN_00678ec0(int param_1, uint param_2, int param_3)

{
    int iVar1;
    uint uVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    int iVar6;
    uint uVar7;
    uint *puVar8;
    int extraout_EDX;
    int *piVar9;
    undefined8 uVar10;
    undefined1 local_30[16];
    undefined1 local_20[16];
    uint local_10;
    uint local_c;

    iVar3 = FUN_006788d0(param_1, param_2, param_3);
    if ((-1 < iVar3) && (iVar3 = FUN_006791c0(param_1), iVar6 = 0, iVar3 == 0))
    {
        while (true)
        {
            while (true)
            {
                iVar3 = param_1 + 0x78;
                iVar4 = FUN_0069d460(iVar3, local_20);
                if (iVar4 < 1)
                    break;
                iVar4 = FUN_0067b380(*(int *)(param_1 + 0x60) * 0x20 + *(int *)(param_1 + 0x48),
                                     local_20);
                if (iVar4 < 0)
                {
                    FUN_0069d310(iVar3, 0);
                }
                else
                {
                    if (iVar6 != 0)
                    {
                        uVar7                     = *(uint *)(param_1 + 0x50);
                        uVar5                     = iVar4 + iVar6 >> 2;
                        *(uint *)(param_1 + 0x50) = uVar7 + uVar5;
                        *(uint *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) +
                                                    (iVar4 + iVar6 >> 0x1f) +
                                                    (uint)CARRY4(uVar7, uVar5);
                    }
                    iVar6 = FUN_00679b40(*(undefined4 *)(param_1 + 0x48), 1);
                    uVar7 = iVar6 + iVar4 >> 2;
                    iVar6 = (iVar6 + iVar4 >> 0x1f) + *(int *)(param_1 + 0x54) +
                            (uint)CARRY4(uVar7, *(uint *)(param_1 + 0x50));
                    if ((param_3 < iVar6) ||
                        ((param_3 <= iVar6 && (param_2 <= uVar7 + *(uint *)(param_1 + 0x50)))))
                        goto LAB_006790ea;
                    FUN_0069d310(iVar3, 0);
                    FUN_0067b2a0(param_1 + 0x250, local_20);
                    FUN_0067aa70(param_1 + 0x1e0, param_1 + 0x250);
                    iVar6 = iVar4;
                    if ((-2 < (int)local_c) && (local_c < 0x80000000))
                    {
                        iVar3                     = *(int *)(param_1 + 0x60);
                        iVar4                     = *(int *)(param_1 + 0x44);
                        puVar8                    = (uint *)(iVar4 + iVar3 * 0x10);
                        uVar7                     = *puVar8;
                        iVar1                     = *(int *)(iVar4 + 4 + iVar3 * 0x10);
                        *(uint *)(param_1 + 0x50) = local_10 - *puVar8;
                        *(uint *)(param_1 + 0x54) = (local_c - iVar1) - (uint)(local_10 < uVar7);
                        if ((*(int *)(param_1 + 0x54) < 1) && (*(int *)(param_1 + 0x54) < 0))
                        {
                            *(undefined4 *)(param_1 + 0x50) = 0;
                            *(undefined4 *)(param_1 + 0x54) = 0;
                        }
                        if (0 < iVar3)
                        {
                            puVar8 = (uint *)(iVar4 + 8);
                            do
                            {
                                uVar7                     = *puVar8;
                                uVar5                     = *(uint *)(param_1 + 0x50);
                                uVar2                     = puVar8[1];
                                *(uint *)(param_1 + 0x50) = uVar5 + uVar7;
                                puVar8                    = puVar8 + 4;
                                iVar3                     = iVar3 + -1;
                                *(uint *)(param_1 + 0x54) =
                                    *(int *)(param_1 + 0x54) + uVar2 + (uint)CARRY4(uVar5, uVar7);
                            } while (iVar3 != 0);
                        }
                    }
                }
            }
            if (((iVar4 < 0) && (iVar4 != -3)) ||
                (FUN_00677ba0(param_1, local_30, 0xffffffff, 0xffffffff), extraout_EDX < 0))
                break;
            iVar3 = FUN_0069cb00(local_30);
            if (*(int *)(param_1 + 0x5c) != iVar3)
            {
                FUN_00678480(param_1);
            }
            if (*(int *)(param_1 + 0x58) < 3)
            {
                iVar6                    = FUN_0069cb00(local_30);
                iVar3                    = *(int *)(param_1 + 0x34);
                iVar4                    = 0;
                *(int *)(param_1 + 0x5c) = iVar6;
                if (0 < iVar3)
                {
                    piVar9 = *(int **)(param_1 + 0x40);
                    do
                    {
                        if (*piVar9 == iVar6)
                            break;
                        iVar4  = iVar4 + 1;
                        piVar9 = piVar9 + 1;
                    } while (iVar4 < iVar3);
                }
                if (iVar4 == iVar3)
                {
                    return -0x89;
                }
                *(int *)(param_1 + 0x60) = iVar4;
                FUN_0069d2f0(param_1 + 0x78, iVar6);
                *(undefined4 *)(param_1 + 0x58) = 3;
                iVar3                           = FUN_006791c0(param_1);
                if (iVar3 != 0)
                {
                    return iVar3;
                }
                iVar6 = 0;
            }
            FUN_0069cf90(param_1 + 0x78, local_30);
        }
    LAB_006790ea:
        uVar7                           = *(uint *)(param_1 + 0x50);
        *(undefined4 *)(param_1 + 0x68) = 0;
        *(undefined4 *)(param_1 + 0x70) = 0;
        *(undefined4 *)(param_1 + 0x6c) = 0;
        *(undefined4 *)(param_1 + 0x74) = 0;
        iVar3                           = *(int *)(param_1 + 0x54);
        if (iVar3 <= param_3)
        {
            if (iVar3 < param_3)
                goto LAB_00679116;
            do
            {
                if (param_2 <= uVar7)
                    break;
            LAB_00679116:
                do
                {
                    uVar5 = param_2 - uVar7;
                    iVar3 = (param_3 - iVar3) - (uint)(param_2 < uVar7);
                    uVar7 = FUN_0067b0c0(param_1 + 0x1e0, 0);
                    if ((iVar3 <= (int)uVar7 >> 0x1f) &&
                        ((iVar3 < (int)uVar7 >> 0x1f || (uVar5 < uVar7))))
                    {
                        uVar7 = uVar5;
                    }
                    FUN_0067b120(param_1 + 0x1e0, uVar7);
                    uVar2                     = *(uint *)(param_1 + 0x50);
                    iVar6                     = (int)uVar7 >> 0x1f;
                    *(uint *)(param_1 + 0x50) = uVar2 + uVar7;
                    *(uint *)(param_1 + 0x54) =
                        *(int *)(param_1 + 0x54) + iVar6 + (uint)CARRY4(uVar2, uVar7);
                    if ((iVar6 <= iVar3) && (((iVar6 < iVar3 || (uVar7 < uVar5)) &&
                                              (iVar3 = FUN_00679240(param_1, 0, 1, 1), iVar3 < 1))))
                    {
                        uVar10                          = FUN_006784b0(param_1, 0xffffffff);
                        *(undefined8 *)(param_1 + 0x50) = uVar10;
                    }
                    iVar3 = *(int *)(param_1 + 0x54);
                    uVar7 = *(uint *)(param_1 + 0x50);
                } while (iVar3 < param_3);
            } while (iVar3 <= param_3);
        }
        iVar3 = 0;
    }
    return iVar3;
}
