// ============================================
// Address:  0x0068a3d0
// Original: FUN_0068a3d0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068a3d0(int param_1)

{
    undefined4 uVar1;

    if (*(int *)(param_1 + 0x18) == 0)
    {
        uVar1 = 0x80040209;
    }
    else
    {
        uVar1 = (**(code **)(**(int **)(param_1 + 0x18) + 0x3c))(*(undefined4 *)(param_1 + 0x18));
    }
    return uVar1;
}
