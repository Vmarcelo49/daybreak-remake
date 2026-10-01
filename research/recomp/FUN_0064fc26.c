// ============================================
// Address:  0x0064fc26
// Original: FUN_0064fc26
// Status:   unreviewed
// ============================================

void FUN_0064fc26(void)

{
    int unaff_EBP;

    if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8))
    {
        std::allocator<std::_Container_proxy>::destroy(
            *(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
            *(_Container_proxy **)(unaff_EBP + -0x14));
        FUN_0064fc1d();
        return;
    }
    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(0, 0);
}
