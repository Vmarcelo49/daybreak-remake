// ============================================
// Address:  0x00650280
// Original: FUN_00650280
// Status:   unreviewed
// ============================================

void __fastcall FUN_00650280(int param_1)

{
    undefined4 local_8;

    if (DAT_006d171c == 0)
    {
        FUN_00650ef0();
    }
    for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1)
    {
        if (*(int *)(param_1 + local_8 * 4) != 0)
        {
            (**(code **)(**(int **)(param_1 + local_8 * 4) + 8))(
                *(undefined4 *)(param_1 + local_8 * 4));
            *(undefined4 *)(param_1 + local_8 * 4) = 0;
        }
    }
    if (*(int *)(param_1 + 0x284) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x284) + 8))(*(undefined4 *)(param_1 + 0x284));
        *(undefined4 *)(param_1 + 0x284) = 0;
    }
    if (*(int *)(param_1 + 0x288) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x288) + 8))(*(undefined4 *)(param_1 + 0x288));
        *(undefined4 *)(param_1 + 0x288) = 0;
    }
    if (*(int *)(param_1 + 0x27c) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x27c) + 8))(*(undefined4 *)(param_1 + 0x27c));
        *(undefined4 *)(param_1 + 0x27c) = 0;
    }
    if (*(int *)(param_1 + 0x280) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x280) + 8))(*(undefined4 *)(param_1 + 0x280));
        *(undefined4 *)(param_1 + 0x280) = 0;
    }
    for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1)
    {
        if (*(int *)(param_1 + 0x30 + local_8 * 4) != 0)
        {
            (**(code **)(**(int **)(param_1 + 0x30 + local_8 * 4) + 8))(
                *(undefined4 *)(param_1 + 0x30 + local_8 * 4));
            *(undefined4 *)(param_1 + 0x30 + local_8 * 4) = 0;
        }
    }
    return;
}
