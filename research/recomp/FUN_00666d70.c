// ============================================
// Address:  0x00666d70
// Original: FUN_00666d70
// Status:   unreviewed
// ============================================

int __fastcall FUN_00666d70(int param_1)

{
    HANDLE pvVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f303;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0065d610();
    local_8 = 0;
    FUN_00667240();
    local_8                         = CONCAT31(local_8._1_3_, 1);
    *(undefined4 *)(param_1 + 0x28) = 0x10;
    *(undefined1 *)(param_1 + 0x38) = 1;
    timeBeginPeriod(1);
    FUN_004261d0();
    pvVar1                      = CreateEventA((LPSECURITY_ATTRIBUTES)0x0, 0, 0, (LPCSTR)0x0);
    *(HANDLE *)(param_1 + 0x1c) = pvVar1;
    pvVar1                      = CreateThread(
        (LPSECURITY_ATTRIBUTES)0x0, 0, FUN_00666f60, (LPVOID)0x0, 0, (LPDWORD)(param_1 + 0x24));
    *(HANDLE *)(param_1 + 0x20) = pvVar1;
    SetThreadPriority(*(HANDLE *)(param_1 + 0x20), 0xf);
    ExceptionList = local_10;
    return param_1;
}
