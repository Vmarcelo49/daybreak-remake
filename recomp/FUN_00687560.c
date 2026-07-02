// ============================================
// Address:  0x00687560
// Original: FUN_00687560
// Status:   unreviewed
// ============================================

undefined4 FUN_00687560(int param_1, int *param_2)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f3fc;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x24));
    local_8 = 0;
    if (param_2 != (int *)0x0)
    {
        (**(code **)(*param_2 + 4))(param_2);
    }
    if (*(int *)(param_1 + 8) != 0)
    {
        (**(code **)(**(int **)(param_1 + 8) + 8))(*(undefined4 *)(param_1 + 8));
    }
    *(int **)(param_1 + 8) = param_2;
    local_8                = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
}
