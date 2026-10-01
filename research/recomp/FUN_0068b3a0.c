// ============================================
// Address:  0x0068b3a0
// Original: FUN_0068b3a0
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b3a0(int param_1, uint param_2, void *param_3)

{
    size_t local_38;
    size_t local_34;
    undefined4 local_30;
    uint local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    if (param_2 != 0)
    {
        if (param_3 == (void *)0x0)
        {
            return 0x80004003;
        }
        if (param_2 < 0x30)
        {
            local_38 = param_2;
        }
        else
        {
            local_38 = 0x30;
        }
        local_34 = local_38;
        local_2c = *(uint *)(param_1 + 4) & 0xffffffdf;
        local_30 = *(undefined4 *)(param_1 + 8);
        local_c  = *(undefined4 *)(param_1 + 0xc);
        local_8  = *(undefined4 *)(param_1 + 0x14);
        local_28 = *(undefined4 *)(param_1 + 0x10);
        local_24 = *(undefined4 *)(param_1 + 0x20);
        local_20 = *(undefined4 *)(param_1 + 0x24);
        local_1c = *(undefined4 *)(param_1 + 0x28);
        local_18 = *(undefined4 *)(param_1 + 0x2c);
        local_14 = *(undefined4 *)(param_1 + 0x40);
        if ((*(uint *)(param_1 + 4) & 8) == 0)
        {
            local_10 = 0;
        }
        else
        {
            local_10 = *(undefined4 *)(param_1 + 0x3c);
        }
        _memcpy(param_3, &local_34, local_38);
    }
    return 0;
}
