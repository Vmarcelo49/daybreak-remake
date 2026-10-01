// ============================================
// Address:  0x0040fd00
// Original: FUN_0040fd00
// Status:   unreviewed
// ============================================

void __thiscall FUN_0040fd00(int param_1, undefined4 param_2)

{
    uint uVar1;
    undefined4 uVar2;
    undefined4 local_c;

    if (((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10)) % 2 == 0) &&
        (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 2U >> 1))
    {
        FUN_0040fe40(1);
    }
    uVar1   = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
    local_c = uVar1 >> 1;
    if (*(uint *)(param_1 + 8) <= local_c)
    {
        local_c = local_c - *(int *)(param_1 + 8);
    }
    if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0)
    {
        uVar2                                                = FUN_00410110(2);
        *(undefined4 *)(*(int *)(param_1 + 4) + local_c * 4) = uVar2;
    }
    FUN_00410130(*(int *)(*(int *)(param_1 + 4) + local_c * 4) + (uVar1 % 2) * 8, param_2);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    return;
}
