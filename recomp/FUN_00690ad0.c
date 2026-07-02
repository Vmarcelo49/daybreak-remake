// ============================================
// Address:  0x00690ad0
// Original: FUN_00690ad0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00690ad0(int param_1)

{
    if (*(int *)(param_1 + 0xf0) < 1)
    {
        Sleep(0);
    }
    else
    {
        Sleep(*(int *)(param_1 + 0xf0) / 10000);
    }
    return;
}
