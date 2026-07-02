// ============================================
// Address:  0x00642060
// Original: FUN_00642060
// Status:   unreviewed
// ============================================

void __fastcall FUN_00642060(int param_1)

{
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        *(undefined4 *)(param_1 + 0x5f0 + local_8 * 0x18) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x6b8);
        *(undefined4 *)(param_1 + 0x5f4 + local_8 * 0x18) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x6bc);
        *(undefined1 *)(param_1 + 0x5f8 + local_8 * 0x18) =
            *(undefined1 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x79c);
        *(int *)(param_1 + 0x5ec + local_8 * 0x18) = local_8;
        *(undefined4 *)(param_1 + 0x650 + local_8 * 0x10) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0xa0);
        *(int *)(param_1 + 0x64c + local_8 * 0x10) = local_8;
        *(undefined2 *)(param_1 + 0x400 + local_8 * 0x10) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x7ac);
        *(int *)(param_1 + 0x3fc + local_8 * 0x10) = local_8;
        *(undefined4 *)(param_1 + 0x690 + local_8 * 0x10) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x300);
        *(int *)(param_1 + 0x68c + local_8 * 0x10) = local_8;
        *(undefined4 *)(param_1 + 0x6d0 + local_8 * 0x10) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x304);
        *(int *)(param_1 + 0x6cc + local_8 * 0x10)        = local_8;
        *(undefined1 *)(param_1 + 0x2dc + local_8 * 0x20) = (undefined1)local_8;
        *(undefined4 *)(param_1 + 0x2e0 + local_8 * 0x20) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x2c);
        *(undefined4 *)(param_1 + 0x2e4 + local_8 * 0x20) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x30);
        *(undefined4 *)(param_1 + 0x2e8 + local_8 * 0x20) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x34);
        *(undefined4 *)(param_1 + 0x2f0 + local_8 * 0x20) =
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x2d8);
        for (local_c = 0; local_c < 9; local_c = local_c + 1)
        {
            *(undefined1 *)(param_1 + local_8 * 0x6c + 0x43c + local_c * 0xc) = (undefined1)local_8;
            *(undefined1 *)(param_1 + local_8 * 0x6c + 0x43d + local_c * 0xc) = (undefined1)local_c;
            *(undefined2 *)(param_1 + local_8 * 0x6c + 0x43e + local_c * 0xc) =
                *(undefined2 *)(*(int *)(param_1 + 0x129c + local_8 * 4) + 0x7dc + local_c * 4);
        }
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
    {
        for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1)
        {
            *(undefined4 *)(param_1 + local_10 * 0x1c + 0x35c + local_14 * 4) =
                *(undefined4 *)(*(int *)(param_1 + 0x129c + local_14 * 4) + 0x7a4);
        }
        if (*(char *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x318) == '\0')
        {
            *(undefined2 *)(param_1 + 0x36c + local_10 * 0x1c) =
                *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x838);
        }
        else if (*(char *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x318) == '\x02')
        {
            *(undefined2 *)(param_1 + 0x36c + local_10 * 0x1c) =
                *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x840);
        }
        else
        {
            *(undefined2 *)(param_1 + 0x36c + local_10 * 0x1c) =
                *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x83c);
        }
        *(undefined2 *)(param_1 + 0x3cc + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x834);
        *(undefined2 *)(param_1 + 0x76c + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x684);
        *(short *)(param_1 + 0x79c + local_10 * 0xc) =
            (short)*(char *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x310);
        *(undefined2 *)(param_1 + 0x70c + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x6dc);
        *(undefined2 *)(param_1 + 0x70e + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x720);
        *(undefined2 *)(param_1 + 0x73c + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x724);
        *(undefined2 *)(param_1 + 0x73e + local_10 * 0xc) =
            *(undefined2 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x728);
    }
    return;
}
