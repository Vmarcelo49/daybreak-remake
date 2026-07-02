// ============================================
// Address:  0x004193a0
// Original: FUN_004193a0
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_004193a0(undefined4 *param_1)

{
    undefined4 *local_18;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069df36;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_004115f0();
    local_8 = 0;
    FUN_00415dc0();
    local_8        = CONCAT31(local_8._1_3_, 1);
    *param_1       = &PTR_FUN_006a1ff4;
    param_1[0x179] = &PTR_FUN_006a1fe0;
    FUN_00415da0();
    if (param_1 == (undefined4 *)0x0)
    {
        local_18 = (undefined4 *)0x0;
    }
    else
    {
        local_18 = param_1 + 0x179;
    }
    FUN_0065fee0(local_18);
    _memset(param_1 + 0x1c1, 0, 0x20);
    param_1[0x1d3] = 0;
    ExceptionList  = local_10;
    return param_1;
}
