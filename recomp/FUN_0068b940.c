// ============================================
// Address:  0x0068b940
// Original: FUN_0068b940
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b940(int param_1)

{
    undefined4 uVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f672;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x14));
    local_8 = 0;
    uVar1   = FUN_00689b00(param_1 + -0xc);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return uVar1;
}
