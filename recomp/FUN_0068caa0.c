// ============================================
// Address:  0x0068caa0
// Original: FUN_0068caa0
// Status:   unreviewed
// ============================================

undefined4 FUN_0068caa0(int *param_1, int param_2)

{
    bool bVar1;
    undefined4 uVar2;
    int iVar3;
    int *local_20;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f76a;
    local_10  = ExceptionList;
    if (param_2 == 0)
    {
        uVar2 = 0x80004003;
    }
    else
    {
        bVar1 = false;
        if (param_1 == (int *)0xc)
        {
            local_20 = (int *)0x0;
        }
        else
        {
            local_20 = param_1 + 1;
        }
        ExceptionList = &local_10;
        FUN_0068d950(local_20);
        local_8 = 0;
        FUN_0068dd10(param_2);
        if (param_1[10] != 0)
        {
            FUN_0068cd10();
        }
        iVar3 = FUN_0068dc80();
        if ((param_1[0x12] != 0) && (iVar3 == param_1[0xc]))
        {
            (**(code **)(param_1[-3] + 0x10))();
            param_1[0x12] = 0;
            bVar1         = true;
        }
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        if (param_1[0x13] != 0)
        {
            (**(code **)(*(int *)param_1[0x13] + 0xc))(param_1[0x13]);
        }
        if (bVar1)
        {
            (**(code **)(*param_1 + 8))(param_1);
        }
        uVar2 = 0;
    }
    ExceptionList = local_10;
    return uVar2;
}
