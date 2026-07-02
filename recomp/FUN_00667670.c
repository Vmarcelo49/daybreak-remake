// ============================================
// Address:  0x00667670
// Original: FUN_00667670
// Status:   unreviewed
// ============================================

void __fastcall FUN_00667670(int param_1)

{
    if (*(int *)(param_1 + 0xc) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0xc) + 8))(*(undefined4 *)(param_1 + 0xc));
        *(undefined4 *)(param_1 + 0xc) = 0;
    }
    if (*(int *)(param_1 + 4) != 0)
    {
        (**(code **)(**(int **)(param_1 + 4) + 8))(*(undefined4 *)(param_1 + 4));
        *(undefined4 *)(param_1 + 4) = 0;
    }
    return;
}
