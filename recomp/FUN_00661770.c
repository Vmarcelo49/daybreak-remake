// ============================================
// Address:  0x00661770
// Original: FUN_00661770
// Status:   unreviewed
// ============================================

void __fastcall FUN_00661770(int param_1)

{
    undefined4 uVar1;
    float10 fVar2;
    float fVar3;
    allocator<char> local_74[68];
    undefined4 local_30;
    undefined4 local_2c;
    float local_28;
    undefined1 local_24[12];
    float local_18;
    float local_14;
    allocator<char> local_10[4];
    float local_c;

    D3DXMatrixLookAtLH(param_1, param_1 + 0x80, param_1 + 0x8c, param_1 + 0x98);
    FUN_0042dfd0(&local_30, param_1 + 0x80);
    std::allocator<char>::allocator<char>(local_10);
    FUN_00423750(0x3f800000, 0, 0);
    D3DXVec3Normalize(&local_30, &local_30);
    fVar2    = (float10)FUN_004365f0(local_2c);
    local_14 = (float)fVar2;
    local_2c = 0;
    D3DXVec3Normalize(&local_30, &local_30);
    FUN_0042e020(local_10, local_24, &local_30);
    fVar2    = (float10)FUN_0042e0e0(&local_30, local_24);
    fVar2    = (float10)FUN_00661a40((float)fVar2);
    local_18 = (float)fVar2;
    if (local_c < 0.0)
    {
        local_18 = -local_18;
    }
    std::allocator<char>::allocator<char>(local_74);
    D3DXMatrixRotationY(param_1 + 0x40, local_18);
    fVar3 = local_14;
    uVar1 = FUN_00423750(-local_28, 0, local_30);
    uVar1 = D3DXMatrixRotationAxis(local_74, uVar1, fVar3);
    FUN_00423780(uVar1);
    return;
}
