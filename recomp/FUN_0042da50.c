// ============================================
// Address:  0x0042da50
// Original: FUN_0042da50
// Status:   unreviewed
// ============================================

float10 __thiscall FUN_0042da50(int param_1, undefined4 param_2)

{
    int iVar1;

    iVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 4))(param_2);
    return (float10) * (float *)(iVar1 + 4) - (float10) * (float *)(param_1 + 0x18);
}
