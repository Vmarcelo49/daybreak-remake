// ============================================
// Address:  0x0069a78d
// Original: FUN_0069a78d
// Status:   unreviewed
// ============================================

void FUN_0069a78d(undefined4 param_1, undefined4 param_2, int param_3)

{
    uint in_EAX;
    uint extraout_ECX;
    uint uVar1;
    short in_FPUControlWord;

    uVar1 = in_EAX;
    if (in_FPUControlWord != 0x27f)
    {
        in_EAX = FUN_00670295();
        uVar1  = extraout_ECX;
    }
    if ((uVar1 & 0x7ff00000) != 0x7ff00000)
    {
        /* WARNING: Subroutine does not return */
        __fload_withFB();
    }
    if ((in_EAX & 0xfffff) == 0 && param_3 == 0)
    {
        /* WARNING: Subroutine does not return */
        __fload_withFB();
    }
    /* WARNING: Subroutine does not return */
    __fload_withFB();
}
