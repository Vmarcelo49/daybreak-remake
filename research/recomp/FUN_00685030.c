// ============================================
// Address:  0x00685030
// Original: FUN_00685030
// Status:   unreviewed
// ============================================

uint FUN_00685030(void)

{
    uint uVar1;

    uVar1 = __ftol();
    if (0x3ff < (int)uVar1)
    {
        return 0x3ff;
    }
    return uVar1 & ((int)uVar1 < 0) - 1;
}
