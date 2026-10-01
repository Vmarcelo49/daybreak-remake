// ============================================
// Address:  0x0063c1e0
// Original: FUN_0063c1e0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0063c1e0(int param_1)

{
    char cVar1;
    uint local_c;

    cVar1 = Empty();
    if (cVar1 == '\0')
    {
        local_c = *(int *)(param_1 + 0x10) + -1 + *(int *)(param_1 + 0xc);
        if (*(uint *)(param_1 + 8) <= local_c)
        {
            local_c = local_c - *(int *)(param_1 + 8);
        }
        std::allocator<std::_Container_proxy>::destroy(
            (allocator<std::_Container_proxy> *)(param_1 + 1),
            *(_Container_proxy **)(*(int *)(param_1 + 4) + local_c * 4));
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
        if (*(int *)(param_1 + 0x10) == 0)
        {
            *(undefined4 *)(param_1 + 0xc) = 0;
        }
    }
    return;
}
