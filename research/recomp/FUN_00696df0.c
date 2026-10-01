// ============================================
// Address:  0x00696df0
// Original: FUN_00696df0
// Status:   unreviewed
// ============================================

int __thiscall FUN_00696df0(undefined4 param_1, int param_2)

{
    int iVar1;

    if (*(int *)(param_2 + 4) == 0)
    {
        iVar1 = -0x7ffbfdcc;
    }
    else
    {
        iVar1 = (**(code **)(**(int **)(param_2 + 4) + 0xc))(param_2 + -0xc, param_1);
        if (-1 < iVar1)
        {
            *(undefined4 *)(param_2 + 4) = 0;
            iVar1                        = 0;
        }
    }
    return iVar1;
}
