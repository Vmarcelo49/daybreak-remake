// ============================================
// Address:  0x00689d50
// Original: FUN_00689d50
// Status:   unreviewed
// ============================================

int __thiscall FUN_00689d50(undefined4 param_1, int param_2, int param_3)

{
    int iVar1;

    if (param_3 == 0)
    {
        iVar1 = -0x7fffbffd;
    }
    else
    {
        iVar1 = (**(code **)(*(int *)(param_2 + -0xc) + 0x20))(param_3, param_1);
        if (iVar1 < 0)
        {
            iVar1 = 1;
        }
    }
    return iVar1;
}
