// ============================================
// Address:  0x00688850
// Original: FUN_00688850
// Status:   unreviewed
// ============================================

LONG FUN_00688850(int *param_1)

{
    LONG LVar1;

    LVar1 = InterlockedDecrement(param_1 + 5);
    if ((LVar1 == 0) && (param_1 != (int *)0x0))
    {
        (**(code **)(*param_1 + 0x1c))(1);
    }
    return LVar1;
}
