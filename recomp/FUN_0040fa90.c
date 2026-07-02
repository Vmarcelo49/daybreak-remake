// ============================================
// Address:  0x0040fa90
// Original: FUN_0040fa90
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0040fa90(undefined4 param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069dccb;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_004248f0();
    local_8 = 0;
    FUN_0040fbd0();
    ExceptionList = local_10;
    return param_1;
}
