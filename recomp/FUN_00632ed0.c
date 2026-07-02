// ============================================
// Address:  0x00632ed0
// Original: FUN_00632ed0
// Status:   unreviewed
// ============================================

void __thiscall FUN_00632ed0(int param_1, float *param_2, char param_3)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    float10 fVar3;
    undefined1 local_60[12];
    undefined1 local_54[36];
    float local_30;
    float local_2c;
    undefined1 local_28[12];
    undefined1 local_1c[12];
    allocator<char> local_10[4];
    float local_c;

    FUN_00423750(*(float *)(param_1 + 0x3c) - *param_2, 0, *(float *)(param_1 + 0x44) - param_2[2]);
    FUN_00423750(*param_2 - *(float *)(param_1 + 0x24), 0, param_2[2] - *(float *)(param_1 + 0x2c));
    std::allocator<char>::allocator<char>(local_10);
    D3DXVec3Normalize(local_28, local_28);
    fVar3    = (float10)FUN_0042df50(local_1c);
    local_2c = (float)fVar3;
    if (40.0 <= local_2c)
    {
        *(float *)(param_1 + 0xc)  = *param_2;
        *(float *)(param_1 + 0x10) = param_2[1];
        *(float *)(param_1 + 0x14) = param_2[2];
    }
    else
    {
        fVar3    = (float10)FUN_0042de80(1600.0 - local_2c * local_2c);
        local_30 = (float)fVar3;
        FUN_0042e020(local_10, local_1c, local_28);
        fVar3 = (float10)FUN_0042e0e0(local_1c, local_28);
        if (fVar3 < (float10)0.0)
        {
            FUN_0042df10(0xbf800000);
        }
        if (local_c <= 0.0)
        {
            uVar1 = FUN_00423750(param_2[2] - *(float *)(param_1 + 0x2c),
                                 0,
                                 -(*param_2 - *(float *)(param_1 + 0x24)));
            D3DXVec3Normalize(local_28, uVar1);
        }
        else
        {
            uVar1 = FUN_00423750(-(param_2[2] - *(float *)(param_1 + 0x2c)),
                                 0,
                                 *param_2 - *(float *)(param_1 + 0x24));
            D3DXVec3Normalize(local_28, uVar1);
        }
        uVar1                           = FUN_004241d0(local_54, local_30);
        puVar2                          = (undefined4 *)FUN_00424180(local_60, uVar1);
        *(undefined4 *)(param_1 + 0xc)  = *puVar2;
        *(undefined4 *)(param_1 + 0x10) = puVar2[1];
        *(undefined4 *)(param_1 + 0x14) = puVar2[2];
    }
    *(float *)(param_1 + 0x24) = *param_2;
    *(float *)(param_1 + 0x28) = param_2[1];
    *(float *)(param_1 + 0x2c) = param_2[2];
    if ((param_3 != '\0') || (*(char *)(param_1 + 0x94) != '\0'))
    {
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0xc);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x14);
    }
    return;
}
