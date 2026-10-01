// ============================================
// Address:  0x0064fd9f
// Original: FUN_0064fd9f
// Status:   unreviewed
// ============================================

void FUN_0064fd9f(void)

{
    int unaff_EBP;

    *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 4;
    if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 0x10))
    {
        std::allocator<std::_Container_proxy>::destroy(
            *(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
            *(_Container_proxy **)(unaff_EBP + -0x14));
        FUN_0064fd9f();
        return;
    }
    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(0, 0);
}
