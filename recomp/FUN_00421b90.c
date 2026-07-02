// ============================================
// Address:  0x00421b90
// Original: FUN_00421b90
// Status:   unreviewed
// ============================================

int __thiscall FUN_00421b90(int param_1, int param_2)

{
    if (param_2 == 2)
    {
        param_1 = param_1 + 0x2cc;
    }
    else if (param_2 == 3)
    {
        param_1 = param_1 + 0x2c0;
    }
    else
    {
        param_1 = param_1 + 0x14;
    }
    return param_1;
}
