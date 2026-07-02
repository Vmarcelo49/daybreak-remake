// ============================================
// Address:  0x00690360
// Original: FUN_00690360
// Status:   unreviewed
// ============================================

int FUN_00690360(int param_1, undefined4 param_2)

{
    int iVar1;
    int iVar2;
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fa76;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    iVar1         = (**(code **)(**(int **)(param_1 + 0x40) + 0x9c))(param_2);
    if (iVar1 < 0)
    {
        FUN_0068d950(*(int *)(param_1 + 0x40) + 0x7c);
        local_8 = 0;
        iVar2   = FUN_0068daa0();
        if (iVar2 == 0)
        {
            iVar2 = FUN_00691ab0();
            if (((iVar2 == 0) && (*(int *)(*(int *)(param_1 + 0x40) + 0x60) == 0)) &&
                (*(char *)(param_1 + -0x74) == '\0'))
            {
                FUN_006883f0(3, iVar1, 0);
                FUN_0068d950(*(int *)(param_1 + 0x40) + 0x94);
                local_8 = CONCAT31(local_8._1_3_, 1);
                iVar2   = FUN_00691bb0();
                if (iVar2 != 0)
                {
                    iVar2 = FUN_00691b90();
                    if (iVar2 == 0)
                    {
                        FUN_0068fae0();
                    }
                }
                local_8 = local_8 & 0xffffff00;
                FUN_0068d9a0();
                *(undefined1 *)(param_1 + -0x74) = 1;
            }
        }
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    ExceptionList = local_10;
    return iVar1;
}
