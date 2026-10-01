// ============================================
// Address:  0x00690ed0
// Original: FUN_00690ed0
// Status:   unreviewed
// ============================================

uint __thiscall FUN_00690ed0(int *param_1, int *param_2, uint *param_3, uint *param_4)

{
    uint uVar1;
    uint uVar2;
    int iVar3;
    int iVar4;
    bool bVar5;
    undefined8 uVar6;
    int local_60;
    int local_5c;
    uint local_50;
    int local_48;
    uint local_40;
    uint local_3c;
    uint local_1c;
    int local_18;
    int local_10;
    int local_c;
    uint local_8;

    if ((-1 < (int)param_3[1]) && ((0 < (int)param_3[1] || (79999 < *param_3))))
    {
        uVar1      = *param_3;
        *param_3   = uVar1 - 80000;
        param_3[1] = param_3[1] - (uint)(uVar1 < 80000);
        uVar1      = *param_4;
        *param_4   = uVar1 - 80000;
        param_4[1] = param_4[1] - (uint)(uVar1 < 80000);
    }
    param_1[0x46] = *param_3;
    param_1[0x47] = param_3[1];
    (**(code **)(*(int *)param_1[6] + 0xc))(param_1[6], &local_1c);
    uVar6    = FUN_00697fc0();
    bVar5    = local_1c < (uint)uVar6;
    local_1c = local_1c - (uint)uVar6;
    local_18 = (local_18 - (int)((ulonglong)uVar6 >> 0x20)) - (uint)bVar5;
    local_48 =
        FUN_00691b10(local_1c - *param_3, (local_18 - param_3[1]) - (uint)(local_1c < *param_3));
    local_10      = local_48;
    iVar3         = (**(code **)(*param_1 + 0xc0))(local_48, local_48 >> 0x1f, local_1c, local_18);
    param_1[0x3b] = (uint)(iVar3 == 0);
    iVar4         = *param_4 - *param_3;
    iVar3         = (int)(param_1[0x44] + (param_1[0x44] >> 0x1f & 0x1fU)) >> 5;
    if ((param_1[0x44] + iVar3 < iVar4) || (iVar4 < param_1[0x44] - iVar3))
    {
        param_1[0x43] = iVar4;
        param_1[0x44] = iVar4;
    }
    if (((param_1[0x3b] == 0) || (iVar3 = (**(code **)(*param_2 + 0x3c))(param_2), iVar3 != 0)) &&
        (param_1[0x3a] != -1))
    {
        local_5c = 0;
    }
    else
    {
        local_5c = 1;
    }
    local_c = local_5c;
    if (local_10 < 1)
    {
        if ((local_10 < param_1[0x40]) && (local_5c == 0))
        {
            param_1[0x40] =
                param_1[0x40] - ((int)(param_1[0x40] + (param_1[0x40] >> 0x1f & 7U)) >> 3);
        }
        else
        {
            param_1[0x40] = local_10;
        }
    }
    else
    {
        param_1[0x40] = 0;
    }
    if (local_10 < 0)
    {
        local_60 = -local_10;
    }
    else
    {
        local_60 = 0;
    }
    local_60 = param_1[0x42] * 3 + local_60;
    iVar3    = (int)(local_60 + (local_60 >> 0x1f & 3U)) >> 2;
    local_3c = local_1c - param_1[0x4e];
    uVar1    = (uint)(local_1c < (uint)param_1[0x4e]);
    uVar2    = local_18 - param_1[0x4f];
    if ((-1 < (int)(uVar2 - uVar1)) &&
        ((uVar2 != uVar1 && SBORROW4(local_18, param_1[0x4f]) == SBORROW4(uVar2, uVar1) ||
          (10000000 < local_3c))))
    {
        local_3c = 10000000;
    }
    local_8 = local_3c;
    if (param_1[0x3d] * 3 - param_1[0x43] != 0 && param_1[0x43] <= param_1[0x3d] * 3)
    {
        if (param_1[0x3b] == 0)
        {
            bVar5 = local_10 * 2 < iVar4;
        }
        else
        {
            bVar5 = local_10 <= iVar4 * 4;
        }
        if ((!bVar5) && (param_1[0x42] < 0x13881))
        {
            uVar1 = (uint)(local_1c < (uint)param_1[0x4e]);
            uVar2 = local_18 - param_1[0x4f];
            if (((int)(uVar2 - uVar1) < 0) ||
                ((uVar2 == uVar1 || SBORROW4(local_18, param_1[0x4f]) != SBORROW4(uVar2, uVar1) &&
                                        (local_1c - param_1[0x4e] < 0x989681))))
            {
                param_1[0x42] = iVar3;
                param_1[0x3a] = -1;
                return 0x80004005;
            }
        }
    }
    bVar5 = false;
    if (local_5c == 0)
    {
        if ((((int)(iVar4 + (iVar4 >> 0x1f & 0xfU)) >> 4) + iVar4 < param_1[0x43]) &&
            (iVar4 * -10 < local_10))
        {
            bVar5 = true;
        }
    }
    else
    {
        bVar5 = true;
    }
    if (local_10 < -9000000)
    {
        bVar5 = false;
    }
    if (bVar5)
    {
        param_1[0x3a] = 0;
        param_1[0x42] = (int)(param_1[0x42] * 3 + (param_1[0x42] * 3 >> 0x1f & 3U)) >> 2;
        iVar3         = param_1[0x43] * 3 + local_3c;
        param_1[0x43] = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
        FUN_00690950(local_48, local_3c);
        param_1[0x4e] = local_1c;
        param_1[0x4f] = local_18;
        if (local_10 < param_1[0x40])
        {
            param_1[0x40] = local_10;
        }
        local_40 = 0;
    }
    else
    {
        param_1[0x3a] = param_1[0x3a] + 1;
        param_1[0x43] = iVar4;
        local_50      = param_1[0x40];
        if ((int)local_50 < -param_1[0x43])
        {
            local_50 = -param_1[0x43];
        }
        uVar1         = *param_3;
        *param_3      = local_50 + *param_3;
        param_3[1]    = param_3[1] + ((int)local_50 >> 0x1f) + (uint)CARRY4(local_50, uVar1);
        local_40      = (uint)(0 < -local_48);
        param_1[0x42] = iVar3;
        if (local_40 == 1)
        {
            local_8 =
                FUN_00691b10(*param_3 - param_1[0x4e],
                             (param_3[1] - param_1[0x4f]) - (uint)(*param_3 < (uint)param_1[0x4e]));
            param_1[0x4e] = *param_3;
            param_1[0x4f] = param_3[1];
        }
        else
        {
            param_1[0x4e] = local_1c;
            param_1[0x4f] = local_18;
        }
        if (0 < -local_48)
        {
            local_48 =
                FUN_00691b10(*param_3 - param_1[0x46],
                             (param_3[1] - param_1[0x47]) - (uint)(*param_3 < (uint)param_1[0x46]));
        }
        FUN_00690950(local_48, local_8);
    }
    return local_40;
}
