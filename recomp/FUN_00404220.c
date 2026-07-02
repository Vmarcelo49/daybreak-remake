// ============================================
// Address:  0x00404220
// Original: FUN_00404220
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00404220(int param_1)

{
    bool bVar1;
    bool bVar2;
    char cVar3;
    int iVar4;
    int iVar5;
    undefined4 *puVar6;
    char *pcVar7;
    int local_38;
    int local_30;
    int local_2c;
    int local_28;
    int local_24;
    int local_20;
    uint local_18;
    int local_c;
    int local_8;

    FUN_006584e0();
    FUN_006585f0();
    cVar3 = FUN_00657820(0xcb);
    if (cVar3 == '\0')
    {
        cVar3 = FUN_00657820(0xcd);
        if (cVar3 == '\0')
        {
            *(undefined4 *)(param_1 + 0x5c4) = 0;
        }
        else
        {
            if (*(int *)(param_1 + 0x5c4) < 0)
            {
                *(undefined4 *)(param_1 + 0x5c4) = 0;
            }
            *(int *)(param_1 + 0x5c4) = *(int *)(param_1 + 0x5c4) + 1;
        }
    }
    else
    {
        if (0 < *(int *)(param_1 + 0x5c4))
        {
            *(undefined4 *)(param_1 + 0x5c4) = 0;
        }
        *(int *)(param_1 + 0x5c4) = *(int *)(param_1 + 0x5c4) + -1;
    }
    *(undefined4 *)(param_1 + 0x5c8) = 0;
    cVar3                            = FUN_006586d0(0x1c);
    if ((cVar3 == '\0') && (cVar3 = FUN_006586d0(0x39), cVar3 == '\0'))
    {
        *(undefined4 *)(param_1 + 0x5cc) = 0;
    }
    else
    {
        *(int *)(param_1 + 0x5cc) = *(int *)(param_1 + 0x5cc) + 1;
    }
    cVar3 = FUN_00657820(1);
    if (cVar3 == '\0')
    {
        *(undefined4 *)(param_1 + 0x5d0) = 0;
    }
    else
    {
        *(int *)(param_1 + 0x5d0) = *(int *)(param_1 + 0x5d0) + 1;
    }
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        FUN_00657390();
        iVar4 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x5c4));
        iVar5 = FUN_00403aa0((&DAT_006cae94)[local_8 * 0x19]);
        if (iVar4 < iVar5)
        {
            *(undefined4 *)(param_1 + 0x5c4) = (&DAT_006cae94)[local_8 * 0x19];
        }
        iVar4 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x5c8));
        iVar5 = FUN_00403aa0((&DAT_006cae98)[local_8 * 0x19]);
        if (iVar4 < iVar5)
        {
            *(undefined4 *)(param_1 + 0x5c8) = (&DAT_006cae98)[local_8 * 0x19];
        }
        if (*(uint *)(param_1 + 0x5cc) < (uint)(&DAT_006cae9c)[local_8 * 0x19])
        {
            *(undefined4 *)(param_1 + 0x5cc) = (&DAT_006cae9c)[local_8 * 0x19];
        }
        if (*(uint *)(param_1 + 0x5d0) < (uint)(&DAT_006caea0)[local_8 * 0x19])
        {
            *(undefined4 *)(param_1 + 0x5d0) = (&DAT_006caea0)[local_8 * 0x19];
        }
    }
    if (*(int *)(param_1 + 0x5c0) == 0)
    {
        if (*(int *)(param_1 + 0x5c4) == 1)
        {
            *(int *)(param_1 + 0x5b8) = (*(int *)(param_1 + 0x5b8) + 1) % 5;
            FUN_0064aed0(2);
        }
        if (*(int *)(param_1 + 0x5c4) == -1)
        {
            *(int *)(param_1 + 0x5b8) = (*(int *)(param_1 + 0x5b8) + 4) % 5;
            FUN_0064aed0(2);
        }
        if (*(int *)(param_1 + 0x5cc) == 1)
        {
            FUN_0064aed0(0);
            if (3 < *(int *)(param_1 + 0x5b8))
            {
                FUN_006488d0();
                return 1;
            }
            *(undefined4 *)(param_1 + 0x5bc)                  = 0;
            *(undefined4 *)(param_1 + 0x5c0)                  = 1;
            (&DAT_006cfe20)[*(int *)(param_1 + 0x5b8) * 0x34] = 0xfe;
            for (local_c = 0; local_c < 0xc; local_c = local_c + 1)
            {
                *(undefined4 *)(&DAT_006cfe24 + local_c * 4 + *(int *)(param_1 + 0x5b8) * 0x34) =
                    0xffffffff;
            }
            *(undefined4 *)(param_1 + 0x5d4) = 1;
        }
        if (*(int *)(param_1 + 0x5d0) == 1)
        {
            FUN_0064aed0(1);
            FUN_006488d0();
            return 1;
        }
        cVar3 = FUN_006586d0(0x1c);
        if ((cVar3 != '\0') && ((cVar3 = FUN_006586d0(0xb8),
                                 cVar3 != '\0' || (cVar3 = FUN_006586d0(0x38), cVar3 != '\0'))))
        {
            FUN_0064ad70();
        }
    }
    else if (*(int *)(param_1 + 0x5c0) == 1)
    {
        iVar4  = *(int *)(param_1 + 0x5b8) * 0x34;
        pcVar7 = &DAT_006cfe20 + iVar4;
        bVar2  = false;
        for (local_18 = 0; (int)local_18 < 0xff; local_18 = local_18 + 1)
        {
            if ((local_18 != 0x94) && (cVar3 = FUN_006586d0(local_18 & 0xff), cVar3 != '\0'))
            {
                if (local_18 == 1)
                {
                    *(undefined4 *)(param_1 + 0x5c0) = 0;
                    FUN_0064aed0(0);
                    break;
                }
                bVar2 = true;
                if ((*(int *)(param_1 + 0x5d4) == 0) && (*(int *)(param_1 + 0x5bc) < 0xc))
                {
                    if (*pcVar7 != -1)
                    {
                        for (local_20 = 0; local_20 < 0xc; local_20 = local_20 + 1)
                        {
                            *(undefined4 *)(&DAT_006cfe24 + local_20 * 4 + iVar4) = 0xffffffff;
                        }
                        *(undefined4 *)(param_1 + 0x5bc) = 0;
                        *pcVar7                          = -1;
                    }
                    bVar1 = false;
                    for (local_24 = 0; local_24 < *(int *)(param_1 + 0x5bc);
                         local_24 = local_24 + 1)
                    {
                        if (*(uint *)(&DAT_006cfe24 + local_24 * 4 + iVar4) == local_18)
                        {
                            bVar1 = true;
                        }
                    }
                    if (!bVar1)
                    {
                        *(uint *)(&DAT_006cfe24 + *(int *)(param_1 + 0x5bc) * 4 + iVar4) = local_18;
                        FUN_0064aed0(2);
                        *(int *)(param_1 + 0x5bc) = *(int *)(param_1 + 0x5bc) + 1;
                    }
                }
            }
        }
        for (local_28 = 0; local_28 < (int)(uint)DAT_006d1a28; local_28 = local_28 + 1)
        {
            puVar6 = (undefined4 *)FUN_00404e20(local_28);
            iVar5  = FUN_00403aa0(*puVar6);
            if (iVar5 < 0x1f5)
            {
                iVar5 = FUN_00404e20(local_28);
                iVar5 = FUN_00403aa0(*(undefined4 *)(iVar5 + 4));
                if (500 < iVar5)
                    goto LAB_004047e8;
                for (local_2c = 0; local_2c < 0x10; local_2c = local_2c + 1)
                {
                    iVar5 = FUN_00404e20(local_28);
                    if (((*(char *)(iVar5 + 0x30 + local_2c) != '\0') &&
                         (bVar2 = true, *(int *)(param_1 + 0x5d4) == 0)) &&
                        (*(int *)(param_1 + 0x5bc) < 0xc))
                    {
                        if (*pcVar7 != local_28)
                        {
                            for (local_30 = 0; local_30 < 0xc; local_30 = local_30 + 1)
                            {
                                *(undefined4 *)(&DAT_006cfe24 + local_30 * 4 + iVar4) = 0xffffffff;
                            }
                            *pcVar7                          = (char)local_28;
                            *(undefined4 *)(param_1 + 0x5bc) = 4;
                        }
                        if ((*(int *)(param_1 + 0x5bc) == 8) &&
                            (iVar5 = FUN_00658700((int)*pcVar7), iVar5 < 8))
                        {
                            *(int *)(&DAT_006cfe24 + *(int *)(param_1 + 0x5bc) * 4 + iVar4) =
                                local_2c;
                            FUN_0064aed0(0);
                            *(undefined4 *)(param_1 + 0x5c0) = 0;
                            FUN_00657330(&DAT_006cfe20 + *(int *)(param_1 + 0x5b8) * 0x34);
                        }
                        else
                        {
                            bVar1 = false;
                            for (local_38 = 4; local_38 < *(int *)(param_1 + 0x5bc);
                                 local_38 = local_38 + 1)
                            {
                                if (*(int *)(&DAT_006cfe24 + local_38 * 4 + iVar4) == local_2c)
                                {
                                    bVar1 = true;
                                }
                            }
                            if (!bVar1)
                            {
                                *(int *)(&DAT_006cfe24 + *(int *)(param_1 + 0x5bc) * 4 + iVar4) =
                                    local_2c;
                                FUN_0064aed0(2);
                                *(int *)(param_1 + 0x5bc) = *(int *)(param_1 + 0x5bc) + 1;
                            }
                        }
                    }
                }
            }
            else
            {
            LAB_004047e8:
                bVar2 = true;
                if ((*(int *)(param_1 + 0x5d4) == 0) && (*pcVar7 != local_28))
                {
                    *pcVar7 = (char)local_28;
                    FUN_0064aed0(2);
                    *(undefined4 *)(param_1 + 0x5bc) = 4;
                }
            }
        }
        if (bVar2)
        {
            *(int *)(param_1 + 0x5d4) = *(int *)(param_1 + 0x5d4) + 1;
        }
        else
        {
            *(undefined4 *)(param_1 + 0x5d4) = 0;
            if (*(int *)(param_1 + 0x5bc) == 0xc)
            {
                *(undefined4 *)(param_1 + 0x5c0) = 0;
                FUN_0064aed0(0);
                FUN_00657330(&DAT_006cfe20 + *(int *)(param_1 + 0x5b8) * 0x34);
            }
        }
    }
    return 7;
}
