// ============================================
// Address:  0x004232c0
// Original: FUN_004232c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004232c0(undefined4 param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069e28b;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    FUN_004244c0(param_1);
    local_8 = 0xffffffff;
    FUN_004244c0();
    ExceptionList = local_10;
    return;
}
