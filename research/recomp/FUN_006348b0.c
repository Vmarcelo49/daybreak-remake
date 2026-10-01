// ============================================
// Address:  0x006348b0
// Original: FUN_006348b0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006348b0(int param_1)

{
    uint local_8;

    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        *(undefined4 *)(param_1 + 0x129c + local_8 * 4) =
            *(undefined4 *)(&DAT_006cfae0 + local_8 * 4);
        FUN_00642c50(*(undefined4 *)(param_1 + 0x129c + local_8 * 4));
    }
    return;
}
