// ============================================
// Address:  0x00664b68
// Original: FUN_00664b68
// Status:   unreviewed
// ============================================

undefined4 FUN_00664b68(void)

{
    undefined1 *puVar1;
    int unaff_EBP;

    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    puVar1        = (undefined1 *)FUN_00663ce0(*(undefined4 *)(unaff_EBP + -0x18));
    *puVar1       = 1;
    puVar1        = (undefined1 *)FUN_00663560(*(undefined4 *)(unaff_EBP + -0x18));
    *puVar1       = 0;
    ExceptionList = *(void **)(unaff_EBP + -0xc);
    return *(undefined4 *)(unaff_EBP + -0x18);
}
