// ============================================
// Address:  0x0069cd70
// Original: FUN_0069cd70
// Status:   unreviewed
// ============================================

undefined4 FUN_0069cd70(undefined4 *param_1)

{
    if (param_1 != (undefined4 *)0x0)
    {
        if ((void *)*param_1 != (void *)0x0)
        {
            _free((void *)*param_1);
        }
        FUN_0069cd50(param_1);
    }
    return 0;
}
