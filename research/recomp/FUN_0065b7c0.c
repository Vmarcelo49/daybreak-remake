// ============================================
// Address:  0x0065b7c0
// Original: FUN_0065b7c0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_0065b7c0(int param_1, undefined4 param_2)

{
    undefined4 *puVar1;
    undefined1 local_8[4];

    FUN_0065d670();
    puVar1                          = (undefined4 *)FUN_006532f0(local_8, param_2);
    *(undefined4 *)(param_1 + 0x18) = *puVar1;
    FUN_006940b0(*(undefined4 *)(param_1 + 0x18));
    FUN_0065d6a0();
    return 1;
}
