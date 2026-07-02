// ============================================
// Address:  0x0068e710
// Original: FUN_0068e710
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068e710(int param_1)

{
    DWORD DVar1;
    UINT Msg;
    WPARAM wParam;
    LPARAM lParam;
    tagMSG local_20;

    while (*(int *)(param_1 + 0xb4) != 0)
    {
        PeekMessageA(&local_20, (HWND)0x0, 0, 0, 0);
        Sleep(1);
    }
    DVar1 = GetQueueStatus(8);
    if ((DVar1 >> 0x10 & 8) != 0)
    {
        lParam = 0;
        wParam = 0;
        Msg    = 0;
        DVar1  = GetCurrentThreadId();
        PostThreadMessageA(DVar1, Msg, wParam, lParam);
    }
    return;
}
