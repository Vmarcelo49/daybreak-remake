// ============================================
// Address:  0x006875f0
// Original: FUN_006875f0
// Status:   unreviewed
// ============================================

undefined4 FUN_006875f0(int param_1, undefined4 *param_2)

{
    undefined4 uVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f40e;
    local_10  = ExceptionList;
    if (param_2 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        ExceptionList = &local_10;
        FUN_0068d950(*(undefined4 *)(param_1 + 0x24));
        local_8 = 0;
        if (*(int *)(param_1 + 8) != 0)
        {
            (**(code **)(**(int **)(param_1 + 8) + 4))(*(undefined4 *)(param_1 + 8));
        }
        *param_2 = *(undefined4 *)(param_1 + 8);
        local_8  = 0xffffffff;
        FUN_0068d9a0();
        uVar1 = 0;
    }
    ExceptionList = local_10;
    return uVar1;
}
