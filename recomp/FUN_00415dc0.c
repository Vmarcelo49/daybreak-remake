// ============================================
// Address:  0x00415dc0
// Original: FUN_00415dc0
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_00415dc0(undefined4 *param_1)

{
    FUN_00415e50();
    *param_1 = &PTR_LAB_006a1e70;
    FUN_0065d610();
    param_1[0x59] = 0;
    _memset(param_1 + 0x48, 0, 0x20);
    _memset(param_1 + 0x50, 0, 0x20);
    return param_1;
}
