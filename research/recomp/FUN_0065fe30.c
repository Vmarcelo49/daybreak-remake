// ============================================
// Address:  0x0065fe30
// Original: FUN_0065fe30
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0065fe30(undefined4 *param_1)

{
    FUN_0065d610();
    *param_1      = 0;
    param_1[1]    = 0;
    param_1[0x19] = 0;
    param_1[0x1b] = 0;
    param_1[0x1c] = 0;
    _memset(param_1 + 10, 0, 0x20);
    return param_1;
}
