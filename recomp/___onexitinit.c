// ============================================
// Address:  0x0066c81b
// Original: ___onexitinit
// Status:   unreviewed
// ============================================

/* Library Function - Single Match
    ___onexitinit

   Library: Visual Studio 2003 Release */

undefined4 ___onexitinit(void)

{
    DAT_006d8ce8 = _malloc(0x80);
    if (DAT_006d8ce8 == (undefined4 *)0x0)
    {
        return 0x18;
    }
    *DAT_006d8ce8 = 0;
    DAT_006d8ce4  = DAT_006d8ce8;
    return 0;
}
