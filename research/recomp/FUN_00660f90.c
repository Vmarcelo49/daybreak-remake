// ============================================
// Address:  0x00660f90
// Original: FUN_00660f90
// Status:   unreviewed
// ============================================

int __fastcall FUN_00660f90(int param_1)

{
    if (*(char *)(param_1 + 0xa0e) == '\0')
    {
        param_1 = 0;
    }
    else
    {
        *(undefined1 *)(param_1 + 0xa0e) = 0;
        param_1                          = param_1 + 0x808;
    }
    return param_1;
}
