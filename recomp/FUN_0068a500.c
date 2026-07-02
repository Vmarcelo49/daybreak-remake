// ============================================
// Address:  0x0068a500
// Original: FUN_0068a500
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068a500(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069f60a;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x9c) != 0)
    {
        ExceptionList = &local_10;
        (**(code **)(**(int **)(param_1 + 0x9c) + 8))(*(undefined4 *)(param_1 + 0x9c));
        *(undefined4 *)(param_1 + 0x9c) = 0;
    }
    local_8 = 0xffffffff;
    FUN_00689210();
    ExceptionList = local_10;
    return;
}
