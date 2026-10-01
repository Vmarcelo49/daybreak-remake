// ============================================
// Address:  0x0064f100
// Original: FUN_0064f100
// Status:   unreviewed
// ============================================

void __fastcall FUN_0064f100(int param_1)

{
    if (*(int *)(param_1 + 4) != 0)
    {
        FUN_0064f370(*(undefined4 *)(param_1 + 4), *(undefined4 *)(param_1 + 8));
        deallocate(*(undefined4 *)(param_1 + 4),
                   *(int *)(param_1 + 0xc) - *(int *)(param_1 + 4) >> 2);
    }
    *(undefined4 *)(param_1 + 4)   = 0;
    *(undefined4 *)(param_1 + 8)   = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    return;
}
