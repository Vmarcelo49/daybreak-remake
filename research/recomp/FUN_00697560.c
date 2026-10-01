// ============================================
// Address:  0x00697560
// Original: FUN_00697560
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00697560(int param_1, int *param_2)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fe29;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 8);
    local_8 = 0;
    if (param_2 != (int *)0x0)
    {
        (**(code **)(*param_2 + 4))(param_2);
    }
    if (*(int *)(param_1 + 0x60) != 0)
    {
        if (*(int *)(param_1 + 0x54) != 0)
        {
            (**(code **)(**(int **)(param_1 + 0x60) + 0x18))(*(undefined4 *)(param_1 + 0x60),
                                                             *(undefined4 *)(param_1 + 0x54));
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        (**(code **)(**(int **)(param_1 + 0x60) + 8))(*(undefined4 *)(param_1 + 0x60));
    }
    *(int **)(param_1 + 0x60) = param_2;
    FUN_00697630();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
}
