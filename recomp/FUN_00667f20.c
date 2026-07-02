// ============================================
// Address:  0x00667f20
// Original: FUN_00667f20
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00667f20(int param_1)

{
    undefined4 uVar1;

    if (*(int *)(param_1 + 4) == 0)
    {
        uVar1 = 0;
    }
    else
    {
        uVar1 = (**(code **)(**(int **)(param_1 + 4) + 0x48))(*(undefined4 *)(param_1 + 4));
    }
    return uVar1;
}
