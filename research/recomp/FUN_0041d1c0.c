// ============================================
// Address:  0x0041d1c0
// Original: FUN_0041d1c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0041d1c0(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c      = &LAB_0069e07a;
    local_10       = ExceptionList;
    ExceptionList  = &local_10;
    *param_1       = &PTR_FUN_006a21d4;
    param_1[0x179] = &PTR_FUN_006a21c8;
    local_8        = 0;
    FUN_0065f780(0);
    local_8 = 0xffffffff;
    FUN_004119f0();
    ExceptionList = local_10;
    return;
}
