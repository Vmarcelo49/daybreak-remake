// ============================================
// Address:  0x006592fd
// Original: FUN_006592fd
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_006592fd(void)

{
    int iVar1;
    int unaff_EBP;

    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    iVar1                           = FUN_00659540();
    *(int *)(unaff_EBP + 0xc)       = iVar1 + *(int *)(unaff_EBP + 0xc);
    if (*(int *)(*(int *)(unaff_EBP + -0x7c) + 4) != 0)
    {
        FUN_00658e10(*(undefined4 *)(*(int *)(unaff_EBP + -0x7c) + 4),
                     *(undefined4 *)(*(int *)(unaff_EBP + -0x7c) + 8));
        deallocate(*(undefined4 *)(*(int *)(unaff_EBP + -0x7c) + 4),
                   (*(int *)(*(int *)(unaff_EBP + -0x7c) + 0xc) -
                    *(int *)(*(int *)(unaff_EBP + -0x7c) + 4)) /
                       0x50);
    }
    *(int *)(*(int *)(unaff_EBP + -0x7c) + 0xc) =
        *(int *)(unaff_EBP + -0x6c) * 0x50 + *(int *)(unaff_EBP + -0x74);
    *(int *)(*(int *)(unaff_EBP + -0x7c) + 8) =
        *(int *)(unaff_EBP + 0xc) * 0x50 + *(int *)(unaff_EBP + -0x74);
    *(undefined4 *)(*(int *)(unaff_EBP + -0x7c) + 4) = *(undefined4 *)(unaff_EBP + -0x74);
    ExceptionList                                    = *(void **)(unaff_EBP + -0xc);
    return;
}
