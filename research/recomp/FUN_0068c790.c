// ============================================
// Address:  0x0068c790
// Original: FUN_0068c790
// Status:   unreviewed
// ============================================

undefined4 FUN_0068c790(int param_1, undefined4 *param_2, undefined4 *param_3)

{
    undefined4 uVar1;
    int iVar2;
    int local_28;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f746;
    local_10  = ExceptionList;
    if (param_2 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else if (param_3 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        if (param_1 == 0xc)
        {
            local_28 = 0;
        }
        else
        {
            local_28 = param_1 + 4;
        }
        ExceptionList = &local_10;
        FUN_0068d950(local_28);
        local_8 = 0;
        _memset(param_3, 0, 0x10);
        if (param_2[2] == 1)
        {
            if (*(int *)(param_1 + 0x44) == 0)
            {
                iVar2 = FUN_0068dc80();
                if (*(int *)(param_1 + 0x30) == iVar2)
                {
                    *(undefined4 *)(param_1 + 0x34) = param_2[1];
                    param_3[1]                      = *(undefined4 *)(param_1 + 0x34);
                    *(undefined4 *)(param_1 + 0x2c) = *param_2;
                    *param_3                        = *(undefined4 *)(param_1 + 0x2c);
                    *(undefined4 *)(param_1 + 0x38) = param_2[2];
                    param_3[2]                      = *(undefined4 *)(param_1 + 0x38);
                    *(undefined4 *)(param_1 + 0x3c) = param_2[3];
                    param_3[3]                      = *(undefined4 *)(param_1 + 0x3c);
                    *(undefined4 *)(param_1 + 0x40) = 1;
                    local_8                         = 0xffffffff;
                    FUN_0068d9a0();
                    uVar1 = 0;
                }
                else
                {
                    local_8 = 0xffffffff;
                    FUN_0068d9a0();
                    uVar1 = 0x80040210;
                }
            }
            else
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                uVar1 = 0x8004020f;
            }
        }
        else
        {
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0x8004020e;
        }
    }
    ExceptionList = local_10;
    return uVar1;
}
