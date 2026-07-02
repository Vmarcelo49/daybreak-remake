// ============================================
// Address:  0x0065a520
// Original: FUN_0065a520
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0065a520(undefined4 param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069efa3;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0065a600();
    local_8 = 0;
    FUN_00653dc0();
    local_8 = CONCAT31(local_8._1_3_, 1);
    FUN_00653dc0();
    ExceptionList = local_10;
    return param_1;
}
