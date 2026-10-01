// ============================================
// Address:  0x00691570
// Original: FUN_00691570
// Status:   unreviewed
// ============================================

undefined4 FUN_00691570(int param_1, undefined4 *param_2)

{
    undefined4 uVar1;
    int iVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069fa9a;
    local_10  = ExceptionList;
    if (param_2 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        ExceptionList = &local_10;
        FUN_0068d950(param_1 + -100);
        local_8 = 0;
        if (*(int *)(param_1 + -200) == 0)
        {
            *param_2 = 0;
            local_8  = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0;
        }
        else
        {
            if (*(int *)(param_1 + 0x44) < 2)
            {
                *param_2 = 0;
            }
            else
            {
                iVar2    = *(int *)(param_1 + 0x44) + -1;
                uVar1    = __alldiv(*(undefined4 *)(param_1 + 0x48),
                                    *(undefined4 *)(param_1 + 0x4c),
                                    iVar2,
                                    iVar2 >> 0x1f);
                *param_2 = uVar1;
            }
            local_8 = 0xffffffff;
            FUN_0068d9a0();
            uVar1 = 0;
        }
    }
    ExceptionList = local_10;
    return uVar1;
}
