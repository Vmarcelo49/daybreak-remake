// ============================================
// Address:  0x00659d80
// Original: FUN_00659d80
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00659d80(int param_1, undefined4 *param_2, undefined4 param_3)

{
    char cVar1;
    int *piVar2;
    void *pvVar3;
    int local_30;
    undefined4 local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ef51;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00425ac0();
    piVar2  = (int *)FUN_0065a8b0(&local_14);
    pvVar3  = operator_new(0xc);
    local_8 = 0;
    if (pvVar3 == (void *)0x0)
    {
        local_30 = 0;
    }
    else
    {
        local_30 = FUN_006679a0();
    }
    local_8 = 0xffffffff;
    *piVar2 = local_30;
    cVar1   = FUN_00667c00(param_3);
    if (cVar1 == '\0')
    {
        if ((int *)*piVar2 != (int *)0x0)
        {
            (**(code **)(*(int *)*piVar2 + 4))(1);
        }
        FUN_0065a7f0(local_14);
        FUN_00654170(0);
    }
    else
    {
        FUN_0065a390((*(int *)(param_1 + 1000) * *(int *)(param_1 + 0x3ec)) / 10000 + -10000);
        *param_2 = local_14;
    }
    ExceptionList = local_10;
    return param_2;
}
