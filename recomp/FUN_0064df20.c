// ============================================
// Address:  0x0064df20
// Original: FUN_0064df20
// Status:   unreviewed
// ============================================

int __thiscall FUN_0064df20(uint *param_1, int param_2)

{
    undefined4 uVar1;
    void *pvVar2;
    uint uVar3;
    void *local_34;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069ebf1;
    local_10  = ExceptionList;
    if (*(int *)(param_2 + 0x20) == 0)
    {
        local_14 = 0;
    }
    else
    {
        ExceptionList = &local_10;
        uVar1         = (**(code **)(**(int **)(param_2 + 0x30) + 0x18))(
            *(undefined4 *)(param_2 + 0x30), DAT_006d16f8, param_2 + 0xc);
        local_14 = (**(code **)(**(int **)(param_2 + 0x30) + 0x2c))(
            *(undefined4 *)(param_2 + 0x30), 0x220, uVar1);
        if ((-1 < local_14) && (local_14 = (**(code **)(**(int **)(param_2 + 0xc) + 0x4c))(
                                    *(undefined4 *)(param_2 + 0xc), 0, param_2 + 0x38),
                                -1 < local_14))
        {
            _free(*(void **)(param_2 + 0x34));
            pvVar2                     = operator_new(*(int *)(param_2 + 0x38) * 0x14);
            *(void **)(param_2 + 0x34) = pvVar2;
            if (*(int *)(param_2 + 0x34) == 0)
            {
                local_14 = -0x7ff8fff2;
            }
            else
            {
                local_14 = (**(code **)(**(int **)(param_2 + 0xc) + 0x4c))(
                    *(undefined4 *)(param_2 + 0xc), *(undefined4 *)(param_2 + 0x34), 0);
                if ((-1 < local_14) && (uVar3 = (**(code **)(**(int **)(param_2 + 0x20) + 0x24))(
                                            *(undefined4 *)(param_2 + 0x20)),
                                        *param_1 < uVar3))
                {
                    uVar3 = (**(code **)(**(int **)(param_2 + 0x20) + 0x24))(
                        *(undefined4 *)(param_2 + 0x20));
                    *param_1 = uVar3;
                    FUN_0064edd0(param_1[1]);
                    uVar3    = *param_1;
                    local_34 = (void *)FUN_0064ee10(uVar3 << 6);
                    local_8  = 0;
                    if (local_34 == (void *)0x0)
                    {
                        local_34 = (void *)0x0;
                    }
                    else
                    {
                        _vector_constructor_iterator_(local_34, 0x40, uVar3, FUN_0068d8d0);
                    }
                    param_1[1] = (uint)local_34;
                    if (param_1[1] == 0)
                    {
                        local_14 = -0x7ff8fff2;
                    }
                }
            }
        }
    }
    ExceptionList = local_10;
    return local_14;
}
