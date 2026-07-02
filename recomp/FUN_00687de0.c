// ============================================
// Address:  0x00687de0
// Original: FUN_00687de0
// Status:   unreviewed
// ============================================

int FUN_00687de0(int param_1)

{
    int iVar1;
    int *piVar2;
    int iVar3;
    int local_1c;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f49e;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(*(undefined4 *)(param_1 + 0x2c));
    local_8 = 0;
    if (*(int *)(param_1 + 8) == 0)
    {
        iVar1 = (**(code **)(*(int *)(param_1 + -0xc) + 0x18))();
        for (local_1c = 0; local_1c < iVar1; local_1c = local_1c + 1)
        {
            piVar2 = (int *)(**(code **)(*(int *)(param_1 + -0xc) + 0x1c))(local_1c);
            iVar3  = FUN_0068da80();
            if ((iVar3 != 0) && (iVar3 = (**(code **)(*piVar2 + 0x14))(), iVar3 < 0))
            {
                local_8 = 0xffffffff;
                FUN_0068d9a0();
                ExceptionList = local_10;
                return iVar3;
            }
        }
    }
    *(undefined4 *)(param_1 + 8) = 1;
    local_8                      = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
}
