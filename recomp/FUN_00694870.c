// ============================================
// Address:  0x00694870
// Original: FUN_00694870
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00694870(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fc3a;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068db70();
    FUN_0068dee0(param_2, param_3);
    local_8 = 0;
    FUN_00425ac0();
    ExceptionList = local_10;
    return param_1;
}
