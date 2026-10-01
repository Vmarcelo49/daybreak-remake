// ============================================
// Address:  0x0068fae0
// Original: FUN_0068fae0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068fae0(int param_1)

{
    undefined4 uVar1;
    int local_24;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f9c6;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x94);
    local_8 = 0;
    if (*(int *)(param_1 + 100) == 0)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        uVar1 = 0;
    }
    else
    {
        *(undefined4 *)(param_1 + 0xc0) = 0;
        if (*(int *)(param_1 + 0x50) != 0)
        {
            FUN_006957e0();
        }
        *(undefined4 *)(param_1 + 0x74) = 1;
        if (param_1 == 0)
        {
            local_24 = 0;
        }
        else
        {
            local_24 = param_1 + 0xc;
        }
        uVar1   = FUN_006883f0(1, 0, local_24);
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    ExceptionList = local_10;
    return uVar1;
}
