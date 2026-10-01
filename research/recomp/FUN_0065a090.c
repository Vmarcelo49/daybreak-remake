// ============================================
// Address:  0x0065a090
// Original: FUN_0065a090
// Status:   unreviewed
// ============================================

void __thiscall FUN_0065a090(int param_1, undefined4 param_2)

{
    undefined4 local_8;

    *(undefined4 *)(param_1 + 1000) = param_2;
    for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1)
    {
        FUN_0065a390((*(int *)(param_1 + 1000) * *(int *)(param_1 + 0x3ec)) / 10000 + -10000);
        FUN_0065a390((*(int *)(param_1 + 1000) * *(int *)(param_1 + 0x3ec)) / 10000 + -10000);
    }
    return;
}
