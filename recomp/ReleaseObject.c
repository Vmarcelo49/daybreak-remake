// ============================================
// Address:  0x0064aed0
// Original: FUN_0064aed0
// Name:     ReleaseObject (status: reviewed)
// TODO(decomp): agent:local: hub de 18 callers. Nome baseado no padrão dtor+notify+clear-slot, mas
// o tipo de objeto é desconhecido — pode ser 'ReleaseSceneObject', 'DestroyEntity', etc. Só će fica
// claro depois que os callers forem nomeados.
// ============================================

void __thiscall ReleaseObject(undefined4 param_1, undefined4 param_2)

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
