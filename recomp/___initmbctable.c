// ============================================
// Address:  0x00672143
// Original: ___initmbctable
// Status:   unreviewed
// ============================================

/* Library Function - Single Match
    ___initmbctable

   Library: Visual Studio 2003 Release */

undefined4 ___initmbctable(void)

{
    if (DAT_006d8cec == 0)
    {
        __setmbcp(-3);
        DAT_006d8cec = 1;
    }
    return 0;
}
