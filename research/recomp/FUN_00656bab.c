// ============================================
// Address:  0x00656bab
// Original: FUN_00656bab
// Status:   unreviewed
// ============================================

void FUN_00656bab(void)

{
    int unaff_EBP;
    undefined4 *unaff_FS_OFFSET;

    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(*(int *)(unaff_EBP + -0x28) + 8) =
        *(int *)(*(int *)(unaff_EBP + -0x28) + 8) + *(int *)(unaff_EBP + 0xc) * 4;
    FUN_006596b0(*(undefined4 *)(unaff_EBP + 8),
                 *(int *)(*(int *)(unaff_EBP + -0x28) + 8) + *(int *)(unaff_EBP + 0xc) * -4,
                 unaff_EBP + -0x14);
    *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
    return;
}
