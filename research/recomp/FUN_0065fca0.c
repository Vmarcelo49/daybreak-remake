// ============================================
// Address:  0x0065fca0
// Original: FUN_0065fca0
// Status:   unreviewed
// ============================================

undefined4 FUN_0065fca0(int param_1, undefined4 param_2, int param_3, int param_4)

{
    HANDLE pvVar1;

    if (param_3 == -0xfffb)
    {
        *(undefined4 *)(param_1 + 0x88) = 0;
        if (*(int *)(param_4 + 0xc) != 0)
        {
            return 0x80158230;
        }
        *(undefined4 *)(param_1 + 0x70) = **(undefined4 **)(param_4 + 0x10);
        *(undefined1 *)(param_1 + 0x74) = 1;
        pvVar1                      = CreateEventA((LPSECURITY_ATTRIBUTES)0x0, 0, 0, (LPCSTR)0x0);
        *(HANDLE *)(param_1 + 0x78) = pvVar1;
        pvVar1                      = CreateThread(
            (LPSECURITY_ATTRIBUTES)0x0, 0, FUN_0065fdc0, (LPVOID)0x0, 0, (LPDWORD)(param_1 + 0x80));
        *(HANDLE *)(param_1 + 0x7c) = pvVar1;
        SetThreadPriority(*(HANDLE *)(param_1 + 0x7c), 0xf);
    }
    else if (param_3 == -0xffef)
    {
        if (*(char *)(param_1 + 0x74) == '\0')
        {
            return 0;
        }
        FUN_0065d670();
        if (*(int *)(param_1 + 0x6c) != 0)
        {
            (**(code **)(**(int **)(param_1 + 0x6c) + 4))(*(undefined4 *)(param_4 + 0xc),
                                                          *(undefined4 *)(param_4 + 0x10));
        }
        *(undefined4 *)(param_1 + 0x88) = 0;
        FUN_0065d6a0();
    }
    return 0;
}
