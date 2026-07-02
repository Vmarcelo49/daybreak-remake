// ============================================
// Address:  0x006402f0
// Original: FUN_006402f0
// Status:   unreviewed
// ============================================

int __fastcall FUN_006402f0(int *param_1)

{
    int iVar1;
    uint local_8;

    local_8 = param_1[1];
    iVar1   = param_1[1] - local_8;
    if (*(uint *)(*param_1 + 8) <= local_8)
    {
        local_8 = local_8 - *(int *)(*param_1 + 8);
    }
    return iVar1 * 0xdc + *(int *)(*(int *)(*param_1 + 4) + local_8 * 4);
}
