// ============================================
// Address:  0x00660900
// Original: FUN_00660900
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_00660900(undefined4 *param_1)

{
    *param_1       = 0;
    param_1[1]     = 0;
    param_1[0x282] = 0x3ff;
    _memset(param_1 + 2, 0, 0x400);
    _memset(param_1 + 0x202, 0, 0x100);
    *(undefined1 *)(param_1 + 0x283)      = 0;
    *(undefined1 *)((int)param_1 + 0xa0d) = 0;
    *(undefined1 *)((int)param_1 + 0xa0e) = 0;
    *(undefined1 *)((int)param_1 + 0xa0f) = 0;
    return param_1;
}
