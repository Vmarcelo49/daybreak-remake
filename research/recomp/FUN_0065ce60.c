// ============================================
// Address:  0x0065ce60
// Original: FUN_0065ce60
// Status:   unreviewed
// ============================================

undefined4 *__thiscall
FUN_0065ce60(undefined4 *param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f118;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00698d60(0, 0, param_2, param_4);
    local_8    = 0;
    *param_1   = &PTR_FUN_006aae54;
    param_1[3] = &PTR_FUN_006aae18;
    param_1[4] = &PTR_LAB_006aae04;
    FUN_00686900(param_3);
    ExceptionList = local_10;
    return param_1;
}
