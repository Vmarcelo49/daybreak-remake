// ============================================
// Address:  0x00422160
// Original: FUN_00422160
// Status:   unreviewed
// ============================================

void __fastcall FUN_00422160(int param_1)

{
    undefined1 local_10[8];
    undefined4 local_8;

    if (DAT_006cfdb0 == '\x01')
    {
        FUN_00423b80();
        local_8 = *(undefined4 *)(param_1 + 8);
        FUN_00415d30(0, local_10, 0, 8);
    }
    *(undefined4 *)(param_1 + 0x7a4) = 10000;
    *(undefined4 *)(param_1 + 0x840) = *(undefined4 *)(param_1 + 0x328);
    *(undefined1 *)(param_1 + 0x846) = 1;
    *(undefined1 *)(param_1 + 0x334) = 0xfc;
    return;
}
