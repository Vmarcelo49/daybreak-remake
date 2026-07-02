// ============================================
// Address:  0x00437ea0
// Original: FUN_00437ea0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00437ea0(int param_1)

{
    char cVar1;

    cVar1 = Empty();
    if (cVar1 == '\0')
    {
        std::allocator<std::_Container_proxy>::destroy(
            (allocator<std::_Container_proxy> *)(param_1 + 1),
            *(_Container_proxy **)(*(int *)(param_1 + 4) + *(int *)(param_1 + 0xc) * 4));
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
        if (*(uint *)(param_1 + 8) <= *(uint *)(param_1 + 0xc))
        {
            *(undefined4 *)(param_1 + 0xc) = 0;
        }
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
        if (*(int *)(param_1 + 0x10) == 0)
        {
            *(undefined4 *)(param_1 + 0xc) = 0;
        }
    }
    return;
}
