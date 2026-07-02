// ============================================
// Address:  0x0066c57d
// Original: FUN_0066c57d
// Status:   unreviewed
// ============================================

uint FUN_0066c57d(uint param_1, uint param_2)

{
    uint uVar1;
    bool in_ZF;
    short in_FPUControlWord;

    if (in_ZF)
    {
        if (((param_2 & 0xfffff) != 0) || (param_1 != 0))
        {
            uVar1 = FUN_006702ac();
            goto LAB_0066c5fb;
        }
        param_1 = param_2 & 0x80000000;
        param_2 = 0;
    joined_r0x0066c5ec:
        if (param_1 == 0)
        {
        LAB_0066c59e:
            if (DAT_006d847c != 0)
            {
                return param_2;
            }
            uVar1 = __math_exit();
            return uVar1;
        }
    }
    else
    {
        if (in_FPUControlWord != 0x27f)
        {
            param_2 = FUN_00670295();
        }
        if ((param_2 & 0x80000000) == 0)
            goto LAB_0066c59e;
        if (((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0))
            goto joined_r0x0066c5ec;
    }
    uVar1 = 1;
LAB_0066c5fb:
    if (DAT_006d847c != 0)
    {
        return uVar1;
    }
    uVar1 = __startOneArgErrorHandling();
    return uVar1;
}
