// ============================================
// Address:  0x00698630
// Original: FUN_00698630
// Status:   unreviewed
// ============================================

int FUN_00698630(undefined4 *param_1)

{
    void *pvVar1;
    int *local_38;
    int local_18;
    int *local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069ff1d;
    local_10  = ExceptionList;
    if (param_1 == (undefined4 *)0x0)
    {
        local_18 = -0x7fffbffd;
    }
    else
    {
        local_18      = 0;
        local_14      = (int *)0x0;
        ExceptionList = &local_10;
        *param_1      = 0;
        pvVar1        = operator_new(100);
        local_8       = 0;
        if (pvVar1 == (void *)0x0)
        {
            local_38 = (int *)0x0;
        }
        else
        {
            local_38 = (int *)FUN_0068d0b0(0, 0, &local_18);
        }
        local_8  = 0xffffffff;
        local_14 = local_38;
        if (local_38 == (int *)0x0)
        {
            local_18 = -0x7ff8fff2;
        }
        else if (local_18 < 0)
        {
            if (local_38 != (int *)0x0)
            {
                (**(code **)(*local_38 + 0xc))(1);
            }
        }
        else
        {
            local_18 = (**(code **)local_38[3])(local_38 + 3, &LAB_006ad024, param_1);
            if (local_18 < 0)
            {
                if (local_14 != (int *)0x0)
                {
                    (**(code **)(*local_14 + 0xc))(1);
                }
                local_18 = -0x7fffbffe;
            }
            else
            {
                local_18 = 0;
            }
        }
    }
    ExceptionList = local_10;
    return local_18;
}
