// ============================================
// Address:  0x0064be90
// Original: FUN_0064be90
// Status:   unreviewed
// ============================================

void __fastcall FUN_0064be90(int param_1)

{
    undefined4 local_c;
    undefined4 local_8;

    local_8                           = 0;
    *(undefined4 *)(param_1 + 0x5304) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x5300) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x52fc) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x52f8) = 0xffffffff;
    for (local_c = 0; local_c < 8; local_c = local_c + 1)
    {
        if (-1 < *(char *)(param_1 + local_c + 0x55c1))
        {
            if ((*(int *)(param_1 + 0x55ac) < local_8) || (3 < local_8))
            {
                *(undefined1 *)(param_1 + local_c + 0x55c1) = 0xff;
            }
            else
            {
                *(undefined1 *)(param_1 + local_c + 0x55c1) = (undefined1)local_8;
                *(int *)(param_1 + 0x52f8 + local_8 * 4)    = local_c;
                local_8                                     = local_8 + 1;
            }
        }
    }
    FUN_0064bf60();
    return;
}
