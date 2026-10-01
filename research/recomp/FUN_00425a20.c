// ============================================
// Address:  0x00425a20
// Original: FUN_00425a20
// Status:   unreviewed
// ============================================

void __fastcall FUN_00425a20(int param_1)

{
    if (*(int *)(param_1 + 4) != 0)
    {
        FUN_00426840(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
        deallocate(*(undefined4 *)(param_1 + 4),
                   (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) / 0xc);
    }
    *(undefined4 *)(param_1 + 4)   = 0;
    *(undefined4 *)(param_1 + 8)   = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    return;
}
