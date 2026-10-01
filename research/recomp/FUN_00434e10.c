// ============================================
// Address:  0x00434e10
// Original: FUN_00434e10
// Status:   unreviewed
// ============================================

void __thiscall FUN_00434e10(int param_1, int param_2, int param_3)

{
    char cVar1;
    undefined4 uVar2;
    float10 fVar3;
    float fVar4;
    float fVar5;
    undefined4 uVar6;
    undefined1 local_28[12];
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    float local_c;
    float local_8;

    fVar3   = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x100));
    local_c = (float)fVar3;
    fVar3   = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x100));
    local_8 = (float)fVar3;
    fVar3   = (float10)FUN_0065d010(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                    *(float *)(*(int *)(param_1 + 0x20) + 100));
    fVar5   = (float)(fVar3 * (float10)local_8);
    fVar4   = local_c;
    fVar3   = (float10)FUN_0065d050(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                        *(float *)(*(int *)(param_1 + 0x20) + 100),
                                    local_c,
                                    fVar5);
    FUN_00423750((float)(fVar3 * (float10)local_8), fVar4, fVar5);
    std::allocator<char>::allocator<char>((allocator<char> *)&local_1c);
    if (*(int *)(param_1 + 0x10 + param_2 * 4) != 0)
    {
        if (*(int *)(param_1 + 0x18 + param_2 * 4) < 0)
        {
            uVar6 = *(undefined4 *)(param_1 + 0x10 + param_2 * 4);
            uVar2 = FUN_00423750(0, 0, 0);
            D3DXVec3Transform(&local_1c, uVar2, uVar6);
        }
        else
        {
            D3DXVec3Transform(&local_1c,
                              *(int *)(param_1 + 0x18 + param_2 * 4) * 0xc + *(int *)(param_1 + 8),
                              *(undefined4 *)(param_1 + 0x10 + param_2 * 4));
        }
    }
    if (*(int *)(*(int *)(param_1 + 0xf4) + 8 + param_3 * 0xc) < 0)
    {
        (**(code **)(*(int *)(param_1 + 0xac) + 0xc))(
            param_3,
            local_1c,
            local_18,
            local_14,
            local_28,
            *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
    }
    else
    {
        cVar1 = FUN_00435920();
        if (cVar1 != '\0')
        {
            (**(code **)(*(int *)(param_1 + 0xac) + 0xc))(
                param_3,
                local_1c,
                local_18,
                local_14,
                local_28,
                *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
        }
    }
    return;
}
