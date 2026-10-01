// ============================================
// Address:  0x00437130
// Original: FUN_00437130
// Status:   unreviewed
// ============================================

void __thiscall FUN_00437130(int param_1, undefined4 param_2)

{
    undefined4 uVar1;
    undefined4 local_14;

    if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U)
    {
        FUN_00437370(1);
    }
    if (*(int *)(param_1 + 0xc) == 0)
    {
        local_14 = *(int *)(param_1 + 8);
    }
    else
    {
        local_14 = *(int *)(param_1 + 0xc);
    }
    local_14 = local_14 + -1;
    if (*(int *)(*(int *)(param_1 + 4) + local_14 * 4) == 0)
    {
        uVar1                                                 = FUN_00437630(1);
        *(undefined4 *)(*(int *)(param_1 + 4) + local_14 * 4) = uVar1;
    }
    FUN_00437650(*(undefined4 *)(*(int *)(param_1 + 4) + local_14 * 4), param_2);
    *(int *)(param_1 + 0xc)  = local_14;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    return;
}
