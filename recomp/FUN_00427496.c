// ============================================
// Address:  0x00427496
// Original: FUN_00427496
// Status:   unreviewed
// ============================================

void FUN_00427496(void)

{
    int unaff_EBP;

    if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8))
    {
        std::allocator<std::_Container_proxy>::destroy(
            *(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
            *(_Container_proxy **)(unaff_EBP + -0x14));
        FUN_0042748d();
        return;
    }
    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(0, 0);
}
