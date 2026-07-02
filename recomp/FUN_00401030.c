// ============================================
// Address:  0x00401030
// Original: FUN_00401030
// Status:   unreviewed
// ============================================

int __fastcall FUN_00401030(int param_1)

{
    int local_8;

    _vector_constructor_iterator_(
        (void *)(param_1 + 0x44), 0xc, 4, std::allocator<char>::allocator<char>);
    _vector_constructor_iterator_(
        (void *)(param_1 + 0x74), 0xc, 6, std::allocator<char>::allocator<char>);
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        *(undefined4 *)(param_1 + local_8 * 4) = 0;
    }
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    return param_1;
}
