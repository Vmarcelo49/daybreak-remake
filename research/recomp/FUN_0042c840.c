// ============================================
// Address:  0x0042c840
// Original: FUN_0042c840
// Status:   unreviewed
// ============================================

void __thiscall FUN_0042c840(int param_1, undefined4 param_2)

{
    undefined4 local_8;

    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        *(undefined4 *)(param_1 + 0x90 + local_8 * 4) = param_2;
    }
    return;
}
