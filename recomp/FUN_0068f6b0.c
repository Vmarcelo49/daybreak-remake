// ============================================
// Address:  0x0068f6b0
// Original: FUN_0068f6b0
// Status:   unreviewed
// ============================================

int __thiscall FUN_0068f6b0(int *param_1, undefined4 param_2)

{
    int iVar1;
    void *local_10;
    undefined1 *puStack_c;
    int local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f990;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    iVar1         = (**(code **)(*param_1 + 0x98))(param_2);
    if (iVar1 < 0)
    {
        if (iVar1 == -0x7ffbfdd5)
        {
            iVar1 = 0;
        }
    }
    else
    {
        if (param_1[5] == 1)
        {
            (**(code **)(*param_1 + 0x50))();
            param_1[0x2d] = 0;
            FUN_0068d950(param_1 + 0x1f);
            local_8 = 0;
            if (param_1[5] == 0)
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                ExceptionList = local_10;
                return 0;
            }
            param_1[0x2d] = 1;
            FUN_0068d950(param_1 + 0x25);
            local_8._0_1_ = 1;
            (**(code **)(*param_1 + 0x34))(param_2);
            local_8 = (uint)local_8._1_3_ << 8;
            FUN_0068d9a0();
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            FUN_00691bf0();
        }
        iVar1 = (**(code **)(*param_1 + 0x2c))();
        if (iVar1 < 0)
        {
            param_1[0x2d] = 0;
            iVar1         = 0;
        }
        else
        {
            (**(code **)(*param_1 + 0x50))();
            param_1[0x2d] = 0;
            FUN_0068d950(param_1 + 0x1f);
            local_8 = 2;
            if (param_1[5] == 0)
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                iVar1 = 0;
            }
            else
            {
                FUN_0068d950(param_1 + 0x25);
                local_8._0_1_ = 3;
                (**(code **)(*param_1 + 0xa8))(param_1[0x1b]);
                (**(code **)(*param_1 + 0x70))();
                (**(code **)(*param_1 + 0x60))();
                (**(code **)(*param_1 + 0x6c))();
                local_8 = CONCAT31(local_8._1_3_, 2);
                FUN_0068d9a0();
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                iVar1 = 0;
            }
        }
    }
    ExceptionList = local_10;
    return iVar1;
}
