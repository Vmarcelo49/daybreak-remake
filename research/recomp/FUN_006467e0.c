// ============================================
// Address:  0x006467e0
// Original: FUN_006467e0
// Status:   unreviewed
// ============================================

void __thiscall FUN_006467e0(int param_1, int param_2, float param_3, float param_4)

{
    if (*(int *)(param_1 + 0xdd4 + param_2 * 4) != 0)
    {
        FUN_00655d60(param_3, param_4);
        FUN_00646cf0(param_2, param_3 + 24.0, param_4 + 24.0);
        FUN_00655d60(param_3 + 24.0, param_4 + 48.0);
    }
    return;
}
