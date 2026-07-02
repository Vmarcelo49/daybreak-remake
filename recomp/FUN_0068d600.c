// ============================================
// Address:  0x0068d600
// Original: FUN_0068d600
// Status:   unreviewed
// ============================================

int FUN_0068d600(int *param_1, int *param_2, int param_3)

{
    undefined4 *puVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    uint local_10;
    uint local_c;
    int local_8;

    if (param_1 == (int *)0x0)
    {
        local_8 = 1;
    }
    else
    {
        puVar1  = (undefined4 *)*param_1;
        local_8 = (**(code **)(*param_2 + 0x1c))(param_2, *puVar1, puVar1[1], puVar1[2], puVar1[3]);
        if (param_3 != 0)
        {
            puVar1  = (undefined4 *)*param_1;
            local_8 = (**(code **)(*param_2 + 0xc))(
                param_2, *puVar1, puVar1[1], puVar1[2], puVar1[3], param_1[1], param_1[2]);
            if (-1 < local_8)
            {
                for (local_c = 0; local_c < (uint)param_1[3]; local_c = local_c + 1)
                {
                    puVar1  = *(undefined4 **)(param_1[4] + 0x14 + local_c * 0x24);
                    puVar2  = (undefined4 *)*param_1;
                    local_8 = (**(code **)(*param_2 + 0x14))(
                        param_2,
                        *puVar2,
                        puVar2[1],
                        puVar2[2],
                        puVar2[3],
                        *(undefined4 *)(param_1[4] + local_c * 0x24),
                        *(undefined4 *)(param_1[4] + 4 + local_c * 0x24),
                        *(undefined4 *)(param_1[4] + 8 + local_c * 0x24),
                        *(undefined4 *)(param_1[4] + 0xc + local_c * 0x24),
                        *(undefined4 *)(param_1[4] + 0x10 + local_c * 0x24),
                        *puVar1,
                        puVar1[1],
                        puVar1[2],
                        puVar1[3],
                        *(undefined4 *)(param_1[4] + 0x18 + local_c * 0x24));
                    if (-1 < local_8)
                    {
                        for (local_10 = 0; local_10 < *(uint *)(param_1[4] + 0x1c + local_c * 0x24);
                             local_10 = local_10 + 1)
                        {
                            puVar1 = *(undefined4 **)(*(int *)(param_1[4] + 0x20 + local_c * 0x24) +
                                                      4 + local_10 * 8);
                            puVar2 = *(undefined4 **)(*(int *)(param_1[4] + 0x20 + local_c * 0x24) +
                                                      local_10 * 8);
                            puVar3 = (undefined4 *)*param_1;
                            local_8 = (**(code **)(*param_2 + 0x18))(
                                param_2,
                                *puVar3,
                                puVar3[1],
                                puVar3[2],
                                puVar3[3],
                                *(undefined4 *)(param_1[4] + local_c * 0x24),
                                *puVar2,
                                puVar2[1],
                                puVar2[2],
                                puVar2[3],
                                *puVar1,
                                puVar1[1],
                                puVar1[2],
                                puVar1[3]);
                            if (local_8 < 0)
                                break;
                        }
                        if (local_8 < 0)
                            break;
                    }
                    if (local_8 < 0)
                        break;
                }
            }
        }
        if (local_8 == -0x7ff8fffe)
        {
            local_8 = 0;
        }
    }
    return local_8;
}
