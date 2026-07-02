// ============================================
// Address:  0x0064aed0
// Original: FUN_0064aed0
// Suggested: ReleaseObject (confidence: medium)
// Status:   suggested — name kept as comment until reviewed
// TODO(decomp): agent:local: hub de 18 callers. Nome baseado no padrão dtor+notify+clear-slot, mas
// o tipo de objeto é desconhecido — pode ser 'ReleaseSceneObject', 'DestroyEntity', etc. Só će fica
// claro depois que os callers forem nomeados. NOTE: agent:local suggested 'ReleaseObject' (dtor
// vtable + notify + clear slot, 18 callers). agent:extraction suggested 'SetSceneState'. Agent
// local considera 'SetSceneState' plausível se o objeto for scene-state, mas o padrão observado
// (FUN_0041d090 ctor-call + FUN_0064ade0 clear slot <0x20) sugere lifecycle de objeto, não state
// set. Operador decide.
// ============================================

void __thiscall FUN_0064aed0(undefined4 param_1, undefined4 param_2)

{
    undefined1 local_10[8];
    undefined2 local_8;

    if (DAT_006cfdb0 == '\x01')
    {
        FUN_0041d090(param_1);
        local_8 = (undefined2)param_2;
        FUN_00415d30(0, local_10, 0x10, 2);
    }
    FUN_0064ade0(param_2);
    return;
}
