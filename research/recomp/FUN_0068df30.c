// ============================================
// Address:  0x0068df30
// Original: FUN_0068df30
// Status:   unreviewed
// ============================================

allocator<char> *__thiscall
FUN_0068df30(allocator<char> *param_1, undefined4 param_2, allocator<char> *param_3)

{
    allocator<char> *local_c;

    std::allocator<char>::allocator<char>(param_1);
    FUN_0068de50(param_2);
    local_c = param_1;
    if (param_3 != (allocator<char> *)0x0)
    {
        local_c = param_3;
    }
    *(allocator<char> **)(param_1 + 4) = local_c;
    *(undefined4 *)(param_1 + 8)       = 0;
    return param_1;
}
