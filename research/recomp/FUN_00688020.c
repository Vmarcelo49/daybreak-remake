// ============================================
// Address:  0x00688020
// Original: FUN_00688020
// Status:   unreviewed
// ============================================

int __thiscall FUN_00688020(int param_1, undefined4 param_2)

{
    int iVar1;

    if (*(int *)(param_1 + 0x18) == 0)
    {
        iVar1 = -0x7ffbfded;
    }
    else
    {
        iVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0xc))(*(undefined4 *)(param_1 + 0x18),
                                                                param_2);
        if (-1 < iVar1)
        {
            FUN_0068d910(param_1 + 0x20);
            iVar1 = 0;
        }
    }
    return iVar1;
}
