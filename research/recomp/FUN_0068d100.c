// ============================================
// Address:  0x0068d100
// Original: FUN_0068d100
// Status:   unreviewed
// ============================================

undefined4 FUN_0068d100(int param_1, undefined4 *param_2, undefined4 *param_3)

{
    undefined4 uVar1;
    int iVar2;
    int local_54;
    _SYSTEM_INFO local_40;
    int local_1c;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f7d9;
    local_10  = ExceptionList;
    if (param_3 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        if (param_1 == 0xc)
        {
            local_54 = 0;
        }
        else
        {
            local_54 = param_1 + 4;
        }
        ExceptionList = &local_10;
        FUN_0068d950(local_54);
        local_8 = 0;
        _memset(param_3, 0, 0x10);
        GetSystemInfo(&local_40);
        if ((param_2[2] == 0) || ((param_2[2] - 1 & local_40.dwAllocationGranularity) != 0))
        {
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0x8004020e;
        }
        else if (*(int *)(param_1 + 0x44) == 1)
        {
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0x8004020f;
        }
        else
        {
            iVar2 = FUN_0068dc80();
            if (iVar2 < *(int *)(param_1 + 0x30))
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                uVar1 = 0x80040210;
            }
            else
            {
                local_1c = param_2[1] + param_2[3];
                local_14 = local_1c % (int)param_2[2];
                if (local_14 != 0)
                {
                    local_1c = (local_1c - local_14) + param_2[2];
                }
                *(int *)(param_1 + 0x34)        = local_1c - param_2[3];
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
        }
    }
    ExceptionList = local_10;
    return uVar1;
}
