// ============================================
// Address:  0x00667ed0
// Original: FUN_00667ed0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00667ed0(int param_1, undefined4 param_2)

{
    undefined4 uVar1;

    if (*(int *)(param_1 + 4) == 0)
    {
        uVar1 = 0;
    }
    else
    {
        (**(code **)(**(int **)(param_1 + 4) + 0x34))(*(undefined4 *)(param_1 + 4), 0);
        uVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x30))(
            *(undefined4 *)(param_1 + 4), 0, 0, param_2);
    }
    return uVar1;
}
