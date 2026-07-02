// ============================================
// Address:  0x00652880
// Original: FUN_00652880
// Status:   unreviewed
// ============================================

void FUN_00652880(int param_1)

{
    int local_60;
    undefined1 local_5c[68];
    uint local_18;
    uint local_14;
    int *local_10;
    int local_c;
    uint local_8;

    if (param_1 == 0)
    {
        local_60 = 0;
    }
    else
    {
        local_60 = param_1 + -4;
    }
    local_c = local_60;
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 3);
    local_10 = DAT_006d13c8;
    if (*(int *)(local_c + 0x20) == 0)
    {
        FUN_00423850(local_5c, &DAT_006d15d0);
        (**(code **)(*local_10 + 0x98))(local_10, "mTransform", local_5c);
        (**(code **)(*local_10 + 0xfc))(local_10, &local_14, 0);
        for (local_8 = 0; local_8 < local_14; local_8 = local_8 + 1)
        {
            (**(code **)(*local_10 + 0x100))(local_10, local_8);
            for (local_18 = 0; local_18 < *(uint *)(local_c + 0x18); local_18 = local_18 + 1)
            {
                (**(code **)(*local_10 + 0x104))(local_10);
                if (*(float *)(*(int *)(local_c + 0x10) + 0x40 + local_18 * 0x48) == 0.0)
                {
                    (**(code **)(**(int **)(local_c + 0xc) + 0xc))(*(undefined4 *)(local_c + 0xc),
                                                                   local_18);
                }
            }
            (**(code **)(*local_10 + 0x108))(local_10);
        }
        (**(code **)(*local_10 + 0x10c))(local_10);
    }
    else
    {
        (**(code **)(*DAT_006d13c8 + 0x98))(DAT_006d13c8, "mTransform", &DAT_006d15d0);
        (**(code **)(*local_10 + 0xfc))(local_10, &local_14, 0);
        for (local_8 = 0; local_8 < local_14; local_8 = local_8 + 1)
        {
            (**(code **)(*local_10 + 0x100))(local_10, local_8);
            for (local_18 = 0; local_18 < *(uint *)(local_c + 0x38); local_18 = local_18 + 1)
            {
                (**(code **)(*local_10 + 0x104))(local_10);
                if (*(float *)(*(int *)(local_c + 0x10) + 0x40 +
                               *(int *)(*(int *)(local_c + 0x34) + local_18 * 0x14) * 0x48) == 0.0)
                {
                    (**(code **)(**(int **)(local_c + 0xc) + 0xc))(
                        *(undefined4 *)(local_c + 0xc),
                        *(undefined4 *)(*(int *)(local_c + 0x34) + local_18 * 0x14));
                }
            }
            (**(code **)(*local_10 + 0x108))(local_10);
        }
        (**(code **)(*local_10 + 0x10c))(local_10);
    }
    return;
}
