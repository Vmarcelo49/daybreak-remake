// ============================================
// Address:  0x006924c0
// Original: FUN_006924c0
// Status:   unreviewed
// ============================================

int FUN_006924c0(ushort *param_1, ushort *param_2)

{
    ushort uVar1;

    do
    {
        if (*param_1 != *param_2)
        {
            return (uint)*param_1 - (uint)*param_2;
        }
        uVar1   = *param_1;
        param_1 = param_1 + 1;
    } while ((uVar1 != 0) && (uVar1 = *param_2, param_2 = param_2 + 1, uVar1 != 0));
    return 0;
}
