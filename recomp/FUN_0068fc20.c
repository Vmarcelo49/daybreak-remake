// ============================================
// Address:  0x0068fc20
// Original: FUN_0068fc20
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068fc20(int param_1)

{
    if (*(int *)(param_1 + 0xc0) != 0)
    {
        timeKillEvent(*(UINT *)(param_1 + 0xc0));
        *(undefined4 *)(param_1 + 0xc0) = 0;
    }
    return;
}
