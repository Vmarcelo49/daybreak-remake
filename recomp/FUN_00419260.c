// ============================================
// Address:  0x00419260
// Original: FUN_00419260
// Status:   unreviewed
// ============================================

int __thiscall FUN_00419260(int param_1, undefined1 *param_2)

{
    int local_10;
    int local_c;
    undefined1 *local_8;

    *param_2 = 4;
    local_8  = param_2;
    for (local_c = 0; local_8 = local_8 + 1, local_c < 8; local_c = local_c + 1)
    {
        *local_8 = *(undefined1 *)(param_1 + local_c + 8);
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
    {
        *local_8 = *(undefined1 *)(param_1 + local_10 + 0x10);
        local_8  = local_8 + 1;
    }
    return (int)local_8 - (int)param_2;
}
