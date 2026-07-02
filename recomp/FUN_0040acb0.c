// ============================================
// Address:  0x0040acb0
// Original: FUN_0040acb0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0040acb0(int param_1)

{
    bool bVar1;
    char cVar2;
    int *piVar3;
    int iVar4;
    uint uVar5;
    int local_c;

    bVar1   = false;
    local_c = 0;
    do
    {
        if ((3 < local_c) || (bVar1))
        {
            return;
        }
        if (DAT_006cfdb0 == '\0')
        {
            FUN_00657390();
            bVar1 = true;
        LAB_0040ad61:
            piVar3 = &DAT_006cae94 + local_c * 0x19;
            iVar4  = FUN_00403aa0(*piVar3);
            if (iVar4 == 1)
            {
                FUN_0064aed0(2);
                switch (*(undefined4 *)(param_1 + 0x3c78))
                {
                case 0:
                    *(int *)(param_1 + 0x3d48) = (*(int *)(param_1 + 0x3d48) + 7 + *piVar3) % 7;
                    if ((*(int *)(param_1 + 0x3d48) != 1) && (*(int *)(param_1 + 0x3d4c) == 2))
                    {
                        *(undefined4 *)(param_1 + 0x3d4c) = 1;
                    }
                    break;
                case 1:
                    if (*(int *)(param_1 + 0x3d48) == 1)
                    {
                        *(int *)(param_1 + 0x3d4c) = (*(int *)(param_1 + 0x3d4c) + *piVar3 + 2 +
                                                      (int)*(char *)(param_1 + 0x3d90)) %
                                                     (*(char *)(param_1 + 0x3d90) + 2);
                    }
                    else
                    {
                        uVar5 = *(int *)(param_1 + 0x3d4c) + 2 + *piVar3 & 0x80000001;
                        if ((int)uVar5 < 0)
                        {
                            uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
                        }
                        *(uint *)(param_1 + 0x3d4c) = uVar5;
                    }
                    break;
                case 2:
                    DAT_006cf3c0 = (DAT_006cf3c0 + 300 + *piVar3 * 0x3c) % 300;
                    break;
                case 3:
                    DAT_006cf3b8 = *piVar3 * 0x19 + DAT_006cf3b8;
                    if (DAT_006cf3b8 < 0x32)
                    {
                        DAT_006cf3b8 = 200;
                    }
                    if (200 < DAT_006cf3b8)
                    {
                        DAT_006cf3b8 = 0x32;
                    }
                    break;
                case 4:
                    DAT_006cf3bc = *piVar3 * 0x19 + DAT_006cf3bc;
                    if (DAT_006cf3bc < 0x32)
                    {
                        DAT_006cf3bc = 200;
                    }
                    if (200 < DAT_006cf3bc)
                    {
                        DAT_006cf3bc = 0x32;
                    }
                    break;
                case 5:
                    DAT_006cf3b0 = *piVar3 * 0x14 + DAT_006cf3b0;
                    if (DAT_006cf3b0 < 0x28)
                    {
                        DAT_006cf3b0 = 200;
                    }
                    if (200 < DAT_006cf3b0)
                    {
                        DAT_006cf3b0 = 0x28;
                    }
                    break;
                case 6:
                    DAT_006cf3b4 = *piVar3 * 0x14 + DAT_006cf3b4;
                    if (DAT_006cf3b4 < 0x28)
                    {
                        DAT_006cf3b4 = 200;
                    }
                    if (200 < DAT_006cf3b4)
                    {
                        DAT_006cf3b4 = 0x28;
                    }
                    break;
                case 7:
                    *(int *)(param_1 + 0x3c7c) = 1 - *(int *)(param_1 + 0x3c7c);
                }
            }
            else
            {
                iVar4 = FUN_00403aa0((&DAT_006cae98)[local_c * 0x19]);
                if (iVar4 == 1)
                {
                    FUN_0064aed0(2);
                    uVar5 = *(int *)(param_1 + 0x3c78) + 8 + (&DAT_006cae98)[local_c * 0x19] &
                            0x80000007;
                    if ((int)uVar5 < 0)
                    {
                        uVar5 = (uVar5 - 1 | 0xfffffff8) + 1;
                    }
                    *(uint *)(param_1 + 0x3c78) = uVar5;
                    if ((*(int *)(param_1 + 0x3c78) == 1) && (*(int *)(param_1 + 0x3d48) == 0))
                    {
                        if ((int)(&DAT_006cae98)[local_c * 0x19] < 1)
                        {
                            *(undefined4 *)(param_1 + 0x3c78) = 0;
                        }
                        else
                        {
                            *(undefined4 *)(param_1 + 0x3c78) = 2;
                        }
                    }
                }
                else if (((&DAT_006cae9c)[local_c * 0x19] == 1) &&
                         (*(int *)(param_1 + 0x3c78) == 7))
                {
                    if (*(int *)(param_1 + 0x3c7c) == 0)
                    {
                        FUN_0064aed0(0);
                        *(undefined1 *)(param_1 + 0x3c44) = 1;
                    }
                    else
                    {
                        FUN_0064aed0(1);
                        *(undefined1 *)(param_1 + 0x3c40) = 0;
                        *(undefined4 *)(param_1 + 0x3c7c) = 0;
                        *(undefined4 *)(param_1 + 0x3c9c) = 0;
                        *(undefined4 *)(param_1 + 0x3c98) = 0;
                        *(undefined4 *)(param_1 + 0x3c94) = 0;
                        *(undefined4 *)(param_1 + 0x3c90) = 0;
                    }
                }
                else if (((&DAT_006caea0)[local_c * 0x19] == 1) ||
                         (cVar2 = FUN_006586d0(1), cVar2 != '\0'))
                {
                    FUN_0064aed0(1);
                    *(undefined1 *)(param_1 + 0x3c40) = 0;
                    *(undefined4 *)(param_1 + 0x3c7c) = 0;
                    *(undefined4 *)(param_1 + 0x3c9c) = 0;
                    *(undefined4 *)(param_1 + 0x3c98) = 0;
                    *(undefined4 *)(param_1 + 0x3c94) = 0;
                    *(undefined4 *)(param_1 + 0x3c90) = 0;
                }
                else if ((&DAT_006caeb8)[local_c * 0x19] == 1)
                {
                    FUN_0064aed0(0);
                    *(undefined1 *)(param_1 + 0x3c44) = 1;
                }
            }
        }
        else
        {
            if ((&DAT_006cfb18)[local_c] != 0)
            {
                if (0 < (int)(&DAT_006cfb18)[local_c])
                {
                    FUN_00657390();
                    bVar1 = true;
                }
                goto LAB_0040ad61;
            }
            cVar2 = FUN_00645e10();
            if (cVar2 == '\0')
            {
                FUN_00657390();
                bVar1 = true;
                goto LAB_0040ad61;
            }
        }
        local_c = local_c + 1;
    } while (true);
}
