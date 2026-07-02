// ============================================
// Address:  0x00699730
// Original: FUN_00699730
// Status:   unreviewed
// ============================================

int __thiscall FUN_00699730(int param_1,
                            undefined4 param_2,
                            undefined4 param_3,
                            undefined4 param_4,
                            undefined4 param_5,
                            undefined4 *param_6,
                            undefined4 param_7)

{
    int iVar1;
    undefined4 uVar2;

    if (param_6 == (undefined4 *)0x0)
    {
        iVar1 = -0x7fffbffd;
    }
    else
    {
        iVar1 = FUN_00699f20(param_2, param_3);
        if (((iVar1 == 0) || (iVar1 = FUN_00698fd0(param_4), iVar1 == 0)) ||
            (iVar1 = FUN_00698fd0(param_5), iVar1 == 0))
        {
            iVar1 = -0x7ffbfdf2;
        }
        else
        {
            iVar1 = FUN_00699110(param_1,
                                 *(undefined4 *)(param_1 + 0x18),
                                 param_2,
                                 param_3,
                                 param_4,
                                 1,
                                 param_5,
                                 param_7,
                                 0);
            if (-1 < iVar1)
            {
                iVar1    = FUN_00699180();
                uVar2    = FUN_0068dac0();
                *param_6 = uVar2;
            }
        }
    }
    return iVar1;
}
