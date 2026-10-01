// ============================================
// Address:  0x00692520
// Original: FUN_00692520
// Status:   unreviewed
// ============================================

int FUN_00692520(ushort *param_1, ushort *param_2)

{
    ushort uVar1;
    ushort local_c;
    ushort local_8;

    while (true)
    {
        local_8 = *param_1;
        local_c = *param_2;
        if ((0x40 < local_8) && (local_8 < 0x5b))
        {
            local_8 = local_8 + 0x20;
        }
        if ((0x40 < local_c) && (local_c < 0x5b))
        {
            local_c = local_c + 0x20;
        }
        if (local_8 != local_c)
            break;
        uVar1   = *param_1;
        param_1 = param_1 + 1;
        if ((uVar1 == 0) || (uVar1 = *param_2, param_2 = param_2 + 1, uVar1 == 0))
        {
            return 0;
        }
    }
    return (uint)local_8 - (uint)local_c;
}
