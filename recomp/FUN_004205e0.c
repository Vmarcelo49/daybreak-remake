// ============================================
// Address:  0x004205e0
// Original: FUN_004205e0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004205e0(int param_1)

{
    int iVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    int local_10;
    undefined4 local_c;
    int local_8;

    local_8 = *(int *)(param_1 + 0x7d4);
    if ((local_8 < 0) || (6 < local_8))
    {
        if (*(char *)(param_1 + 0x844) == '\0')
        {
            if (*(char *)(param_1 + 0x846) == '\0')
            {
                if (*(char *)(param_1 + 0x845) == '\0')
                {
                    return;
                }
                local_8 = 1;
            }
            else
            {
                local_8 = 5;
            }
        }
        else
        {
            local_8 = 0;
        }
    }
    (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8, 0x1c, &local_c);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, 0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 2);
    FUN_0064ebc0(0, 0, (float)*(int *)(*(int *)(param_1 + 0x23c) + 0x1c) * 0.016);
    for (local_10 = 0; local_10 < 0xb; local_10 = local_10 + 1)
    {
        puVar2 = (undefined4 *)(param_1 + 0x38c + local_10 * 0x40);
        puVar3 = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x23c) + 0x4498 + local_8 * 4) + 0x5c);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1)
        {
            *puVar3 = *puVar2;
            puVar2  = puVar2 + 1;
            puVar3  = puVar3 + 1;
        }
        FUN_0064e580(0);
        FUN_0064e1a0();
    }
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 6);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, local_c);
    return;
}
