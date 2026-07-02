// ============================================
// Address:  0x00689bb0
// Original: FUN_00689bb0
// Status:   unreviewed
// ============================================

undefined4 FUN_00689bb0(int param_1, int param_2)

{
    undefined4 uVar1;
    int iVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f5e3;
    local_10  = ExceptionList;
    if (param_2 == 0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        ExceptionList = &local_10;
        FUN_0068d950(*(undefined4 *)(param_1 + 0x14));
        local_8 = 0;
        iVar2   = FUN_0068da80();
        if (iVar2 == 0)
        {
            FUN_00686d50();
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0x80040209;
        }
        else
        {
            FUN_00686f20(param_2, param_1 + 0x28);
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0;
        }
    }
    ExceptionList = local_10;
    return uVar1;
}
