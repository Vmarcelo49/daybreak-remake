// ============================================
// Address:  0x0040dd10
// Original: FUN_0040dd10
// Status:   unreviewed
// ============================================

void __fastcall FUN_0040dd10(undefined4 param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069dbeb;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    FUN_0040dcc0(param_1);
    local_8 = 0xffffffff;
    FUN_00657320();
    ExceptionList = local_10;
    return;
}
