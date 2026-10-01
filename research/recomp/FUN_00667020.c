// ============================================
// Address:  0x00667020
// Original: FUN_00667020
// Status:   unreviewed
// ============================================

void __thiscall FUN_00667020(int param_1, undefined4 param_2)

{
    *(undefined4 *)(param_1 + 0x28) = param_2;
    if (*(int *)(param_1 + 0x28) < 0)
    {
        *(undefined4 *)(param_1 + 0x28) = 0;
    }
    return;
}
