// ============================================
// Address:  0x0064e9e0
// Original: FUN_0064e9e0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_0064e9e0(int param_1, undefined4 param_2, undefined4 param_3)

{
    int iVar1;
    int local_8;

    local_8 = 0;
    while (true)
    {
        if (1 < local_8)
        {
            return 1;
        }
        iVar1 = (**(code **)(**(int **)(param_1 + 0xc + local_8 * 4) + 0x4c))(
            *(undefined4 *)(param_1 + 0xc + local_8 * 4), param_2, param_3);
        if (iVar1 < 0)
            break;
        local_8 = local_8 + 1;
    }
    return 0;
}
