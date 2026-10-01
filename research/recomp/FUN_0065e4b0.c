// ============================================
// Address:  0x0065e4b0
// Original: FUN_0065e4b0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0065e4b0(int param_1)

{
    int iVar1;
    wchar_t *pwVar2;

    while (true)
    {
        iVar1 = FUN_0063bf40();
        if (iVar1 == 0)
            break;
        pwVar2 =
            std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>::back(
                (basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>
                     *)(param_1 + 4));
        _free(*(void **)pwVar2);
        FUN_00432fa0();
    }
    return;
}
