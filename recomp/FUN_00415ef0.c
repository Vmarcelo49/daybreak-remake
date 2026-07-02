// ============================================
// Address:  0x00415ef0
// Original: FUN_00415ef0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00415ef0(int param_1, undefined1 *param_2)

{
    int local_1c;
    int local_18;
    int local_14;
    int local_10;
    int local_c;
    int local_8;

    *param_2 = 0x10;
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        param_2[local_8 + 1] = *(undefined1 *)(param_1 + local_8 + 8);
    }
    for (local_c = 0; local_c < 8; local_c = local_c + 1)
    {
        for (local_10 = 0; local_10 < 9; local_10 = local_10 + 1)
        {
            param_2[local_c * 9 + local_10 + 9] =
                *(undefined1 *)(param_1 + 0x10 + local_c * 9 + local_10);
        }
    }
    for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1)
    {
        param_2[local_14 + 0x51] = *(undefined1 *)(param_1 + local_14 + 0x58);
    }
    for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1)
    {
        param_2[local_18 + 0x59] = *(undefined1 *)(param_1 + local_18 + 0x60);
    }
    for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1)
    {
        param_2[local_1c + 0x5d] = *(undefined1 *)(param_1 + local_1c + 100);
    }
    param_2[0x61] = *(undefined1 *)(param_1 + 0x68);
    param_2[0x62] = *(undefined1 *)(param_1 + 0x69);
    return 99;
}
