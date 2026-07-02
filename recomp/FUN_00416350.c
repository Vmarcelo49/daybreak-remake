// ============================================
// Address:  0x00416350
// Original: FUN_00416350
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00416350(int param_1, undefined4 param_2, undefined4 param_3)

{
    undefined4 uVar1;
    undefined1 local_1c[8];
    undefined4 local_14;
    int local_10;
    int local_c;
    int local_8;

    local_8 = 0;
    for (local_c = 1; local_c < 8; local_c = local_c + 1)
    {
        if (*(int *)(param_1 + 0x120 + local_c * 4) != 0)
        {
            local_8 = local_8 + 1;
        }
    }
    uVar1 = param_3;
    if (local_8 < DAT_006cfdcc)
    {
        for (local_10 = 1; uVar1 = param_2, local_10 < 8; local_10 = local_10 + 1)
        {
            if ((*(int *)(param_1 + 0x120 + local_10 * 4) == 0) &&
                ((&DAT_006cfdd1)[local_10] != '\0'))
            {
                FUN_00416410();
                local_14 = param_3;
                FUN_00415d30(local_10, local_1c, 10, 2);
            }
        }
    }
    return uVar1;
}
