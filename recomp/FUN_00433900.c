// ============================================
// Address:  0x00433900
// Original: FUN_00433900
// Status:   unreviewed
// ============================================

void __thiscall FUN_00433900(int param_1, undefined4 param_2)

{
    uint uVar1;
    undefined4 uVar2;
    uint uVar3;
    undefined4 local_14;

    if ((*(uint *)(param_1 + 0xc) % 4 == 0) &&
        (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 4U >> 2))
    {
        FUN_00432c10(1);
    }
    if (*(int *)(param_1 + 0xc) == 0)
    {
        local_14 = *(int *)(param_1 + 8) << 2;
    }
    else
    {
        local_14 = *(int *)(param_1 + 0xc);
    }
    uVar3 = local_14 - 1;
    uVar1 = uVar3 >> 2;
    if (*(int *)(*(int *)(param_1 + 4) + uVar1 * 4) == 0)
    {
        uVar2                                              = FUN_004107e0(4);
        *(undefined4 *)(*(int *)(param_1 + 4) + uVar1 * 4) = uVar2;
    }
    FUN_00432ee0(*(int *)(*(int *)(param_1 + 4) + uVar1 * 4) + (uVar3 % 4) * 4, param_2);
    *(uint *)(param_1 + 0xc) = uVar3;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    return;
}
