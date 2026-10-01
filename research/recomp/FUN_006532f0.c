// ============================================
// Address:  0x006532f0
// Original: FUN_006532f0
// Status:   unreviewed
// ============================================

undefined4 *FUN_006532f0(undefined4 *param_1, undefined4 param_2)

{
    char cVar1;
    int *piVar2;
    void *pvVar3;
    undefined4 uVar4;
    int local_30;
    undefined4 local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ecb6;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00425ac0();
    piVar2  = (int *)FUN_00654280(&local_14);
    pvVar3  = operator_new(0x1c);
    local_8 = 0;
    if (pvVar3 == (void *)0x0)
    {
        local_30 = 0;
    }
    else
    {
        local_30 = FUN_006628f0();
    }
    local_8 = 0xffffffff;
    *piVar2 = local_30;
    cVar1   = FUN_00662d10(param_2);
    if (cVar1 == '\0')
    {
        if (*piVar2 == 0)
        {
            uVar4 = 0;
        }
        else
        {
            uVar4 = FUN_00653b00(1);
        }
        FUN_0065a7f0(local_14);
        FUN_00653ae0(uVar4);
        FUN_00654170(0);
    }
    else
    {
        *param_1 = local_14;
    }
    ExceptionList = local_10;
    return param_1;
}
