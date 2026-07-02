// ============================================
// Address:  0x00426ea0
// Original: FUN_00426ea0
// Status:   unreviewed
// ============================================

undefined4 *__thiscall
FUN_00426ea0(undefined4 *param_1, undefined4 param_2, undefined4 param_3, undefined4 *param_4)

{
    int iVar1;
    undefined4 *puVar2;

    *param_1   = param_2;
    param_1[1] = param_3;
    puVar2     = param_1 + 2;
    for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1)
    {
        *puVar2 = *param_4;
        param_4 = param_4 + 1;
        puVar2  = puVar2 + 1;
    }
    return param_1;
}
