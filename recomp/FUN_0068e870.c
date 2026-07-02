// ============================================
// Address:  0x0068e870
// Original: FUN_0068e870
// Status:   unreviewed
// ============================================

undefined4 FUN_0068e870(int param_1)

{
    int iVar1;
    int *piVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f8f9;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x70);
    local_8 = 0;
    if (*(int *)(param_1 + 8) == 0)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    else
    {
        iVar1 = FUN_0068da80();
        if (iVar1 == 0)
        {
            *(undefined4 *)(param_1 + 8) = 0;
            local_8                      = 0xffffffff;
            FUN_0068d9a0();
        }
        else
        {
            FUN_00687cf0(param_1);
            iVar1 = FUN_00691b50();
            if (iVar1 != 0)
            {
                piVar2 = (int *)FUN_00691b50();
                (**(code **)(*piVar2 + 0x18))(piVar2);
            }
            FUN_0068fde0(1);
            (**(code **)(*(int *)(param_1 + -0xc) + 0x80))();
            (**(code **)(*(int *)(param_1 + -0xc) + 0x28))(0);
            (**(code **)(*(int *)(param_1 + -0xc) + 100))();
            (**(code **)(*(int *)(param_1 + -0xc) + 0x6c))();
            FUN_00691bf0();
            FUN_0068e710();
            *(undefined4 *)(param_1 + 0x54) = 0;
            local_8                         = 0xffffffff;
            FUN_0068d9a0();
        }
    }
    ExceptionList = local_10;
    return 0;
}
