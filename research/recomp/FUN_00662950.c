// ============================================
// Address:  0x00662950
// Original: FUN_00662950
// Status:   unreviewed
// ============================================

void __fastcall FUN_00662950(int *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069f270;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    if (*param_1 != 0)
    {
        ExceptionList = &local_10;
        CloseHandle((HANDLE)*param_1);
    }
    FUN_00663420();
    local_8 = 0xffffffff;
    FUN_00663190();
    ExceptionList = local_10;
    return;
}
