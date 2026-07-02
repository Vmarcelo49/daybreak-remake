// ============================================
// Address:  0x004010c0
// Original: FUN_004010c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004010c0(int param_1)

{
    int local_8;

    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        if (*(int *)(param_1 + local_8 * 4) != 0)
        {
            if (*(int *)(param_1 + local_8 * 4) != 0)
            {
                FUN_00402010(1);
            }
            *(undefined4 *)(param_1 + local_8 * 4) = 0;
        }
    }
    if (*(int *)(param_1 + 0x20) != 0)
    {
        if (*(int *)(param_1 + 0x20) != 0)
        {
            FUN_00402010(1);
        }
        *(undefined4 *)(param_1 + 0x20) = 0;
    }
    if (*(int *)(param_1 + 0x24) != 0)
    {
        if (*(int *)(param_1 + 0x24) != 0)
        {
            FUN_00402010(1);
        }
        *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (*(int *)(param_1 + 0x28) != 0)
    {
        if (*(int *)(param_1 + 0x28) != 0)
        {
            FUN_00402010(1);
        }
        *(undefined4 *)(param_1 + 0x28) = 0;
    }
    return;
}
