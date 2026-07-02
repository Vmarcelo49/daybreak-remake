// ============================================
// Address:  0x00689840
// Original: FUN_00689840
// Status:   unreviewed
// ============================================

int FUN_00689840(int param_1, int param_2, int param_3)

{
    int iVar1;
    int local_18;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f5bf;
    local_10  = ExceptionList;
    if (param_2 == 0)
    {
        local_18 = -0x7fffbffd;
    }
    else if (param_3 == 0)
    {
        local_18 = -0x7fffbffd;
    }
    else
    {
        ExceptionList = &local_10;
        FUN_0068d950(*(undefined4 *)(param_1 + 0x14));
        local_8 = 0;
        if (*(int *)(param_1 + 0xc) == 0)
        {
            iVar1 = FUN_0068daa0();
            if ((iVar1 == 0) && (*(char *)(param_1 + 0x19) == '\0'))
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                local_18 = -0x7ffbfddc;
            }
            else
            {
                local_18 = (**(code **)(*(int *)(param_1 + -0xc) + 0x28))(param_2);
                if (local_18 < 0)
                {
                    (**(code **)(*(int *)(param_1 + -0xc) + 0x2c))();
                    local_8 = 0xffffffff;
                    FUN_0068d9a0();
                }
                else
                {
                    local_18 = (**(code **)(*(int *)(param_1 + -0xc) + 0x20))(param_3);
                    if (local_18 == 0)
                    {
                        *(int *)(param_1 + 0xc) = param_2;
                        (**(code **)(**(int **)(param_1 + 0xc) + 4))(
                            *(undefined4 *)(param_1 + 0xc));
                        local_18 = (**(code **)(*(int *)(param_1 + -0xc) + 0x24))(param_3);
                        if ((-1 < local_18) &&
                            (local_18 = (**(code **)(*(int *)(param_1 + -0xc) + 0x30))(param_2),
                             -1 < local_18))
                        {
                            local_8 = 0xffffffff;
                            FUN_0068d9a0();
                            ExceptionList = local_10;
                            return 0;
                        }
                        (**(code **)(**(int **)(param_1 + 0xc) + 8))(
                            *(undefined4 *)(param_1 + 0xc));
                        *(undefined4 *)(param_1 + 0xc) = 0;
                        (**(code **)(*(int *)(param_1 + -0xc) + 0x2c))();
                        local_8 = 0xffffffff;
                        FUN_0068d9a0();
                    }
                    else
                    {
                        (**(code **)(*(int *)(param_1 + -0xc) + 0x2c))();
                        if (((-1 < local_18) || (local_18 == -0x7fffbffb)) ||
                            (local_18 == -0x7ff8ffa9))
                        {
                            local_18 = -0x7ffbfdd6;
                        }
                        local_8 = 0xffffffff;
                        FUN_0068d9a0();
                    }
                }
            }
        }
        else
        {
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            local_18 = -0x7ffbfdfc;
        }
    }
    ExceptionList = local_10;
    return local_18;
}
