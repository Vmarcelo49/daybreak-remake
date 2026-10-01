// ============================================
// Address:  0x0065a420
// Original: FUN_0065a420
// Status:   unreviewed
// ============================================

void __fastcall FUN_0065a420(int param_1)

{
    if (*(int *)(param_1 + 0x14) != 0)
    {
        _free(*(void **)(param_1 + 0x14));
        *(undefined4 *)(param_1 + 0x14) = 0;
    }
    return;
}
