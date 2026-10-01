// ============================================
// Address:  0x0068d2d0
// Original: FUN_0068d2d0
// Status:   unreviewed
// ============================================

int __fastcall FUN_0068d2d0(int param_1)

{
    int iVar1;
    LPVOID pvVar2;
    void *pvVar3;
    int local_50;
    int local_4c;
    int local_24;
    int local_20;
    int local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    int local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f7f6;
    local_10  = ExceptionList;
    if (param_1 == 0)
    {
        local_4c = 0;
    }
    else
    {
        local_4c = param_1 + 0x10;
    }
    ExceptionList = &local_10;
    FUN_0068d950(local_4c);
    local_8  = 0;
    iVar1    = FUN_0068cf80();
    local_24 = iVar1;
    if (iVar1 < 0)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    else if (iVar1 == 1)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        iVar1 = 0;
    }
    else
    {
        if (*(int *)(param_1 + 0x60) != 0)
        {
            FUN_0068d500();
        }
        local_20 = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x48);
        if ((1 < *(int *)(param_1 + 0x44)) &&
            (iVar1 = local_20 % *(int *)(param_1 + 0x44), iVar1 != 0))
        {
            local_20 = (*(int *)(param_1 + 0x44) - iVar1) + local_20;
        }
        pvVar2 = VirtualAlloc((LPVOID)0x0, *(int *)(param_1 + 0x38) * local_20, 0x1000, 4);
        *(LPVOID *)(param_1 + 0x60) = pvVar2;
        if (*(int *)(param_1 + 0x60) == 0)
        {
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            iVar1 = -0x7ff8fff2;
        }
        else
        {
            local_18 = *(int *)(param_1 + 0x60);
            while (*(int *)(param_1 + 0x3c) < *(int *)(param_1 + 0x38))
            {
                pvVar3        = operator_new(0x48);
                local_8._0_1_ = 1;
                if (pvVar3 == (void *)0x0)
                {
                    local_50 = 0;
                }
                else
                {
                    local_50 = FUN_0068adc0(0,
                                            param_1,
                                            &local_24,
                                            local_18 + *(int *)(param_1 + 0x48),
                                            *(undefined4 *)(param_1 + 0x40));
                }
                local_8  = (uint)local_8._1_3_ << 8;
                local_14 = local_50;
                if (local_50 == 0)
                {
                    local_8 = 0xffffffff;
                    FUN_0068d9a0();
                    ExceptionList = local_10;
                    return -0x7ff8fff2;
                }
                FUN_0068dd10(local_50);
                *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
                local_18                 = local_18 + local_20;
            }
            *(undefined4 *)(param_1 + 0x4c) = 0;
            local_8                         = 0xffffffff;
            FUN_0068d9a0();
            iVar1 = 0;
        }
    }
    ExceptionList = local_10;
    return iVar1;
}
