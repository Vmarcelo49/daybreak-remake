// ============================================
// Address:  0x004366f0
// Original: FUN_004366f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004366f0(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069e5db;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x30) != 0)
    {
        ExceptionList = &local_10;
        _free(*(void **)(param_1 + 0x30));
        *(undefined4 *)(param_1 + 0x30) = 0;
    }
    if (*(int *)(param_1 + 0x34) != 0)
    {
        _free(*(void **)(param_1 + 0x34));
        *(undefined4 *)(param_1 + 0x34) = 0;
    }
    FUN_00437230();
    local_8 = 0xffffffff;
    FUN_00437230();
    ExceptionList = local_10;
    return;
}
