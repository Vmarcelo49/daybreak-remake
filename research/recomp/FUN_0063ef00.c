// ============================================
// Address:  0x0063ef00
// Original: FUN_0063ef00
// Status:   unreviewed
// ============================================

void __thiscall FUN_0063ef00(int param_1, int param_2)

{
    int local_c;
    short *local_8;

    local_8 = (short *)(param_2 + 1);
    for (local_c = 0; local_c < 4; local_c = local_c + 1)
    {
        *(int *)(param_1 + 8 + local_c * 4) = (int)*local_8;
        local_8                             = local_8 + 1;
    }
    *(short *)(param_1 + 0x18) = *local_8;
    return;
}
