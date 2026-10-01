// ============================================
// Address:  0x0063a130
// Original: FUN_0063a130
// Status:   unreviewed
// ============================================

void __thiscall FUN_0063a130(int param_1, int param_2, float param_3, float param_4)

{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    tagRECT local_40;
    tagRECT local_30;
    tagRECT local_20;
    int local_10;
    char local_9;
    float local_8;

    if ((*(char *)(param_1 + 0x4430) == '\0') || (*(char *)(param_1 + 0x4431) == '\0'))
    {
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 7, 0);
        (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 5, 1);
        (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 6, 1);
        local_9 = '\0';
        if ((*(int *)(param_1 + 0x4a3c) != 4) && (*(int *)(param_1 + 0x4a3c) != 5))
        {
            if (*(int *)(param_1 + 0x4a3c) == 3)
            {
                param_3 = 0.0;
                param_4 = 0.0;
                local_8 = 1.0;
            }
            else
            {
                if (DAT_006cfba0 == 1)
                {
                    local_8 = 1.0;
                }
                else
                {
                    local_8 = 0.5;
                }
                local_9 = '\x01';
            }
            for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
            {
                if (*(int *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x828) != 0)
                {
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x13, 10);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 1);
                    iVar1 = FUN_0066b668();
                    iVar2 = FUN_0066b668();
                    iVar3 = FUN_0066b668();
                    iVar4 = FUN_0066b668();
                    SetRect(&local_20, iVar4, iVar3, iVar2, iVar1);
                    FUN_00651820(&local_20, 0xffffffff);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x13, 5);
                    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 6);
                    break;
                }
            }
            if (local_9 != '\0')
            {
                if (*(char *)(param_1 + 0x454c + param_2 * 0x160) == '\0')
                {
                    FUN_00643230(param_3, param_4, local_8);
                }
                FUN_00644150(param_3, param_4, local_8);
            }
            if ((*(char *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x844) != '\0') &&
                (*(char *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x334) != '\0'))
            {
                iVar1 = FUN_0066b668();
                iVar2 = FUN_0066b668();
                iVar3 = FUN_0066b668();
                iVar4 = FUN_0066b668();
                SetRect(&local_30, iVar4, iVar3, iVar2, iVar1);
                FUN_00651820(&local_30,
                             (uint) * (byte *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x334)
                                     << 0x18 |
                                 0xb00000);
            }
            if ((*(char *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x846) != '\0') &&
                (*(char *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x334) != '\0'))
            {
                iVar1 = FUN_0066b668();
                iVar2 = FUN_0066b668();
                iVar3 = FUN_0066b668();
                iVar4 = FUN_0066b668();
                SetRect(&local_40, iVar4, iVar3, iVar2, iVar1);
                FUN_00651820(&local_40,
                             (uint) * (byte *)(*(int *)(param_1 + 0x129c + param_2 * 4) + 0x334)
                                     << 0x18 |
                                 0xffff);
            }
            if (*(int *)(param_1 + 0x43e4 + param_2 * 4) != 0)
            {
                FUN_00408250(local_8 * *(float *)(param_1 + 0x4404 + param_2 * 4));
                FUN_004120f0((*(float *)(param_1 + 0x4404 + param_2 * 4) - 1.0) * 5.0);
                FUN_00655d60(local_8 * 400.0 + param_3, local_8 * 300.0 + param_4);
            }
            if (*(int *)(param_1 + 0x4414) != 0)
            {
                FUN_00408250(local_8 * *(float *)(param_1 + 0x441c));
                FUN_004120f0((*(float *)(param_1 + 0x441c) - 1.0) * 5.0);
                FUN_00655d60(local_8 * 400.0 + param_3, local_8 * 200.0 + param_4);
            }
            if (*(int *)(param_1 + 0x4418) != 0)
            {
                FUN_00408250(local_8 * *(float *)(param_1 + 0x4420));
                FUN_004120f0((*(float *)(param_1 + 0x4420) - 1.0) * 5.0);
                FUN_00655d60(local_8 * 400.0 + param_3, local_8 * 400.0 + param_4);
            }
            (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 7, 1);
            (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 5, 2);
            (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 6, 2);
        }
    }
    return;
}
