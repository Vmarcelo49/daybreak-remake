// ============================================
// Address:  0x00410f60
// Original: FUN_00410f60
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00410f60(int param_1)

{
    char cVar1;
    int iVar2;
    int iVar3;
    undefined4 uVar4;
    int local_a0;

    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') && ((cVar1 = FUN_006586d0(0xb8),
                             cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
        FUN_0064ad70();
    }
    cVar1 = FUN_006586d0(0x1e);
    if (cVar1 != '\0')
    {
        FUN_00431d30();
        FUN_00431da0();
    }
    cVar1 = FUN_006586d0(0xcb);
    if (cVar1 == '\0')
    {
        cVar1 = FUN_006586d0(0xcd);
        if (cVar1 == '\0')
        {
            *(undefined4 *)(param_1 + 500) = 0;
        }
        else
        {
            if (*(int *)(param_1 + 500) < 0)
            {
                *(undefined4 *)(param_1 + 500) = 0;
            }
            *(int *)(param_1 + 500) = *(int *)(param_1 + 500) + 1;
        }
    }
    else
    {
        if (0 < *(int *)(param_1 + 500))
        {
            *(undefined4 *)(param_1 + 500) = 0;
        }
        *(int *)(param_1 + 500) = *(int *)(param_1 + 500) + -1;
    }
    cVar1 = FUN_006586d0(200);
    if (cVar1 == '\0')
    {
        cVar1 = FUN_006586d0(0xd0);
        if (cVar1 == '\0')
        {
            *(undefined4 *)(param_1 + 0x1f8) = 0;
        }
        else
        {
            if (*(int *)(param_1 + 0x1f8) < 0)
            {
                *(undefined4 *)(param_1 + 0x1f8) = 0;
            }
            *(int *)(param_1 + 0x1f8) = *(int *)(param_1 + 0x1f8) + 1;
        }
    }
    else
    {
        if (0 < *(int *)(param_1 + 0x1f8))
        {
            *(undefined4 *)(param_1 + 0x1f8) = 0;
        }
        *(int *)(param_1 + 0x1f8) = *(int *)(param_1 + 0x1f8) + -1;
    }
    cVar1 = FUN_006586d0(0x1c);
    if ((((cVar1 == '\0') && (cVar1 = FUN_006586d0(0x39), cVar1 == '\0')) ||
         (cVar1 = FUN_006586d0(0xb8), cVar1 != '\0')) ||
        (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))
    {
        *(undefined4 *)(param_1 + 0x1fc) = 0;
    }
    else
    {
        *(int *)(param_1 + 0x1fc) = *(int *)(param_1 + 0x1fc) + 1;
    }
    cVar1 = FUN_006586d0(1);
    if (cVar1 == '\0')
    {
        *(undefined4 *)(param_1 + 0x200) = 0;
    }
    else
    {
        *(int *)(param_1 + 0x200) = *(int *)(param_1 + 0x200) + 1;
    }
    for (local_a0 = 0; local_a0 < 4; local_a0 = local_a0 + 1)
    {
        FUN_00657390();
        iVar2 = FUN_0066b65c(*(undefined4 *)(param_1 + 500));
        iVar3 = FUN_00403aa0((&DAT_006cae94)[local_a0 * 0x19]);
        if (iVar2 < iVar3)
        {
            *(undefined4 *)(param_1 + 500) = (&DAT_006cae94)[local_a0 * 0x19];
        }
        iVar2 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x1f8));
        iVar3 = FUN_00403aa0((&DAT_006cae98)[local_a0 * 0x19]);
        if (iVar2 < iVar3)
        {
            *(undefined4 *)(param_1 + 0x1f8) = (&DAT_006cae98)[local_a0 * 0x19];
        }
        if ((*(uint *)(param_1 + 0x1fc) < (uint)(&DAT_006cae9c)[local_a0 * 0x19]) ||
            (*(uint *)(param_1 + 0x1fc) < (uint)(&DAT_006caeb8)[local_a0 * 0x19]))
        {
            *(undefined4 *)(param_1 + 0x1fc) = (&DAT_006cae9c)[local_a0 * 0x19];
        }
        if (*(uint *)(param_1 + 0x200) < (uint)(&DAT_006caea0)[local_a0 * 0x19])
        {
            *(undefined4 *)(param_1 + 0x200) = (&DAT_006caea0)[local_a0 * 0x19];
        }
    }
    if (*(int *)(param_1 + 0x1fc) == 1)
    {
        FUN_00405290(1);
        if (*(int *)(param_1 + 0x1f0) < 5)
        {
            FUN_0064aed0(0);
        }
        switch (*(undefined4 *)(param_1 + 0x1f0))
        {
        case 0:
            DAT_006cfbc4 = 0xff;
            DAT_006cfce9 = 1;
            uVar4        = 4;
            break;
        case 1:
            DAT_006cfce9 = 0;
            uVar4        = 3;
            break;
        case 2:
            DAT_006cfce9 = 0;
            uVar4        = 0xb;
            break;
        case 3:
            uVar4 = 6;
            break;
        case 4:
            uVar4 = 7;
            break;
        case 5:
            if (DAT_006cfced != '\0')
            {
                FUN_00403ac0();
            }
            uVar4 = 0x16;
            break;
        default:
            goto switchD_004113dc_default;
        }
    }
    else
    {
    switchD_004113dc_default:
        if (*(int *)(param_1 + 0x1f8) == 1)
        {
            *(int *)(param_1 + 0x1f0) = (*(int *)(param_1 + 0x1f0) + 1) % 6;
            FUN_0064aed0(2);
        }
        else if (*(int *)(param_1 + 0x1f8) == -1)
        {
            *(int *)(param_1 + 0x1f0) = (*(int *)(param_1 + 0x1f0) + 5) % 6;
            FUN_0064aed0(2);
        }
        uVar4 = 1;
    }
    return uVar4;
}
