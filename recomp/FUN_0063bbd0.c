// ============================================
// Address:  0x0063bbd0
// Original: FUN_0063bbd0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_0063bbd0(int param_1, undefined1 *param_2)

{
    undefined2 uVar1;

    *param_2                        = 0x35;
    param_2[1]                      = *(undefined1 *)(param_1 + 8);
    *(undefined2 *)(param_2 + 2)    = *(undefined2 *)(param_1 + 10);
    *(undefined2 *)(param_2 + 4)    = *(undefined2 *)(param_1 + 0xc);
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 6)    = uVar1;
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 8)    = uVar1;
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 10)   = uVar1;
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 0xc)  = uVar1;
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 0xe)  = uVar1;
    uVar1                           = FUN_0066b668();
    *(undefined2 *)(param_2 + 0x10) = uVar1;
    return 0x12;
}
