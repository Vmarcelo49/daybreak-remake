// ============================================
// Address:  0x00692180
// Original: FUN_00692180
// Status:   unreviewed
// ============================================

int FUN_00692180(void)

{
    HMODULE hModule;
    FARPROC pFVar1;
    int local_c;

    local_c = -0x7fffbffb;
    hModule = GetModuleHandleA("ole32.dll");
    if (hModule != (HMODULE)0x0)
    {
        pFVar1 = GetProcAddress(hModule, "CoInitializeEx");
        if (pFVar1 != (FARPROC)0x0)
        {
            local_c = (*pFVar1)(0, 4);
        }
    }
    return local_c;
}
