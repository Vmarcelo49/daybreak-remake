// ============================================
// Address:  0x00420b30
// Original: FUN_00420b30
// Status:   unreviewed
// ============================================

void __fastcall FUN_00420b30(int param_1)

{
    undefined4 *puVar1;
    undefined4 uVar2;
    int iVar3;
    allocator<char> *paVar4;
    undefined4 *puVar5;
    undefined1 local_ec[64];
    int local_ac;
    int local_a8;
    allocator<char> local_a4[64];
    float local_64;
    float local_60;
    float local_5c;
    allocator<char> local_54[16];
    allocator<char> local_44[64];

    std::allocator<char>::allocator<char>(local_44);
    if (*(char *)(param_1 + 0xaecc) == '\0')
    {
        if (*(float *)(param_1 + 0x2c) == 0.0)
        {
            puVar1 = (undefined4 *)D3DXMatrixRotationY(
                local_44,
                ((*(float *)(param_1 + 0x5c) + 90.0 + *(float *)(param_1 + 100) +
                  *(float *)(param_1 + 0x30)) *
                 -3.1415927) /
                    180.0);
            puVar5 = (undefined4 *)(*(int *)(param_1 + 0x11c) + 0x5c);
            for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
            {
                *puVar5 = *puVar1;
                puVar1  = puVar1 + 1;
                puVar5  = puVar5 + 1;
            }
            uVar2 = D3DXMatrixTranslation(local_44,
                                          *(undefined4 *)(param_1 + 0x14),
                                          *(undefined4 *)(param_1 + 0x18),
                                          *(undefined4 *)(param_1 + 0x1c));
            FUN_00423780(uVar2);
        }
        else
        {
            puVar1 =
                (undefined4 *)D3DXMatrixTranslation(local_44, 0, -*(float *)(param_1 + 0x2d8), 0);
            puVar5 = (undefined4 *)(*(int *)(param_1 + 0x11c) + 0x5c);
            for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
            {
                *puVar5 = *puVar1;
                puVar1  = puVar1 + 1;
                puVar5  = puVar5 + 1;
            }
            uVar2 = D3DXMatrixRotationX(local_44, (*(float *)(param_1 + 0x2c) * 3.1415927) / 180.0);
            FUN_00423780(uVar2);
            uVar2 = D3DXMatrixRotationY(local_44,
                                        ((*(float *)(param_1 + 0x5c) + 90.0 +
                                          *(float *)(param_1 + 100) + *(float *)(param_1 + 0x30)) *
                                         -3.1415927) /
                                            180.0);
            FUN_00423780(uVar2);
            uVar2 = D3DXMatrixTranslation(local_44,
                                          *(undefined4 *)(param_1 + 0x14),
                                          *(float *)(param_1 + 0x18) + *(float *)(param_1 + 0x2d8),
                                          *(undefined4 *)(param_1 + 0x1c));
            FUN_00423780(uVar2);
        }
    }
    else if (*(char *)(*(int *)(param_1 + 0xaed0) + 0xaed8) == '\x01')
    {
        std::allocator<char>::allocator<char>(local_a4);
        std::allocator<char>::allocator<char>((allocator<char> *)&local_64);
        std::allocator<char>::allocator<char>(local_54);
        D3DXMatrixInverse(local_a4, 0, *(int *)(param_1 + 0x11c) + 0x5c);
        puVar1 = (undefined4 *)FUN_00423850(local_ec, local_a4);
        paVar4 = local_a4;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *(undefined4 *)paVar4 = *puVar1;
            puVar1                = puVar1 + 1;
            paVar4                = paVar4 + 4;
        }
        paVar4 = local_a4;
        uVar2  = FUN_00423750(0, 0, 0);
        D3DXVec3Transform(&local_64, uVar2, paVar4);
        FUN_00423890(*(int *)(param_1 + 0x11c) + 0x5c);
        D3DXMatrixTranslation(*(int *)(param_1 + 0x11c) + 0x5c, -local_64, -local_60, -local_5c);
        FUN_00423780(*(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0xaed4));
    }
    else
    {
        puVar1 = *(undefined4 **)(*(int *)(param_1 + 0xaed0) + 0xaed4);
        puVar5 = (undefined4 *)(*(int *)(param_1 + 0x11c) + 0x5c);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *puVar5 = *puVar1;
            puVar1  = puVar1 + 1;
            puVar5  = puVar5 + 1;
        }
    }
    D3DXMatrixRotationY(param_1 + 0x338, (*(float *)(param_1 + 0x68) * 3.1415927) / 180.0);
    for (local_a8 = 0; local_a8 < 2; local_a8 = local_a8 + 1)
    {
        for (local_ac = 0; local_ac < 0x100; local_ac = local_ac + 1)
        {
            if (*(float *)(param_1 + local_ac * 0x38 + 0x75ec + local_a8 * 4) <= 0.0)
            {
                FUN_0064eb00(local_a8, local_ac, 0);
                FUN_0064eb80(local_a8, local_ac, 0);
            }
            else
            {
                FUN_0064eb00(local_a8, local_ac, 1);
                FUN_0064eb80(local_a8,
                             local_ac,
                             *(undefined4 *)(param_1 + local_ac * 0x38 + 0x75ec + local_a8 * 4));
                FUN_0064ebc0(local_a8,
                             local_ac,
                             *(undefined4 *)(param_1 + local_ac * 0x38 + 0x75e4 + local_a8 * 4));
            }
        }
    }
    FUN_0064e580(0);
    return;
}
