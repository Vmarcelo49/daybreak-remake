// ============================================
// Address:  0x0068c0c0
// Original: FUN_0068c0c0
// Status:   unreviewed
// ============================================

int __thiscall FUN_0068c0c0(int *param_1,
                            undefined4 param_2,
                            undefined4 param_3,
                            undefined4 param_4,
                            undefined4 param_5,
                            undefined4 param_6,
                            undefined8 param_7)

{
    int iVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f6cc;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00686860(param_2, 0);
    local_8 = 0;
    iVar1   = FUN_0068c1a0();
    if (iVar1 < 0)
    {
        local_8 = 0xffffffff;
        FUN_006867e0();
    }
    else
    {
        iVar1 = (**(code **)(*param_1 + 0x58))(param_3, param_4, param_5, param_6, param_7);
        if (iVar1 < 0)
        {
            local_8 = 0xffffffff;
            FUN_006867e0();
        }
        else
        {
            local_8 = 0xffffffff;
            FUN_006867e0();
            iVar1 = 0;
        }
    }
    ExceptionList = local_10;
    return iVar1;
}
