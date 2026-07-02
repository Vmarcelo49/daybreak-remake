// ============================================
// Address:  0x004369c0
// Original: FUN_004369c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004369c0(int *param_1)

{
    undefined4 uVar1;
    int local_8;

    uVar1 = FUN_00430750(*(undefined4 *)*param_1,
                         *(undefined4 *)(*param_1 + 4),
                         *(undefined4 *)(*param_1 + 8),
                         0x3f800000);
    FUN_00437130(uVar1);
    FUN_0041b8e0();
    if (param_1[3] < param_1[1])
    {
        param_1[3] = param_1[3] + 1;
        for (local_8 = 0; local_8 <= param_1[3] * param_1[2]; local_8 = local_8 + 1)
        {
            *(float *)(param_1[0xd] + 0x18 + (local_8 * 2 + 1) * 0x1c) =
                (float)local_8 / (float)(param_1[3] * param_1[2]);
            *(undefined4 *)(param_1[0xd] + 0x18 + local_8 * 0x38) =
                *(undefined4 *)(param_1[0xd] + 0x18 + (local_8 * 2 + 1) * 0x1c);
        }
    }
    return;
}
