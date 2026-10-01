// ============================================
// Address:  0x00435450
// Original: FUN_00435450
// Status:   unreviewed
// ============================================

void __thiscall FUN_00435450(int param_1,
                             int param_2,
                             undefined4 param_3,
                             undefined4 param_4,
                             undefined4 param_5,
                             undefined4 param_6,
                             undefined4 param_7)

{
    char cVar1;
    float10 fVar2;
    float fVar3;
    float fVar4;
    undefined1 local_18[12];
    float local_c;
    float local_8;

    fVar2   = (float10)FUN_0065d010(param_7);
    local_c = (float)fVar2;
    fVar2   = (float10)FUN_0065d050(param_7);
    local_8 = (float)fVar2;
    fVar2   = (float10)FUN_0065d010(param_6);
    fVar4   = (float)(fVar2 * (float10)local_8);
    fVar3   = local_c;
    fVar2   = (float10)FUN_0065d050(param_6, local_c, fVar4);
    FUN_00423750((float)(fVar2 * (float10)local_8), fVar3, fVar4);
    if (*(int *)(*(int *)(param_1 + 0xf4) + 8 + param_2 * 0xc) < 0)
    {
        (**(code **)(*(int *)(param_1 + 0xac) + 0xc))(
            param_2,
            param_3,
            param_4,
            param_5,
            local_18,
            *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
    }
    else
    {
        cVar1 = FUN_00435920();
        if (cVar1 != '\0')
        {
            (**(code **)(*(int *)(param_1 + 0xac) + 0xc))(
                param_2,
                param_3,
                param_4,
                param_5,
                local_18,
                *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
        }
    }
    return;
}
