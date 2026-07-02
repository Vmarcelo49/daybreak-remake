// ============================================
// Address:  0x0042e9a0
// Original: FUN_0042e9a0
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0042e9a0(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e3a8;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0042f720();
    local_8  = 0;
    *param_1 = &PTR_FUN_006a2500;
    FUN_00425ac0();
    param_1[0xc]  = 0;
    param_1[0xd]  = 0;
    param_1[0xe]  = 0;
    ExceptionList = local_10;
    return param_1;
}
