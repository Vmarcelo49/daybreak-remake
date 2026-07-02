// ============================================
// Address:  0x0064ada0
// Original: FUN_0064ada0
// Status:   unreviewed
// ============================================

int __thiscall FUN_0064ada0(int param_1, int param_2)

{
    if ((param_2 < 0) || (3 < param_2))
    {
        param_1 = param_1 + 0x56d0;
    }
    else
    {
        param_1 = param_1 + 0x5600 + param_2 * 0x34;
    }
    return param_1;
}
