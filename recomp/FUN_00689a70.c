// ============================================
// Address:  0x00689a70
// Original: FUN_00689a70
// Status:   unreviewed
// ============================================

undefined4 FUN_00689a70(int param_1)

{
    int iVar1;
    undefined4 uVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f5d1;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x14));
    local_8 = 0;
    iVar1   = FUN_0068daa0();
    if (iVar1 == 0)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        uVar2 = 0x80040224;
    }
    else
    {
        uVar2   = FUN_00689b00(param_1 + -0xc);
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    ExceptionList = local_10;
    return uVar2;
}
