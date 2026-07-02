// ============================================
// Address:  0x00422900
// Original: FUN_00422900
// Status:   unreviewed
// ============================================

void __fastcall FUN_00422900(int param_1)

{
    undefined1 local_10[8];
    undefined4 local_8;

    if (DAT_006cfdb0 == '\x01')
    {
        FUN_00423ea0();
        local_8 = *(undefined4 *)(param_1 + 8);
        FUN_00415d30(0, local_10, 0, 8);
    }
    *(undefined1 *)(param_1 + 0xaec8) = 1;
    return;
}
