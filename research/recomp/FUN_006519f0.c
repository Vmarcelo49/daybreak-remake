// ============================================
// Address:  0x006519f0
// Original: FUN_006519f0
// Status:   unreviewed
// ============================================

void FUN_006519f0(int param_1, int param_2)

{
    undefined4 uVar1;
    int local_60;
    int local_5c;
    undefined4 local_58;
    uint local_54;
    uint local_50;
    allocator<char> local_4c[68];
    int local_8;

    if (param_1 == 0)
    {
        local_5c = 0;
    }
    else
    {
        local_5c = param_1 + -4;
    }
    local_8 = local_5c;
    if (*(int *)(local_5c + 0x20) == 0)
    {
        if (param_2 == 0)
        {
            local_60 = 0;
        }
        else
        {
            local_60 = param_2 + -0x10;
        }
        (**(code **)(*DAT_006d16f8 + 0xb0))(DAT_006d16f8, 0x100, local_60 + 0x60);
        for (local_54 = 0; local_54 < *(uint *)(local_8 + 0x18); local_54 = local_54 + 1)
        {
            (**(code **)(*DAT_006d16f8 + 0xc4))(DAT_006d16f8,
                                                local_54 * 0x48 + *(int *)(local_8 + 0x10));
            uVar1 = FUN_00662890(local_54);
            (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, uVar1);
            if (*(float *)(*(int *)(local_8 + 0x10) + 0x40 + local_54 * 0x48) == 0.0)
            {
                (**(code **)(**(int **)(local_8 + 0xc) + 0xc))(*(undefined4 *)(local_8 + 0xc),
                                                               local_54);
            }
            else
            {
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 1);
                (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8, 0x1c, &local_58);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, 0);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 0);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 2);
                (**(code **)(**(int **)(local_8 + 0xc) + 0xc))(*(undefined4 *)(local_8 + 0xc),
                                                               local_54);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 1);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 6);
                (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, local_58);
            }
        }
    }
    else
    {
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 3);
        std::allocator<char>::allocator<char>(local_4c);
        FUN_00423890(local_4c);
        (**(code **)(*DAT_006d16f8 + 0xb0))(DAT_006d16f8, 0x100, local_4c);
        for (local_50 = 0; local_50 < *(uint *)(local_8 + 0x38); local_50 = local_50 + 1)
        {
            (**(code **)(*DAT_006d16f8 + 0xc4))(
                DAT_006d16f8,
                *(int *)(*(int *)(local_8 + 0x34) + local_50 * 0x14) * 0x48 +
                    *(int *)(local_8 + 0x10));
            uVar1 = FUN_00662890(*(undefined4 *)(*(int *)(local_8 + 0x34) + local_50 * 0x14));
            (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, uVar1);
            (**(code **)(**(int **)(local_8 + 0xc) + 0xc))(
                *(undefined4 *)(local_8 + 0xc),
                *(undefined4 *)(*(int *)(local_8 + 0x34) + local_50 * 0x14));
        }
    }
    return;
}
