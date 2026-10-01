// ============================================
// Address:  0x00659a48
// Original: FUN_00659a48
// Status:   unreviewed
// ============================================

void FUN_00659a48(void)

{
    int unaff_EBP;

    if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 0x10))
    {
        std::allocator<std::_Container_proxy>::destroy(
            *(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
            *(_Container_proxy **)(unaff_EBP + -0x14));
        FUN_00659a3f();
        return;
    }
    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(0, 0);
}
