// ============================================
// Address:  0x00693000
// Original: FUN_00693000
// Status:   unreviewed
// ============================================

DWORD FUN_00693000(HANDLE param_1, uint param_2, HWND param_3, UINT param_4, int param_5)

{
    BOOL BVar1;
    HANDLE pvVar2;
    DWORD DVar3;
    UINT UVar4;
    WPARAM wParam;
    int nPriority;
    uint nPriority_00;
    LPARAM lParam;
    tagMSG local_64;
    DWORD local_48;
    uint local_44;
    tagMSG local_40;
    DWORD local_24;
    uint local_20;
    DWORD local_1c;
    uint local_18;
    int local_14;
    DWORD local_10;
    HANDLE local_c;
    int local_8;

    local_14 = 0;
    local_c  = param_1;
    local_8  = param_5;
    if ((param_2 != 0xffffffff) && (param_2 != 0))
    {
        local_10 = GetTickCount();
    }
    while (true)
    {
        local_20 = (param_5 != 0) + 1;
        local_1c = WaitForMultipleObjects(local_20, &local_c, 0, 0);
        if (local_1c < local_20)
            break;
        local_24 = param_2;
        if (10 < param_2)
        {
            local_24 = 10;
        }
        local_1c = MsgWaitForMultipleObjects(
            local_20, &local_c, 0, local_24, (uint)(param_3 != (HWND)0x0) * 8 + 0x40);
        if ((local_1c != local_20) && ((local_1c != 0x102 || (local_24 == param_2))))
            break;
        if (param_3 != (HWND)0x0)
        {
            while (BVar1 = PeekMessageA(&local_40, param_3, param_4, param_4, 1), BVar1 != 0)
            {
                DispatchMessageA(&local_40);
            }
        }
        PeekMessageA(&local_40, (HWND)0x0, 0, 0, 0);
        if ((param_2 != 0xffffffff) && (param_2 != 0))
        {
            local_48 = GetTickCount();
            local_44 = local_48 - local_10;
            local_10 = local_48;
            if (param_2 < local_44)
            {
                param_2 = 0;
            }
            else
            {
                param_2 = param_2 - local_44;
            }
        }
        if (local_14 == 0)
        {
            pvVar2   = GetCurrentThread();
            local_18 = GetThreadPriority(pvVar2);
            if (local_18 < 2)
            {
                nPriority = 2;
                pvVar2    = GetCurrentThread();
                SetThreadPriority(pvVar2, nPriority);
            }
            local_14 = 1;
        }
    }
    if (local_14 != 0)
    {
        nPriority_00 = local_18;
        pvVar2       = GetCurrentThread();
        SetThreadPriority(pvVar2, nPriority_00);
        DVar3 = GetQueueStatus(8);
        if ((DVar3 >> 0x10 & 8) != 0)
        {
            UVar4 = DAT_006d8954;
            if (DAT_006d8954 == 0)
            {
                DAT_006d8954 = RegisterWindowMessageA("AMUnblock");
                UVar4        = DAT_006d8954;
            }
            while (UVar4 != 0)
            {
                UVar4 = PeekMessageA(&local_64, (HWND)0xffffffff, DAT_006d8954, DAT_006d8954, 1);
            }
            lParam = 0;
            wParam = 0;
            UVar4  = DAT_006d8954;
            DVar3  = GetCurrentThreadId();
            PostThreadMessageA(DVar3, UVar4, wParam, lParam);
        }
    }
    return local_1c;
}
