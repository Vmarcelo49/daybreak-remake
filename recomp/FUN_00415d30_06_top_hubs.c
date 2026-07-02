// ============================================
// Address:  0x00415d30
// Original: FUN_00415d30
// Suggested: InvokeVtableFirstMethod (confidence: low)
// Status:   suggested — name kept as comment until reviewed
// TODO(decomp): agent:local: adapter de chamada virtual genérica. Nome descritivo da mecânica, não
// do propósito — difícil refinar sem saber quem é o callee concreto.
// ============================================

void __thiscall FUN_00415d30(undefined4 param_1,
                             undefined4 param_2,
                             undefined4 *param_3,
                             undefined4 param_4,
                             undefined4 param_5)

{
    undefined4 uVar1;

    uVar1 = (**(code **)*param_3)(param_1);
    FUN_00660400(param_2, param_1, uVar1, param_4, param_5);
    return;
}
