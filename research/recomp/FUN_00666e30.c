// ============================================
// Address:  0x00666e30
// Original: FUN_00666e30
// Status:   unreviewed
// ============================================

void __fastcall FUN_00666e30(int param_1)

{
    char cVar1;
    undefined4 *puVar2;
    undefined1 local_20[4];
    DWORD local_1c;
    undefined1 local_18[4];
    undefined1 local_14[4];
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    puStack_c                       = &LAB_0069f320;
    local_10                        = ExceptionList;
    local_8                         = 1;
    ExceptionList                   = &local_10;
    *(undefined1 *)(param_1 + 0x38) = 0;
    local_1c                        = 0x103;
    while (local_1c == 0x103)
    {
        GetExitCodeThread(*(HANDLE *)(param_1 + 0x20), &local_1c);
    }
    FUN_0065d670();
    FUN_00653d10(local_14);
    FUN_00654620(local_18);
    while (true)
    {
        cVar1 = const_iterator__operator__(local_18);
        if (cVar1 == '\0')
            break;
        puVar2 = (undefined4 *)FUN_00653d70();
        SetEvent((HANDLE)*puVar2);
        puVar2 = (undefined4 *)FUN_00653d70();
        CloseHandle((HANDLE)*puVar2);
        FUN_0042fc40(local_20, 0);
    }
    FUN_004261d0();
    FUN_0065d6a0();
    CloseHandle(*(HANDLE *)(param_1 + 0x1c));
    CloseHandle(*(HANDLE *)(param_1 + 0x20));
    local_8 = local_8 & 0xffffff00;
    FUN_00424670();
    local_8 = 0xffffffff;
    FUN_0065d640();
    ExceptionList = local_10;
    return;
}
