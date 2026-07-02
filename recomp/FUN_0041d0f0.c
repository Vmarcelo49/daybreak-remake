// ============================================
// Address:  0x0041d0f0
// Original: FUN_0041d0f0
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0041d0f0(undefined4 *param_1)

{
    undefined4 *local_18;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e068;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_004115f0();
    local_8 = 0;
    FUN_0041af50();
    *param_1       = &PTR_FUN_006a21d4;
    param_1[0x179] = &PTR_FUN_006a21c8;
    FUN_00415da0();
    if (param_1 == (undefined4 *)0x0)
    {
        local_18 = (undefined4 *)0x0;
    }
    else
    {
        local_18 = param_1 + 0x179;
    }
    FUN_0065f780(local_18);
    param_1[0x1ba]                        = 0;
    param_1[0x1bb]                        = 1;
    *(undefined1 *)(param_1 + 0x1bc)      = 0;
    *(undefined1 *)((int)param_1 + 0x6f1) = 0;
    ExceptionList                         = local_10;
    return param_1;
}
