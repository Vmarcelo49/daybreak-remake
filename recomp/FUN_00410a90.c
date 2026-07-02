// ============================================
// Address:  0x00410a90
// Original: FUN_00410a90
// Status:   unreviewed
// ============================================

void FUN_00410a90(void)

{
    char *pcVar1;
    int unaff_EBP;
    uint uVar2;

    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    if (*(int *)(unaff_EBP + 0xc) != 0)
    {
        uVar2  = *(uint *)(unaff_EBP + 0xc);
        pcVar1 = std::basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _>::
            _Myptr(*(basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _> *
                         *)(unaff_EBP + -0x1c));
        std::char_traits<char>::copy(*(char **)(unaff_EBP + -0x14), pcVar1, uVar2);
    }
    std::basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _>::_Tidy(
        *(basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _> *
              *)(unaff_EBP + -0x1c),
        true,
        0);
    *(undefined4 *)(*(int *)(unaff_EBP + -0x1c) + 4)    = *(undefined4 *)(unaff_EBP + -0x14);
    *(undefined4 *)(*(int *)(unaff_EBP + -0x1c) + 0x18) = *(undefined4 *)(unaff_EBP + -0x18);
    std::basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _>::_Eos(
        *(basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _> *
              *)(unaff_EBP + -0x1c),
        *(uint *)(unaff_EBP + 0xc));
    ExceptionList = *(void **)(unaff_EBP + -0xc);
    return;
}
