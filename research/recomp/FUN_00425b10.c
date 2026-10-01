// ============================================
// Address:  0x00425b10
// Original: FUN_00425b10
// Status:   unreviewed
// ============================================

void __thiscall FUN_00425b10(int param_1, uint param_2)

{
    uint uVar1;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    int local_14;
    int local_10;
    uint local_c;
    uint local_8;

    uVar1 = FUN_00426bb0();
    if ((uVar1 >> 4) - *(int *)(param_1 + 8) < param_2)
    {
        FUN_00426050();
    }
    local_c = *(uint *)(param_1 + 8) >> 1;
    if (local_c < 8)
    {
        local_c = 8;
    }
    if (param_2 < local_c)
    {
        uVar1 = FUN_00426bb0();
        if (*(uint *)(param_1 + 8) <= (uVar1 >> 4) - local_c)
        {
            param_2 = local_c;
        }
    }
    local_8  = *(uint *)(param_1 + 0xc) >> 4;
    local_14 = FUN_004107e0(*(int *)(param_1 + 8) + param_2);
    local_10 = local_14 + local_8 * 4;
    local_10 = FUN_0065ae90(*(int *)(param_1 + 4) + local_8 * 4,
                            *(int *)(param_1 + 4) + *(int *)(param_1 + 8) * 4,
                            local_10,
                            param_1);
    if (param_2 < local_8)
    {
        FUN_0065ae90(
            *(undefined4 *)(param_1 + 4), *(int *)(param_1 + 4) + param_2 * 4, local_10, param_1);
        local_10 = FUN_0065ae90(*(int *)(param_1 + 4) + param_2 * 4,
                                *(int *)(param_1 + 4) + local_8 * 4,
                                local_14,
                                param_1);
        local_20 = 0;
        FUN_00433060(local_10, param_2, &local_20, param_1);
    }
    else
    {
        local_10 = FUN_0065ae90(
            *(undefined4 *)(param_1 + 4), *(int *)(param_1 + 4) + local_8 * 4, local_10, param_1);
        local_18 = 0;
        FUN_00433060(local_10, param_2 - local_8, &local_18, param_1);
        local_1c = 0;
        FUN_00433060(local_14, local_8, &local_1c, param_1);
    }
    FUN_00659670(*(int *)(param_1 + 4) + local_8 * 4,
                 *(int *)(param_1 + 4) + *(int *)(param_1 + 8) * 4,
                 param_1);
    if (*(int *)(param_1 + 4) != 0)
    {
        deallocate(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
    }
    *(int *)(param_1 + 4)  = local_14;
    *(uint *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2;
    return;
}
