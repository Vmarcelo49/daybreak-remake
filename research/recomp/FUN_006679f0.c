// ============================================
// Address:  0x006679f0
// Original: FUN_006679f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006679f0(int param_1)

{
    if (*(int *)(param_1 + 4) != 0)
    {
        (**(code **)(**(int **)(param_1 + 4) + 8))(*(undefined4 *)(param_1 + 4));
        *(undefined4 *)(param_1 + 4) = 0;
    }
    return;
}
