// ============================================
// Address:  0x0067e0c0
// Original: FUN_0067e0c0
// Status:   unreviewed
// ============================================

void FUN_0067e0c0(void *param_1)

{
    if (*(int *)((int)param_1 + 0x30) != 0)
    {
        FUN_0067dff0(param_1);
        _free(param_1);
    }
    return;
}
