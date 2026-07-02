// ============================================
// Address:  0x0067a3a0
// Original: FUN_0067a3a0
// Status:   unreviewed
// ============================================

void FUN_0067a3a0(undefined4 *param_1)

{
    int iVar1;

    if (((int *)param_1[0x10] != (int *)0x0) && (*(int *)param_1[0x10] != 0))
    {
        FUN_0069d5e0(param_1 + 1);
    }
    FUN_0067a330(param_1);
    if ((void *)param_1[0x11] != (void *)0x0)
    {
        _free((void *)param_1[0x11]);
    }
    if ((void *)param_1[0x1a] != (void *)0x0)
    {
        _free((void *)param_1[0x1a]);
    }
    for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1)
    {
        *param_1 = 0;
        param_1  = param_1 + 1;
    }
    return;
}
