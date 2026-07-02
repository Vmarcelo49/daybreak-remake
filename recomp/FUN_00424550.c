// ============================================
// Address:  0x00424550
// Original: FUN_00424550
// Status:   unreviewed
// ============================================

void __thiscall FUN_00424550(int param_1, undefined4 param_2)

{
    undefined4 uVar1;
    undefined4 local_c;

    if (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 1U)
    {
        FUN_00425180(1);
    }
    local_c = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
    if (*(uint *)(param_1 + 8) <= local_c)
    {
        local_c = local_c - *(int *)(param_1 + 8);
    }
    if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0)
    {
        uVar1                                                = FUN_00425440(1);
        *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar1;
    }
    FUN_00425460(*(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4), param_2);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    return;
}
