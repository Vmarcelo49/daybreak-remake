// ============================================
// Address:  0x006902a0
// Original: FUN_006902a0
// Status:   unreviewed
// ============================================

int FUN_006902a0(int param_1)

{
    int local_1c;
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fa5c;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x7c);
    local_8 = 0;
    FUN_0068d950(*(int *)(param_1 + 0xcc) + 0x94);
    local_8  = CONCAT31(local_8._1_3_, 1);
    local_1c = (**(code **)(**(int **)(param_1 + 0xcc) + 0x88))();
    if (-1 < local_1c)
    {
        local_1c = FUN_0068ab90(param_1);
    }
    local_8 = local_8 & 0xffffff00;
    FUN_0068d9a0();
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return local_1c;
}
