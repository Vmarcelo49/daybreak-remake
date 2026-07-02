// ============================================
// Address:  0x00643230
// Original: FUN_00643230
// Status:   unreviewed
// ============================================

void __thiscall FUN_00643230(int *param_1, float param_2, float param_3, float param_4)

{
    int iVar1;
    int *piVar2;
    undefined4 uVar3;
    float *pfVar4;
    uint uVar5;
    undefined1 *puVar6;
    undefined4 uVar7;
    char local_19c;
    undefined1 local_194[80];
    undefined1 local_144[80];
    undefined1 local_f4[80];
    undefined1 local_a4[80];
    int local_54;
    uint local_50;
    int local_4c;
    uint local_48;
    int local_44;
    float local_40;
    int local_3c;
    int local_38;
    char local_31;
    undefined4 local_30;
    char local_2a;
    char local_29;
    int local_28;
    char local_24[4];
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    float local_10;
    float local_c;
    char local_5;

    std::allocator<char>::allocator<char>((allocator<char> *)&local_18);
    if (*(char *)(param_1[0x2dc] + 0x2dc) == '\0')
    {
        uVar3 = std::allocator<char>::allocator<char>(
            (allocator<char> *)(*(int *)(param_1[0x2dc] + 0x308) + 0x20));
        pfVar4   = (float *)FUN_00430630(uVar3);
        local_18 = *pfVar4;
        local_10 = pfVar4[2];
        local_c  = 1.0;
        local_14 = pfVar4[1] + 70.0;
        uVar3    = FUN_00661a00();
        puVar6   = local_a4;
        FUN_006619f0(puVar6, uVar3);
        uVar3 = FUN_00423850(puVar6, uVar3);
        D3DXVec4Transform(&local_18, &local_18, uVar3);
        local_20 = ((local_18 / local_c) * 400.0 + 400.0) * param_4 + param_2;
        local_1c = ((-local_14 / local_c) * 300.0 + 300.0) * param_4 + param_3;
        local_29 = 0 < *(int *)(*(int *)(param_1[0x2dc] + 0x308) + 0x7ac);
        local_2a = -1 < *(int *)(param_1[0x2dc] + 0x304);
        iVar1    = param_1[0x2dc];
        piVar2   = (int *)FUN_00658a10(0);
        if ((*(int *)(iVar1 + 0x300) == *(int *)(*piVar2 + 0x300)) && (local_2a == '\0'))
        {
            local_19c = '\x01';
        }
        else
        {
            local_19c = '\0';
        }
        local_31 = local_19c;
        FUN_00408250(((float)*(int *)(param_1[0x2dc] + 0x30c) * 0.1 + 1.0) * param_4);
        FUN_006451f0((float)*param_1 / 2.0 + (float)*(int *)(param_1[0x2dc] + 0x30c) * 9.0);
        if (local_29 == '\0')
        {
            if (local_2a == '\0')
            {
                if ((*(char *)(param_1[0x2dc] + 0x318) == '\x01') &&
                    (*(char *)(param_1[0x2dc] + 0x845) != '\0'))
                {
                    local_30 = 2;
                    if (*(int *)(param_1[0x2dc] + 0x848) == 0)
                    {
                        local_28 = 0;
                    }
                    else
                    {
                        local_28 = (*param_1 % 0x1e) / 0xf;
                    }
                }
                else
                {
                    local_30 = 0;
                    local_28 = 1;
                }
            }
            else
            {
                local_30 = 0;
                local_28 = 2;
            }
        }
        else
        {
            local_30 = 0;
            local_28 = 0;
        }
        FUN_00655830(local_20, local_1c, local_30, local_28);
        if (local_31 != '\0')
        {
            FUN_006451f0(-(float)*param_1);
            FUN_00408250(((float)*(int *)(param_1[0x2dc] + 0x30c) * 0.1 + 1.0) * param_4);
            FUN_00655830(local_20, local_1c, local_30, local_28);
        }
    }
    else
    {
        FUN_00650c30(3);
        FUN_0040da60((param_4 * 800.0) / 512.0, (param_4 * 600.0) / 512.0);
        FUN_00655d60(param_2, param_3);
        FUN_00650c30(0);
    }
    local_24[0] = '\0';
    local_24[1] = 0;
    local_24[2] = 0;
    local_24[3] = 0;
    local_38    = 0;
    while (iVar1 = FUN_004258e0(), local_38 < iVar1)
    {
        piVar2 = (int *)FUN_00424800(local_38);
        if (*piVar2 != 0)
        {
            piVar2 = (int *)FUN_00424800(local_38);
            if (*piVar2 == 1)
            {
                local_3c = 0;
            }
            else
            {
                iVar1    = FUN_00424800(local_38);
                local_3c = (*(int *)(iVar1 + 8) % 10 < 5) + 1;
            }
            iVar1    = FUN_00424800(local_38);
            local_40 = (float)*(int *)(iVar1 + 8) * 0.005 + 1.0;
            iVar1    = FUN_00424800(local_38);
            if (local_24[*(int *)(iVar1 + 4)] == '\0')
            {
                FUN_00408250(param_4 * local_40);
                iVar1 = FUN_00424800(local_38);
                switch (*(undefined4 *)(iVar1 + 4))
                {
                case 0:
                    FUN_00655d60(param_4 * 400.0 + param_2, param_4 * 64.0 + param_3);
                    break;
                case 1:
                    FUN_00655d60(param_4 * 400.0 + param_2, param_4 * 536.0 + param_3);
                    break;
                case 2:
                    FUN_00655d60(param_4 * 64.0 + param_2, param_4 * 300.0 + param_3);
                    break;
                case 3:
                    FUN_00655d60(param_4 * 736.0 + param_2, param_4 * 300.0 + param_3);
                }
            }
            piVar2 = (int *)FUN_00424800(local_38);
            if (*piVar2 == 2)
            {
                iVar1                         = FUN_00424800(local_38);
                local_24[*(int *)(iVar1 + 4)] = '\x01';
            }
        }
        local_38 = local_38 + 1;
    }
    FUN_00408250(param_4);
    local_5 = '\0';
    if (DAT_006cfdb0 == '\0')
    {
        if ((*DAT_006cfa24 != 0) && (*(char *)(*DAT_006cfa24 + 1) != '\0'))
        {
            local_5 = '\x01';
        }
    }
    else if ((DAT_006cfa24[DAT_006cfdb4] != 0) &&
             (*(char *)(DAT_006cfa24[DAT_006cfdb4] + 1) != '\0'))
    {
        local_5 = '\x01';
    }
    if (local_5 != '\0')
    {
        uVar3  = std::allocator<char>::allocator<char>((allocator<char> *)(param_1[0x2dc] + 0x20));
        pfVar4 = (float *)FUN_00430630(uVar3);
        local_18 = *pfVar4;
        local_10 = pfVar4[2];
        local_c  = 1.0;
        local_14 = pfVar4[1] + 150.0;
        uVar3    = FUN_00661a00();
        puVar6   = local_f4;
        FUN_006619f0(puVar6, uVar3);
        uVar3 = FUN_00423850(puVar6, uVar3);
        D3DXVec4Transform(&local_18, &local_18, uVar3);
        if (0.0 < local_10)
        {
            local_44 = (&DAT_006cfaf8)[*(int *)(param_1[0x2dc] + 8)];
            local_20 = ((local_18 / local_c) * 400.0 + 400.0) * param_4 + param_2;
            local_1c =
                (((-local_14 / local_c) * 300.0 + 300.0) * param_4 + param_3) - param_4 * 32.0;
            if ((local_1c - param_4 * 32.0 < param_3) && (local_10 < 1000.0))
            {
                local_1c = param_4 * 32.0 + param_3;
            }
            FUN_00408250(param_4);
            FUN_00655d60(local_20, local_1c);
            FUN_00645210(param_1[0x2dc] + 0x7a8, 10000, 0);
            FUN_00645690(local_20, local_1c, param_4);
            FUN_00645210(param_1[0x2dc] + 0x7a4, 10000, 0);
            FUN_00645690(local_20, local_1c, param_4);
            FUN_00655830(param_4 * 24.0 + local_20,
                         param_4 * 16.0 + local_1c,
                         local_44 % 3,
                         local_44 / 3 + **(int **)(param_1[0x2dc] + 0xc) * 4);
            if ((local_44 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[local_44]] != '\0'))
            {
                FUN_00646cf0((&DAT_006cfb18)[local_44],
                             param_4 * -50.0 + local_20,
                             param_4 * -26.0 + local_1c);
            }
        }
    }
    local_48 = 0;
    while (uVar5 = FUN_0064f010(), local_48 < uVar5)
    {
        piVar2   = (int *)FUN_00658a10(local_48);
        uVar3    = std::allocator<char>::allocator<char>((allocator<char> *)(*piVar2 + 0x20));
        pfVar4   = (float *)FUN_00430630(uVar3);
        local_18 = *pfVar4;
        local_10 = pfVar4[2];
        local_c  = 1.0;
        local_14 = pfVar4[1] + 150.0;
        uVar3    = FUN_00661a00();
        puVar6   = local_144;
        FUN_006619f0(puVar6, uVar3);
        uVar3 = FUN_00423850(puVar6, uVar3);
        D3DXVec4Transform(&local_18, &local_18, uVar3);
        if (0.0 < local_10)
        {
            piVar2   = (int *)FUN_00658a10(local_48);
            local_4c = (&DAT_006cfaf8)[*(int *)(*piVar2 + 8)];
            local_20 = ((local_18 / local_c) * 400.0 + 400.0) * param_4 + param_2;
            local_1c =
                (((-local_14 / local_c) * 300.0 + 300.0) * param_4 + param_3) - param_4 * 32.0;
            if ((local_1c - param_4 * 32.0 < param_3) && (local_10 < 1000.0))
            {
                local_1c = param_4 * 32.0 + param_3;
            }
            FUN_00408250(param_4);
            FUN_00655d60(local_20, local_1c);
            uVar7  = 0;
            uVar3  = 10000;
            piVar2 = (int *)FUN_00658a10(local_48);
            FUN_00645210(*piVar2 + 0x7a8, uVar3, uVar7);
            FUN_00645690(local_20, local_1c, param_4);
            uVar7  = 0;
            uVar3  = 10000;
            piVar2 = (int *)FUN_00658a10(local_48);
            FUN_00645210(*piVar2 + 0x7a4, uVar3, uVar7);
            FUN_00645690(local_20, local_1c, param_4);
            piVar2 = (int *)FUN_00658a10(local_48);
            FUN_00655830(param_4 * 24.0 + local_20,
                         param_4 * 16.0 + local_1c,
                         local_4c % 3,
                         local_4c / 3 + **(int **)(*piVar2 + 0xc) * 4);
            if ((local_4c < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[local_4c]] != '\0'))
            {
                FUN_00646cf0((&DAT_006cfb18)[local_4c],
                             param_4 * -50.0 + local_20,
                             param_4 * -26.0 + local_1c);
            }
        }
        local_48 = local_48 + 1;
    }
    local_50 = 0;
    while (uVar5 = FUN_0064f010(), local_50 < uVar5)
    {
        piVar2   = (int *)FUN_00658a10(local_50);
        uVar3    = std::allocator<char>::allocator<char>((allocator<char> *)(*piVar2 + 0x20));
        pfVar4   = (float *)FUN_00430630(uVar3);
        local_18 = *pfVar4;
        local_10 = pfVar4[2];
        local_c  = 1.0;
        local_14 = pfVar4[1] + 150.0;
        uVar3    = FUN_00661a00();
        puVar6   = local_194;
        FUN_006619f0(puVar6, uVar3);
        uVar3 = FUN_00423850(puVar6, uVar3);
        D3DXVec4Transform(&local_18, &local_18, uVar3);
        if (0.0 < local_10)
        {
            piVar2   = (int *)FUN_00658a10(local_50);
            local_54 = (&DAT_006cfaf8)[*(int *)(*piVar2 + 8)];
            local_20 = ((local_18 / local_c) * 400.0 + 400.0) * param_4 + param_2;
            local_1c =
                (((-local_14 / local_c) * 300.0 + 300.0) * param_4 + param_3) - param_4 * 32.0;
            if ((local_1c - param_4 * 32.0 < param_3) && (local_10 < 1000.0))
            {
                local_1c = param_4 * 32.0 + param_3;
            }
            FUN_00408250(param_4);
            FUN_00655d60(local_20, local_1c);
            uVar7  = 0;
            uVar3  = 10000;
            piVar2 = (int *)FUN_00658a10(local_50);
            FUN_00645210(*piVar2 + 0x7a8, uVar3, uVar7);
            FUN_00645690(local_20, local_1c, param_4);
            uVar7  = 0;
            uVar3  = 10000;
            piVar2 = (int *)FUN_00658a10(local_50);
            FUN_00645210(*piVar2 + 0x7a4, uVar3, uVar7);
            FUN_00645690(local_20, local_1c, param_4);
            piVar2 = (int *)FUN_00658a10(local_50);
            FUN_00655830(param_4 * 24.0 + local_20,
                         param_4 * 16.0 + local_1c,
                         local_54 % 3,
                         local_54 / 3 + **(int **)(*piVar2 + 0xc) * 4);
            if ((local_54 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[local_54]] != '\0'))
            {
                FUN_00646cf0((&DAT_006cfb18)[local_54],
                             param_4 * -50.0 + local_20,
                             param_4 * -26.0 + local_1c);
            }
        }
        local_50 = local_50 + 1;
    }
    return;
}
