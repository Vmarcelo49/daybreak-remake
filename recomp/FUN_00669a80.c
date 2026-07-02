// ============================================
// Address:  0x00669a80
// Original: FUN_00669a80
// Status:   unreviewed
// ============================================

void __fastcall FUN_00669a80(undefined4 *param_1)

{
    *param_1 = &PTR_FUN_006ab36c;
    if (param_1[4] != 0)
    {
        _free((void *)param_1[4]);
        param_1[4] = 0;
    }
    return;
}
