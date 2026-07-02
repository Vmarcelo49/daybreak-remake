// ============================================
// Address:  0x0065b9f0
// Original: FUN_0065b9f0
// Status:   unreviewed
// ============================================

void __thiscall FUN_0065b9f0(int param_1, int param_2)

{
    if (param_2 < 0)
    {
        *(undefined4 *)(param_1 + 0x135c) = 0;
    }
    else if (param_2 < 0x2711)
    {
        *(int *)(param_1 + 0x135c) = param_2;
    }
    else
    {
        *(undefined4 *)(param_1 + 0x135c) = 10000;
    }
    if (*(int *)(param_1 + 0x10) != 0)
    {
        FUN_0065a390((*(int *)(param_1 + 0x135c) * *(int *)(param_1 + 0x1360)) / 10000 + -10000);
    }
    return;
}
