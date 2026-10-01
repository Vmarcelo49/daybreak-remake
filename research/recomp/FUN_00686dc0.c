// ============================================
// Address:  0x00686dc0
// Original: FUN_00686dc0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00686dc0(int param_1, int param_2)

{
    int iVar1;

    iVar1 = FUN_006871d0(param_2, &DAT_006ad998);
    if ((iVar1 != 0) && (iVar1 = FUN_006871d0(param_1, param_2), iVar1 != 0))
    {
        return 0;
    }
    iVar1 = FUN_006871d0(param_2 + 0x10, &DAT_006ad998);
    if ((iVar1 != 0) && (iVar1 = FUN_006871d0(param_1 + 0x10, param_2 + 0x10), iVar1 != 0))
    {
        return 0;
    }
    iVar1 = FUN_006871d0(param_2 + 0x2c, &DAT_006ad998);
    if (iVar1 != 0)
    {
        iVar1 = FUN_006871d0(param_1 + 0x2c, param_2 + 0x2c);
        if (iVar1 != 0)
        {
            return 0;
        }
        if (*(int *)(param_1 + 0x40) != *(int *)(param_2 + 0x40))
        {
            return 0;
        }
        if ((*(int *)(param_1 + 0x40) != 0) && (iVar1 = _memcmp(*(void **)(param_1 + 0x44),
                                                                *(void **)(param_2 + 0x44),
                                                                *(size_t *)(param_1 + 0x40)),
                                                iVar1 != 0))
        {
            return 0;
        }
    }
    return 1;
}
