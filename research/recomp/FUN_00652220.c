// ============================================
// Address:  0x00652220
// Original: FUN_00652220
// Status:   unreviewed
// ============================================

void FUN_00652220(int param_1, int param_2)

{
    undefined4 uVar1;
    int local_7c;
    int local_78;
    int local_70;
    undefined4 local_6c;
    uint local_68;
    undefined1 local_64[68];
    int *local_20;
    int local_1c;
    int *local_18;
    uint local_14;
    uint local_10;
    int local_c;
    uint local_8;

    if (param_1 == 0)
    {
        local_70 = 0;
    }
    else
    {
        local_70 = param_1 + -4;
    }
    local_c = local_70;
    if (*(int *)(local_70 + 0x20) == 0)
    {
        local_1c = 0;
        local_20 = DAT_006d13c4;
        FUN_00423850(local_64, &DAT_006d1510);
        (**(code **)(*local_20 + 0x98))(local_20, "mTransform", local_64);
        if (param_2 == 0)
        {
            local_78 = 0;
        }
        else
        {
            local_78 = param_2 + -0x10;
        }
        (**(code **)(*local_20 + 0x98))(local_20, "mTransformB", local_78 + 0x60);
        (**(code **)(*local_20 + 0x98))(local_20, "mTransformLight", &DAT_006d15d0);
        (**(code **)(*local_20 + 0x88))(local_20, "vLight", &DAT_006d1610);
        (**(code **)(*local_20 + 0xfc))(local_20, &local_10, 0);
        (**(code **)(*local_20 + 0xd0))(local_20, &DAT_006aab70, DAT_006d13f0);
        (**(code **)(*local_20 + 0xd0))(local_20, &DAT_006aab78, DAT_006d13f4);
        for (local_8 = 0; local_8 < local_10; local_8 = local_8 + 1)
        {
            if (local_8 == 0)
            {
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 2);
            }
            else
            {
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 3);
            }
            (**(code **)(*local_20 + 0x100))(local_20, local_8);
            for (local_14 = 0; local_14 < *(uint *)(local_c + 0x18); local_14 = local_14 + 1)
            {
                if (*(float *)(*(int *)(local_c + 0x10) + 0x40 + local_14 * 0x48) == 0.0)
                {
                    (**(code **)(*local_20 + 0x88))(local_20,
                                                    "MaterialColor",
                                                    *(int *)(local_c + 0x10) + 0x30 +
                                                        local_14 * 0x48);
                    if (local_8 == 1)
                    {
                        uVar1 = FUN_00662890(local_14);
                        (**(code **)(*local_20 + 0xd0))(local_20, &DAT_006aab90, uVar1);
                    }
                    else
                    {
                        (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, 0);
                    }
                    (**(code **)(*local_20 + 0x104))(local_20);
                    (**(code **)(**(int **)(local_c + 0xc) + 0xc))(*(undefined4 *)(local_c + 0xc),
                                                                   local_14);
                }
                else
                {
                    local_1c = local_1c + 1;
                }
            }
            (**(code **)(*local_20 + 0x108))(local_20);
        }
        (**(code **)(*local_20 + 0x10c))(local_20);
        if (local_1c != 0)
        {
            if (param_2 == 0)
            {
                local_7c = 0;
            }
            else
            {
                local_7c = param_2 + -0x10;
            }
            (**(code **)(*DAT_006d16f8 + 0xb0))(DAT_006d16f8, 0x100, local_7c + 0x60);
            for (local_68 = 0; local_68 < *(uint *)(local_c + 0x18); local_68 = local_68 + 1)
            {
                if (*(float *)(*(int *)(local_c + 0x10) + 0x40 + local_68 * 0x48) != 0.0)
                {
                    (**(code **)(*DAT_006d16f8 + 0xc4))(DAT_006d16f8,
                                                        local_68 * 0x48 + *(int *)(local_c + 0x10));
                    uVar1 = FUN_00662890(local_68);
                    (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, uVar1);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 1);
                    (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8, 0x1c, &local_6c);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, 0);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 0);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 2);
                    (**(code **)(**(int **)(local_c + 0xc) + 0xc))(*(undefined4 *)(local_c + 0xc),
                                                                   local_68);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 1);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 6);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, local_6c);
                }
            }
        }
    }
    else
    {
        local_18 = *(int **)(&DAT_006d13c0 + DAT_006d13e8 * 4);
        (**(code **)(*local_18 + 0x98))(local_18, "mTransform", &DAT_006d1510);
        (**(code **)(*local_18 + 0x98))(local_18, "mTransformLight", &DAT_006d15d0);
        (**(code **)(*local_18 + 0x88))(local_18, "vLight", &DAT_006d1610);
        (**(code **)(*local_18 + 0xd0))(local_18, &DAT_006aab18, DAT_006d13f0);
        (**(code **)(*local_18 + 0xd0))(local_18, &DAT_006aab20, DAT_006d13f4);
        (**(code **)(*local_18 + 0xfc))(local_18, &local_10, 0);
        for (local_8 = 0; local_8 < local_10; local_8 = local_8 + 1)
        {
            if (local_8 == 0)
            {
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 2);
            }
            else
            {
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 3);
            }
            (**(code **)(*local_18 + 0x100))(local_18, local_8);
            for (local_14 = 0; local_14 < *(uint *)(local_c + 0x38); local_14 = local_14 + 1)
            {
                (**(code **)(*local_18 + 0x88))(
                    local_18,
                    "MaterialColor",
                    *(int *)(local_c + 0x10) + 0x30 +
                        *(int *)(*(int *)(local_c + 0x34) + local_14 * 0x14) * 0x48);
                if (local_8 == 1)
                {
                    uVar1 =
                        FUN_00662890(*(undefined4 *)(*(int *)(local_c + 0x34) + local_14 * 0x14));
                    (**(code **)(*local_18 + 0xd0))(local_18, &DAT_006aab38, uVar1);
                }
                else
                {
                    (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, 0);
                }
                (**(code **)(*local_18 + 0x104))(local_18);
                (**(code **)(**(int **)(local_c + 0xc) + 0xc))(
                    *(undefined4 *)(local_c + 0xc),
                    *(undefined4 *)(*(int *)(local_c + 0x34) + local_14 * 0x14));
            }
            (**(code **)(*local_18 + 0x108))(local_18);
        }
        (**(code **)(*local_18 + 0x10c))(local_18);
    }
    return;
}
