// ============================================
// Address:  0x00434a70
// Original: FUN_00434a70
// Status:   unreviewed
// ============================================

void __thiscall FUN_00434a70(int param_1, int param_2, int param_3)

{
    if ((-1 < param_2) && (param_2 < 2))
    {
        if (param_3 < 0)
        {
            *(undefined4 *)(param_1 + 0x18 + param_2 * 4) = 0xffffffff;
        }
        else if (*(char *)(*(int *)(param_1 + 0xc) + param_3) == '\0')
        {
            *(undefined4 *)(param_1 + 0x18 + param_2 * 4) = 0xffffffff;
        }
        else
        {
            FUN_004358c0(*(undefined4 *)(param_1 + 0x10 + param_2 * 4));
            *(int *)(param_1 + 0x18 + param_2 * 4) = param_3;
            (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x18 + param_2 * 4) * 0x970 +
                                        *(int *)(param_1 + 4)))();
        }
    }
    return;
}
