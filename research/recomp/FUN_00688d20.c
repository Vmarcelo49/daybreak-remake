// ============================================
// Address:  0x00688d20
// Original: FUN_00688d20
// Status:   unreviewed
// ============================================

LONG FUN_00688d20(int *param_1)

{
    LONG LVar1;

    LVar1 = InterlockedDecrement(param_1 + 4);
    if ((LVar1 == 0) && (param_1 != (int *)0x0))
    {
        (**(code **)(*param_1 + 0x1c))(1);
    }
    return LVar1;
}
