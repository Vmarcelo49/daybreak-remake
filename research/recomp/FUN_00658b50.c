// ============================================
// Address:  0x00658b50
// Original: FUN_00658b50
// Status:   unreviewed
// ============================================

void __fastcall FUN_00658b50(int param_1)

{
    if (*(int *)(param_1 + 4) != 0)
    {
        FUN_00658e10(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
        deallocate(*(undefined4 *)(param_1 + 4),
                   (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) / 0x50);
    }
    *(undefined4 *)(param_1 + 4)   = 0;
    *(undefined4 *)(param_1 + 8)   = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    return;
}
