// ============================================
// Address:  0x00410820
// Original: FUN_00410820
// Status:   unreviewed
// ============================================

int __fastcall FUN_00410820(int *param_1)

{
    int iVar1;
    uint local_8;

    local_8 = (uint)param_1[1] >> 1;
    iVar1   = local_8 * -2;
    if (*(uint *)(*param_1 + 8) <= local_8)
    {
        local_8 = local_8 - *(int *)(*param_1 + 8);
    }
    return *(int *)(*(int *)(*param_1 + 4) + local_8 * 4) + (param_1[1] + iVar1) * 8;
}
