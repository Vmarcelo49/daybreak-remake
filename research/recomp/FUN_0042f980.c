// ============================================
// Address:  0x0042f980
// Original: FUN_0042f980
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0042f980(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e41b;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a2570;
    FUN_0042fb20();
    local_8 = 0;
    FUN_0065d610();
    ExceptionList = local_10;
    return param_1;
}
