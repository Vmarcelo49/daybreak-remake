// ============================================
// Address:  0x00661320
// Original: FUN_00661320
// Status:   unreviewed
// ============================================

bool __fastcall FUN_00661320(int param_1)

{
    bool bVar1;

    bVar1 = *(char *)(param_1 + 0xa0c) != '\0';
    if (bVar1)
    {
        *(undefined1 *)(param_1 + 0xa0c) = 0;
    }
    return bVar1;
}
