// ============================================
// Address:  0x0069cd00
// Original: FUN_0069cd00
// Status:   unreviewed
// ============================================

void FUN_0069cd00(int param_1, int param_2)

{
    void *pvVar1;

    if (*(int *)(param_1 + 0x18) <= *(int *)(param_1 + 0x1c) + param_2)
    {
        param_2                    = *(int *)(param_1 + 0x18) + 0x20 + param_2;
        *(int *)(param_1 + 0x18)   = param_2;
        pvVar1                     = _realloc(*(void **)(param_1 + 0x10), param_2 * 4);
        *(void **)(param_1 + 0x10) = pvVar1;
        pvVar1 = _realloc(*(void **)(param_1 + 0x14), *(int *)(param_1 + 0x18) << 3);
        *(void **)(param_1 + 0x14) = pvVar1;
    }
    return;
}
