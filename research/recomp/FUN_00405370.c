// ============================================
// Address:  0x00405370
// Original: FUN_00405370
// Status:   unreviewed
// ============================================

void __fastcall FUN_00405370(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069db2a;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a14fc;
    local_8       = 0;
    FUN_0065bea0();
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
