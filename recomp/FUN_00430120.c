// ============================================
// Address:  0x00430120
// Original: FUN_00430120
// Status:   unreviewed
// ============================================

void __fastcall FUN_00430120(int param_1)

{
    undefined4 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 *puVar4;
    int iVar5;
    undefined4 *puVar6;
    undefined1 *puVar7;
    undefined1 *puVar8;
    undefined1 *puVar9;
    undefined1 local_90[16];
    undefined1 local_80[16];
    undefined1 local_70[16];
    undefined1 local_60[16];
    undefined1 local_50[16];
    undefined1 local_40[16];
    undefined1 local_30[16];
    float local_20;
    int local_1c;
    int local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    puVar6 = (undefined4 *)(param_1 + 0x48);
    puVar4 = (undefined4 *)(*(int *)(param_1 + 0x40) + 0x5c);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1)
    {
        *puVar4 = *puVar6;
        puVar6  = puVar6 + 1;
        puVar4  = puVar4 + 1;
    }
    FUN_0064e580(*(undefined4 *)(param_1 + 4));
    D3DXVec4Transform(param_1 + 0x88, param_1 + 0x18, param_1 + 0x48);
    D3DXVec4Transform(param_1 + 0x98, param_1 + 0x28, param_1 + 0x48);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x8c);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x90);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x94);
    for (local_18 = 0; local_18 < 9; local_18 = local_18 + 1)
    {
        for (local_1c = 0; local_1c < 5; local_1c = local_1c + 1)
        {
            local_20 = (float)local_1c / 5.0;
            if (local_18 == 0)
            {
                FUN_0065d2f0(local_20, &local_14);
            }
            else if (local_18 == 1)
            {
                FUN_0065d380(local_20, &local_14);
            }
            else if (local_18 == 7)
            {
                FUN_0065d4d0(local_20, &local_14);
            }
            else if (local_18 == 8)
            {
                FUN_0065d580(local_20, &local_14);
            }
            else
            {
                FUN_0065d430(local_20, &local_14);
            }
            uVar1  = FUN_00430790(local_80, local_8);
            puVar9 = local_90;
            uVar2  = FUN_00430790(local_60, local_c);
            puVar8 = local_70;
            uVar3  = FUN_00430790(local_40, local_10);
            puVar7 = local_50;
            FUN_00430790(local_30, local_14);
            FUN_004306f0(puVar7, uVar3);
            FUN_004306f0(puVar8, uVar2);
            puVar4    = (undefined4 *)FUN_004306f0(puVar9, uVar1);
            puVar6    = (undefined4 *)(param_1 + 0x158 + (local_18 * 5 + 1 + local_1c) * 0x10);
            *puVar6   = *puVar4;
            puVar6[1] = puVar4[1];
            puVar6[2] = puVar4[2];
            puVar6[3] = puVar4[3];
        }
    }
    return;
}
