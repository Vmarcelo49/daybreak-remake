// ============================================
// Address:  0x00437270
// Original: FUN_00437270
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00437270(undefined4 *param_1, undefined4 *param_2)

{
    undefined4 uVar1;
    undefined4 uVar2;

    uVar1 = *param_1;
    uVar2 = param_1[1];
    iterator__operator__();
    *param_2   = uVar1;
    param_2[1] = uVar2;
    return param_2;
}
