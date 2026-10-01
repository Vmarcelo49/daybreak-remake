// ============================================
// Address:  0x006549fb
// Original: FUN_006549fb
// Status:   unreviewed
// ============================================

void FUN_006549fb(void)

{
    int unaff_EBP;

    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(*(int *)(unaff_EBP + -0x28) + 8) =
        *(int *)(*(int *)(unaff_EBP + -0x28) + 8) + *(int *)(unaff_EBP + 0xc) * 4;
    FUN_006596b0(*(undefined4 *)(unaff_EBP + 8),
                 *(int *)(*(int *)(unaff_EBP + -0x28) + 8) + *(int *)(unaff_EBP + 0xc) * -4,
                 unaff_EBP + -0x14);
    ExceptionList = *(void **)(unaff_EBP + -0xc);
    return;
}
