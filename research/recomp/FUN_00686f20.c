// ============================================
// Address:  0x00686f20
// Original: FUN_00686f20
// Status:   unreviewed
// ============================================

undefined4 FUN_00686f20(undefined4 *param_1, undefined4 *param_2)

{
    LPVOID pvVar1;
    int iVar2;
    undefined4 *puVar3;
    undefined4 *puVar4;

    puVar3 = param_2;
    puVar4 = param_1;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
    {
        *puVar4 = *puVar3;
        puVar3  = puVar3 + 1;
        puVar4  = puVar4 + 1;
    }
    if (param_2[0x10] != 0)
    {
        pvVar1        = CoTaskMemAlloc(param_2[0x10]);
        param_1[0x11] = pvVar1;
        if (param_1[0x11] == 0)
        {
            param_1[0x10] = 0;
            return 0x8007000e;
        }
        _memcpy((void *)param_1[0x11], (void *)param_2[0x11], param_1[0x10]);
    }
    if (param_1[0xf] != 0)
    {
        (**(code **)(*(int *)param_1[0xf] + 4))(param_1[0xf]);
    }
    return 0;
}
