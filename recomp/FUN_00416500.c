// ============================================
// Address:  0x00416500
// Original: FUN_00416500
// Status:   unreviewed
// ============================================

void __thiscall FUN_00416500(int param_1, int param_2)

{
    *(undefined1 *)(param_1 + 8) = *(undefined1 *)(param_2 + 1);
    *(undefined1 *)(param_1 + 9) = *(undefined1 *)(param_2 + 2);
    _memcpy((void *)(param_1 + 10), (void *)(param_2 + 3), 0x50);
    return;
}
