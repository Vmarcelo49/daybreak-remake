// ============================================
// Address:  0x0065994d
// Original: FUN_0065994d
// Status:   unreviewed
// ============================================

void FUN_0065994d(void)

{
    int unaff_EBP;

    *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 0x50;
    if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8))
    {
        std::allocator<std::_Container_proxy>::destroy(
            *(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
            *(_Container_proxy **)(unaff_EBP + -0x14));
        FUN_0065994d();
        return;
    }
    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(0, 0);
}
