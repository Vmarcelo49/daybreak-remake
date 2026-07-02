// ============================================
// Address:  0x0068abf0
// Original: FUN_0068abf0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068abf0(int param_1)

{
    undefined4 uVar1;

    *(undefined1 *)(param_1 + 0x24) = 0;
    if (*(int *)(param_1 + 0x9c) == 0)
    {
        uVar1 = 0x8004020a;
    }
    else
    {
        *(undefined1 *)(param_1 + 0xa1) = 0;
        uVar1 = (**(code **)(**(int **)(param_1 + 0x9c) + 0x18))(*(undefined4 *)(param_1 + 0x9c));
    }
    return uVar1;
}
