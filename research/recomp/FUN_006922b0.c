// ============================================
// Address:  0x006922b0
// Original: FUN_006922b0
// Status:   unreviewed
// ============================================

bool __fastcall FUN_006922b0(LPVOID param_1)

{
    HANDLE pvVar1;
    bool bVar2;

    pvVar1 = CreateSemaphoreA((LPSECURITY_ATTRIBUTES)0x0, 0, 0x7fffffff, (LPCSTR)0x0);
    *(HANDLE *)((int)param_1 + 0x3c) = pvVar1;
    if (*(int *)((int)param_1 + 0x3c) == 0)
    {
        bVar2 = false;
    }
    else
    {
        pvVar1 = CreateThread(
            (LPSECURITY_ATTRIBUTES)0x0, 0, FUN_00692310, param_1, 0, (LPDWORD)((int)param_1 + 4));
        *(HANDLE *)((int)param_1 + 8) = pvVar1;
        bVar2                         = *(int *)((int)param_1 + 8) != 0;
    }
    return bVar2;
}
