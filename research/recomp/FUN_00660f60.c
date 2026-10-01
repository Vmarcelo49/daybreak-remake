// ============================================
// Address:  0x00660f60
// Original: FUN_00660f60
// Status:   unreviewed
// ============================================

int __fastcall FUN_00660f60(int param_1)

{
    if (*(char *)(param_1 + 0xa0d) == '\0')
    {
        param_1 = 0;
    }
    else
    {
        *(undefined1 *)(param_1 + 0xa0d) = 0;
        param_1                          = param_1 + 8;
    }
    return param_1;
}
