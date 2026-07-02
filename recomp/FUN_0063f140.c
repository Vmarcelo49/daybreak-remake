// ============================================
// Address:  0x0063f140
// Original: FUN_0063f140
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_0063f140(int param_1, undefined1 *param_2)

{
    undefined2 uVar1;

    *param_2                     = 9;
    *(undefined2 *)(param_2 + 1) = *(undefined2 *)(param_1 + 8);
    uVar1                        = FUN_0066b668();
    *(undefined2 *)(param_2 + 3) = uVar1;
    uVar1                        = FUN_0066b668();
    *(undefined2 *)(param_2 + 5) = uVar1;
    uVar1                        = FUN_0066b668();
    *(undefined2 *)(param_2 + 7) = uVar1;
    param_2[9]                   = *(undefined1 *)(param_1 + 0x18);
    return 10;
}
